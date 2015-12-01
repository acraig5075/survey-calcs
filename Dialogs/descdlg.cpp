#include "descdlg.h"
#include "Types/desc.h"
#include "ui_descdlg.h"

DescDlg::DescDlg(QWidget *parent, Desc &desc) :
	QDialog(parent),
	ui(new Ui::DescDlg),
	m_desc(desc)
{
	ui->setupUi(this);

	QRegularExpression regExp("^.{1,8}$");
	auto nameValidator = new QRegularExpressionValidator(regExp, this);

	ui->nameEdit->setValidator(nameValidator);
	ui->nameEdit->setText(desc.m_name);
	ui->descriptionEdit->setText(desc.m_description);
}

DescDlg::~DescDlg()
{
	delete ui;
}

void DescDlg::on_DescDlg_accepted()
{
	m_desc.m_name = ui->nameEdit->text();
	m_desc.m_description = ui->descriptionEdit->text();
}
