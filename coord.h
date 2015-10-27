#ifndef COORD_H
#define COORD_H

#include <QSqlRecord>

class Coord
{
public:
	Coord();
	Coord(const QSqlRecord &record);

public:
	std::string m_name;
	std::string m_class;
	std::string m_desc;
	double m_easting = 0.0;
	double m_northing = 0.0;
	double m_elevation = 0.0;
};

#endif // COORD_H
