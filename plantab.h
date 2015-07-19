#ifndef PLANWIDGET_H
#define PLANWIDGET_H

#include <QWidget>

namespace Ui {
class PlanTab;
}

class PlanTab : public QWidget
{
	Q_OBJECT

public:
	explicit PlanTab(QWidget *parent = 0);
	~PlanTab();

	QString GetStatus() const;

public slots:
	void onClear();
	void onLoad();

private slots:
	void on_w_loadButton_clicked();

private:
	Ui::PlanTab *ui;
	int m_nPoints = 0;
};

#endif // PLANWIDGET_H
