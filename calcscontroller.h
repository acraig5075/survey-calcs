#ifndef CALCSCONTROLLER_H
#define CALCSCONTROLLER_H

#include "calc.h"
#include <QObject>
#include <memory>

class Calc;

class CalcsController : public QObject
{
	Q_OBJECT

	std::vector<std::unique_ptr<Calc>> m_calcList;

	template <typename T>
	void ReadCalc();

public:
	explicit CalcsController(QObject *parent = 0);

	void Read();
	QStringList GetDescriptions() const;
signals:

public slots:
};

#endif // CALCSCONTROLLER_H
