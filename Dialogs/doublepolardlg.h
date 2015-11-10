#ifndef DOUBLEPOLARDLG_H
#define DOUBLEPOLARDLG_H

#include <QDialog>
#include "calc.h"

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

private:
	Ui::DoublePolarDlg *ui;
	DpObsCalc &m_dpObs;
};

#endif // DOUBLEPOLARDLG_H
