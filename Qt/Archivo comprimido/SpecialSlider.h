#include "ui_Form.h"
#include <QLCDNumber>

class SpecialSlider: public QWidget
{
	Q_OBJECT

	public: 
		SpecialSlider(QWidget *parent=0);
	private: 
		Ui::SpecialSlider ui;
};
