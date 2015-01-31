#include <QLCDNumber>


class MyLCD: public QLCDNumber
{
	Q_OBJECT
public:
	MyLCD(QWidget *parent);

	public slots:
		void setColorToNumber(int n);
		void setToZero();
};
