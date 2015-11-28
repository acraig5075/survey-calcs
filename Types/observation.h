#ifndef OBSERVATION_H
#define OBSERVATION_H

#include <QSqlRecord>
#include <QWidget>

class Observation
{
public:
	Observation() = default;
	explicit Observation(const QSqlRecord &record);

	void SetFrom(const QSqlRecord &record);

	bool Add(QWidget *parent);
	bool Edit(QWidget *parent);
	bool Delete();

	QString m_station;
	int m_setup = 0;
	QString m_target;
	QString m_desc;
	double m_dirc = 0;
	double m_vert = 0;
	double m_dist = 0;
	double m_prismHgt = 0;

private:
	void AddDescIfNotExist();
};

#endif // OBSERVATION_H
