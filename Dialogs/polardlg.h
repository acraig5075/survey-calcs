#ifndef POLARDLG_H
#define POLARDLG_H

#include <QDialog>

class PolarsCalc;
class Coord;

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
	void wireResult(const PolarsCalc &polar);
	void pack(PolarsCalc &polar, const Coord &from) const;

private slots:
	void onCoordAction();
	void onTargetAction();

	void on_calcButton_clicked();

private:
	Ui::PolarDlg *ui;
	PolarsCalc &m_polar;
};

#endif // POLARDLG_H
