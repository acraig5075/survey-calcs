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

void GLWidget::initializeGL()
{
	glClearColor(1, 1, 0, 1);
	glOrtho(m_extents.left(), m_extents.right(), m_extents.bottom(), m_extents.top(), -1.0, 1.0);
	//gluLookAt();

}

void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
