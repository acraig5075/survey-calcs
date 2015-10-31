#ifndef EDITCOORDDLG_H
#define EDITCOORDDLG_H

#include <QDialog>

class Coord;

namespace Ui {
class EditCoordDlg;
}

class EditCoordDlg : public QDialog
{
	Q_OBJECT

public:
	explicit EditCoordDlg(QWidget *parent, Coord &coord);
	~EditCoordDlg();

private slots:
	//void on_buttonBox_accepted();

	virtual void done(int r) override;

private:
	Ui::EditCoordDlg *ui;
	Coord &m_coord;
	bool ValidateName(const QString &name);
	bool HandleNewMnemonics(const QString &desc, const QString &clas);
};

#endif // EDITCOORDDLG_H
