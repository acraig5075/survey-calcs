#ifndef PLANWIDGET_H
#define PLANWIDGET_H

#include <QWidget>

namespace Ui {
class PlanWidget;
}

class PlanTab : public QWidget
{
	Q_OBJECT

public:
	explicit PlanTab(QWidget *parent = 0);
	~PlanTab();

	QString GetStatus() const;

public slots:
	void on_w_loadButton_clicked();

private:
	Ui::PlanWidget *ui;
};

#endif // PLANWIDGET_H
