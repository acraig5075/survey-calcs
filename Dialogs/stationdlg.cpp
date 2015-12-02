#include "stationdlg.h"
#include "ui_stationdlg.h"
#include "utils.h"
#include "Types\occupied.h"

StationDlg::StationDlg(QWidget *parent, Occupied &occupied) :
	QDialog(parent),
	ui(new Ui::StationDlg),
	m_station(occupied)
{
	ui->setupUi(this);

	ui->nameEdit->setText(m_station.m_name);
	ui->setupEdit->setText(QString::number(m_station.m_setup));
	ui->orientEdit->setText(Utils::Rad2Dms(m_station.m_oc));
	ui->instrEdit->setText(QString::number(m_station.m_instHgt, 'f', 3));
	ui->dateEdit->setDate(m_station.m_date);

	ui->orientEdit->setPlaceholderText("ddd.mmss");

	QRegularExpression regExp("^.{1,8}$");
	auto nameValidator = new QRegularExpressionValidator(regExp, this);

	ui->nameEdit->setValidator(nameValidator);
	ui->orientEdit->setValidator(new QDoubleValidator(-360.0, 360.0, 4, this));
	ui->instrEdit->setValidator(new QDoubleValidator(-1000.0, 1000.0, 3, this));
}

StationDlg::~StationDlg()
{
	delete ui;
}

void StationDlg::on_StationDlg_accepted()
{
	m_station.m_name = ui->nameEdit->text();
	m_station.m_setup = ui->setupEdit->text().toInt();
	m_station.m_date = ui->dateEdit->date();
	m_station.m_oc = Utils::Dms2Rad(ui->orientEdit->text());
	m_station.m_instHgt = ui->instrEdit->text().toDouble();
}
