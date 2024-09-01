#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStringList>
#include <QDebug>

MainWindow::
MainWindow (QWidget *parent)
    : QMainWindow (parent)
    , ui {new Ui::MainWindow}
    , compiler{ new HCompiler() }
    , stdTerm{ new UTerm(this) }
{
  ui->setupUi (this);

  connect(compiler
    , qOverload<QString>
    (&HCompiler::compiled)
    , this, &MainWindow::srcCompiled);

  connect(stdTerm
    , &UTerm::sigFinishedExec
    , this, &MainWindow::stdTermFinished);

  connect(stdTerm
    , &UTerm::sigOutputAvailable
    , this, &MainWindow::stdOutputAvailable);
  connect(compiler
    , qOverload<QString>
    (&HCompiler::linked)
    , this, &MainWindow::finishedLinking);

}

MainWindow::
~MainWindow () { delete ui; }

void MainWindow::
on_openButton_pressed()
{
  compiler->readSrc();
  ui->srcEdit->setText(
      compiler->getSrcString()
  );
  qDebug() << compiler->getSrcString();
}


void MainWindow::
on_cButton_pressed()
{
  compiler->writeSrc( ui->srcEdit->toPlainText() );
  compiler->compile();
}

void MainWindow::
srcCompiled(QString assembly)
{
  ui->asmBrowser->setText(assembly);
}

void MainWindow::
on_pushButton_pressed()
{
  compiler->writeSrc( ui->srcEdit->toPlainText() );
}

void MainWindow::on_runButton_pressed()
{
  compiler->terminate();
  ui->stdIn->clear();
  stdTerm->clearStdOut();
  compiler->link();
}

void MainWindow::
fillStdOutBrowser()
{
  QString out{ stdTerm->getStdOut() };
  qDebug() << out;
  ui->stdOut->setText(out);
}

void MainWindow::
finishedLinking(QString execPath)
{
  currentTask = fillStdOut;
  QStringList ARGS{ ui->stdIn->text()
                        .split(' ') };
  ui->stdIn->clear();
  ui->stdOut->clear();
  stdTerm->exec(execPath, ARGS);
}

void MainWindow::
stdTermFinished()
{

  switch(currentTask)
  {
    case(fillStdOut):
    {
      fillStdOutBrowser();
      break;
    }
    case(clearStdOut):
    {
      ui->stdOut->clear();
      break;
    }
  }

}

void MainWindow::
stdOutputAvailable()
{
  QString out{ stdTerm->getStdOut() };
  ui->stdOut->append( out );
}


void MainWindow::on_stdIn_returnPressed()
{
  QString in{ ui->stdIn->text() };
  stdTerm->write( in );
  ui->stdIn->clear();
}


void MainWindow::on_tButton_pressed()
{
  stdTerm->terminate();
  ui->stdOut->append("\nProcess Terminated\n");
}

