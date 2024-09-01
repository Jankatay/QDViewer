#ifndef UTERM_H
#define UTERM_H

#include <QObject>
#include <QProcess>
#include <QString>
#include <QStringList>

class UTerm : public QObject
{
  Q_OBJECT

public:
  UTerm(QObject *parent);
  QString getCmd();
  QString getStdOut();
  void exec(QString cmd, QStringList args);
  void write(QString in);
  void terminate();
  void clearStdOut();

signals:
  void sigFinishedExec();
  void sigOutputAvailable();

public slots:
  void finishedExec(int, QProcess::ExitStatus);
  void outputAvailable();

private:
  QString currentCmd;
  QStringList currentArgs;
  QString currentStdOut;
  QProcess *process;
};

#endif // UTERM_H
