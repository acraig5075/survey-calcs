#include "stationstab.h"
#include "ui_stationstab.h"
#include "stationsquerymodel.h"
#include "occupied.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

StationsTab::StationsTab(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::StationsTab)
{
	ui->setupUi(this);
	m_pModel = new StationsQueryModel(this);
	ui->w_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

	connect(ui->w_tableView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(onDoubleClick(const QModelIndex&)));
}

StationsTab::~StationsTab()
{
	delete ui;
}

QString StationsTab::GetStatus() const
{
	int rowCount = m_pModel->rowCount();
	return QString("%1 stations").arg(rowCount);
}

void StationsTab::onClear()
{
	m_pModel->clear();
	ui->w_tableView->setModel(nullptr);
}

void StationsTab::onLoad()
{
	QSqlDatabase db = QSqlDatabase::database();
	if (db.isOpen())
	{
		QSqlQuery query(db);
		query.prepare(StationsQueryModel::ModelQueryString);
		query.exec();

		m_pModel->setQuery(query);
		if (m_pModel->lastError().isValid())
			qDebug() << m_pModel->lastError();

		ui->w_tableView->setModel(m_pModel);
		ui->w_tableView->show();
	}
}

void StationsTab::on_w_loadButton_clicked()
{
	onLoad();
}

void StationsTab::onDoubleClick(const QModelIndex& index)
{
	QSqlRecord record = m_pModel->record(index.row());

	Occupied station(record);

}
