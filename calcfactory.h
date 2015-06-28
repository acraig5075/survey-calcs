#ifndef CALCFACTORY_H
#define CALCFACTORY_H

class Calc;

class CalcFactory
{
public:
	CalcFactory() = delete;

	static Calc* Instance(int typeId);
};

#endif // CALCFACTORY_H
