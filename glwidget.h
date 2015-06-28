#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

class GLWidget : public QGLWidget
{
	Q_OBJECT

public:
	GLWidget(QWidget *parent = 0);

	void SetOrtho(const QRectF &extents, const QPointF &lookAt);
	void initializeGL() override;
	void paintGL() override;
	//void resizeGL(int w, int h) override;

private:
	QRectF m_extents;
	QPointF m_lookAt;
};

#endif // GLWIDGET_H
