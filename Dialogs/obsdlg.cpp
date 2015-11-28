#include "obsdlg.h"
#include "ui_obsdlg.h"
#include "Types/observation.h"
#include "utils.h"
#include <QPushButton>
#include <QRegularExpressionValidator>

using DMSValidator = QDoubleValidator;

ObsDlg::ObsDlg(QWidget *parent, Observation &obs) :
	QDialog(parent),
	ui(new Ui::ObsDlg),
	m_obs(obs)
{
	ui->setupUi(this);

	ui->targetEdit->setText(m_obs.m_target);
	ui->angleEdit->setText(Utils::Rad2Dms(m_obs.m_dirc));
	ui->vertEdit->setText(Utils::Rad2Dms(m_obs.m_vert));
	ui->distEdit->setText(QString::number(m_obs.m_dist, 'f', 3));
	ui->prismEdit->setText(QString::number(m_obs.m_prismHgt, 'f', 3));

	Utils::DescriptionCombobox(this, ui->descCombo, m_obs.m_desc);

	ui->angleEdit->setPlaceholderText("ddd.mmss");
	ui->vertEdit->setPlaceholderText("ddd.mmss");

	QRegularExpression regExp("^.{1,8}$");
	auto nameValidator = new QRegularExpressionValidator(regExp, this);

	ui->targetEdit->setValidator(nameValidator);
	ui->angleEdit->setValidator(new DMSValidator(this));
	ui->vertEdit->setValidator(new DMSValidator(this));
	ui->distEdit->setValidator(new QDoubleValidator(this));
	ui->prismEdit->setValidator(new QDoubleValidator(this));
	ui->descCombo->setValidator(nameValidator);

	connect(ui->targetEdit, SIGNAL(textChanged(QString)), this, SLOT(checkLineEdits(QString)));
}

ObsDlg::~ObsDlg()
{
	delete ui;
}

void ObsDlg::checkLineEdits(QString text)
{
	int pos;
	QPushButton *okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
	auto state = ui->targetEdit->validator()->validate(text.trimmed(), pos);
	okButton->setEnabled(QValidator::Acceptable == state);
}

void ObsDlg::on_ObsDlg_accepted()
{
	m_obs.m_target = ui->targetEdit->text().trimmed();
	m_obs.m_dirc = Utils::Dms2Rad(ui->angleEdit->text());
	m_obs.m_vert = Utils::Dms2Rad(ui->vertEdit->text());
	m_obs.m_dist = ui->distEdit->text().toDouble();
	m_obs.m_prismHgt = ui->distEdit->text().toDouble();
	m_obs.m_desc = ui->descCombo->currentText().trimmed();
}
