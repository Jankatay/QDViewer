#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "uterm.h"
#include "hcompiler.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow (QWidget *parent = nullptr);
  ~MainWindow ();

private slots:
  void on_openButton_pressed();
  void on_cButton_pressed();
  void srcCompiled(QString assembly);
  void on_pushButton_pressed();
  void on_runButton_pressed();
  void fillStdOutBrowser();
  void finishedLinking(QString execPath);
  void stdTermFinished();
  void stdOutputAvailable();

  void on_stdIn_returnPressed();

  void on_tButton_pressed();

private:
  Ui::MainWindow *ui;
  HCompiler *compiler;
  UTerm *stdTerm;

  enum Tasks
  {
    fillStdOut,
    clearStdOut,
    endCurrentProcess
  }
  currentTask;
};

#endif // MAINWINDOW_H
