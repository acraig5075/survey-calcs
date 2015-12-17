#include "stationdlg.h"
#include "ui_stationdlg.h"
#include "utils.h"
#include "Types\occupied.h"
#include <QPushButton>

StationDlg::StationDlg(QWidget *parent, Occupied &occupied) :
	QDialog(parent),
	ui(new Ui::StationDlg),
	m_station(occupied)
{
	ui->setupUi(this);

	ui->nameEdit->setName(m_station.m_name);
	ui->setupEdit->setValue(m_station.m_setup);
	ui->orientEdit->setAngle(m_station.m_oc);
	ui->instrEdit->setValue(m_station.m_instHgt);
	ui->dateEdit->setDate(m_station.m_date);

	bool isEditing = !m_station.m_name.isEmpty();
	if (isEditing)
	{
		// disallow changing the name when in edit mode
		ui->nameEdit->setReadOnly(true);
		ui->nameEdit->setEnabled(false);
	}
	else
	{
		// initially have OK btn disabled when in add mode.
		QPushButton *okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
		okButton->setEnabled(false);
	}

	ui->setupEdit->setReadOnly(true); // never editable

	connect(ui->nameEdit, SIGNAL(textChanged(QString)), this, SLOT(checkLineEdits(QString)));
}

StationDlg::~StationDlg()
{
	delete ui;
}

void StationDlg::checkLineEdits(QString text)
{
	int pos;
	QPushButton *okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
	auto state = ui->nameEdit->validator()->validate(text.trimmed(), pos);
	okButton->setEnabled(QValidator::Acceptable == state);
}

void StationDlg::on_StationDlg_accepted()
{
	m_station.m_name = ui->nameEdit->name();
	m_station.m_setup = ui->setupEdit->value();
	m_station.m_date = ui->dateEdit->date();
	m_station.m_oc = ui->orientEdit->angle();
	m_station.m_instHgt = ui->instrEdit->value();
}

void StationDlg::on_nameEdit_editingFinished()
{
	int nextSetup = 0;
	QString name = ui->nameEdit->name();

	int pos;
	if (QValidator::Acceptable == ui->nameEdit->validator()->validate(name, pos))
	{
		QSqlQuery query;
		query.prepare("SELECT MAX(setupno) FROM occupied WHERE station = :name");
		query.bindValue(":name", name);

		nextSetup = 1;
		if (Utils::ExecQuery(query))
		{
			if (query.next())
				nextSetup = query.value(0).toInt() + 1;
		}
	}

	ui->setupEdit->setValue(nextSetup);
}
