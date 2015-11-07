#include "coordstab.h"
#include "ui_coordstab.h"
#include "coordquerymodel.h"
#include "coordscontroller.h"
#include "coord.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QMenu>
#include <QSqlRecord>
#include <QStringList>

CoordsTab::CoordsTab(CoordsController &coordsController, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::CoordsTab),
	m_coordsController(coordsController)
{
	ui->setupUi(this);
	m_pModel = new CoordQueryModel(this);

	ui->w_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->w_tableView->setContextMenuPolicy(Qt::CustomContextMenu);

	connect(ui->w_tableView, SIGNAL(customContextMenuRequested(QPoint)), SLOT(onCustomContextMenuRequested(QPoint)));
	connect(ui->w_tableView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(onDoubleClick(const QModelIndex&)));
	connect(this, SIGNAL(coordPlotChanged()), parent, SLOT(onPlanViewChanged()));
}


CoordsTab::~CoordsTab()
{
	delete ui;
}

QString CoordsTab::GetStatus() const
{
	int rowCount = m_pModel->rowCount();
	return QString("%1 coordinates").arg(rowCount);
}

void CoordsTab::onClear()
{
	m_pModel->clear();
	ui->w_tableView->setModel(nullptr);
}

void CoordsTab::onLoad()
{
	QSqlDatabase db = QSqlDatabase::database();
	if (db.isOpen())
	{
		QSqlQuery query(db);
		query.prepare(CoordQueryModel::ModelQueryString);
		query.exec();

		m_pModel->setQuery(query);
		while (m_pModel->canFetchMore())
			m_pModel->fetchMore();

		if (m_pModel->lastError().isValid())
			qDebug() << m_pModel->lastError();

		ui->w_tableView->setModel(m_pModel);
		ui->w_tableView->show();
	}
}

void CoordsTab::on_w_loadButton_clicked()
{
	onLoad();
}

void CoordsTab::onCustomContextMenuRequested(QPoint pos)
{
	QMenu *menu = new QMenu(this);
	QAction *togglePlotAction = new QAction("Toggle Plot on/off", this);

	menu->addAction(togglePlotAction);
	menu->popup(ui->w_tableView->viewport()->mapToGlobal(pos));

	connect(togglePlotAction, SIGNAL(triggered()), this, SLOT(onTogglePlot()));
}

void CoordsTab::onTogglePlot()
{
	// Get selected point names
	QStringList selNames;
	QItemSelectionModel *selection = ui->w_tableView->selectionModel();
	if (selection)
	{
		QModelIndexList selRows = selection->selectedRows();
		for (QModelIndex index : selRows)
		{
			QSqlRecord record = m_pModel->record(index.row());
			QString name = record.value("Name").toString();
			selNames.push_back(QString("'%1'").arg(name));
		}
	}

	// Update table with toggled plot field
	if (!selNames.isEmpty())
	{
		QSqlDatabase db = QSqlDatabase::database();
		if (db.isOpen())
		{
			QString update = QString("UPDATE coord SET plot = (CASE WHEN plot IS NULL THEN '1' ELSE NULL END) WHERE name IN (%1)").arg(selNames.join(','));

			QSqlQuery query(db);
			query.prepare(update);
			bool ok = query.exec();

			qDebug() << "Update query returned " << ok;
			if (!ok)
				qDebug() << query.lastError();

			m_pModel->query().exec();

			emit coordPlotChanged();
		}
	}
}

void CoordsTab::onDoubleClick(const QModelIndex& index)
{
	QSqlRecord record = m_pModel->record(index.row());

	Coord coord(record);

	if (m_coordsController.EditCoord(this, coord))
	{
		m_pModel->query().exec();
	}
}
