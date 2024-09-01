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
  compiler->link();
  //QString execPath{  };
  //stdTerm->exec("", QStringList());
  //QString execPath{ compiler->getExecPath() };
  //QStringList ARGS{ ui->stdIn->text().split(' ') };
  //ui->stdIn->clear();
  //qDebug() << execPath << ARGS;
  //stdTerm->exec(execPath, ARGS);
  //qDebug() << execPath << ARGS << "called";
}

void MainWindow::
fillStdOutBrowser()
{
  //ui->stdOut->setText(out);
}

void MainWindow::
finishedLinking(QString execPath)
{
  currentTask = fillStdOut;
  stdTerm->exec(execPath, QStringList());
  qDebug() << "finished linking";
}

void MainWindow::
stdTermFinished()
{

  switch(currentTask)
  {
    case(fillStdOut):
    {
      QString out{ stdTerm->getStdOut() };
      ui->stdOut->setText( out );
    }
  }

}
