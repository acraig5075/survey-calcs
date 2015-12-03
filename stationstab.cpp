#include "stationstab.h"
#include "ui_stationstab.h"
#include "Models/stationsquerymodel.h"
#include "Types/occupied.h"
#include "stationscontroller.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

StationsTab::StationsTab(StationsController &controller, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::StationsTab),
	m_stationsController(controller)
{
	ui->setupUi(this);
	m_pModel = new StationsQueryModel(this);
	ui->w_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

	onClear();

	connect(ui->w_tableView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(onDoubleClick(const QModelIndex&)));
	connect(this, SIGNAL(stationCountChanged()), parent, SLOT(onStatusTextChanged()));
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
	ui->w_tableView->setStyleSheet("QTableView { background: lightGray }");
	ui->addButton->setEnabled(false);
	ui->obsButton->setEnabled(false);
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

		int column = 0;
		for (auto label: StationsQueryModel::HorizontalHeaderList)
			m_pModel->setHeaderData(column++, Qt::Horizontal, label);

		ui->w_tableView->setModel(m_pModel);
		ui->w_tableView->setStyleSheet("QTableView { background: white }");
		ui->w_tableView->show();
		ui->addButton->setEnabled(true);
		ui->obsButton->setEnabled(true);
	}
}

void StationsTab::on_obsButton_clicked()
{
	QStringList selNames;
	QItemSelectionModel *selection = ui->w_tableView->selectionModel();
	if (selection)
	{
		QModelIndexList selRows = selection->selectedRows();
		if (selRows.size() == 1)
		{
			QSqlRecord record = m_pModel->record(selRows.first().row());

			Occupied station(record);

			m_stationsController.ShowObservations(this, station);
		}
	}
}

void StationsTab::onDoubleClick(const QModelIndex& index)
{
	QSqlRecord record = m_pModel->record(index.row());

	Occupied station(record);

	if (m_stationsController.EditStation(this, station))
	{
		m_pModel->query().exec();
	}
}

void StationsTab::on_addButton_clicked()
{
	Occupied station;

	if (m_stationsController.AddStation(this, station))
	{
		m_pModel->setQuery(StationsQueryModel::ModelQueryString);

		emit stationCountChanged();
	}
}
