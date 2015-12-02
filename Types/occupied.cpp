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

QSqlQuery Occupied::GetInsertQueryString()
{
	QSqlQuery query;
	query.prepare("INSERT INTO occupied (station, setupno, date, oc, insthgt) "
				  "VALUES (:station, :setupno, :date, :oc, :insthgt)");

	query.bindValue(":station", m_name);
	query.bindValue(":setupno", m_setup);
	query.bindValue(":date", m_date);
	query.bindValue(":oc", m_oc);
	query.bindValue(":insthgt", m_instHgt);

	return query;
}

QSqlQuery Occupied::GetUpdateQueryString(const QString name, int setup)
{
	QSqlQuery query;
	query.prepare("UPDATE occupied SET"
				  " date = :date"
				  ", oc = :oc"
				  ", insthgt = :insthgt"
				  " WHERE station = :name AND setupno = :setup");

	query.bindValue(":date", m_date);
	query.bindValue(":oc", m_oc);
	query.bindValue(":insthgt", m_instHgt);
	query.bindValue(":name", name);
	query.bindValue(":setup", setup);

	return query;
}

