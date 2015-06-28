#ifndef CALC_H
#define CALC_H

#include "QString"

class Calc
{
public:
	Calc();

	virtual QString desc() const = 0;
};


class UnknownCalc : public Calc
{
public:
	virtual QString desc() const override { return "Unknown\nMy new line"; }
};

class BeaconsCalc : public Calc
{
public:
	virtual QString desc() const override { return "Beacon\nMy new line"; }
};

class CommentCalc : public Calc
{
public:
	virtual QString desc() const override { return "Comment\nMy new line"; }
};

class DpObsCalc : public Calc
{
public:
	virtual QString desc() const override { return "Double Polar\nMy new line"; }
};

class DpStnsCalc : public Calc
{
public:
	virtual QString desc() const override { return "DpStns\nMy new line"; }
};

class DupsCalc : public Calc
{
public:
	virtual QString desc() const override { return "Dups\nMy new line"; }
};

class HelmertCalc : public Calc
{
public:
	virtual QString desc() const override { return "Helmert\nMy new line"; }
};

class IntersCalc : public Calc
{
public:
	virtual QString desc() const override { return "Intersection\nMy new line"; }
};

class JoinsCalc : public Calc
{
public:
	virtual QString desc() const override { return "Join\nMy new line"; }
};

class OffsetLnCalc : public Calc
{
public:
	virtual QString desc() const override { return "Offset Line\nMy new line"; }
};

class OffsetsCalc : public Calc
{
public:
	virtual QString desc() const override { return "Offsets\nMy new line"; }
};

class PolarsCalc : public Calc
{
public:
	virtual QString desc() const override { return "Polar\nMy new line"; }
};

class ResecsCalc : public Calc
{
public:
	virtual QString desc() const override { return "Resection\nMy new line"; }
};

class RoadWCalc : public Calc
{
public:
	virtual QString desc() const override { return "Road width\nMy new line"; }
};

class RouteCalc : public Calc
{
public:
	virtual QString desc() const override { return "Route\nMy new line"; }
};

class RPolarsCalc : public Calc
{
public:
	virtual QString desc() const override { return "Reverse Polar\nMy new line"; }
};

class SpObsCalc : public Calc
{
public:
	virtual QString desc() const override { return "Batch Polars\nMy new line"; }
};

class SpStnsCalc : public Calc
{
public:
	virtual QString desc() const override { return "SpStns\nMy new line"; }
};

class TObsCalc : public Calc
{
public:
	virtual QString desc() const override { return "TObs\nMy new line"; }
};

class XFormCalc : public Calc
{
public:
	virtual QString desc() const override { return "XForm\nMy new line"; }
};

#endif // CALC_H
