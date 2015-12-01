#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QLabel>
#include <QPair>

class CoordsController;
class CalcsController;
class StationsController;
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

private:
	void CreateRequiredTables();

protected:
	void closeEvent(QCloseEvent *);

public slots:
	void onPlanViewChanged();
	void onStatusTextChanged();

private slots:
	void on_actionFileNew_triggered();
	void on_actionFileOpen_triggered();
	void on_actionFileClose_triggered();
	void on_actionFileExit_triggered();
	void on_actionCoordClass_triggered();

	void on_w_tabs_currentChanged(int index);

	void onCloseDatabase();
	void onChangedDatabase();
	void SetCaption();

	void on_actionCoordDescr_triggered();

signals:
	void databaseChanged();
	void databaseClosed();
	void updatePlanView();
	void coordCountChanged();

private:
	Ui::MainWindow *ui;
	QSqlDatabase m_db;
	QPair<QString, QString> m_filenames;
	CoordsController *m_pCoordsController;
	CalcsController *m_pCalcsController;
	StationsController *m_pStationsController;
	CoordsTab *m_pCoordsTab;
	StationsTab *m_pStationsTab;
	CalcsTab *m_pCalcsTab;
	PlanTab *m_pPlanTab;
	QLabel *m_statusLabel;
};

#endif // MAINWINDOW_H
