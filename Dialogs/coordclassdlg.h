#ifndef COORDCLASSDLG_H
#define COORDCLASSDLG_H

#include <QDialog>

class QSqlQueryModel;

namespace Ui {
class CoordClassDlg;
}

class CoordClassDlg : public QDialog
{
	Q_OBJECT

public:
	explicit CoordClassDlg(QWidget *parent = 0);
	~CoordClassDlg();

private:
	Ui::CoordClassDlg *ui;
	QSqlQueryModel *m_pModel;
	void Init();
};

#endif // COORDCLASSDLG_H
