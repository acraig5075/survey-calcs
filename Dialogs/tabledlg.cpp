#include "tabledlg.h"
#include "ui_tabledlg.h"
#include "Types/Observation.h"
#include "Types/desc.h"
#include "stationscontroller.h"
#include "Models/observationsquerymodel.h"
#include "Models/descquerymodel.h"
#include <QSqlQuery>
#include <QMenu>
#include <QMessageBox>


TableBaseDlg::TableBaseDlg(const QString &caption, const QString &query, bool stretch, QWidget *parent) :
	QDialog(parent),
	m_query(query),
	ui(new Ui::TableBaseDlg)
{
	ui->setupUi(this);

	setWindowTitle(caption);

	ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
	ui->tableView->horizontalHeader()->setStretchLastSection(stretch);
	ui->tableView->setStyleSheet("QTableView { background: lightGray }"
								 "QTableView::item { background-color: white }"
								 "QTableView::item:selected { background-color: rgb(0,140,255) }");
}

TableBaseDlg::~TableBaseDlg()
{
	delete ui;
}


void TableBaseDlg::on_addButton_clicked()
{
	if (AddRow())
		m_pModel->setQuery(m_query);
}

void TableBaseDlg::on_tableView_customContextMenuRequested(const QPoint &pos)
{
	QMenu *menu = new QMenu(this);
	QAction *deleteAction = new QAction("Delete", this);

	menu->addAction(deleteAction);
	menu->popup(ui->tableView->viewport()->mapToGlobal(pos));

	connect(deleteAction, SIGNAL(triggered()), this, SLOT(onDelete()));
}

void TableBaseDlg::onDelete()
{
	bool refresh = false;
	QItemSelectionModel *selection = ui->tableView->selectionModel();
	if (selection)
	{
		QModelIndexList selRows = selection->selectedRows();
		if (!selRows.empty())
		{
			QString confirmMsg = "Are you sure you want to delete the selected row(s)?";
			if (QMessageBox::Yes == QMessageBox::question(this, "Confirm", confirmMsg, QMessageBox::Yes | QMessageBox::No, QMessageBox::No))
			{
				for (QModelIndex index : selRows)
				{
					QSqlRecord record = m_pModel->record(index.row());
					if (DeleteRow(record))
						refresh = true;
					else
						break;
				}
			}
		}
	}

	if (refresh)
		m_pModel->setQuery(m_query);
}

void TableBaseDlg::on_tableView_doubleClicked(const QModelIndex &index)
{
	QSqlRecord record = m_pModel->record(index.row());

	if (EditRow(record))
		m_pModel->setQuery(m_query);
}


/***************************************************************************/



template <typename Type, typename Model>
TableDlg<Type, Model>::TableDlg(const Type &type, const QString &caption, const QString &query, bool stretch, QWidget *parent)
	: TableBaseDlg(caption, query, stretch, parent)
	, m_type(type)
{
	m_pModel = new Model(this);
	m_pModel->setQuery(query);

	int column = 0;
	for (auto label: Model::HorizontalHeaderList)
		m_pModel->setHeaderData(column++, Qt::Horizontal, label);

	ui->tableView->setModel(m_pModel);
}

template <typename Type, typename Model>
bool TableDlg<Type, Model>::AddRow()
{
	Type type(m_type);
	return type.Add(this);
}

template <typename Type, typename Model>
bool TableDlg<Type, Model>::EditRow(QSqlRecord &record)
{
	Type type(m_type);
	type.SetFrom(record);
	return type.Edit(this);
}

template <typename Type, typename Model>
bool TableDlg<Type, Model>::DeleteRow(QSqlRecord &record)
{
	Type type(m_type);
	type.SetFrom(record);
	return type.Delete();
}


/***************************************************************************/

// explicit instantiations
template class TableDlg<Observation, ObservationsQueryModel>;
template class TableDlg<Desc, DescQueryModel>;
