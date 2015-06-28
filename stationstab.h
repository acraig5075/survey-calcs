#ifndef STATIONSTAB_H
#define STATIONSTAB_H

#include <QWidget>

namespace Ui {
class StationsTab;
}

class StationsTab : public QWidget
{
	Q_OBJECT

public:
	explicit StationsTab(QWidget *parent = 0);
	~StationsTab();

private slots:
	void on_w_loadButton_clicked();

private:
	Ui::StationsTab *ui;
};

#endif // STATIONSTAB_H
