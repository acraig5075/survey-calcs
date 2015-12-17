#include "editjoindlg.h"
#include "ui_editjoindlg.h"
#include "utils.h"
#include "compute.h"


EditJoinDlg::EditJoinDlg(QWidget *parent, JoinsCalc &join) :
	QDialog(parent),
	ui(new Ui::EditJoinDlg),
	m_join(join)
{
	ui->setupUi(this);

	QAction *coordAction1 = ui->fromNameEdit->addAction(QIcon(":/yellow-hand-16.png"), QLineEdit::TrailingPosition);
	QAction *coordAction2 = ui->toNameEdit->addAction(QIcon(":/yellow-hand-16.png"), QLineEdit::TrailingPosition);
	connect(coordAction1, &QAction::triggered, this, &EditJoinDlg::onCoordAction1);
	connect(coordAction2, &QAction::triggered, this, &EditJoinDlg::onCoordAction2);

	ui->fromNameEdit->setName(join.m_fromname);
	ui->fromEastingEdit->setValue(join.m_fy);
	ui->fromNorthingEdit->setValue(join.m_fx);
	ui->toNameEdit->setName(join.m_toname);
	ui->toEastingEdit->setValue(join.m_ty);
	ui->toNorthingEdit->setValue(join.m_tx);
	ui->distEdit->setValue(join.m_dist);
	ui->dircEdit->setAngle(join.m_dirc);

	ui->toNorthingEdit->setAlignment(Qt::AlignRight);
	ui->toEastingEdit->setAlignment(Qt::AlignRight);
	ui->fromNorthingEdit->setAlignment(Qt::AlignRight);
	ui->fromEastingEdit->setAlignment(Qt::AlignRight);
	ui->distEdit->setAlignment(Qt::AlignRight);
	ui->dircEdit->setAlignment(Qt::AlignRight);
	ui->distEdit->setReadOnly(true);
	ui->dircEdit->setReadOnly(true);
}

EditJoinDlg::~EditJoinDlg()
{
	delete ui;
}

void EditJoinDlg::on_calculateButton_clicked()
{
	m_join.m_fromname = ui->fromNameEdit->name();
	m_join.m_fy = ui->fromEastingEdit->value();
	m_join.m_fx = ui->fromNorthingEdit->value();
	m_join.m_toname = ui->toNameEdit->name();
	m_join.m_ty = ui->toEastingEdit->value();
	m_join.m_tx = ui->toNorthingEdit->value();

	Compute::Join(m_join);

	ui->distEdit->setValue(m_join.m_dist);
	ui->dircEdit->setAngle(m_join.m_dirc);
}

void EditJoinDlg::onCoordAction1()
{
	auto p1 = qMakePair<QString, QLineEdit *>(m_join.m_fromname, ui->fromNameEdit);
	auto p2 = qMakePair<double, QLineEdit *>(m_join.m_fy, ui->fromEastingEdit);
	auto p3 = qMakePair<double, QLineEdit *>(m_join.m_fx, ui->fromNorthingEdit);

	Utils::LoadCoord(this, p1, p2, p3);
}

void EditJoinDlg::onCoordAction2()
{
	auto p1 = qMakePair<QString, QLineEdit *>(m_join.m_toname, ui->toNameEdit);
	auto p2 = qMakePair<double, QLineEdit *>(m_join.m_ty, ui->toEastingEdit);
	auto p3 = qMakePair<double, QLineEdit *>(m_join.m_tx, ui->toNorthingEdit);

	Utils::LoadCoord(this, p1, p2, p3);
}
