#ifndef STATIONDLG_H
#define STATIONDLG_H

#include <QDialog>

class Occupied;

namespace Ui {
class StationDlg;
}

class StationDlg : public QDialog
{
	Q_OBJECT

public:
	explicit StationDlg(QWidget *parent, Occupied &occupied);
	~StationDlg();

private slots:
	void checkLineEdits(QString text);
	void on_StationDlg_accepted();
	void on_nameEdit_editingFinished();

private:
	Ui::StationDlg *ui;
	Occupied &m_station;
};

#endif // STATIONDLG_H
