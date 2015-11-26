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

	// I think an ObservationsController is needed.
	bool Add(const Observation &obs);
	bool Edit() {}
	bool Delete() {}

	void ShowObservations(QWidget *parent, const Occupied &station);
};

#endif // STATIONSCONTROLLER_H
