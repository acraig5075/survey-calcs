#ifndef UTILS_H
#define UTILS_H

#include <QString>

namespace Utils
{
	QString MakeWorkingCopy(const QString &filename);
	bool CopyAndOverwrite(const QString &source, const QString destination);
	QString Rad2Dms(double radians);
}

#endif // UTILS_H
