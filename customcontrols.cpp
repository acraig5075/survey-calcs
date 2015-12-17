#include "customcontrols.h"
#include "utils.h"

NameValidator::NameValidator(QWidget *parent)
	: QRegularExpressionValidator(QRegularExpression("^.{1,8}$"), parent)
{}

AngleValidator::AngleValidator(QWidget *parent)
	: QDoubleValidator(-360.0, 360.0, 4, parent)
{}

LengthValidator::LengthValidator(QWidget *parent)
	: QDoubleValidator(0.0, 10000000.0, 3, parent)
{
	setNotation(QDoubleValidator::StandardNotation);
}

IntLineEdit::IntLineEdit(QWidget *parent)
	: QLineEdit(parent)
{
	setValidator(new QIntValidator(this));
}

void IntLineEdit::setValue(int value)
{
	setText(QString::number(value, 'f', 3));
}

int IntLineEdit::value() const
{
	return text().toInt();
}

DoubleLineEdit::DoubleLineEdit(QWidget *parent)
	: QLineEdit(parent)
{
	auto validator = new QDoubleValidator(this);
	validator->setNotation(QDoubleValidator::StandardNotation);
	setValidator(validator);
}

void DoubleLineEdit::setValue(double value)
{
	setText(QString::number(value, 'f', 3));
}

double DoubleLineEdit::value() const
{
	return text().toDouble();
}

NameLineEdit::NameLineEdit(QWidget *parent)
	: QLineEdit(parent)
{
	setValidator(new NameValidator(this));
}

void NameLineEdit::setName(const QString &name)
{
	setText(name);
}

QString NameLineEdit::name() const
{
	return text();
}

AngleLineEdit::AngleLineEdit(QWidget *parent)
	: QLineEdit(parent)
{
	setValidator(new AngleValidator(this));
	setPlaceholderText("ddd.mmss");
}

void AngleLineEdit::setAngle(double radians)
{
	setText(Utils::Rad2Dms(radians));
}

double AngleLineEdit::angle() const
{
	return Utils::Dms2Rad(text());
}

LengthLineEdit::LengthLineEdit(QWidget *parent)
	: QLineEdit(parent)
{
	setValidator(new LengthValidator(this));
}

void LengthLineEdit::setValue(double value)
{
	setText(QString::number(value, 'f', 3));
}

double LengthLineEdit::value() const
{
	return text().toDouble();
}
