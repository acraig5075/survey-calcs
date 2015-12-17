#include "descdlg.h"
#include "Types/desc.h"
#include "ui_descdlg.h"

DescDlg::DescDlg(QWidget *parent, Desc &desc) :
	QDialog(parent),
	ui(new Ui::DescDlg),
	m_desc(desc)
{
	ui->setupUi(this);
	ui->nameEdit->setName(desc.m_name);
	ui->descriptionEdit->setText(desc.m_description);
}

DescDlg::~DescDlg()
{
	delete ui;
}

void DescDlg::on_DescDlg_accepted()
{
	m_desc.m_name = ui->nameEdit->name();
	m_desc.m_description = ui->descriptionEdit->text();
}
