#ifndef JOINS_H
#define JOINS_H

#include "Types/calc.h"

class JoinsCalc : public Calc
{
public:
	QString m_fromname;
	QString m_toname;
	double m_fy = 0, m_fx = 0;
	double m_ty = 0, m_tx = 0;
	double m_dirc = 0, m_dist = 0;

	JoinsCalc() = default;
	explicit JoinsCalc(const QSqlRecord &record);
	static const QString SqlSelectQuery;
	virtual QString desc() const override;
	virtual bool Edit(QWidget *parent) override;
	virtual QString GetUpdateQueryString() const override;
};


#endif // JOINS_H

