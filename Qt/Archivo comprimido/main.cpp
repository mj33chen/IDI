#include <QApplication>
#include "SpecialSlider.h"

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	SpecialSlider sp;
	sp.show();
	return app.exec();
}