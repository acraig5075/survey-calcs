#include "calcfactory.h"
#include "calc.h"


Calc* CalcFactory::Instance(int typeId)
{
	switch (typeId)
	{
	case 1:
		return new JoinsCalc;
	case 2:
		return new PolarsCalc;
	case 3:
		return new IntersCalc;
	case 8:
		return new DpObsCalc;
	case 15:
		return new SpObsCalc;
	case 17:
		return new OffsetsCalc;
	case 18:
		return new XFormCalc;
	case 20:
		return new BeaconsCalc;
	default:
		return new UnknownCalc;
	}
}
