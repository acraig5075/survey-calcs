#include "plantab.h"
#include "ui_plantab.h"
#include "QSqlDatabase"
#include "QSqlQuery"
#include "QDebug"
#include <QVector>

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

QString PlanTab::GetStatus() const
{
	return QString("View ready");
}

void PlanTab::on_w_loadButton_clicked()
{
	QSqlDatabase db = QSqlDatabase::database();
	if (db.isOpen())
	{
		QSqlQuery query1(db);
		query1.prepare("SELECT MIN(y) AS lowEasting, MAX(y) AS highEasting, MIN(x) AS lowNorthing, MAX(x) AS highNorthing, AVG(y) AS midEasting, AVG(x) AS midNorthing FROM coord");
		query1.exec();

		if (query1.first())
		{
			QRectF bounds;
			bounds.setTop(query1.value("lowNorthing").toReal());
			bounds.setLeft(query1.value("highEasting").toReal());
			bounds.setRight(query1.value("lowEasting").toReal());
			bounds.setBottom(query1.value("highNorthing").toReal());

			QPointF center;
			center.setX(query1.value("midEasting").toReal());
			center.setY(query1.value("midNorthing").toReal());

			ui->w_glWidget->SetOrtho(bounds, center);
		}

		QSqlQuery query2(db);
		query2.prepare("SELECT y AS easting, x AS northing FROM coord");
		query2.exec();

		QVector<QPointF> points;

		while (query2.next())
		{
			QPointF p;
			p.setX(query2.value("easting").toReal());
			p.setY(query2.value("northing").toReal());
			points.push_back(p);
		}

		ui->w_glWidget->SetPointList(points);
		qDebug() << points.size() << " points copied to glWindow";
	}

}
