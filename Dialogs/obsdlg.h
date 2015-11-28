#ifndef OBSDLG_H
#define OBSDLG_H

#include <QDialog>

class Observation;

namespace Ui {
class ObsDlg;
}

class ObsDlg : public QDialog
{
	Q_OBJECT

public:
	explicit ObsDlg(QWidget *parent, Observation &obs);
	~ObsDlg();

private slots:
	void checkLineEdits(QString text);

	void on_ObsDlg_accepted();

private:
	Ui::ObsDlg *ui;
	Observation &m_obs;
};

#endif // OBSDLG_H
