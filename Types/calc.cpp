#include "calc.h"
#include "calctypes.h"
#include <QVariant>

const QString Calc::SqlCreateQuery = "CREATE TABLE `calcs` ("
		"`order` BIGINT PRIMARY KEY ASC,"
		"`type` SMALLINT,"
		"`lines` SMALLINT,"
		"`page` SMALLINT,"
		"`select` VARCHAR(1)"
		")";

const QString JoinsCalc::SqlSelectQuery = "SELECT calcref, fromname, fy, fx, toname, ty, tx, dirc, dist FROM joins ORDER BY calcref";
const QString PolarsCalc::SqlSelectQuery = "SELECT calcref, fromname, fy, fx, toname, ty, tx, dirc, dist, oc FROM polars ORDER BY calcref";
const QString DpObsCalc::SqlSelectQuery = "SELECT dpobs.calcref, dpobs.trg1, dpobs.dir1, dpobs.ver1, dpobs.dis1, dpobs.y1, dpobs.x1, dpobs.trg2, dpobs.dir2, dpobs.ver2, dpobs.dis2, dpobs.y2, dpobs.x2, dpobs.aname, dpobs.ay, dpobs.ax, dpobs.adopt, dpstns.from1, dpstns.setup1, dpstns.fy1, dpstns.fx1, dpstns.from2, dpstns.setup2, dpstns.fy2, dpstns.fx2, dpstns.oc1, dpstns.oc2 FROM dpobs JOIN dpstns ON dpobs.calcref = dpstns.calcref ORDER BY dpobs.calcref";

Calc::Calc()
{
}

bool Calc::SortFunc(CalcPtr const& a, CalcPtr const& b)
{
	return a->m_calcref < b->m_calcref;
}

void Calc::setCalcRef(int calcRef)
{
	m_calcref = calcRef;
}
