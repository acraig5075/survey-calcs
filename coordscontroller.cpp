#include "coordscontroller.h"
#include "Types/coord.h"
#include "utils.h"
#include "Dialogs/editcoorddlg.h"

CoordsController::CoordsController(QObject *parent) : QObject(parent)
{

}

bool CoordsController::EditCoord(QWidget *parent, const Coord &coord)
{
	Coord newCoord(coord);
	EditCoordDlg dlg(parent, newCoord);
	if (QDialog::Accepted == dlg.exec())
	{
		QString update = newCoord.GetUpdateQueryString(coord.m_name);
		return Utils::UpdateDatabase(update);
	}

	return false;
}
