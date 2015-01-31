#include "MyLCD.h"

MyLCD::MyLCD(QWidget *parent=0):QLCDNumber(parent)
{
}

void MyLCD::setColorToNumber(int n) {
	if (n == 0) {
		setStyleSheet("color:rgb(0, 255, 0)");
	}

	else if (n % 2 == 0) {
		setStyleSheet("color:rgb(0, 0, 255)");
	}

	else {
		setStyleSheet("color:rgb(255, 0, 0)");
	}

	display(n);
}

void MyLCD::setToZero() {
	setStyleSheet("color:rgb(0, 255, 0)");
	display(0);
}