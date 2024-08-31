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

void MainWindow::on_pushButton_pressed()
{
  compiler->writeSrc( ui->srcEdit->toPlainText() );
}
void MainWindow::on_runButton_pressed()
{
  //QString execPath{  };
  //stdTerm->exec("", QStringList());
  compiler->link();
}

