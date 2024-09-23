#ifndef MY_SCENE_H
#define MY_SCENE_H

#include <QWidget>
#include <QGraphicsScene>
#include<QAbstractGraphicsShapeItem>
#include<QGraphicsRectItem>
#include<QRectF>
#include <QVector>
#include<QTimer>
#include "tablemodel.h"
#include "my_way.h"

class My_scene : public  QGraphicsScene
{
    Q_OBJECT
private:

 bool m_start_is_checked{false};      //признаки для выбора начала и конца пути
 bool m_finish_is_checked{false};

 int green_level{333};      //для раскрашивания
 int yellow_level{667};
 int red_level{999};
 int black_level{0};

 QAbstractGraphicsShapeItem * m_rect;
 QVector<QAbstractGraphicsShapeItem*> basa_rect;
 double width_rect{15};
 QPen my_pen;
 QBrush my_brush;

 QModelIndex index_start;
 QModelIndex index_finish;

 bool m_tracing{false};
 QModelIndex index_tracing;

 //int timer_interval{1000/*index_start.data().toInt()*/};
 //int timer;



public:

 ~My_scene(){ for(auto x: basa_rect) delete x;/*delete m_rect;*/}

    explicit My_scene(QWidget *parent = nullptr);

signals:
 void GetIndex(QModelIndex&,int,int);
 void Start_Finish_Points(QModelIndex&,QModelIndex&);
 void enableGo(bool);
 void BlackAreas(bool);
 void enableTrace(bool);
 void findTheWay();
 void ReachNotToTrace();


public slots:

// void Timer_lapse(int lapse){timer_interval=lapse;}

 void Get_Start_Finish_Index(QModelIndex& index_start_out,QModelIndex& index_finish_out){

     index_start=index_start_out;
     index_finish=index_finish_out;


 }

 void Check_Points(bool tmp){
     m_start_is_checked=tmp;
     m_finish_is_checked=tmp;
 }


    void fill_scene(TableModel& model){
    m_tracing=false;
     //   this->clear();             //   или через clear сделать   //утечку убрал, но тормозить начинает
        for (auto x: basa_rect){
           // delete x;
            this->removeItem(x);
        }
        basa_rect.clear();
        //this->clear();
      //  this->update();


        m_start_is_checked=false;
        m_finish_is_checked=false;
        //m_tmp_is_checked=false;
        //    QRectF tmp_Rect(0,0,width_rect ,width_rect);
   //    qDebug()<<model.index(2,3).data(Qt::DisplayRole).toInt()  ;         //!!!!       //тут получаю значение индекса модели
   //my_pen.setColor(Qt::black);
   //m_rect->setPen(my_pen);
      //  this->clear();
        const QModelIndex tmp;

        my_pen.setColor(Qt::black);
        my_pen.setWidth(1);
        m_rect->setPen(my_pen);

        for (int i=0;i<model.rowCount(tmp); i++)
         for (int j=0;j<model.columnCount(tmp); j++)
        {

            m_rect=new QGraphicsRectItem;
            QRectF tmp_Rect(j*width_rect,i*width_rect,width_rect ,width_rect);
            qgraphicsitem_cast<QGraphicsRectItem*>(m_rect)->setRect(tmp_Rect.normalized());
            basa_rect.push_back(m_rect);

            if (model.index(i,j).data().toInt()==black_level )
                my_brush.setColor(Qt::black);
            else if (model.index(i,j).data().toInt()<=green_level )
                my_brush.setColor(Qt::green);
            else if (model.index(i,j).data().toInt()<=yellow_level )
                my_brush.setColor(Qt::yellow);
            else if (model.index(i,j).data().toInt()<=red_level )
                my_brush.setColor(Qt::red);

            //m_rect->setPen(my_pen);
            m_rect->setBrush(my_brush.color() );
            addItem(m_rect);
         //   delete m_rect;

        }

//        for (int i=0;i<model.rowCount(tmp); i++)
//         for (int j=0;j<model.columnCount(tmp); j++) {
//              m_rect[i+j].removeFromIndex();
//         }
    //qDebug()<< m_rect[2].brush()<<m_rect[3].brush();
       // qDebug()<<"scene"<<model.columnCount(tmp) ;


    }



    void fillChanges(QModelIndex index) {




        m_rect=new QGraphicsRectItem;
        QRectF tmp_Rect(index.column()*width_rect,index.row()*width_rect,width_rect ,width_rect);
        qgraphicsitem_cast<QGraphicsRectItem*>(m_rect)->setRect(tmp_Rect.normalized());
        basa_rect.push_back(m_rect);

        if (m_start_is_checked==true || m_finish_is_checked==true) {

//            my_pen.setColor(Qt::white );
//            my_pen.setWidth(1);
//            my_brush.setColor(Qt::cyan);

            m_rect->setBrush(my_brush.color() );
            m_rect->setPen(my_pen);
         } else {

             my_pen.setColor(Qt::black);
             my_pen.setWidth(1);
             m_rect->setBrush(my_brush.color() );
             m_rect->setPen(my_pen);




        if (index.data().toInt()==black_level )
            my_brush.setColor(Qt::black);
        else if (index.data().toInt()<=green_level )
            my_brush.setColor(Qt::green);
        else if (index.data().toInt()<=yellow_level )
            my_brush.setColor(Qt::yellow);
        else if (index.data().toInt()<=red_level )
            my_brush.setColor(Qt::red);

        m_rect->setBrush(my_brush.color() );

         }



        addItem(m_rect);

    }

void SetAlgBrush(QColor tmp){
        my_brush.setColor(tmp);
        my_pen.setColor(Qt::white );
        my_pen.setWidth(1);
    }

void SetTracing(/*bool tmp*/){
    m_tracing=!m_tracing;
}

void Reached(bool tmp) {
m_tracing=!tmp;
//killTimer(timer);
}




    // QGraphicsScene interface
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

// QGraphicsScene interface
protected:
virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

// QObject interface
protected:
virtual void timerEvent(QTimerEvent *event);


};

#endif // MY_SCENE_H
