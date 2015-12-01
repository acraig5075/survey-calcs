#ifndef DESCDLG_H
#define DESCDLG_H

#include <QDialog>

class Desc;

namespace Ui {
class DescDlg;
}

class DescDlg : public QDialog
{
	Q_OBJECT

public:
	DescDlg(QWidget *parent, Desc &desc);
	~DescDlg();

private slots:
	void on_DescDlg_accepted();

private:
	Ui::DescDlg *ui;
	Desc &m_desc;
};

#endif // DESCDLG_H
