#ifndef STATIONSCONTROLLER_H
#define STATIONSCONTROLLER_H

#include <QObject>

class Occupied;
class Observation;

class StationsController : public QObject
{
public:
	StationsController(QObject *parent);

	bool AddStation() {}
	bool EditStation() {}
	bool DeleteStation() {}

	void ShowObservations(QWidget *parent, const Occupied &station);
};

#endif // STATIONSCONTROLLER_H
