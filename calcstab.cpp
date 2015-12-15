#include "calcstab.h"
#include "ui_calcstab.h"
#include "Types/calc.h"
#include "Models/calcslistmodel.h"
#include "calcfactory.h"
#include "calcscontroller.h"
#include "calctypes.h"
#include "utils.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QMenu>

CalcsTab::CalcsTab(CalcsController &calcsController, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::CalcsTab),
	m_calcsController(calcsController)
{
	ui->setupUi(this);

	m_pModel = new CalcsListModel(this);

	QMenu *menu = new QMenu(this);
	QAction *joinAction = new QAction("Join", this);
	QAction *dpolarAction = new QAction("Double Polar", this);
	menu->addAction(joinAction);
	menu->addAction(dpolarAction);

	ui->addButton->setMenu(menu);

	onClear();

	connect(this, SIGNAL(calcsCountChanged()), parent, SLOT(onStatusTextChanged()));
	connect(joinAction, SIGNAL(triggered()), this, SLOT(onAddJoin()));
	connect(dpolarAction, SIGNAL(triggered()), this, SLOT(onAddDPolar()));
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
	m_calcsController.clear();
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

template <typename T>
bool CreateTableIfNotExists()
{
	return Utils::ExecQuery(T::SqlCreateQuery);
}

template <typename T>
void CalcsTab::Add(QWidget *parent)
{
	if (m_calcsController.Add<T>(parent))
	{
		size_t count = m_calcsController.numCalcs();
		QString desc = m_calcsController.GetDescriptionAt(count - 1);

		m_pModel->addDesc(desc);
		emit calcsCountChanged();
		QModelIndex index = m_pModel->index(m_pModel->rowCount() - 1, 0);

		ui->w_listView->setFocus();
		ui->w_listView->scrollToBottom();
		ui->w_listView->selectionModel()->select(index, QItemSelectionModel::ClearAndSelect);
	}
}

void CalcsTab::onAddJoin()
{
	Add<JoinsCalc>(this);
}

void CalcsTab::onAddDPolar()
{
	Add<DpObsCalc>(this);
}
