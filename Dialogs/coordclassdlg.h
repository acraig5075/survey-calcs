#ifndef COORDCLASSDLG_H
#define COORDCLASSDLG_H

#include <QDialog>

class QSqlQueryModel;
class QItemSelection;

namespace Ui {
class CoordClassDlg;
}

class CoordClassDlg : public QDialog
{
	Q_OBJECT

public:
	explicit CoordClassDlg(QWidget *parent = 0);
	~CoordClassDlg();

protected slots:
	void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
private:
	Ui::CoordClassDlg *ui;
	QSqlQueryModel *m_pModel;
	void Init();
};

#endif // COORDCLASSDLG_H
