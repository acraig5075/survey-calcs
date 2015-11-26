#include "coordstab.h"
#include "ui_coordstab.h"
#include "coordscontroller.h"
#include "Models/coordquerymodel.h"
#include "Types/coord.h"
#include "utils.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QMenu>
#include <QSqlRecord>
#include <QStringList>
#include <QMessageBox>


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
	connect(this, SIGNAL(coordCountChanged()), parent, SLOT(onStatusTextChanged()));
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
	QAction *deleteAction = new QAction("Delete", this);

	menu->addAction(togglePlotAction);
	menu->addAction(deleteAction);
	menu->popup(ui->w_tableView->viewport()->mapToGlobal(pos));

	connect(togglePlotAction, SIGNAL(triggered()), this, SLOT(onTogglePlot()));
	connect(deleteAction, SIGNAL(triggered()), this, SLOT(onDelete()));
}

void CoordsTab::OperateOnSelection(std::function<QString(const QStringList &)> operationQuery, const QString &confirmMsg)
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

	// Perform sql operation on table
	if (!selNames.isEmpty() && (confirmMsg.isEmpty() || QMessageBox::Yes == QMessageBox::question(this, "Confirm", confirmMsg, QMessageBox::Yes | QMessageBox::No, QMessageBox::No)))
	{
		QSqlDatabase db = QSqlDatabase::database();
		if (db.isOpen())
		{
			QString update = operationQuery(selNames);

			QSqlQuery query(db);
			query.prepare(update);
			Utils::ExecQuery(query);

			m_pModel->setQuery(CoordQueryModel::ModelQueryString); // m_pModel->query()->exec() caused empty rows after underlying db had a delete performed on it. ???

			emit coordPlotChanged();
		}
	}
}

void CoordsTab::onTogglePlot()
{
	OperateOnSelection([](const QStringList &names) -> QString
	{
		return QString("UPDATE coord SET plot = (CASE WHEN plot IS NULL THEN '1' ELSE NULL END) WHERE name IN (%1)").arg(names.join(','));
	});
}

void CoordsTab::onDelete()
{
	OperateOnSelection([](const QStringList &names) -> QString
	{
		return QString("DELETE FROM coord WHERE name IN (%1)").arg(names.join(','));
	}, "Are you sure you want to delete the selected coordinates?");

	emit coordCountChanged();
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
