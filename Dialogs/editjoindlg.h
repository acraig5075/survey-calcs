#ifndef EDITJOINDLG_H
#define EDITJOINDLG_H

#include <QDialog>
#include "calc.h"

namespace Ui {
class EditJoinDlg;
}

class EditJoinDlg : public QDialog
{
	Q_OBJECT

public:
	explicit EditJoinDlg(QWidget *parent, JoinsCalc &join);
	~EditJoinDlg();

private slots:
	void on_calculateButton_clicked();
	void onCoordAction1();
	void onCoordAction2();

private:
	Ui::EditJoinDlg *ui;
	JoinsCalc &m_join;
};

#endif // EDITJOINDLG_H
