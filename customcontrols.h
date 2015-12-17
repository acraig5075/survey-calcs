#ifndef CUSTOMCONTROLS_H
#define CUSTOMCONTROLS_H

#include <QLineEdit>
#include <QDoubleValidator>
#include <QRegularExpressionValidator>


class NameValidator : public QRegularExpressionValidator
{
public:
	NameValidator(QWidget *parent);
};

class AngleValidator : public QDoubleValidator
{
public:
	AngleValidator(QWidget *parent);
};

class LengthValidator : public QDoubleValidator
{
public:
	LengthValidator(QWidget *parent);
};

class IntLineEdit : public QLineEdit
{
public:
	IntLineEdit(QWidget *parent);
	void setValue(int value);
	int value() const;
};

class DoubleLineEdit : public QLineEdit
{
public:
	DoubleLineEdit(QWidget *parent);
	void setValue(double radians);
	double value() const;
};

class NameLineEdit : public QLineEdit
{
public:
	NameLineEdit(QWidget *parent);
	void setName(const QString &name);
	QString name() const;
};

class AngleLineEdit : public QLineEdit
{
public:
	AngleLineEdit(QWidget *parent);
	void setAngle(double angle);
	double angle() const;
};

class LengthLineEdit : public QLineEdit
{
public:
	LengthLineEdit(QWidget *parent);
	void setValue(double value);
	double value() const;
};

#endif // CUSTOMCONTROLS_H

