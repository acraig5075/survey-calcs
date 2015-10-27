#ifndef EDITCOORDDLG_H
#define EDITCOORDDLG_H

#include <QDialog>

class Coord;
class CoordsController;

namespace Ui {
class EditCoordDlg;
}

class EditCoordDlg : public QDialog
{
	Q_OBJECT

public:
	explicit EditCoordDlg(QWidget *parent, Coord &coord, const CoordsController &controller);
	~EditCoordDlg();

private slots:
	void on_buttonBox_accepted();

private:
	Ui::EditCoordDlg *ui;
	Coord &m_coord;
};

#endif // EDITCOORDDLG_H
