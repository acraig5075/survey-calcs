#ifndef COORDSCONTROLLER_H
#define COORDSCONTROLLER_H

#include <QObject>

class Coord;

// The intention of this class is to handle any database modifications on the `coords` table.
class CoordsController : public QObject
{
	Q_OBJECT
	bool ModifyCoordTable(const QString &sql);

public:
	explicit CoordsController(QObject *parent = 0);

	bool EditCoord(QWidget *parent, const Coord &coord);

signals:

public slots:
};

#endif // COORDSCONTROLLER_H
