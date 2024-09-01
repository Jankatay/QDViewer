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
  void exec(QString cmd, QStringList args);
  QString getCmd();
  QString getStdOut();

signals:
  void sigFinishedExec();

public slots:
  void finishedExec(int, QProcess::ExitStatus);

private:
  QString currentCmd;
  QStringList currentArgs;
  QString currentStdOut;
  QProcess *process;
};

#endif // UTERM_H
