#include "utils.h"
#include "Types/coord.h"
#include "Types/occupied.h"
#include "Types/observation.h"
#include "Models/coordquerymodel.h"
#include "Models/stationsquerymodel.h"
#include "Models/observationsquerymodel.h"
#include "Dialogs/selectcoorddlg.h"
#include <QTemporaryFile>
#include <QDebug>
#include <QtMath>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include <QLineEdit>


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


bool ExecQuery(const QString &sql)
{
	QSqlDatabase db = QSqlDatabase::database();
	if (db.isOpen())
	{
		QSqlQuery query(db);
		query.prepare(sql);
		return ExecQuery(query);
	}
	else
	{
		qDebug() << "Database is not open!";
		return false;
	}
}

bool ExecQuery(QSqlQuery &query)
{
	QSqlDatabase db = QSqlDatabase::database();
	if (db.isOpen())
	{
		if (query.exec())
		{
			qDebug() << query.lastQuery();
			return true;
		}
		else
		{
			qDebug() << query.lastError();
			return false;
		}
	}
	else
	{
		qDebug() << "Database is not open!";
		return false;
	}
}

QString Rad2Dms(double radians)
{
	int sign = (radians < 0 ? -1 : 1);
	double degrees = qRadiansToDegrees(fabs(radians));
	int d = static_cast<int>(floor(degrees));
	double minutes = (degrees - d) * 60.0;
	int m = static_cast<int>(floor(minutes));
	double seconds = (minutes - m) * 60.0;
	int s = static_cast<int>(floor(seconds));

	return QString("%1:%2:%3")
			.arg(d * sign)
			.arg(m, 2, 10, QChar('0'))
			.arg(s, 2, 10, QChar('0'));
}

double Dms2Rad(QString dms)
{
	int d = 0, m = 0, s = 0;
	auto tokens = dms.split(QChar(':'));
	size_t count = tokens.size();

	if (count > 0)
		d = tokens.at(0).toInt();
	if  (count > 1)
		m = tokens.at(1).toInt();
	if (count > 2)
		s = tokens.at(2).toInt();
	int sign = (d < 0 ? -1 : 1);

	return sign * qDegreesToRadians(abs(d) + m / 60.0 + s / 3600.0);
}

bool LoadCoord(QWidget *parent, QPair<QString, QLineEdit *> &name, QPair<double, QLineEdit *> &y, QPair<double, QLineEdit *> &x)
{
	QVector<int> hideColumns = {1, 2, 3, 6}; // y, x, z, plot
	QString query = CoordQueryModel::ModelQueryString;

	SelectionDlg<Coord, CoordQueryModel> dlg(parent, "Coordinate Selection", false, query, hideColumns);
	if (dlg.exec() == QDialog::Accepted)
	{
		Coord coord = dlg.GetSingleSelection();
		if (!coord.m_name.isEmpty())
		{
			// update variables
			name.first = coord.m_name;
			y.first = coord.m_easting;
			x.first = coord.m_northing;
			// update controls
			if (name.second)
				name.second->setText(name.first);
			if (y.second)
				y.second->setText(QString::number(y.first, 'f', 3));
			if (x.second)
				x.second->setText(QString::number(x.first, 'f', 3));
			return true;
		}
	}
	return false;
}

bool LoadStation(QWidget *parent, QPair<QString, QLineEdit *> &name, QPair<int, QLineEdit *> &setup, QPair<double, QLineEdit *> &oc)
{
	QVector<int> hideColumns = {};
	QString query = StationsQueryModel::ModelQueryString;

	SelectionDlg<Occupied, StationsQueryModel> dlg(parent, "Station Selection", false, query, hideColumns);
	if (dlg.exec() == QDialog::Accepted)
	{
		Occupied station = dlg.GetSingleSelection();
		if (!station.m_name.isEmpty())
		{
			// update variables
			name.first = station.m_name;
			setup.first = station.m_setup;
			oc.first = station.m_oc;
			// update controls
			if (name.second)
				name.second->setText(name.first);
			if (setup.second)
				setup.second->setText(QString::number(setup.first));
			if (oc.second)
				oc.second->setText(Rad2Dms(setup.first));
			return true;
		}
	}
	return false;
}

bool LoadObs(QWidget *parent, const QString &station, int setup, Observation &obs)
{
	QVector<int> hideColumns = {};
	QString query = ObservationsQueryModel::ModelQueryString.arg(station).arg(setup);

	SelectionDlg<Observation, ObservationsQueryModel> dlg(parent, "Observation Selection", false, query, hideColumns);
	if (dlg.exec() == QDialog::Accepted)
	{
		obs = dlg.GetSingleSelection();
		if (!obs.m_target.isEmpty())
			return true;
	}
	return false;
}

double Angle(double x, double y)
{
	double angle;

	if (x == 0.0)
		{
		if (y > 0.0)
			angle = M_PI_2;
		else
			{
			if (y < 0.0)
				angle = -M_PI_2;
			else
				angle = 0.0;
			}
		}
	else
		{
		if (y == 0.0)
			{
			if (x > 0.0)
				angle = 0.0;
			else
				angle = M_PI;
			}
		else
			angle = atan2(y, x);
		}

	return angle;
}

void Join(double e1, double n1, double e2, double n2, double &dist, double &dirn)
{
	double de = e2 - e1;
	double dn = n2 - n1;

	dist = _hypot(de, dn);
	dirn = M_PI + Angle(dn, de);

	if (dirn >= 2.0 * M_PI)
		dirn = dirn - M_PI - M_PI;
}

void Polar(double e1, double n1, double dist, double dirn, double &e2, double &n2)
{
	e2 = e1 + dist * sin(dirn);
	n2 = n1 + dist * cos(dirn);
}
}
