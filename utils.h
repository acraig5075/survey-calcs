#ifndef UTILS_H
#define UTILS_H

#include <QPair>
class QWidget;
class QLineEdit;

namespace Utils
{
	QString MakeWorkingCopy(const QString &filename);
	bool CopyAndOverwrite(const QString &source, const QString destination);
	bool UpdateDatabase(const QString &sql);
	QString Rad2Dms(double radians);
	double Dms2Rad(QString dms);
	bool LoadCoord(QWidget *parent, QPair<QString, QLineEdit *> &p1, QPair<double, QLineEdit *> &p2, QPair<double, QLineEdit *> &p3);
	bool LoadStation(QWidget *parent, QPair<QString, QLineEdit *> &name, QPair<int, QLineEdit *> &setup, QPair<double, QLineEdit *> &oc);
	void Join(double e1, double n1, double e2, double n2, double &dist, double &dirn);
	void Polar(double e1, double n1, double dist, double dirn, double &e2, double &n2);
}

#endif // UTILS_H
