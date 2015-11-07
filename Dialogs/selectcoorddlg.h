#ifndef SELECTCOORDDLG_H
#define SELECTCOORDDLG_H

#include <QDialog>
#include "coord.h"

class CoordQueryModel;

namespace Ui {
class SelectCoordDlg;
}

class SelectCoordDlg : public QDialog
{
	Q_OBJECT

public:
	explicit SelectCoordDlg(QWidget *parent, bool multiSelection = false);
	~SelectCoordDlg();

	Coord GetSingleSelection() const;
	QVector<Coord> GetMultiSelection() const;

private slots:
	void on_SelectCoordDlg_accepted();

	void on_SelectCoordDlg_rejected();

private:
	Ui::SelectCoordDlg *ui;
	CoordQueryModel *m_pModel = nullptr;
	QVector<Coord> m_selCoords;
};

#endif // SELECTCOORDDLG_H
