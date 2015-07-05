#include "glwidget.h"
#include <QtOpenGL>

GLWidget::GLWidget(QWidget *parent)
	: QGLWidget(parent)
{

}

void GLWidget::SetOrtho(const QRectF &extents, const QPointF &lookAt)
{
	m_extents = extents;
	m_lookAt = lookAt;
	initializeGL();
}

void GLWidget::SetPointList(const std::vector<QPointF> &points)
{
	m_pointList.clear();
	m_pointList = points;
}

void GLWidget::initializeGL()
{
	glClearColor(1, 1, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(m_extents.left(), m_extents.right(), m_extents.bottom(), m_extents.top(), -1.0, 1.0);
}

void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	glPointSize(0.2f);
	for (auto qp : m_pointList)
		glVertex2f(qp.x(), qp.y());
	glEnd();

}
