#ifndef CFILES_H
#define CFILES_H

#include <QFile>
#include <filesystem>
#include <QTextStream>
#include <QFileDialog>
#include <QTemporaryFile>

class CFiles
{
public:
  CFiles();
  bool readSrc();
  void writeSrc(QString text);

  QTemporaryFile SRC; //source file
  QTemporaryFile OUT; //output file
  QTemporaryFile OBJ; //object file
};

#endif // CFILES_H
