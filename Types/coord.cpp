#include "coord.h"
#include <QtCore/QVariant>


const QString Coord::SqlCreateQuery = "CREATE TABLE `coord` ("
		"`fbp` SMALLINT,"
		"`fbp2` SMALLINT,"
		"`name` VARCHAR(8),"
		"`y` FLOAT,"
		"`x` FLOAT,"
		"`h` FLOAT,"
		"`cp` SMALLINT,"
		"`class` VARCHAR(8),"
		"`desc` VARCHAR(8),"
		"`calcref` BIGINT,"
		"`select` VARCHAR(1),"
		"`order` SMALLINT,"
		"`plot` VARCHAR(1),"
		"`note` VARCHAR(10)"
		")";

Coord::Coord(const QSqlRecord &record)
{
	m_name = record.value("name").toString();
	m_class = record.value("class").toString();
	m_desc = record.value("desc").toString();
	m_easting = record.value("y").toDouble();
	m_northing = record.value("x").toDouble();
	m_elevation = record.value("h").toDouble();
}

QString Coord::GetUpdateQueryString(const QString &oldName)
{
	return QString("UPDATE coord SET `name`='%1', `y`=%2, `x`=%3, `h`=%4, `class`='%5', `desc`='%6' WHERE `name`='%7'")
			.arg(m_name)
			.arg(QString::number(m_easting, 'f', 6))
			.arg(QString::number(m_northing, 'f', 6))
			.arg(QString::number(m_elevation, 'f', 6))
			.arg(m_class)
			.arg(m_desc)
			.arg(oldName);
}
