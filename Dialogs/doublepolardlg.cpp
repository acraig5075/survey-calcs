#include "doublepolardlg.h"
#include "ui_doublepolardlg.h"
#include "utils.h"
#include "Types/observation.h"
#include <QPair>

namespace Compute
{
void DoublePolar(DpObsCalc &dpObs)
{
	Utils::Polar(dpObs.m_fy1, dpObs.m_fx1, dpObs.m_obs[0].m_dist, dpObs.m_obs[0].m_dirc, dpObs.m_y1, dpObs.m_x1);
	Utils::Polar(dpObs.m_fy2, dpObs.m_fx2, dpObs.m_obs[1].m_dist, dpObs.m_obs[1].m_dirc, dpObs.m_y2, dpObs.m_x2);
	dpObs.m_ay = (dpObs.m_y1 + dpObs.m_y2) / 2.0;
	dpObs.m_ax = (dpObs.m_x1 + dpObs.m_x2) / 2.0;
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

	ui->previewEdit->setText(m_dpObs.desc());
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
	ui->previewEdit->setText(m_dpObs.desc());
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

	if (Utils::LoadStation(this, p1, p2, p3))
		ui->previewEdit->clear();
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
