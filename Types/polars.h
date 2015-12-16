#ifndef POLARS_H
#define POLARS_H

#include "Types/calc.h"
#include "Types/occupied.h"
#include "Types/observation.h"
#include <QtMath>

class PolarsCalc : public Calc
{
public:
	Occupied m_stn;
	Observation m_obs;
	double m_fy = 0, m_fx = 0;
	double m_ty = 0, m_tx = 0;

	static const int TypeID = PolarTypeID;
	static const QString SqlSelectQuery;
	static const QString SqlCreateQuery;

	PolarsCalc() = default;
	explicit PolarsCalc(const QSqlRecord &record);

	virtual QString desc() const override;
	virtual bool Edit(QWidget *parent) override;
	virtual QString GetUpdateQueryString() const override;
	virtual QString GetInsertQueryString() const override;
};


#endif // POLARS_H

