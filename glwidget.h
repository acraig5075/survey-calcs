#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <QVector>

class PlotWidget : public QWidget
{
	Q_OBJECT

public:
	PlotWidget(QWidget *parent = 0);

	void SetOrtho(const QRectF &extents);
	void SetPointList(QVector<QPair<QPointF, Qt::GlobalColor> > &points);

	void paintEvent(QPaintEvent *);
private:
	bool m_hasExtents = false;
	QRectF m_extents;
	QPointF m_lookAt;
	QVector<QPair<QPointF, Qt::GlobalColor>> m_pointList;
};

#endif // GLWIDGET_H
