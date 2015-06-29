#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QSqlDatabase"

class CoordsTab;
class StationsTab;
class CalcsTab;
class PlanTab;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();


private slots:
	void on_actionOpen_triggered();

	void on_actionClose_triggered();

signals:
	void databaseChanged();
	void databaseClosed();

private:
	Ui::MainWindow *ui;
	QSqlDatabase m_db;
	CoordsTab *m_pCoordsTab;
	StationsTab *m_pStationsTab;
	CalcsTab *m_pCalcsTab;
	PlanTab *m_pPlanTab;
};

#endif // MAINWINDOW_H
