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

  lastCmd = compileCmd;
  QStringList ARGS{CFLAGS};
  ARGS << "-c" << srcPath
       << "-o" << objPath;
  term->exec(CC, ARGS);
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

  lastCmd = dumpCmd;
  QString objPath{ FILES.OBJ.fileName() };
  QStringList ARGS{"-d", objPath};
  qDebug() << DUMP << ARGS;
  term->exec(DUMP, ARGS);
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
//  can do its fucking job
void HCompiler::
cmdFinished()
{
  QString cmd{ term->getCmd() };
  switch(lastCmd)
  {
    case(compileCmd):
    {
      FILES.OBJ.flush();
      FILES.OBJ.close();
      FILES.SRC.close();
      dump();
      break;
    }

    case(linkCmd):
    {
      QString outPath{ FILES.OUT };
      emit linked(FILES.OUT);
      break;
    }

    case(dumpCmd):
    {
      FILES.OBJ.close();
      QString assembly{ term->getStdOut() };
      emit compiled(assembly);
      break;
    }
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
  return FILES.OUT;
}

void HCompiler::
link()
{
  qDebug() << ".......";
  if(!FILES.SRC.open())
  {
    QMessageBox::warning(NULL, "outWarning"
      , "Could not make a temp executable");
  }

  QStringList ARGS{FILES.SRC.fileName()
          , "-o" , FILES.OUT };

  lastCmd = linkCmd;
  term->exec(CC, ARGS);
  qDebug() << "FILE" << FILES.OUT;
}

void HCompiler::
terminate()
{
  term->terminate();
}
