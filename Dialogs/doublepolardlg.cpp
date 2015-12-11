#include "doublepolardlg.h"
#include "ui_doublepolardlg.h"
#include "utils.h"
#include "Types/observation.h"
#include <QPair>

namespace Compute
{
double SlopeToHorizontal(double slope, double zenith)
{
	return slope * sin(zenith);
}

void DoublePolar(DpObsCalc &dp)
{
	double dist1 = SlopeToHorizontal(dp.m_obs[0].m_dist, dp.m_obs[0].m_vert);
	double dist2 = SlopeToHorizontal(dp.m_obs[1].m_dist, dp.m_obs[1].m_vert);

	Utils::Polar(dp.m_fy1, dp.m_fx1, dist1, dp.m_obs[0].m_dirc, dp.m_y1, dp.m_x1);
	Utils::Polar(dp.m_fy2, dp.m_fx2, dist2, dp.m_obs[1].m_dirc, dp.m_y2, dp.m_x2);

	if (dp.m_adopt == "1")
	{
		dp.m_ay = dp.m_y1;
		dp.m_ax = dp.m_x1;
	}
	else if (dp.m_adopt == "2")
	{
		dp.m_ay = dp.m_y2;
		dp.m_ax = dp.m_x2;
	}
	else if (dp.m_adopt == "W" && dist1 + dist2 != 0.0) // weighted by dist
	{
		double de = dp.m_y2 - dp.m_y1;
		double dn = dp.m_x2 - dp.m_x1;
		dp.m_ay = dp.m_y1 + de * dist1 / (dist1 + dist2);
		dp.m_ax = dp.m_x1 + dn * dist1 / (dist1 + dist2);
	}
	else // mean
	{
		dp.m_ay = (dp.m_y1 + dp.m_y2) / 2.0;
		dp.m_ax = (dp.m_x1 + dp.m_x2) / 2.0;
	}
}
}

DoublePolarDlg::DoublePolarDlg(QWidget *parent, DpObsCalc &dpObs) :
	QDialog(parent),
	ui(new Ui::DoublePolarDlg),
	m_dpObs(dpObs)
{
	ui->setupUi(this);

	const QString dms = "ddd.mmss";
	ui->dir1Edit->setPlaceholderText(dms);
	ui->ver1Edit->setPlaceholderText(dms);
	ui->dir2Edit->setPlaceholderText(dms);
	ui->ver2Edit->setPlaceholderText(dms);
	ui->oc1Edit->setPlaceholderText(dms);
	ui->oc2Edit->setPlaceholderText(dms);

	QAction *stationAction1 = ui->from1Edit->addAction(QIcon(":/blue-hand-16.png"), QLineEdit::TrailingPosition);
	QAction *stationAction2 = ui->from2Edit->addAction(QIcon(":/blue-hand-16.png"), QLineEdit::TrailingPosition);
	QAction *stationAction3 = ui->setup1Edit->addAction(QIcon(":/blue-hand-16.png"), QLineEdit::TrailingPosition);
	QAction *stationAction4 = ui->setup2Edit->addAction(QIcon(":/blue-hand-16.png"), QLineEdit::TrailingPosition);
	connect(stationAction1, &QAction::triggered, this, &DoublePolarDlg::onStation1Action);
	connect(stationAction2, &QAction::triggered, this, &DoublePolarDlg::onStation2Action);
	connect(stationAction3, &QAction::triggered, this, &DoublePolarDlg::onStation1Action);
	connect(stationAction4, &QAction::triggered, this, &DoublePolarDlg::onStation2Action);

	QAction *targetAction1 = ui->trg1Edit->addAction(QIcon(":/green-hand-16.png"), QLineEdit::TrailingPosition);
	QAction *targetAction2 = ui->trg2Edit->addAction(QIcon(":/green-hand-16.png"), QLineEdit::TrailingPosition);
	connect(targetAction1, &QAction::triggered, this, &DoublePolarDlg::onTarget1Action);
	connect(targetAction2, &QAction::triggered, this, &DoublePolarDlg::onTarget2Action);

	connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

	wireStation(m_dpObs.m_stn[0], ui->from1Edit, ui->setup1Edit, ui->oc1Edit);
	wireStation(m_dpObs.m_stn[1], ui->from2Edit, ui->setup2Edit, ui->oc2Edit);
	wireObservation(m_dpObs.m_obs[0], ui->trg1Edit, ui->dir1Edit, ui->ver1Edit, ui->dis1Edit);
	wireObservation(m_dpObs.m_obs[1], ui->trg2Edit, ui->dir2Edit, ui->ver2Edit, ui->dis2Edit);

	ui->station1Radio->setChecked(m_dpObs.m_adopt == "1");
	ui->station2Radio->setChecked(m_dpObs.m_adopt == "2");
	ui->weightedRadio->setChecked(m_dpObs.m_adopt == "W");
	if (m_dpObs.m_adopt != "1" && m_dpObs.m_adopt != "w" && m_dpObs.m_adopt != "W")
		ui->meanRadio->setChecked(true);

	ui->targetEdit->setText(m_dpObs.m_aname);
	wireResult();
}

DoublePolarDlg::~DoublePolarDlg()
{
	delete ui;
}

void DoublePolarDlg::wireStation(const Occupied &station, QLineEdit *nameEdit, QLineEdit *setupEdit, QLineEdit *corrEdit)
{
	if (!station.m_name.isEmpty())
	{
		nameEdit->setText(station.m_name);
		setupEdit->setText(QString::number(station.m_setup));
		corrEdit->setText(Utils::Rad2Dms(station.m_oc));
	}
}

void DoublePolarDlg::wireObservation(const Observation &obs, QLineEdit *targetEdit, QLineEdit *dircEdit, QLineEdit *vertEdit, QLineEdit *distEdit)
{
	if (!obs.m_target.isEmpty())
	{
		targetEdit->setText(obs.m_target);
		dircEdit->setText(Utils::Rad2Dms(obs.m_dirc));
		vertEdit->setText(Utils::Rad2Dms(obs.m_vert));
		distEdit->setText(QString::number(obs.m_dist, 'f', 3));
	}
}

void DoublePolarDlg::wireResult()
{
	ui->eastingEdit->setText(QString::number(m_dpObs.m_ay, 'f', 3));
	ui->northingEdit->setText(QString::number(m_dpObs.m_ax, 'f', 3));
}

void DoublePolarDlg::on_calculateButton_clicked()
{
	m_dpObs.m_stn[0].m_name = ui->from1Edit->text();
	m_dpObs.m_obs[0].m_target = ui->trg1Edit->text();
	m_dpObs.m_obs[0].m_dirc = Utils::Dms2Rad(ui->dir1Edit->text());
	m_dpObs.m_stn[0].m_oc = Utils::Dms2Rad(ui->oc1Edit->text());
	m_dpObs.m_obs[0].m_vert = Utils::Dms2Rad(ui->ver1Edit->text());
	m_dpObs.m_obs[0].m_dist = ui->dis1Edit->text().toDouble();

	m_dpObs.m_stn[1].m_name = ui->from2Edit->text();
	m_dpObs.m_obs[1].m_target = ui->trg2Edit->text();
	m_dpObs.m_obs[1].m_dirc = Utils::Dms2Rad(ui->dir2Edit->text());
	m_dpObs.m_stn[1].m_oc = Utils::Dms2Rad(ui->oc2Edit->text());
	m_dpObs.m_obs[1].m_vert = Utils::Dms2Rad(ui->ver2Edit->text());
	m_dpObs.m_obs[1].m_dist = ui->dis2Edit->text().toDouble();

	Compute::DoublePolar(m_dpObs);

	wireResult();

	if (m_dpObs.m_aname.isEmpty())
		ui->targetEdit->setText(m_dpObs.m_obs[0].m_target);
	else
		ui->targetEdit->setText(m_dpObs.m_aname);
}

void DoublePolarDlg::onStation1Action()
{
	onStationAction(m_dpObs.m_stn[0], ui->from1Edit, ui->setup1Edit, ui->oc1Edit);
}

void DoublePolarDlg::onStation2Action()
{
	onStationAction(m_dpObs.m_stn[1], ui->from2Edit, ui->setup2Edit, ui->oc2Edit);
}

void DoublePolarDlg::onStationAction(Occupied &station, QLineEdit *nameEdit, QLineEdit *setupEdit, QLineEdit *corrEdit)
{
	auto p1 = qMakePair(station.m_name, nameEdit);
	auto p2 = qMakePair(station.m_setup, setupEdit);
	auto p3 = qMakePair(station.m_oc, corrEdit);

	Utils::LoadStation(this, p1, p2, p3);
}

void DoublePolarDlg::onTarget1Action()
{
	onTargetAction(m_dpObs.m_obs[0], ui->from1Edit, ui->setup1Edit, ui->trg1Edit, ui->dir1Edit, ui->ver1Edit, ui->dis1Edit);
}

void DoublePolarDlg::onTarget2Action()
{
	onTargetAction(m_dpObs.m_obs[1], ui->from2Edit, ui->setup2Edit, ui->trg2Edit, ui->dir2Edit, ui->ver2Edit, ui->dis2Edit);
}

void DoublePolarDlg::onTargetAction(Observation &obs, const QLineEdit *nameEdit, const QLineEdit *setupEdit, QLineEdit *targetEdit, QLineEdit *dircEdit, QLineEdit *vertEdit, QLineEdit *distEdit)
{
	QString from = nameEdit->text();
	int setup = setupEdit->text().toInt();

	if (Utils::LoadObs(this, from, setup, obs))
		wireObservation(obs, targetEdit, dircEdit, vertEdit, distEdit);
}

void DoublePolarDlg::on_radio_toggled(const QString &adopt)
{
	m_dpObs.m_adopt = adopt;
	Compute::DoublePolar(m_dpObs);
	wireResult();
}

void DoublePolarDlg::on_meanRadio_toggled(bool checked)
{
	if (checked)
		on_radio_toggled("M");
}

void DoublePolarDlg::on_station1Radio_toggled(bool checked)
{
	if (checked)
		on_radio_toggled("1");
}

void DoublePolarDlg::on_station2Radio_toggled(bool checked)
{
	if (checked)
		on_radio_toggled("2");
}

void DoublePolarDlg::on_weightedRadio_toggled(bool checked)
{
	if (checked)
		on_radio_toggled("W");
}
