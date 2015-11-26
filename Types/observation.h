#ifndef OBSERVATION_H
#define OBSERVATION_H

#include <QSqlRecord>

class Observation
{
public:
	Observation() = default;
	explicit Observation(const QSqlRecord &record);

	void SetFrom(const QSqlRecord &record);

	bool Add();
	bool Edit();
	bool Delete();

	QString m_station;
	int m_setup = 0;
	QString m_target;
	QString m_desc;
	double m_dirc = 0;
	double m_vert = 0;
	double m_dist = 0;
	double m_prismHgt = 0;
};

#endif // OBSERVATION_H
