#include "hcompiler.h"
#include <QDebug>
#include <QMessageBox>
#include <qglobal.h>

HCompiler::
HCompiler(QString cc, QStringList cflags, QString dump)
    : CFLAGS{ cflags }, CC{ cc }, DUMP{ dump }
    , term{ new UTerm(this) }
{
  FILES.SRC.setAutoRemove(false);
  FILES.OBJ.setAutoRemove(false);
  FILES.OBJ.setAutoRemove(false);

  connect( term, &UTerm::sigFinishedExec
         , this, &HCompiler::cmdFinished);
}

QString HCompiler::
getSrcString()
{
  if( !FILES.SRC.open() )
  {
    QMessageBox::warning(NULL, "WARNING"
    , "Error. "
      "Could not make temporary files.");
  }
  QByteArray srcBytes{ FILES.SRC.readAll() };
  QString srcString{ srcBytes };

  FILES.SRC.close();
  return srcString;
}

void HCompiler::
changeFlags( QStringList newFlags )
{
  CFLAGS = newFlags;
}

void HCompiler::
compile()
{
  if(!FILES.SRC.open() || !FILES.OBJ.open())
  {
    QMessageBox::warning(NULL, "compileWarning"
    , "Program needs access to the temp path."
    "\nIt can't compile otherwise");
    return;
  }

  QString srcPath{ FILES.SRC.fileName() };
  QString objPath{ FILES.OBJ.fileName() };

  QStringList ARGS{CFLAGS};
  ARGS << "-c" << srcPath
       << "-o" << objPath;

  term->exec(CC, ARGS);
  qDebug() << CC << ARGS;
}

void HCompiler::
dump()
{
  if(!FILES.OBJ.open())
  {
    QMessageBox::warning(NULL, "dumpWarning"
    , "Check temp folder and permissions");
    return;
  }

  QString objPath{ FILES.OBJ.fileName() };
  QStringList ARGS{"-d", objPath};
  term->exec(DUMP, ARGS);
  qDebug() << DUMP << ARGS;
}

void HCompiler::
readSrc()
{
  bool read = FILES.readSrc();
  if(!read)
  {
    QMessageBox::warning(NULL, "WARNING"
    , "Can't open file. Check file permissions");
  }
}

//  TODO: Handle some signals so mainwindow
// can do its fucking job
void HCompiler::
cmdFinished(QProcess *process)
{
  QString cmd{ term->getCmd() };

  if( cmd.compare(CC) == 0 )
  {
    qDebug() << "CC called";
    FILES.OBJ.flush();
    FILES.OBJ.close();
    FILES.SRC.close();
    dump();
  }

  else if( cmd.compare(DUMP) == 0)
  {
    qDebug() << "dump called";
    FILES.OBJ.close();
    QString assembly{ term->getStdOut() };
    emit compiled(assembly);
  }
}

void HCompiler::
writeSrc(QString text)
{
  FILES.writeSrc(text);
}

QString HCompiler::
getExecPath()
{
  return FILES.OUT.fileName();
}

void HCompiler::
link()
{
  if(!FILES.OUT.open())
  {
    QMessageBox::warning(NULL, "outWarning"
      , "Could not make a temp executable");
  }

  QStringList ARGS{FILES.OBJ.fileName()
          , "-o" , FILES.OUT.fileName() };

  term->exec(CC, ARGS);
  FILES.OUT.close();
}
