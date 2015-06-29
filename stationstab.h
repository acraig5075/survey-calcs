#ifndef STATIONSTAB_H
#define STATIONSTAB_H

#include <QWidget>

class StationsQueryModel;

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
	void onClear();
	void onLoad();

public slots:
	void on_w_loadButton_clicked();

private:
	Ui::StationsTab *ui;
	StationsQueryModel *m_pModel;
};

#endif // STATIONSTAB_H
