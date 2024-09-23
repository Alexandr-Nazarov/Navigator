#include <QTranslator>
#include <QIcon>
#include <QApplication>


#include "navogator.h"
#include "tablemodel.h"
#include "mytableview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //=== переводчик
    QTranslator translator;

    QString filespec=QString(/*"Navigator_"*/":/Translations/Navigator_");
    filespec += QLocale::system().name();
    translator.load(filespec,".");

    QApplication ::installTranslator(&translator);

    //--перевод в стандартных диалогах
    QString filespec2=QString("qt_")+QLocale::system().name();
    QString directory2=QLibraryInfo::location(QLibraryInfo::TranslationsPath);
    QTranslator translator2;
    translator2.load(filespec2, directory2);
    QApplication ::installTranslator(&translator2);
    //===



    Navogator w;
    w.show();

    return a.exec();
}
