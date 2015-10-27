#include "coord.h"
#include <QtCore/QVariant>

Coord::Coord()
{

}

Coord::Coord(const QSqlRecord &record)
{
	m_name = record.value("name").toString().toStdString();
	m_class = record.value("class").toString().toStdString();
	m_desc = record.value("desc").toString().toStdString();
	m_easting = record.value("y").toDouble();
	m_northing = record.value("x").toDouble();
	m_elevation = record.value("h").toDouble();
}
