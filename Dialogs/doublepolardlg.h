#ifndef DOUBLEPOLARDLG_H
#define DOUBLEPOLARDLG_H

#include <QDialog>
#include "Types/dpolars.h"

class Occupied;
class Observation;
class QLineEdit;
class NameLineEdit;
class IntLineEdit;
class AngleLineEdit;
class LengthLineEdit;

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
	void onTargetAction(Observation &obs, const NameLineEdit *nameEdit, const IntLineEdit *setupEdit, NameLineEdit *targetEdit, AngleLineEdit *dircEdit, AngleLineEdit *vertEdit, LengthLineEdit *distEdit);
	void on_meanRadio_toggled(bool checked);
	void on_station1Radio_toggled(bool checked);
	void on_station2Radio_toggled(bool checked);
	void on_weightedRadio_toggled(bool checked);
	void on_radio_toggled(const QString &adopt);

private:
	Ui::DoublePolarDlg *ui;
	DpObsCalc &m_dpObs;

	void wireStation(const Occupied &station, NameLineEdit *nameEdit, IntLineEdit *setupEdit, AngleLineEdit *corrEdit);
	void wireObservation(const Observation &obs, NameLineEdit *targetEdit, AngleLineEdit *dircEdit, AngleLineEdit *vertEdit, LengthLineEdit *distEdit);
	void wireResult();
};

#endif // DOUBLEPOLARDLG_H
