#include "compute.h"
#include "utils.h"
#include "calctypes.h"
#include <QtMath>


namespace Compute
{

double SlopeToHorizontal(double slope, double zenith)
{
	return slope * sin(zenith);
}

void Join(JoinsCalc &join)
{
	Utils::Join(join.m_fy, join.m_fx, join.m_ty, join.m_tx, join.m_dist, join.m_dirc);
}

void Polar(PolarsCalc &p)
{
	double dist = SlopeToHorizontal(p.m_obs.m_dist, p.m_obs.m_vert);
	Utils::Polar(p.m_fy, p.m_fx, dist, p.m_obs.m_dirc, p.m_ty, p.m_tx);
}

void DoublePolar(DpObsCalc &dp)
{
	double dist1 = SlopeToHorizontal(dp.m_obs[0].m_dist, dp.m_obs[0].m_vert);
	double dist2 = SlopeToHorizontal(dp.m_obs[1].m_dist, dp.m_obs[1].m_vert);

	Utils::Polar(dp.m_fy1, dp.m_fx1, dist1, dp.m_obs[0].m_dirc, dp.m_y1, dp.m_x1);
	Utils::Polar(dp.m_fy2, dp.m_fx2, dist2, dp.m_obs[1].m_dirc, dp.m_y2, dp.m_x2);

	if (dp.m_adopt == "1")
	{
		dp.m_ay = dp.m_y1;
		dp.m_ax = dp.m_x1;
	}
	else if (dp.m_adopt == "2")
	{
		dp.m_ay = dp.m_y2;
		dp.m_ax = dp.m_x2;
	}
	else if (dp.m_adopt == "W" && dist1 + dist2 != 0.0) // weighted by dist
	{
		double de = dp.m_y2 - dp.m_y1;
		double dn = dp.m_x2 - dp.m_x1;
		dp.m_ay = dp.m_y1 + de * dist1 / (dist1 + dist2);
		dp.m_ax = dp.m_x1 + dn * dist1 / (dist1 + dist2);
	}
	else // mean
	{
		dp.m_ay = (dp.m_y1 + dp.m_y2) / 2.0;
		dp.m_ax = (dp.m_x1 + dp.m_x2) / 2.0;
	}
}

}

