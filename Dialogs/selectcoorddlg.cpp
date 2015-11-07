#include "selectcoorddlg.h"
#include "ui_selectcoorddlg.h"
#include "coordquerymodel.h"
#include <QSqlRecord>

SelectCoordDlg::SelectCoordDlg(QWidget *parent, bool multiSelection) :
	QDialog(parent),
	ui(new Ui::SelectCoordDlg)
{
	ui->setupUi(this);

	m_pModel = new CoordQueryModel(this);
	m_pModel->setQuery(CoordQueryModel::ModelQueryString);
	ui->tableView->setModel(m_pModel);
	ui->tableView->setColumnHidden(1, true); // y
	ui->tableView->setColumnHidden(2, true); // x
	ui->tableView->setColumnHidden(3, true); // z
	ui->tableView->setColumnHidden(6, true); // plot

	ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	if (multiSelection)
		ui->tableView->setSelectionMode(QAbstractItemView::MultiSelection);
	else
		ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
}

SelectCoordDlg::~SelectCoordDlg()
{
	delete ui;
}

void SelectCoordDlg::on_SelectCoordDlg_accepted()
{
	// Get selected point names
	QItemSelectionModel *selection = ui->tableView->selectionModel();
	if (selection)
	{
		QModelIndexList selRows = selection->selectedRows();
		for (QModelIndex index : selRows)
		{
			QSqlRecord record = m_pModel->record(index.row());
			m_selCoords.push_back(Coord(record));
		}
	}
}

void SelectCoordDlg::on_SelectCoordDlg_rejected()
{
	m_selCoords.clear();
}

Coord SelectCoordDlg::GetSingleSelection() const
{
	if (m_selCoords.isEmpty())
		return Coord();
	else
		return m_selCoords.at(0);
}

QVector<Coord> SelectCoordDlg::GetMultiSelection() const
{
	return m_selCoords;
}

