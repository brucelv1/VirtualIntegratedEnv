#ifndef _Delta_Dlg2x3Parameter_H_
#define _Delta_Dlg2x3Parameter_H_

#include <QtGui/QDialog>
#include "GUI/ui_Parameter.h"

class Dlg2x3Parameter :
	public QDialog, public Ui_Parameter
{
	Q_OBJECT
public:
	Dlg2x3Parameter(QWidget* parent = NULL);
	~Dlg2x3Parameter(void);
};
#endif //_Delta_Dlg2x3Parameter_H_