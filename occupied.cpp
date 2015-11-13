#include "occupied.h"
#include <QVariant>


Occupied::Occupied(const QSqlRecord &record)
{
	m_name = record.value(0).toString();
	m_setup = record.value(1).toInt();
	m_oc = record.value(2).toDouble();
	m_instHgt = record.value(3).toDouble();
	m_date = record.value(4).toDate();
}

