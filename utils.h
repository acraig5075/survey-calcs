#ifndef UTILS_H
#define UTILS_H

#include <QPair>
class QWidget;
class QLineEdit;
class Observation;

namespace Utils
{
	QString MakeWorkingCopy(const QString &filename);
	bool CopyAndOverwrite(const QString &source, const QString destination);
	bool UpdateDatabase(const QString &sql);
	QString Rad2Dms(double radians);
	double Dms2Rad(QString dms);
	bool LoadCoord(QWidget *parent, QPair<QString, QLineEdit *> &p1, QPair<double, QLineEdit *> &p2, QPair<double, QLineEdit *> &p3);
	bool LoadStation(QWidget *parent, QPair<QString, QLineEdit *> &name, QPair<int, QLineEdit *> &setup, QPair<double, QLineEdit *> &oc);
	bool LoadObs(QWidget *parent, const QString &station, int setup, Observation &obs);
	void Join(double e1, double n1, double e2, double n2, double &dist, double &dirn);
	void Polar(double e1, double n1, double dist, double dirn, double &e2, double &n2);

	template <typename TDlg, typename TCalc>
	bool EditDialog(QWidget *parent, TCalc &calc)
	{
		TCalc localCopy = calc;
		TDlg dlg(parent, localCopy);
		if (dlg.exec() == QDialog::Accepted)
		{
			calc = localCopy;
			return true;
		}

		return false;
	}
}

#endif // UTILS_H
