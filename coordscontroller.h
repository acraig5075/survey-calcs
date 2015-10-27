#ifndef COORDSCONTROLLER_H
#define COORDSCONTROLLER_H

#include <QObject>

class Coord;

// The intention of this class is to handle any database modifications on the `coords` table.
class CoordsController : public QObject
{
	Q_OBJECT
public:
	explicit CoordsController(QObject *parent = 0);

	void EditCoord(QWidget *parent, const Coord &coord);

	QStringList GetDescriptionList() const;
	QStringList GetClassificationList() const;
	QStringList GetMnemonicList(const QString &select) const;

signals:

public slots:
};

#endif // COORDSCONTROLLER_H
