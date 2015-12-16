#ifndef POLARDLG_H
#define POLARDLG_H

#include <QDialog>

class PolarsCalc;

namespace Ui {
class PolarDlg;
}

class PolarDlg : public QDialog
{
	Q_OBJECT

public:
	PolarDlg(QWidget *parent, PolarsCalc &polar);
	~PolarDlg();

private:
	Ui::PolarDlg *ui;
	PolarsCalc &m_polar;
};

#endif // POLARDLG_H
