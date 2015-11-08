#include "doublepolardlg.h"
#include "ui_doublepolardlg.h"
#include "utils.h"

DoublePolarDlg::DoublePolarDlg(QWidget *parent, DpObsCalc &dpObs) :
	QDialog(parent),
	ui(new Ui::DoublePolarDlg),
	m_dpObs(dpObs)
{
	ui->setupUi(this);

	connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

	ui->from1Edit->setText(m_dpObs.m_from1);
	ui->trg1Edit->setText(m_dpObs.m_trg1);
	ui->dir1Edit->setText(Utils::Rad2Dms(m_dpObs.m_dir1));
	ui->oc1Edit->setText(Utils::Rad2Dms(m_dpObs.m_oc1));
	ui->ver1Edit->setText(Utils::Rad2Dms(m_dpObs.m_ver1));
	ui->dis1Edit->setText(QString::number(m_dpObs.m_dis1, 'f', 3));

	ui->from2Edit->setText(m_dpObs.m_from2);
	ui->trg2Edit->setText(m_dpObs.m_trg2);
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

}
