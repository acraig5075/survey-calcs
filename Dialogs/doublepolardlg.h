#ifndef DOUBLEPOLARDLG_H
#define DOUBLEPOLARDLG_H

#include <QDialog>
#include "Types/dpolars.h"

class Occupied;
class Observation;
class QLineEdit;

namespace Ui {
class DoublePolarDlg;
}

class DoublePolarDlg : public QDialog
{
	Q_OBJECT

public:
	explicit DoublePolarDlg(QWidget *parent, DpObsCalc &dpObs);
	~DoublePolarDlg();

private slots:
	void on_calculateButton_clicked();
	void onStation1Action();
	void onStation2Action();
	void onTarget1Action();
	void onTarget2Action();
	void onStationAction(Occupied &station, QLineEdit *nameEdit, QLineEdit *setupEdit, QLineEdit *corrEdit);
	void onTargetAction(Observation &obs, const QLineEdit *nameEdit, const QLineEdit *setupEdit, QLineEdit *targetEdit, QLineEdit *dircEdit, QLineEdit *vertEdit, QLineEdit *distEdit);

private:
	Ui::DoublePolarDlg *ui;
	DpObsCalc &m_dpObs;

	void wireStation(const Occupied &station, QLineEdit *nameEdit, QLineEdit *setupEdit, QLineEdit *corrEdit);
	void wireObservation(const Observation &obs, QLineEdit *targetEdit, QLineEdit *dircEdit, QLineEdit *vertEdit, QLineEdit *distEdit);
};

#endif // DOUBLEPOLARDLG_H
