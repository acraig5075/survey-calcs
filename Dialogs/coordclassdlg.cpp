#include "coordclassdlg.h"
#include "ui_coordclassdlg.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QItemSelection>

CoordClassDlg::CoordClassDlg(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::CoordClassDlg)
{
	ui->setupUi(this);

	m_pModel = new QSqlQueryModel(this);

	ui->m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);

	Init();

	connect(ui->m_tableView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), SLOT(onSelectionChanged(QItemSelection,QItemSelection)));
}

CoordClassDlg::~CoordClassDlg()
{
	delete ui;
}

void CoordClassDlg::Init()
{
	QSqlDatabase db = QSqlDatabase::database();
	if (db.isOpen())
	{
		QSqlQuery query(db);
		query.prepare("SELECT class AS Abbreviation, description AS Description, ptype AS 'Plot type' FROM class ORDER BY 'order', class");
		query.exec();

		m_pModel->setQuery(query);
		while (m_pModel->canFetchMore())
			m_pModel->fetchMore();

		if (m_pModel->lastError().isValid())
			qDebug() << m_pModel->lastError();

		ui->m_tableView->setModel(m_pModel);
		ui->m_tableView->show();
	}
}

void CoordClassDlg::onSelectionChanged(const QItemSelection & /*selected*/, const QItemSelection & /*deselected*/)
{
	QItemSelectionModel *selection = ui->m_tableView->selectionModel();
	if (selection)
	{
		bool canMoveUp = false;
		bool canMoveDown = false;

		QModelIndexList selRows = selection->selectedRows();
		if (selRows.size() == 1)
		{
			QModelIndex modelIndex = selRows.at(0);
			if (modelIndex.row() > 0)
				canMoveUp = true;
			if (modelIndex.row() < this->m_pModel->rowCount() - 1)
				canMoveDown = true;
		}

		ui->m_upButton->setEnabled(canMoveUp);
		ui->m_downButton->setEnabled(canMoveDown);
	}
}
