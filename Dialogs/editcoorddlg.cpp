#include "editcoorddlg.h"
#include "ui_editcoorddlg.h"
#include "coord.h"
#include "coordscontroller.h"
#include <QStringListModel>
#include <functional>

namespace
{
	int IndexOf(const QStringList &list, const QString &str)
	{
		if (list.contains(str))
			return list.indexOf(str);
		return -1;
	}

	void ComboboxSelection(QWidget *parent, const CoordsController &controller, QStringList (CoordsController::*func)() const, QComboBox *comboBox, const std::string &initial)
	{
		auto stringList = (controller.*func)();
		auto stringModel = new QStringListModel(stringList, parent);
		comboBox->setModel(stringModel);
		comboBox->setCurrentIndex(IndexOf(stringList, QString::fromStdString(initial)));
	}
}

EditCoordDlg::EditCoordDlg(QWidget *parent, Coord &coord, const CoordsController &controller) :
	QDialog(parent),
	ui(new Ui::EditCoordDlg),
	m_coord(coord)
{
	ui->setupUi(this);

	ui->nameEdit->setText(QString::fromStdString(coord.m_name));
	ui->eastingEdit->setText(QString::number(coord.m_easting, 'f', 3));
	ui->northingEdit->setText(QString::number(coord.m_northing, 'f', 3));
	ui->elevationEdit->setText(QString::number(coord.m_elevation, 'f', 3));

	ComboboxSelection(this, controller, &CoordsController::GetDescriptionList, ui->descriptionCombo, coord.m_desc);
	ComboboxSelection(this, controller, &CoordsController::GetClassificationList, ui->classificationCombo, coord.m_class);

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

void EditCoordDlg::on_buttonBox_accepted()
{
	m_coord.m_name = ui->nameEdit->text().toStdString();
	m_coord.m_easting = ui->eastingEdit->text().toDouble();
	m_coord.m_northing = ui->northingEdit->text().toDouble();
	m_coord.m_elevation = ui->elevationEdit->text().toDouble();
	m_coord.m_desc = ui->descriptionCombo->currentText().toStdString();
	m_coord.m_class = ui->classificationCombo->currentText().toStdString();
}
