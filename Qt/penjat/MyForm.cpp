#include "MyForm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>

MyForm::MyForm(QWidget* parent): QWidget(parent)
{
  ui.setupUi(this);
  paraula = "DICCIONARI";
  init();
  connect(ui.nouButton, SIGNAL(clicked()), this, SLOT(reset()));
  connect(ui.lineEdit, SIGNAL(textEdited(QString)), this, SLOT(actualitzar(QString)));
}

void MyForm::reset() {
	init();
}

void MyForm::actualitzar(const QString & text) {
	int size = text.size();
	if (size > oldSize) {
		ui.paraulaLabel->setText(QString::number(size));
	}
	oldSize = size;
}

void MyForm::init() {
  displayParaula = "**********";
  oldSize = 0;
  intents = 5;
  ui.paraulaLabel->setText(displayParaula);
  ui.lcdNumber->display(intents);
  ui.lineEdit->clear();
  ui.lineEdit->setStyleSheet("QLineEdit{background: white;}");
  ui.lineEdit->setReadOnly(false);
}

void MyForm::guanyar() {
	ui.lineEdit->setStyleSheet("QLineEdit{background: green;}");
	ui.lineEdit->setReadOnly(true);
}

void MyForm::perdre() {
	ui.lineEdit->setStyleSheet("QLineEdit{background: red;}");
	ui.lineEdit->setReadOnly(true);
}