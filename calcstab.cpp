#include "calcstab.h"
#include "ui_calcstab.h"
#include "Types/calc.h"
#include "Models/calcslistmodel.h"
#include "calcfactory.h"
#include "calcscontroller.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

CalcsTab::CalcsTab(CalcsController &calcsController, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::CalcsTab),
	m_calcsController(calcsController)
{
	ui->setupUi(this);

	m_pModel = new CalcsListModel(this);

	onClear();
}

CalcsTab::~CalcsTab()
{
	delete ui;
}

QString CalcsTab::GetStatus() const
{
	int rowCount = m_pModel->rowCount();
	return QString("%1 calculations").arg(rowCount);
}

void CalcsTab::onClear()
{
	m_pModel->clear();
	ui->w_listView->setStyleSheet("QListView { background: lightGray }");
	ui->addButton->setEnabled(false);
}

void CalcsTab::onLoad()
{
	QSqlDatabase db = QSqlDatabase::database();
	if (db.isOpen())
	{
		m_calcsController.Read();
		QStringList descList = m_calcsController.GetDescriptions();
		m_pModel->addDesc(descList);

		ui->w_listView->setModel(m_pModel);
		ui->w_listView->setStyleSheet("QListView { background: white }");
		ui->w_listView->show();
		ui->addButton->setEnabled(true);
	}
}

void CalcsTab::on_w_listView_doubleClicked(const QModelIndex &index)
{
	int i = index.row();

	if (m_calcsController.EditCalcAt(i, this))
	{
		QString desc = m_calcsController.GetDescriptionAt(i);

		m_pModel->editDesc(i, desc);
	}
}
