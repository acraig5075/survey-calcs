#ifndef UTILS_H
#define UTILS_H

#include <QString>

class Utils
{
public:
	Utils();

	static QString MakeWorkingCopy(const QString &filename);
	static bool CopyAndOverwrite(const QString &source, const QString destination);
};

#endif // UTILS_H
