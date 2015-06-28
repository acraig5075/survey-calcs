#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calc.h"
#include "calcfactory.h"
#include "stationstab.h"
#include "plantab.h"
#include "calcslistmodel.h"
#include "coordquerymodel.h"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include "QtSql/QSqlQueryModel"
#include "QtSql/QSqlError"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	auto pStationsTab = new StationsTab(this);
	ui->w_stationsLayout->addWidget(pStationsTab);
	auto pPlanTab = new PlanTab(this);
	ui->w_planLayout->addWidget(pPlanTab);
}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::on_w_loadButton_clicked()
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("D:\\Data\\j216.sqlite");
	if (db.open())
	{
		QSqlQuery query(db);
		query.prepare("SELECT name AS Name, y AS Y, x AS X, h AS H, desc AS Desc FROM coord ORDER BY class, name");
		query.exec();

		auto pModel = new CoordQueryModel(this);
		pModel->setQuery(query);
		if (pModel->lastError().isValid())
			qDebug() << pModel->lastError();

		ui->w_tableView->setModel(pModel);
		ui->w_tableView->show();
		db.close();
	}
	else
		qDebug() << "Failed to open QSqlDatabase";
}

void MainWindow::on_w_loadButton_2_clicked()
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("D:\\Data\\j216.sqlite");
	if (db.open())
	{
		QSqlQuery query(db);
		query.prepare("SELECT type FROM calcs ORDER BY `order`");
		query.exec();

		QStringList descList;
		while (query.next())
		{
			int calcType = query.value("type").toInt();
			auto pCalc = CalcFactory::Instance(calcType);
			descList.push_back(pCalc->desc());
			delete pCalc;
		}

		auto pModel = new CalcsListModel(this);
		pModel->addDesc(descList);
		ui->w_listView->setModel(pModel);
		ui->w_listView->show();
		db.close();
	}
	else
		qDebug() << "Failed to open QSqlDatabase";

}
