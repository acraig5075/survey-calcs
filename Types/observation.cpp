#include "observation.h"
#include <QVariant>

Observation::Observation(const QSqlRecord &record)
{
	m_target = record.value("target").toString();
	m_dirc = record.value("dirc").toDouble();
	m_vert = record.value("vert").toDouble();
	m_dist = record.value("dist").toDouble();
	m_desc = record.value("desc").toString();
	m_prismHgt = record.value("prismhgt").toDouble();
}

