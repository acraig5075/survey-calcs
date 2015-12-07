#ifndef OCCUPIED_H
#define OCCUPIED_H

#include <QSqlRecord>
#include <QSqlQuery>
#include <QDate>

class Occupied
{
public:
	Occupied() = default;
	explicit Occupied(const QSqlRecord &record);

	QSqlQuery GetInsertQueryString();
	QSqlQuery GetUpdateQueryString(const QString name, int setup);

	QString m_name;
	int m_setup = 0;
	double m_oc = 0.0;
	double m_instHgt = 0.0;
	QDate m_date;

	static const QString SqlCreateQuery;
};

#endif // OCCUPIED_H
