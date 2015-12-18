#include "utils.h"
#include "Types/coord.h"
#include "Types/occupied.h"
#include "Types/observation.h"
#include "Models/coordquerymodel.h"
#include "Models/stationsquerymodel.h"
#include "Models/observationsquerymodel.h"
#include "Dialogs/selectcoorddlg.h"
#include "Dialogs/editcoorddlg.h"
#include <QTemporaryFile>
#include <QDebug>
#include <QtMath>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include <QLineEdit>
#include <QComboBox>


namespace Utils
{
QString MakeTemporaryFile()
{
	QTemporaryFile tempFile;
	tempFile.open();
	QString name = tempFile.fileName();
	tempFile.close();
	return name;
}

QString MakeWorkingCopy(const QString &filename)
{
	QString backup = MakeTemporaryFile();

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
	if (!QFile::exists(source) || destination.isEmpty())
	{
		qDebug() << "File copy failed because of bad inputs";
		return false;
	}

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


void Rad2Dms(double radians, int &sign, int &d, int &m, int &s)
{
	sign = (radians < 0 ? -1 : 1);
	double degrees = qRadiansToDegrees(fabs(radians));
	d = static_cast<int>(floor(degrees));
	double minutes = (degrees - d) * 60.0;
	m = static_cast<int>(floor(minutes));
	double seconds = (minutes - m) * 60.0;
	s = static_cast<int>(floor(seconds + 0.5));
}

QString Rad2Dms(double radians)
{
	int sign, d, m, s;
	Rad2Dms(radians, sign, d, m, s);

	return QString("%1.%2%3")
			.arg(d * sign)
			.arg(m, 2, 10, QChar('0'))
			.arg(s, 2, 10, QChar('0'));
}

QString Rad2Dms(double radians, QChar delimiter)
{
	int sign, d, m, s;
	Rad2Dms(radians, sign, d, m, s);

	return QString("%1%2%3%4%5")
			.arg(d * sign)
			.arg(delimiter)
			.arg(m, 2, 10, QChar('0'))
			.arg(delimiter)
			.arg(s, 2, 10, QChar('0'));
}

double Dms2Rad(QString dms)
{
	double value = dms.toDouble();
	int sign = (value < 0 ? -1 : 1);
	value *= sign;

	int d = static_cast<int>(floor(value));
	double minutes = (value - d) * 100.0;
	int m = static_cast<int>(floor(minutes));
	double seconds = (minutes - m) * 100.0;
	int s = static_cast<int>(floor(seconds + 0.5));

	return sign * qDegreesToRadians(d + m / 60.0 + s / 3600.0);
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
				oc.second->setText(Rad2Dms(setup.first, ':'));
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

void ComboboxSelection(QWidget *parent, const QString &query, QComboBox *comboBox, const QString &initial)
{
	auto model = new QSqlQueryModel(parent);
	model->setQuery(query);
	comboBox->setModel(model);
	int index = comboBox->findText(initial);
	comboBox->setCurrentIndex(index);
}

void DescriptionCombobox(QWidget *parent, QComboBox *comboBox, const QString &initial)
{
	ComboboxSelection(parent, "SELECT `desc` FROM desc ORDER BY `desc`", comboBox, initial);
}

void ClassificationCombobox(QWidget *parent, QComboBox *comboBox, const QString &initial)
{
	ComboboxSelection(parent, "SELECT `class` FROM class ORDER BY `order`", comboBox, initial);
}

bool LookupCoord(QWidget *parent, const QString &fromname, Coord &from)
{
	QSqlQuery query;
	query.prepare("SELECT `name`, `y`, `x`, `h`, `desc`, `class`, `plot` FROM `coord` WHERE `name` = :name");
	query.bindValue(":name", fromname);

	if (ExecQuery(query))
	{
		if (query.next())
		{
			Coord copy(query.record());
			from = copy;
			return true;
		}
	}

	Coord copy;
	copy.m_name = fromname;
	EditCoordDlg dlg(parent, copy);
	if (dlg.exec() == QDialog::Accepted)
	{
		from = copy;
		return true;
	}

	return false;
}

}
