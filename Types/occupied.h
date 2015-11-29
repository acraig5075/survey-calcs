#ifndef OCCUPIED_H
#define OCCUPIED_H

#include <QSqlRecord>
#include <QDate>

class Occupied
{
public:
	Occupied() = default;
	explicit Occupied(const QSqlRecord &record);

	QString m_name;
	int m_setup;
	double m_oc;
	double m_instHgt;
	QDate m_date;

	static const QString SqlCreateQuery;
};

#endif // OCCUPIED_H
