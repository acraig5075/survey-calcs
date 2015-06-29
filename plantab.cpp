#include "plantab.h"
#include "ui_plantab.h"
#include "QSqlDatabase"
#include "QSqlQuery"
#include "QDebug"

PlanTab::PlanTab(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::PlanWidget)
{
	ui->setupUi(this);
}

PlanTab::~PlanTab()
{
	delete ui;
}

void PlanTab::on_w_loadButton_clicked()
{
	QSqlDatabase db = QSqlDatabase::database();
	if (db.isOpen())
	{
		QSqlQuery query(db);
		query.prepare("SELECT MIN(y) AS lowEasting, MAX(y) AS highEasting, MIN(x) AS lowNorthing, MAX(x) AS highNorthing, AVG(y) AS midEasting, AVG(x) AS midNorthing FROM coord");
		query.exec();

		if (query.first())
		{
			QRectF bounds;
			bounds.setTop(query.value("lowNorthing").toReal());
			bounds.setLeft(query.value("highEasting").toReal());
			bounds.setRight(query.value("lowEasting").toReal());
			bounds.setBottom(query.value("highNorthing").toReal());

			QPointF center;
			center.setX(query.value("midEasting").toReal());
			center.setY(query.value("midNorthing").toReal());

			ui->w_glWidget->SetOrtho(bounds, center);
		}
	}

}
