#include "ui_MyForm.h"
#include <string>
using namespace std;

class MyForm : public QWidget
{
 Q_OBJECT
 
public:
  MyForm(QWidget *parent = 0);
  
public slots:
 
      void reset();
      void actualitzar(const QString & text);
  
private:
  Ui::MyForm ui;
  QString paraula;
  QString displayParaula;
  int intents;
  int oldSize;

  void init();
  void guanyar();
  void perdre();
};
