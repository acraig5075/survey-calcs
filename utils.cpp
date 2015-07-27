#include "utils.h"
#include <QTemporaryFile>
#include <QDebug>

Utils::Utils()
{
}

QString Utils::MakeWorkingCopy(const QString &filename)
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


bool Utils::CopyAndOverwrite(const QString &source, const QString destination)
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
