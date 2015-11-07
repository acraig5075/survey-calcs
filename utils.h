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
	bool LoadCoord(QWidget *parent, QPair<QString, QLineEdit *> &p1, QPair<double, QLineEdit *> &p2, QPair<double, QLineEdit *> &p3);
}

#endif // UTILS_H
