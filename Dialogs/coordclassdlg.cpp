#include "coordclassdlg.h"
#include "ui_coordclassdlg.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

CoordClassDlg::CoordClassDlg(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::CoordClassDlg)
{
	ui->setupUi(this);

	m_pModel = new QSqlQueryModel(this);

	ui->m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);

	Init();
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
