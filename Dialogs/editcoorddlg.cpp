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

	ui->nameEdit->setText(coord.m_name);
	ui->eastingEdit->setText(QString::number(coord.m_easting, 'f', 3));
	ui->northingEdit->setText(QString::number(coord.m_northing, 'f', 3));
	ui->elevationEdit->setText(QString::number(coord.m_elevation, 'f', 3));

	Utils::DescriptionCombobox(this, ui->descriptionCombo, coord.m_desc);
	Utils::ClassificationCombobox(this, ui->classificationCombo, coord.m_class);

	auto validator = new QDoubleValidator(-10000000.0, 10000000.0, 3, this);
	validator->setNotation(QDoubleValidator::StandardNotation);

	ui->eastingEdit->setValidator(validator);
	ui->northingEdit->setValidator(validator);
	ui->elevationEdit->setValidator(validator);
}

EditCoordDlg::~EditCoordDlg()
{
	delete ui;
}

void EditCoordDlg::done(int r)
{
	if (QDialog::Accepted == r)
	{
		QString name = ui->nameEdit->text();
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
		m_coord.m_easting = ui->eastingEdit->text().toDouble();
		m_coord.m_northing = ui->northingEdit->text().toDouble();
		m_coord.m_elevation = ui->elevationEdit->text().toDouble();
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
