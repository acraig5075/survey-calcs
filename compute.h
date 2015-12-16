#ifndef COMPUTE_H
#define COMPUTE_H

class JoinsCalc;
class PolarsCalc;
class DpObsCalc;

namespace Compute
{

double SlopeToHorizontal(double slope, double zenith);

void Join(JoinsCalc &join);
void Polar(PolarsCalc &p);
void DoublePolar(DpObsCalc &dp);

};

#endif // COMPUTE_H
