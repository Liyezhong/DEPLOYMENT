#include "myapplication.h"
#include <exception>
#include <QDebug>

MyApplication::MyApplication(int& argc, char** argv) :
  QApplication(argc, argv) {}

bool MyApplication::notify(QObject* receiver, QEvent* event) {
  bool done = true;
  try {
    done = QApplication::notify(receiver, event);
  } catch (const std::exception& ex) {
    //

  } catch (...) {
    //

  }
  return done;



  QApplication::exit();
  return false;


}
