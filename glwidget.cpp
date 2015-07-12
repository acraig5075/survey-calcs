#include "glwidget.h"
#include "QPainter"

GLWidget::GLWidget(QWidget *parent)
	: QWidget(parent)
{

}

void GLWidget::SetOrtho(const QRectF &extents, const QPointF &lookAt)
{
	m_extents = extents;
	m_lookAt = lookAt;

	int wSide = static_cast<int>(qMax(extents.width(), extents.height()));
	QPointF wCenter = extents.center();
	int wLeft = static_cast<int>(wCenter.x()) + wSide / 2;
	int wTop = static_cast<int>(wCenter.y()) - wSide / 2;

	int vSide = std::min(width(), height());
	int vLeft = (width() - vSide / 2);
	int vTop = (height() - vSide / 2);

	QPainter painter(this);
	painter.setWindow(wLeft, wTop, wSide, wSide);
	painter.setViewport(vLeft, vTop, vSide, vSide);
}

void GLWidget::SetPointList(QVector<QPointF> &points)
{
	m_pointList.clear();
	m_pointList = points;
}

void GLWidget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.setPen(Qt::blue);
	painter.setFont(QFont("Arial", 30));
	painter.drawText(rect(), Qt::AlignCenter, "Qt");

	if (!m_pointList.empty())
		painter.drawPoints(&m_pointList.at(0), m_pointList.size());
}
