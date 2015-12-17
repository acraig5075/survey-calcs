#include "doublepolardlg.h"
#include "ui_doublepolardlg.h"
#include "Types/observation.h"
#include "utils.h"
#include "compute.h"
#include <QPair>


DoublePolarDlg::DoublePolarDlg(QWidget *parent, DpObsCalc &dpObs) :
	QDialog(parent),
	ui(new Ui::DoublePolarDlg),
	m_dpObs(dpObs)
{
	ui->setupUi(this);

	setStyleSheet("QDialog { background: lightBlue } "
				  "QGroupBox { "
				  "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 2, stop: 0 #E0E0E0, stop: 1 #FFFFFF); "
				  "border: 2px solid gray; "
				  "border-radius: 5px; "
				  "margin-top: 1ex; "
				  "}"
				  );

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
	if (m_dpObs.m_adopt != "1" && m_dpObs.m_adopt != "2" && m_dpObs.m_adopt != "W")
		ui->meanRadio->setChecked(true);

	ui->targetEdit->setName(m_dpObs.m_aname);
	wireResult();
}

DoublePolarDlg::~DoublePolarDlg()
{
	delete ui;
}

void DoublePolarDlg::wireStation(const Occupied &station, NameLineEdit *nameEdit, IntLineEdit *setupEdit, AngleLineEdit *corrEdit)
{
	if (!station.m_name.isEmpty())
	{
		nameEdit->setName(station.m_name);
		setupEdit->setValue(station.m_setup);
		corrEdit->setAngle(station.m_oc);
	}
}

void DoublePolarDlg::wireObservation(const Observation &obs, NameLineEdit *targetEdit, AngleLineEdit *dircEdit, AngleLineEdit *vertEdit, LengthLineEdit *distEdit)
{
	if (!obs.m_target.isEmpty())
	{
		targetEdit->setName(obs.m_target);
		dircEdit->setAngle(obs.m_dirc);
		vertEdit->setAngle(obs.m_vert);
		distEdit->setValue(obs.m_dist);
	}
}

void DoublePolarDlg::wireResult()
{
	ui->eastingEdit->setValue(m_dpObs.m_ay);
	ui->northingEdit->setValue(m_dpObs.m_ax);
}

void DoublePolarDlg::on_calculateButton_clicked()
{
	m_dpObs.m_stn[0].m_name = ui->from1Edit->name();
	m_dpObs.m_obs[0].m_target = ui->trg1Edit->name();
	m_dpObs.m_obs[0].m_dirc = ui->dir1Edit->angle();
	m_dpObs.m_stn[0].m_oc = ui->oc1Edit->angle();
	m_dpObs.m_obs[0].m_vert = ui->ver1Edit->angle();
	m_dpObs.m_obs[0].m_dist = ui->dis1Edit->value();

	m_dpObs.m_stn[1].m_name = ui->from2Edit->name();
	m_dpObs.m_obs[1].m_target = ui->trg2Edit->name();
	m_dpObs.m_obs[1].m_dirc = ui->dir2Edit->angle();
	m_dpObs.m_stn[1].m_oc = ui->oc2Edit->angle();
	m_dpObs.m_obs[1].m_vert = ui->ver2Edit->angle();
	m_dpObs.m_obs[1].m_dist = ui->dis2Edit->value();

	Compute::DoublePolar(m_dpObs);

	wireResult();

	if (m_dpObs.m_aname.isEmpty())
		ui->targetEdit->setName(m_dpObs.m_obs[0].m_target);
	else
		ui->targetEdit->setName(m_dpObs.m_aname);
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

void DoublePolarDlg::onTargetAction(Observation &obs, const NameLineEdit *nameEdit, const IntLineEdit *setupEdit, NameLineEdit *targetEdit, AngleLineEdit *dircEdit, AngleLineEdit *vertEdit, LengthLineEdit *distEdit)
{
	QString from = nameEdit->name();
	int setup = setupEdit->value();

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
