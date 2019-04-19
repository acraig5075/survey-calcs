#include "polardlg.h"
#include "ui_polardlg.h"
#include "Types/polars.h"
#include "Types/coord.h"
#include "utils.h"
#include "compute.h"
#include <QAction>


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

	QAction *coordAction = ui->fromEdit->addAction(QIcon(":/yellow-hand-16.png"), QLineEdit::TrailingPosition);
	QAction *targetAction = ui->trgEdit->addAction(QIcon(":/green-hand-16.png"), QLineEdit::TrailingPosition);
	connect(coordAction, &QAction::triggered, this, &PolarDlg::onCoordAction);
	connect(targetAction, &QAction::triggered, this, &PolarDlg::onTargetAction);

	ui->fromEdit->setName(polar.m_stn.m_name);
	ui->trgEdit->setName(polar.m_obs.m_target);
	ui->dirEdit->setAngle(polar.m_obs.m_dirc);
	ui->vertEdit->setAngle(polar.m_obs.m_vert);
	ui->ocEdit->setAngle(polar.m_stn.m_oc);
	ui->distEdit->setValue(polar.m_obs.m_dist);
	ui->instrEdit->setValue(polar.m_stn.m_instHgt);
	ui->prismEdit->setValue(polar.m_obs.m_prismHgt);

	wireResult(polar);

	layout()->setSizeConstraint(QLayout::SetFixedSize);
}

PolarDlg::~PolarDlg()
{
	delete ui;
}

void PolarDlg::onCoordAction()
{
	QString name;
	double n, e;
	auto p1 = qMakePair<QString, QLineEdit *>(name, ui->fromEdit);
	auto p2 = qMakePair<double, QLineEdit *>(n, nullptr);
	auto p3 = qMakePair<double, QLineEdit *>(e, nullptr);

	Utils::LoadCoord(this, p1, p2, p3);
}

void PolarDlg::onTargetAction()
{
	QString from = ui->fromEdit->name();
	int setup = 0;

	Observation selection;
	if (Utils::LoadObs(this, from, setup, selection))
	{
		ui->trgEdit->setName(selection.m_target);
		ui->dirEdit->setAngle(selection.m_dirc);
		ui->vertEdit->setAngle(selection.m_vert);
		ui->distEdit->setValue(selection.m_dist);
		ui->prismEdit->setValue(selection.m_prismHgt);
	}
}

void PolarDlg::wireResult(const PolarsCalc &polar)
{
	ui->toEdit->setName(polar.m_obs.m_target);
	ui->northEdit->setValue(polar.m_tx);
	ui->eastEdit->setValue(polar.m_ty);
	ui->elevEdit->setValue(0.0);
}

void PolarDlg::pack(PolarsCalc &polar, const Coord &from) const
{
	polar.m_stn.m_name = from.m_name;
	polar.m_fx = from.m_northing;
	polar.m_fy = from.m_easting;

	polar.m_obs.m_target = ui->trgEdit->name();
	polar.m_obs.m_dirc = ui->dirEdit->angle();
	polar.m_obs.m_vert = ui->vertEdit->angle();
	polar.m_stn.m_oc = ui->ocEdit->angle();
	polar.m_obs.m_dist = ui->distEdit->value();
	polar.m_stn.m_instHgt = ui->instrEdit->value();
	polar.m_obs.m_prismHgt = ui->prismEdit->value();
	polar.m_obs.m_target = ui->toEdit->name();

	polar.m_tx = ui->northEdit->value();
	polar.m_ty = ui->eastEdit->value();
}

void PolarDlg::on_calcButton_clicked()
{
	QString fromname = ui->fromEdit->name();
	if (!fromname.isEmpty())
	{
		Coord from;
		if (Utils::LookupCoord(this, fromname, from))
		{
			PolarsCalc polar;
			pack(polar, from);
			Compute::Polar(polar);
			wireResult(polar);
		}
	}
}
