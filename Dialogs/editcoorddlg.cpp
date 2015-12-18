#include "editcoorddlg.h"
#include "ui_editcoorddlg.h"
#include "Types/coord.h"
#include "utils.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>

namespace
{
bool ModelContains(const QComboBox *comboBox, const QString &value)
{
	auto model = static_cast<QSqlQueryModel *>(comboBox->model());
	for (int i = 0; i < model->rowCount(); ++i)
	{
		if (value == model->record(i).value(0).toString())
			return true;
	}
	return false;
}

bool TableContains(QWidget *parent, const QString &value)
{
	QSqlQuery query;
	query.prepare("SELECT `name` from coord WHERE `name` = :name");
	query.bindValue(":name", value);
	if (query.exec())
	{
		if (query.next())
		{
			QString msg = QString("%1 already exists in the database").arg(value);
			QMessageBox::critical(parent, "Error", msg, QMessageBox::Ok);
			return true;
		}
	}
	return false;
}
}

EditCoordDlg::EditCoordDlg(QWidget *parent, Coord &coord) :
	QDialog(parent),
	ui(new Ui::EditCoordDlg),
	m_coord(coord)
{
	ui->setupUi(this);

	ui->nameEdit->setName(coord.m_name);
	ui->eastingEdit->setValue(coord.m_easting);
	ui->northingEdit->setValue(coord.m_northing);
	ui->elevationEdit->setValue(coord.m_elevation);

	Utils::DescriptionCombobox(this, ui->descriptionCombo, coord.m_desc);
	Utils::ClassificationCombobox(this, ui->classificationCombo, coord.m_class);

	if (!coord.m_name.isEmpty())
	{
		if (coord.m_easting == 0.0)
			ui->eastingEdit->setFocus();
		else
			ui->nameEdit->setFocus();
	}
}

EditCoordDlg::~EditCoordDlg()
{
	delete ui;
}

void EditCoordDlg::done(int r)
{
	if (QDialog::Accepted == r)
	{
		QString name = ui->nameEdit->name();
		QString desc = ui->descriptionCombo->currentText().toUpper();
		QString clas = ui->classificationCombo->currentText().toUpper();

		if (!ValidateName(name))
		{
			ui->nameEdit->selectAll();
			ui->nameEdit->setFocus();
			return;
		}

		if (!HandleNewMnemonics(desc, clas))
		{
			desc = m_coord.m_desc;
			clas = m_coord.m_class;
		}

		m_coord.m_name = name;
		m_coord.m_desc = desc;
		m_coord.m_class = clas;
		m_coord.m_easting = ui->eastingEdit->value();
		m_coord.m_northing = ui->northingEdit->value();
		m_coord.m_elevation = ui->elevationEdit->value();
	}

	QDialog::done(r);
}

bool EditCoordDlg::ValidateName(const QString &name)
{
	if (name != m_coord.m_name)
	{
		if (name.isEmpty() || TableContains(this, name))
			return false;
	}
	return true;
}

bool EditCoordDlg::HandleNewMnemonics(const QString &desc, const QString &clas)
{
	bool newDesc = !ModelContains(ui->descriptionCombo, desc);
	bool newClass = !ModelContains(ui->classificationCombo, clas);

	if (newDesc || newClass)
	{
		QSqlDatabase db = QSqlDatabase::database();
		db.transaction();
		if (newDesc)
		{
			QSqlQuery query;
			query.prepare("INSERT INTO desc (`desc`) VALUES (:value)");
			query.bindValue(":value", desc);
			if (!query.exec())
				qDebug() << query.lastError();
		}
		if (newClass)
		{
			QSqlQuery query;
			query.prepare("INSERT INTO class (`class`) VALUES (:value)");
			query.bindValue(":value", clas);
			if (!query.exec())
				qDebug() << query.lastError();
		}
		if (!db.commit())
		{
			QMessageBox::critical(this, "Error", "Failed to add new description or classification", QMessageBox::Ok);
			return false;
		}
	}
	return true;
}
