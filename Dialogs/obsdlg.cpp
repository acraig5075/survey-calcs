#include "obsdlg.h"
#include "ui_obsdlg.h"
#include "Types/observation.h"
#include "utils.h"
#include <QPushButton>
#include <QRegularExpressionValidator>


ObsDlg::ObsDlg(QWidget *parent, Observation &obs) :
	QDialog(parent),
	ui(new Ui::ObsDlg),
	m_obs(obs)
{
	ui->setupUi(this);

	ui->targetEdit->setName(m_obs.m_target);
	ui->angleEdit->setAngle(m_obs.m_dirc);
	ui->vertEdit->setAngle(m_obs.m_vert);
	ui->distEdit->setValue(m_obs.m_dist);
	ui->prismEdit->setValue(m_obs.m_prismHgt);

	Utils::DescriptionCombobox(this, ui->descCombo, m_obs.m_desc);

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
	m_obs.m_target = ui->targetEdit->name().trimmed();
	m_obs.m_dirc = ui->angleEdit->angle();
	m_obs.m_vert = ui->vertEdit->angle();
	m_obs.m_dist = ui->distEdit->value();
	m_obs.m_prismHgt = ui->distEdit->value();
	m_obs.m_desc = ui->descCombo->currentText().trimmed();
}
