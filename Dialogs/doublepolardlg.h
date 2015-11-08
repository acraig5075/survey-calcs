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

private:
	Ui::DoublePolarDlg *ui;
	DpObsCalc &m_dpObs;
};

#endif // DOUBLEPOLARDLG_H
