#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QLabel>
#include <QPair>

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

	void writePositionSettings();
	void readPositionSettings();
protected:
	void closeEvent(QCloseEvent *);

public slots:
	void onPlanViewChanged();

private slots:
	void on_actionOpen_triggered();
	void on_actionClose_triggered();
	void on_w_tabs_currentChanged(int index);
	void on_actionExit_triggered();
	void onCloseDatabase();

signals:
	void databaseChanged();
	void databaseClosed();
	void updatePlanView();

private:
	Ui::MainWindow *ui;
	QSqlDatabase m_db;
	QPair<QString, QString> m_filenames;
	CoordsTab *m_pCoordsTab;
	StationsTab *m_pStationsTab;
	CalcsTab *m_pCalcsTab;
	PlanTab *m_pPlanTab;
	QLabel *m_statusLabel;
};

#endif // MAINWINDOW_H
