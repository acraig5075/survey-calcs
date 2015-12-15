#ifndef CALCSCONTROLLER_H
#define CALCSCONTROLLER_H

#include "Types/calc.h"
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
	QString GetDescriptionAt(size_t i) const;
	bool EditCalcAt(size_t i, QWidget *parent);
	size_t numCalcs() const;
	void clear();

	template <typename T>
	bool Add(QWidget *parent);

signals:

public slots:
};

#endif // CALCSCONTROLLER_H
