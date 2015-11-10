//#include "selectcoorddlg.h"
//#include "ui_selectcoorddlg.h"
//#include <QSqlRecord>
//#include <QSqlQueryModel>


//SelectBaseDlg::SelectBaseDlg(QWidget *parent, bool multiSelection) :
//	QDialog(parent),
//	ui(new Ui::SelectCoordDlg)
//{
//	ui->setupUi(this);

//	ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
//	if (multiSelection)
//		ui->tableView->setSelectionMode(QAbstractItemView::MultiSelection);
//	else
//		ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
//}

//SelectBaseDlg::~SelectBaseDlg()
//{
//	delete ui;
//}

//void SelectBaseDlg::on_SelectBaseDlg_accepted()
//{
//	// Get selected point names
//	QItemSelectionModel *selection = ui->tableView->selectionModel();
//	if (selection)
//	{
//		QModelIndexList selRows = selection->selectedRows();
//		for (QModelIndex index : selRows)
//		{
//			QSqlRecord record = m_pModel->record(index.row());
//			AddToSelection(record);
//		}
//	}
//}

//void SelectBaseDlg::on_SelectBaseDlg_rejected()
//{
//	ClearSelection();
//}





//template<typename T, typename U>
//SelectionDlg<T, U>::SelectionDlg(QWidget *parent, bool multiSelection)
//	: SelectBaseDlg(parent, multiSelection)
//{
//	m_pModel = new U(this);
//	m_pModel->setQuery(U::ModelQueryString);
//	ui->tableView->setModel(m_pModel);
//	ui->tableView->setColumnHidden(1, true); // y
//	ui->tableView->setColumnHidden(2, true); // x
//	ui->tableView->setColumnHidden(3, true); // z
//	ui->tableView->setColumnHidden(6, true); // plot
//}

//template<typename T, typename U>
//void SelectionDlg<T, U>::AddToSelection(const QSqlRecord &record)
//{
//	m_selection.push_back(T(record));
//}

//template<typename T, typename U>
//void SelectionDlg<T, U>::ClearSelection()
//{
//	m_selection.clear();
//}

//template<typename T, typename U>
//T SelectionDlg<T, U>::GetSingleSelection() const
//{
//	if (m_selection.isEmpty())
//		return T();
//	else
//		return m_selection.at(0);
//}

//template<typename T, typename U>
//QVector<T> SelectionDlg<T, U>::GetMultiSelection() const
//{
//	return m_selection;
//}

