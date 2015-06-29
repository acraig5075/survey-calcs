#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "coordstab.h"
#include "stationstab.h"
#include "calcstab.h"
#include "plantab.h"
#include "QFileDialog"
#include "QDebug"
#include "QErrorMessage"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	m_db = QSqlDatabase::addDatabase("QSQLITE");

	m_pCoordsTab = new CoordsTab(this);
	m_pStationsTab = new StationsTab(this);
	m_pCalcsTab = new CalcsTab(this);
	m_pPlanTab = new PlanTab(this);

	ui->w_coordsLayout->addWidget(m_pCoordsTab);
	ui->w_stationsLayout->addWidget(m_pStationsTab);
	ui->w_calcsLayout->addWidget(m_pCalcsTab);
	ui->w_planLayout->addWidget(m_pPlanTab);

	connect(this, SIGNAL(databaseChanged()), m_pCoordsTab, SLOT(onLoad()));
	connect(this, SIGNAL(databaseChanged()), m_pStationsTab, SLOT(onLoad()));
	connect(this, SIGNAL(databaseChanged()), m_pCalcsTab, SLOT(onLoad()));
	connect(this, SIGNAL(databaseChanged()), m_pPlanTab, SLOT(onLoad()));

	connect(this, SIGNAL(databaseClosed()), m_pCoordsTab, SLOT(onClear()));
	connect(this, SIGNAL(databaseClosed()), m_pStationsTab, SLOT(onClear()));
	connect(this, SIGNAL(databaseClosed()), m_pCalcsTab, SLOT(onClear()));
	connect(this, SIGNAL(databaseClosed()), m_pPlanTab, SLOT(onClear()));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
	auto filename = QFileDialog::getOpenFileName(this,
		tr("Open File"), "", tr("sqlite3 database (*.sqlite)"));

	if (!filename.isEmpty())
	{
		if (m_db.isOpen())
			m_db.close();

		emit databaseClosed();

		m_db.setDatabaseName(filename);
		if (m_db.open())
		{
			emit databaseChanged();
		}
		else
		{
			QErrorMessage msg(this);
			msg.showMessage(QString("Could not open database %1").arg(filename));
			m_db.setDatabaseName("");
		}
	}
}

void MainWindow::on_actionClose_triggered()
{
	emit databaseClosed();
}
