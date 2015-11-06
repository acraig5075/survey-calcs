#ifndef UTILS_H
#define UTILS_H

#include <QString>

class Utils
{
public:
	Utils();

	static QString MakeWorkingCopy(const QString &filename);
	static bool CopyAndOverwrite(const QString &source, const QString destination);
	static QString Rad2Dms(double radians);

};

#endif // UTILS_H
