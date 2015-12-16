#include "polardlg.h"
#include "ui_polardlg.h"
#include "Types/polars.h"
#include "utils.h"
#include "compute.h"

namespace
{
QString FormatReal(double value)
{
	return QString::number(value, 'f', 3);
}

class NameValidator : public QRegularExpressionValidator
{
public:
	NameValidator(QWidget *parent)
		: QRegularExpressionValidator(QRegularExpression("^.{1,8}$"), parent)
	{}
};

class AngleValidator : public QDoubleValidator
{
public:
	AngleValidator(QWidget *parent)
		: QDoubleValidator(-360.0, 360.0, 4, parent)
	{}
};

class LengthValidator : public QDoubleValidator
{
public:
	LengthValidator(QWidget *parent)
		: QDoubleValidator(0.0, 10000000.0, 3, parent)
	{}
};
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

	QAction *stationAction = ui->fromEdit->addAction(QIcon(":/blue-hand-16.png"), QLineEdit::TrailingPosition);
	QAction *targetAction = ui->trgEdit->addAction(QIcon(":/green-hand-16.png"), QLineEdit::TrailingPosition);
	connect(stationAction, &QAction::triggered, this, &PolarDlg::onStationAction);
	connect(targetAction, &QAction::triggered, this, &PolarDlg::onTargetAction);

	const QString dms = "ddd.mmss";
	ui->dirEdit->setPlaceholderText(dms);
	ui->vertEdit->setPlaceholderText(dms);
	ui->ocEdit->setPlaceholderText(dms);

	ui->fromEdit->setValidator(new NameValidator(this));
	ui->setupEdit->setValidator(new QIntValidator(this));
	ui->trgEdit->setValidator(new NameValidator(this));
	ui->dirEdit->setValidator(new AngleValidator(this));
	ui->vertEdit->setValidator(new AngleValidator(this));
	ui->ocEdit->setValidator(new AngleValidator(this));
	ui->distEdit->setValidator(new LengthValidator(this));
	ui->instrEdit->setValidator(new LengthValidator(this));
	ui->prismEdit->setValidator(new LengthValidator(this));
	ui->toEdit->setValidator(new NameValidator(this));
	ui->northEdit->setValidator(new QDoubleValidator(this));
	ui->eastEdit->setValidator(new QDoubleValidator(this));
	ui->elevEdit->setValidator(new QDoubleValidator(this));

	ui->fromEdit->setText(polar.m_stn.m_name);
	ui->setupEdit->setText(QString::number(polar.m_stn.m_setup));
	ui->trgEdit->setText(polar.m_obs.m_target);
	ui->dirEdit->setText(Utils::Rad2Dms(polar.m_obs.m_dirc));
	ui->vertEdit->setText((Utils::Rad2Dms(polar.m_obs.m_vert)));
	ui->ocEdit->setText(Utils::Rad2Dms(polar.m_stn.m_oc));
	ui->distEdit->setText(FormatReal(polar.m_obs.m_dist));
	ui->instrEdit->setText(FormatReal(polar.m_stn.m_instHgt));
	ui->prismEdit->setText(FormatReal(polar.m_obs.m_prismHgt));

	wireResult(polar);
}

PolarDlg::~PolarDlg()
{
	delete ui;
}

void PolarDlg::onStationAction()
{
	auto p1 = qMakePair(m_polar.m_stn.m_name, ui->fromEdit);
	auto p2 = qMakePair(m_polar.m_stn.m_setup, ui->setupEdit);
	auto p3 = qMakePair(m_polar.m_stn.m_oc, ui->ocEdit);
	// what about instrHgt ?

	Utils::LoadStation(this, p1, p2, p3);
}

void PolarDlg::onTargetAction()
{
	QString from = ui->fromEdit->text();
	int setup = ui->setupEdit->text().toInt();

	Observation selection;
	if (Utils::LoadObs(this, from, setup, selection))
	{
		ui->trgEdit->setText(selection.m_target);
		ui->dirEdit->setText(Utils::Rad2Dms(selection.m_dirc));
		ui->vertEdit->setText((Utils::Rad2Dms(selection.m_vert)));
		ui->distEdit->setText(FormatReal(selection.m_dist));
		ui->prismEdit->setText(FormatReal(selection.m_prismHgt));
	}
}

void PolarDlg::wireResult(const PolarsCalc &polar)
{
	ui->toEdit->setText(polar.m_obs.m_target);
	ui->northEdit->setText(FormatReal(polar.m_tx));
	ui->eastEdit->setText(FormatReal(polar.m_ty));
	ui->elevEdit->setText("0.000");
}

void PolarDlg::pack(PolarsCalc &polar) const
{
	polar.m_stn.m_name = ui->fromEdit->text();
	polar.m_stn.m_setup = ui->setupEdit->text().toInt();
	polar.m_obs.m_target = ui->trgEdit->text();
	polar.m_obs.m_dirc = Utils::Dms2Rad(ui->dirEdit->text());
	polar.m_obs.m_vert = Utils::Dms2Rad(ui->vertEdit->text());
	polar.m_stn.m_oc = Utils::Dms2Rad(ui->ocEdit->text());
	polar.m_obs.m_dist = ui->distEdit->text().toDouble();
	polar.m_stn.m_instHgt = ui->instrEdit->text().toDouble();
	polar.m_obs.m_prismHgt = ui->prismEdit->text().toDouble();
	polar.m_obs.m_target = ui->toEdit->text();
	polar.m_tx = ui->northEdit->text().toDouble();
	polar.m_ty = ui->eastEdit->text().toDouble();
}

void PolarDlg::on_calcButton_clicked()
{
	PolarsCalc polar;
	pack(polar);
	Compute::Polar(polar);
	wireResult(polar);
}
