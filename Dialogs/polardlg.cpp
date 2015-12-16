#include "polardlg.h"
#include "ui_polardlg.h"
#include "Types/polars.h"
#include "utils.h"

namespace
{
	QString FormatReal(double value)
	{
		return QString::number(value, 'f', 3);
	}
}

PolarDlg::PolarDlg(QWidget *parent, PolarsCalc &polar) :
	QDialog(parent),
	ui(new Ui::PolarDlg),
	m_polar(polar)
{
	ui->setupUi(this);

	setStyleSheet("QDialog { background: QLinearGradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ccf, stop: 1 #eef) } "
				  "QGroupBox { "
				  "background-color: QLinearGradient(x1: 0, y1: 0, x2: 0, y2: 2, stop: 0 #E0E0E0, stop: 1 #FFFFFF); "
				  "border: 2px solid #88D; "
				  "border-radius: 5px; "
				  "margin-top: 1ex; "
				  "}"
				  );

	const QString dms = "ddd.mmss";
	ui->dirEdit->setPlaceholderText(dms);
	ui->vertEdit->setPlaceholderText(dms);
	ui->ocEdit->setPlaceholderText(dms);

	ui->fromEdit->setText(polar.m_stn.m_name);
	ui->setupEdit->setText(QString::number(polar.m_stn.m_setup));
	ui->trgEdit->setText(polar.m_obs.m_target);
	ui->dirEdit->setText(Utils::Rad2Dms(polar.m_obs.m_dirc));
	ui->vertEdit->setText((Utils::Rad2Dms(polar.m_obs.m_vert)));
	ui->ocEdit->setText(Utils::Rad2Dms(polar.m_stn.m_oc));
	ui->distEdit->setText(FormatReal(polar.m_obs.m_dist));
	ui->instrEdit->setText(FormatReal(polar.m_stn.m_instHgt));
	ui->prismEdit->setText(FormatReal(polar.m_obs.m_prismHgt));
	ui->toEdit->setText(polar.m_obs.m_target);
	ui->northEdit->setText(FormatReal(polar.m_tx));
	ui->eastEdit->setText(FormatReal(m_polar.m_ty));
	ui->elevEdit->setText("0.000");
}

PolarDlg::~PolarDlg()
{
	delete ui;
}
