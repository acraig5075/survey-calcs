#include "glwidget.h"
#include "QPainter"
#include "QDebug"

PlotWidget::PlotWidget(QWidget *parent)
	: QWidget(parent)
{

}

void PlotWidget::SetOrtho(const QRectF &extents)
{
	m_extents = extents;
	m_hasExtents = true;
}

void PlotWidget::SetPointList(QVector<QPointF> &points)
{
	m_pointList.clear();
	m_pointList = points;
}

void PlotWidget::paintEvent(QPaintEvent *)
{
	if (m_hasExtents)
	{
		int wSide = static_cast<int>(qMax(m_extents.width(), m_extents.height()));
		QPointF wCenter = m_extents.center();
		int wLeft = static_cast<int>(wCenter.x()) - wSide / 2;
		int wTop = static_cast<int>(wCenter.y()) - wSide / 2;

		int vSide = std::min(width(), height());
		int vLeft = ((width() - vSide) / 2);
		int vTop = ((height() - vSide) / 2);

		QPainter painter(this);
		painter.setViewport(vLeft, vTop, vSide, vSide);
		painter.setWindow(wLeft, wTop, wSide, wSide);

		painter.fillRect(wLeft, wTop, wSide, wSide, Qt::lightGray);

		painter.setPen(Qt::blue);
		painter.setFont(QFont("Arial", 300));
		painter.drawText(rect(), Qt::AlignCenter, "Qt");

		if (!m_pointList.empty())
			painter.drawPoints(&m_pointList.at(0), m_pointList.size());
	}
}
