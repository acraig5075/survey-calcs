#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "QWidget"
#include "QVector"

class GLWidget : public QWidget
{
	Q_OBJECT

public:
	GLWidget(QWidget *parent = 0);

	void SetOrtho(const QRectF &extents, const QPointF &lookAt);
	void SetPointList(QVector<QPointF> &points);

	void paintEvent(QPaintEvent *);
private:
	QRectF m_extents;
	QPointF m_lookAt;
	QVector<QPointF> m_pointList;
};

#endif // GLWIDGET_H
