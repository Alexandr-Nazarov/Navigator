#ifndef MY_SIZE_H
#define MY_SIZE_H

#include <QWidget>
#include <QDebug>
#include <QVector>
#include <QList>
#include <ctime>
#include <QTableView>
#include<QImage>

#include "tablemodel.h"
#include "mytableview.h"


class My_Size : public QWidget
{
    Q_OBJECT
public:
    explicit My_Size(QWidget *parent = nullptr);

private:

int X;
int Y;
bool dom {false};
bool uniform{true};

TableModel model;

//QVector<QVector<int>>arr;

public:

void fill_Matrix(/*QVector<QVector<int>>&*/);
void fill_Map_Matrix(QString&);

signals:
void ModelCreate(TableModel&);
void XChanged(QString);
void YChanged(QString);

public slots:

void selected_Dimension_X(QString tmp){
    X=tmp.toInt();
}

void selected_Dimension_Y(QString tmp){
    Y=tmp.toInt();
}

void selected_Impassable(bool tmp){
    dom=tmp;
}

void selected_Uniform(bool tmp){
    uniform=tmp;
}

void create_Matrix(){

    model.clear_Hash();
    model.set_Rows(X);
    model.set_Columns(Y);


    //arr.clear();
    //arr.shrink_to_fit();
    //arr.reserve(X*Y);
    fill_Matrix(/*arr*/);
}

void send_index(QModelIndex& index,int x,int y){
   // model.index(i, j, QModelIndex());
    index=model.index(x,y,QModelIndex());
  //  qDebug()<<index.data().toInt() ;
}

void send_XY(QModelIndex& index){
   // model.index(i, j, QModelIndex());
    index=model.index(X-1,Y-1,QModelIndex());
}


void create_Map_Matrix(QString& tmp){

    model.clear_Hash();
  //  model.set_Rows(X);
  //  model.set_Columns(Y);


      fill_Map_Matrix(tmp);
}

void sendToSaveInFile(QTextStream& out){
   const QModelIndex tmp;
   out<<model.rowCount(tmp) <<' '<<model.columnCount(tmp)<<'\n';
   for (int i=0;i<model.rowCount(tmp); i++){
    for (int j=0;j<model.columnCount(tmp); j++){
        out<<model.index(i,j).data().toInt()<<' ';
    }
       out<<'\n';
    }
}

void takeToOpenFromFile(QTextStream&in) {

  in>>X>>Y;

  QString tmp_x=QString::number(X);
  QString tmp_y=QString::number(Y);
  emit XChanged(tmp_x);
  emit YChanged(tmp_y);

  model.clear_Hash();
  model.set_Rows(X);
  model.set_Columns(Y);

  int value;
  for (int i=0; i<X;++i) {
      for (int j=0; j<Y;++j) {
          QModelIndex index = model.index(i, j, QModelIndex());
          in>>value;
          model.setData(index,value, Qt::EditRole);
      }
  }

 emit ModelCreate(model);

}


};

#endif // MY_SIZE_H
