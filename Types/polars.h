#ifndef POLARS_H
#define POLARS_H

#include "Types/calc.h"

class PolarsCalc : public Calc
{
public:
	QString m_fromname;
	QString m_toname;
	double m_fy = 0, m_fx = 0;
	double m_ty = 0, m_tx = 0;
	double m_dirc = 0, m_dist = 0, m_oc = 0;

	static const int TypeID = PolarTypeID;
	static const QString SqlSelectQuery;

	PolarsCalc() = default;
	explicit PolarsCalc(const QSqlRecord &record);

	virtual QString desc() const override;
};


#endif // POLARS_H

