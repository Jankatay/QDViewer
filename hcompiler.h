#ifndef HCOMPILER_H
#define HCOMPILER_H

#include <QObject>
#include <QStringList>
#include <QString>
#include <QFile>
#include <filesystem>
#include <QLineEdit>
#include "cfiles.h"
#include "uterm.h"

const QStringList defaultFlags{
  "-O0", "-c", "-fno-stack-protector", "-w"
};

class HCompiler : public QObject
{
  Q_OBJECT

public:
  HCompiler( QString cc="g++"
    , QStringList cflags = defaultFlags
    , QString dump = "objdump");

  QString getExecPath();
  QString getSrcString();

  void changeFlags(QStringList newFlags);
  void compile();
  void dump();
  void link();
  void setFiles(CFiles newFiles);
  void readSrc();
  void writeSrc(QString text);

private slots:
  void cmdFinished(QProcess *process);

signals:
  void compiled(QString assembly);
  void linked(QString filePath);

private:
  QString CC;
  QStringList CFLAGS;
  QString DUMP;
  CFiles FILES;
  UTerm *term;
};

#endif // HCOMPILER_H
