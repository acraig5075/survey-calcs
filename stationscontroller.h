#ifndef STATIONSCONTROLLER_H
#define STATIONSCONTROLLER_H

#include <QObject>

class Occupied;
class Observation;

class StationsController : public QObject
{
public:
	StationsController(QObject *parent);

	bool AddStation(QWidget *parent, Occupied &station);
	bool EditStation(QWidget *parent, const Occupied &station);
	bool DeleteStation() {}

	void ShowObservations(QWidget *parent, const Occupied &station);
};

#endif // STATIONSCONTROLLER_H
