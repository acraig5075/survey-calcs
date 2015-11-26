#include "tabledlg.h"
#include "ui_tabledlg.h"
#include "Types/Observation.h"
#include "stationscontroller.h"
#include "Models/observationsquerymodel.h"


TableBaseDlg::TableBaseDlg(const QString &caption, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::TableBaseDlg)
{
	ui->setupUi(this);

	setWindowTitle(caption);

	ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
}

TableBaseDlg::~TableBaseDlg()
{
	delete ui;
}


void TableBaseDlg::on_addButton_clicked()
{
	AddRow();
}


/***************************************************************************/



template <typename Type, typename Controller, typename Model>
TableDlg<Type, Controller, Model>::TableDlg(Controller &controller, const QString &caption, const QString &query, QWidget *parent)
	: TableBaseDlg(caption, parent)
	, m_controller(controller)
{
	m_pModel = new Model(this);
	m_pModel->setQuery(query);
	ui->tableView->setModel(m_pModel);
}

template <typename Type, typename Controller, typename Model>
bool TableDlg<Type, Controller, Model>::AddRow()
{
	return false; //return m_controller.Add();
}

// explicit instantiations
template class TableDlg<Observation, StationsController, ObservationsQueryModel>;
