#include "uterm.h"
#include <QDebug>
#include <qglobal.h>
#include <QByteArray>
#include <QMessageBox>

UTerm::UTerm (QObject *parent)
  : process{ new QProcess(this) }
{
  // Connect signals.
  connect( process
    , qOverload<int, QProcess::ExitStatus>
    (&QProcess::finished)
    , this, &UTerm::finishedExec );

  connect( process
    , &QProcess::readyReadStandardOutput
    , this, &UTerm::outputAvailable);

}

void
UTerm::finishedExec( int
  , QProcess::ExitStatus exitStatus)
{
  if(exitStatus == QProcess::CrashExit)
  {
    QStringList err;
    err << "Could not run:\n";
    err << "cmd:\t" << currentCmd << "\n";
    err << "args:\n" << currentArgs.join(' ');
    err << "\n\nPlease ensure you have the GNU binutils installed";
    QMessageBox::warning(NULL, "cErr", err.join(' '));
    return;
  }
  emit sigFinishedExec();
}

void
UTerm::exec( QString cmd
      , QStringList args )
{
  currentCmd = cmd;
  currentArgs = args;
  process->start(currentCmd, currentArgs);
}

QString
UTerm::getStdOut()
{
  return currentStdOut;
}


QString UTerm::
getCmd()
{
  return currentCmd;
}

void UTerm::
outputAvailable()
{
  QByteArray out{ process->readAllStandardOutput() };
  currentStdOut = out;
  emit sigOutputAvailable();
}

void UTerm::
write(QString in)
{
  if(! process->isWritable() )
  {
    QMessageBox::warning(NULL, "nostdin"
    , "No process is running.\n"
      "Simply click run with this box"
      "filled for parameter arguments");
  }

  in.append('\n');
  process->write( in.toUtf8() );
}

void UTerm::
terminate()
{
  process->terminate();
}

void UTerm::
clearStdOut()
{
  currentStdOut.clear();
}
