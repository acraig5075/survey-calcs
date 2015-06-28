#include "stationstab.h"
#include "ui_stationstab.h"
#include "stationsquerymodel.h"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include "QtSql/QSqlError"
#include "QDebug"

StationsTab::StationsTab(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::StationsTab)
{
	ui->setupUi(this);
}

StationsTab::~StationsTab()
{
	delete ui;
}

void StationsTab::on_w_loadButton_clicked()
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("D:\\Data\\j216.sqlite");
	if (db.open())
	{
		QSqlQuery query(db);
		query.prepare("SELECT station AS Name, setupno AS Setup, insthgt AS `Instr. hgt`, date AS Date FROM occupied ORDER BY station, setupno");
		query.exec();

		auto pModel = new StationsQueryModel(this);
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
