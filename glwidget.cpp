#include "glwidget.h"
#include <QPainter>
#include <QDebug>

PlotWidget::PlotWidget(QWidget *parent)
	: QWidget(parent)
{

}

void PlotWidget::SetOrtho(const QRectF &extents)
{
	m_extents = extents;
	m_hasExtents = true;
}

namespace
{
using PointPair = QPair<QPointF, Qt::GlobalColor>;

bool SortByColor(const PointPair &a, const PointPair &b)
{
	return a.second < b.second;
}

}

void PlotWidget::SetPointList(QVector<QPair<QPointF, Qt::GlobalColor>> &points)
{
	m_pointList.clear();
	m_pointList = points;
	qSort(m_pointList.begin(), m_pointList.end(), SortByColor);
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

		Qt::GlobalColor currentColor = Qt::black;
		for (const QPair<QPointF, Qt::GlobalColor> &p : m_pointList)
		{
			if (p.second != currentColor)
			{
				currentColor = p.second;
				painter.setPen(currentColor);
			}
			painter.drawPoint(p.first);
		}
	}
}
