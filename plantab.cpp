#include "plantab.h"
#include "ui_plantab.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QVector>

PlanTab::PlanTab(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::PlanTab)
{
	ui->setupUi(this);
}

PlanTab::~PlanTab()
{
	delete ui;
}

QString PlanTab::GetStatus() const
{
	if (m_nPoints <= 0)
		return QString("View ready");
	else
		return QString("%1 points").arg(m_nPoints);
}

void PlanTab::onClear()
{
	m_nPoints = 0;
}

namespace
{
Qt::GlobalColor MatchingColor(const QString &ptype)
{
	if (ptype == "DR" || ptype == "SR" || ptype == "Ts")
		return Qt::red;
	else if (ptype == "Db" || ptype == "Sb")
		return Qt::blue;
	else if (ptype == "DG" || ptype == "SG")
		return Qt::green;
	else
		return Qt::black;
}
}

void PlanTab::onLoad()
{
	m_nPoints = 0;

	QSqlDatabase db = QSqlDatabase::database();
	if (db.isOpen())
	{
		QString whereFilter = "WHERE plot IS NOT NULL";

		QSqlQuery query1(db);
		query1.prepare(QString("SELECT MIN(y) AS lowEasting, MAX(y) AS highEasting, MIN(x) AS lowNorthing, MAX(x) AS highNorthing FROM coord %1").arg(whereFilter));
		query1.exec();

		if (query1.first())
		{
			QRectF bounds;
			bounds.setTop(query1.value("highNorthing").toReal());
			bounds.setLeft(query1.value("lowEasting").toReal());
			bounds.setRight(query1.value("highEasting").toReal());
			bounds.setBottom(query1.value("lowNorthing").toReal());

			ui->w_plotWidget->SetOrtho(bounds);
		}

		QSqlQuery query2(db);
		query2.prepare(QString("SELECT coord.y AS easting, coord.x AS northing, class.ptype FROM coord INNER JOIN class ON coord.class = class.class %1").arg(whereFilter));
		query2.exec();

		QVector<QPair<QPointF, Qt::GlobalColor>> points;

		while (query2.next())
		{
			QString ptype = query2.value("ptype").toString();
			Qt::GlobalColor color = MatchingColor(ptype);

			QPointF p;
			p.setX(query2.value("easting").toReal());
			p.setY(query2.value("northing").toReal());

			points.push_back(qMakePair(p, color));
		}

		m_nPoints = points.size();

		ui->w_plotWidget->SetPointList(points);
	}
}

void PlanTab::on_w_loadButton_clicked()
{
	onLoad();
}
