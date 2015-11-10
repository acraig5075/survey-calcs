#include "doublepolardlg.h"
#include "ui_doublepolardlg.h"
#include "utils.h"
#include <QPair>

namespace Compute
{
void DoublePolar(DpObsCalc &dpObs)
{
	Utils::Polar(dpObs.m_fy1, dpObs.m_fx1, dpObs.m_dis1, dpObs.m_dir1, dpObs.m_y1, dpObs.m_x1);
	Utils::Polar(dpObs.m_fy2, dpObs.m_fx2, dpObs.m_dis2, dpObs.m_dir2, dpObs.m_y2, dpObs.m_x2);
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

	ui->from1Edit->setText(m_dpObs.m_from1);
	ui->trg1Edit->setText(m_dpObs.m_trg1);
	ui->setup1Edit->setText(QString::number(m_dpObs.m_setup1));
	ui->dir1Edit->setText(Utils::Rad2Dms(m_dpObs.m_dir1));
	ui->oc1Edit->setText(Utils::Rad2Dms(m_dpObs.m_oc1));
	ui->ver1Edit->setText(Utils::Rad2Dms(m_dpObs.m_ver1));
	ui->dis1Edit->setText(QString::number(m_dpObs.m_dis1, 'f', 3));

	ui->from2Edit->setText(m_dpObs.m_from2);
	ui->trg2Edit->setText(m_dpObs.m_trg2);
	ui->setup2Edit->setText(QString::number(m_dpObs.m_setup2));
	ui->dir2Edit->setText(Utils::Rad2Dms(m_dpObs.m_dir2));
	ui->oc2Edit->setText(Utils::Rad2Dms(m_dpObs.m_oc2));
	ui->ver2Edit->setText(Utils::Rad2Dms(m_dpObs.m_ver2));
	ui->dis2Edit->setText(QString::number(m_dpObs.m_dis2, 'f', 3));

	ui->previewEdit->setText(m_dpObs.desc());
}

DoublePolarDlg::~DoublePolarDlg()
{
	delete ui;
}

void DoublePolarDlg::on_calculateButton_clicked()
{
	m_dpObs.m_from1 = ui->from1Edit->text();
	m_dpObs.m_trg1 = ui->trg1Edit->text();
	m_dpObs.m_dir1 = Utils::Dms2Rad(ui->dir1Edit->text());
	m_dpObs.m_oc1 = Utils::Dms2Rad(ui->oc1Edit->text());
	m_dpObs.m_ver1 = Utils::Dms2Rad(ui->ver1Edit->text());
	m_dpObs.m_dis1 = ui->dis1Edit->text().toDouble();

	m_dpObs.m_from2 = ui->from2Edit->text();
	m_dpObs.m_trg2 = ui->trg2Edit->text();
	m_dpObs.m_dir2 = Utils::Dms2Rad(ui->dir2Edit->text());
	m_dpObs.m_oc2 = Utils::Dms2Rad(ui->oc2Edit->text());
	m_dpObs.m_ver2 = Utils::Dms2Rad(ui->ver2Edit->text());
	m_dpObs.m_dis2 = ui->dis2Edit->text().toDouble();

	Compute::DoublePolar(m_dpObs);
	ui->previewEdit->setText(m_dpObs.desc());
}

void DoublePolarDlg::onStation1Action()
{
	auto p1 = qMakePair(m_dpObs.m_from1, ui->from1Edit);
	auto p2 = qMakePair(m_dpObs.m_setup1, ui->setup1Edit);
	auto p3 = qMakePair(m_dpObs.m_oc1, ui->oc1Edit);

	if (Utils::LoadStation(this, p1, p2, p3))
		ui->previewEdit->clear();
}

void DoublePolarDlg::onStation2Action()
{
	auto p1 = qMakePair(m_dpObs.m_from2, ui->from2Edit);
	auto p2 = qMakePair(m_dpObs.m_setup2, ui->setup2Edit);
	auto p3 = qMakePair(m_dpObs.m_oc2, ui->oc2Edit);

	if (Utils::LoadStation(this, p1, p2, p3))
		ui->previewEdit->clear();
}

void DoublePolarDlg::onTarget1Action()
{

}

void DoublePolarDlg::onTarget2Action()
{

}

