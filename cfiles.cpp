#include "cfiles.h"
#include <QErrorMessage>
#include <QDebug>
#include <QMessageBox>

CFiles::
CFiles()
{
  OUT = QDir::temp()
  .absoluteFilePath("CPROJECT_XXXXXX.out");

  SRC.setFileTemplate(QDir::temp()
  .absoluteFilePath("CPROJECT_XXXXXX.cpp"));

  OBJ.setFileTemplate(QDir::temp()
  .absoluteFilePath("CPROJECT_XXXXXX.obj"));

  if(!SRC.open() || !OBJ.open())
  {
    qDebug() << "Couldn't make an SRC file";
  }
  qDebug() << OUT;
  SRC.close();
  OBJ.close();
}

bool CFiles::
readSrc()
{
  QString filePath{
    QFileDialog::getOpenFileName(nullptr
      , "Select source", ""
      , "(*.cpp);;All Files (*)")
  };

  QFile file{filePath};
  if(!file.open(QIODevice::ReadWrite
                  | QIODevice::Text))
  {
    qDebug() << "couldn't";
    return false;
  }

  if( !SRC.open() )
  {
    return false;
  }
  SRC.write( file.readAll() );
  SRC.flush();
  SRC.close();
  return true;
}

void CFiles::
writeSrc(QString text)
{
  QFile SRCTRUNCATE{SRC.fileName()};

  if (! SRCTRUNCATE.open(QIODevice::WriteOnly
      | QIODevice::Truncate))
  {
    qDebug() << "couldn't save temp files";
    return;
  }

  SRCTRUNCATE.write( text.toUtf8() );
  SRCTRUNCATE.flush();
  SRCTRUNCATE.close();
}

