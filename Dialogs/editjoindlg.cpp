#include "editjoindlg.h"
#include "ui_editjoindlg.h"
#include "utils.h"


namespace Compute
{
void Join(JoinsCalc &join)
{
	join.m_dist = _hypot(join.m_fy - join.m_ty, join.m_fx - join.m_tx);
	join.m_dirc = 0.0;
}
}

EditJoinDlg::EditJoinDlg(QWidget *parent, JoinsCalc &join) :
	QDialog(parent),
	ui(new Ui::EditJoinDlg),
	m_join(join)
{
	ui->setupUi(this);

	ui->fromNameEdit->setText(join.m_fromname);
	ui->fromEastingEdit->setText(QString::number(join.m_fy, 'f', 3));
	ui->fromNorthingEdit->setText(QString::number(join.m_fx, 'f', 3));
	ui->toNameEdit->setText(join.m_toname);
	ui->toEastingEdit->setText(QString::number(join.m_ty, 'f', 3));
	ui->toNorthingEdit->setText(QString::number(join.m_tx, 'f', 3));
	ui->previewEdit->setText(join.desc());

	ui->toNorthingEdit->setAlignment(Qt::AlignRight);
	ui->toEastingEdit->setAlignment(Qt::AlignRight);
	ui->fromNorthingEdit->setAlignment(Qt::AlignRight);
	ui->fromEastingEdit->setAlignment(Qt::AlignRight);
	ui->previewEdit->setFont(QFont("Courier", 8, QFont::Normal | QFont::Courier));

	auto validator = new QDoubleValidator(-10000000.0, 10000000.0, 3, this);
	validator->setNotation(QDoubleValidator::StandardNotation);

	ui->fromEastingEdit->setValidator(validator);
	ui->fromNorthingEdit->setValidator(validator);
	ui->toEastingEdit->setValidator(validator);
	ui->toNorthingEdit->setValidator(validator);
}

EditJoinDlg::~EditJoinDlg()
{
	delete ui;
}

void EditJoinDlg::on_calculateButton_clicked()
{
	m_join.m_fromname = ui->fromNameEdit->text();
	m_join.m_fy = ui->fromEastingEdit->text().toDouble();
	m_join.m_fx = ui->fromNorthingEdit->text().toDouble();
	m_join.m_toname = ui->toNameEdit->text();
	m_join.m_ty = ui->toEastingEdit->text().toDouble();
	m_join.m_tx = ui->toNorthingEdit->text().toDouble();

	Compute::Join(m_join);
	ui->previewEdit->setText(m_join.desc());
}

void EditJoinDlg::on_fromButton_clicked()
{
	auto p1 = qMakePair(m_join.m_fromname, ui->fromNameEdit);
	auto p2 = qMakePair(m_join.m_fy, ui->fromEastingEdit);
	auto p3 = qMakePair(m_join.m_fx, ui->fromNorthingEdit);

	if (Utils::LoadCoord(this, p1, p2, p3))
		ui->previewEdit->clear();
}

void EditJoinDlg::on_toButton_clicked()
{
	auto p1 = qMakePair(m_join.m_toname, ui->toNameEdit);
	auto p2 = qMakePair(m_join.m_ty, ui->toEastingEdit);
	auto p3 = qMakePair(m_join.m_tx, ui->toNorthingEdit);

	if (Utils::LoadCoord(this, p1, p2, p3))
		ui->previewEdit->clear();
}
