#include "calcfactory.h"
#include "calctypes.h"

std::unique_ptr<Calc> CalcFactory::Instance(int typeId)
{
	switch (typeId)
	{
	case JoinsCalc::TypeID:
		return std::make_unique<JoinsCalc>();
	case PolarsCalc::TypeID:
		return std::make_unique<PolarsCalc>();
	case 3:
		return std::make_unique<IntersCalc>();
	case DpObsCalc::TypeID:
		return std::make_unique<DpObsCalc>();
	case 15:
		return std::make_unique<SpObsCalc>();
	case 17:
		return std::make_unique<OffsetsCalc>();
	case 18:
		return std::make_unique<XFormCalc>();
	case 20:
		return std::make_unique<BeaconsCalc>();
	default:
		return std::make_unique<UnknownCalc>();
	}
}
