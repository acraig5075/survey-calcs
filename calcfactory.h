#ifndef CALCFACTORY_H
#define CALCFACTORY_H

#include <memory>

class Calc;

class CalcFactory
{
public:
	CalcFactory() = delete;

	static std::unique_ptr<Calc> Instance(int typeId);
};

#endif // CALCFACTORY_H
