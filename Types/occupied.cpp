#include "occupied.h"
#include <QVariant>


const QString Occupied::SqlCreateQuery = "CREATE TABLE `occupied` ("
		"`station` VARCHAR(8),"
		"`setupno` SMALLINT,"
		"`desc` VARCHAR(8),"
		"`date` BIGINT,"
		"`observer` VARCHAR(3),"
		"`booker` VARCHAR(3),"
		"`oc` FLOAT,"
		"`insthgt` FLOAT,"
		"`stationhgt` FLOAT,"
		"`instsystem` VARCHAR(6),"
		"`select` VARCHAR(1),"
		"`page` SMALLINT"
	 	")";

Occupied::Occupied(const QSqlRecord &record)
{
	m_name = record.value(0).toString();
	m_setup = record.value(1).toInt();
	m_oc = record.value(2).toDouble();
	m_instHgt = record.value(3).toDouble();
	m_date = record.value(4).toDate();
}

