#ifndef NAVOGATOR_H
#define NAVOGATOR_H

#include <QMainWindow>
#include <QWidget>
#include <QDebug>
#include <QIntValidator>
#include <QTableView>
#include "my_scene.h"
//#include "my_size.h"
#include "tablemodel.h"
#include "my_way.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Navogator; }
QT_END_NAMESPACE

class Navogator : public /*QWidget*/QMainWindow
{
    Q_OBJECT

public:
    Navogator(QWidget *parent = nullptr);
    ~Navogator();

private:
    My_scene *scene;
    Ui::Navogator *ui;
    QMenuBar* m_bar;
    QMenu *info;
    QMenu *open;
    QAction *help_action;
    QAction *about_action;
    QAction *open_table_action;
    QAction *open_map_action;
    QAction *save_table_action;



public:

    QMenuBar* createmenubar(QFrame*);


signals:
void mySignal(QString);

//-работа с файлами
void toSaveInFile(QTextStream&);
void toOpenFromFile(QTextStream&);
void sendMap(QString&);

//--

public slots:

void on_about_action_triggered();
void on_help_action_triggered();
void on_save_table_action_triggered();
void on_open_table_action_triggered();
void on_open_map_action_triggered();

//void many_points(int);



// QWidget interface
protected:
virtual void paintEvent(QPaintEvent *event);


};
#endif // NAVOGATOR_H
