#ifndef DPOLARS_H
#define DPOLARS_H

#include "Types/polars.h"
#include "Types/occupied.h"
#include "Types/observation.h"

class DpObsCalc : public Calc
{
public:
	Occupied m_stn[2];
	Observation m_obs[2];

	QString m_aname;
	QString m_adopt = "M";
	double m_y1 = 0, m_x1 = 0, m_y2 = 0, m_x2 = 0, m_ay = 0, m_ax = 0;
	double m_fy1 = 0, m_fx1 = 0, m_fy2 = 0, m_fx2 = 0;

	static const int TypeID = DpObsTypeID;
	static const QString SqlSelectQuery;

	DpObsCalc() = default;
	explicit DpObsCalc(const QSqlRecord &record);

	virtual QString desc() const override;
	virtual bool Edit(QWidget *parent) override;
};

#endif // DPOLARS_H

