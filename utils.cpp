#include "utils.h"
#include <QTemporaryFile>
#include <QDebug>
#include <QtMath>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>

namespace Utils
{
QString MakeWorkingCopy(const QString &filename)
{
	QString backup;

	{
		QTemporaryFile tempFile;
		tempFile.open();
		backup = tempFile.fileName();
		tempFile.close();
	}

	if (!backup.isEmpty())
	{
		qDebug() << QString("Copying %1 to %2").arg(filename, backup);
		if (QFile::copy(filename, backup))
			return backup;
	}

	return "";
}


bool CopyAndOverwrite(const QString &source, const QString destination)
{
	qDebug() << QString("Copying %1 to %2").arg(source, destination);

	if (!QFile::exists(destination) || QFile::remove(destination))
	{
		if (QFile::copy(source, destination))
			return true;
	}

	qDebug() << "File overwrite failed";
	return false;
}


bool UpdateDatabase(const QString &sql)
{
	QSqlDatabase db = QSqlDatabase::database();
	if (db.isOpen())
	{
		QSqlQuery query(db);
		query.prepare(sql);
		bool ok = query.exec();

		qDebug() << "Update query returned " << ok;
		if (!ok)
			qDebug() << query.lastError();
		return ok;
	}

	return false;
}

QString Rad2Dms(double radians)
{
	int sign = (radians < 0 ? -1 : 1);
	double degrees = fabs(qRadiansToDegrees(radians));
	int d = static_cast<int>(floor(degrees)) * sign;
	double minutes = (degrees - d) * 60.0;
	int m = static_cast<int>(floor(minutes));
	double seconds = (minutes - m) * 60.0;
	int s = static_cast<int>(floor(seconds));

	return QString("%1:%2:%3")
			.arg(d)
			.arg(m, 2, 10, QChar('0'))
			.arg(s, 2, 10, QChar('0'));
}
}
