#include "my_scene.h"

My_scene::My_scene(QWidget *parent) :  QGraphicsScene(parent)
{
//QGraphicsScene::setSceneRect(0,0,width_rect*500,width_rect*500);

my_pen.setColor(Qt::black);
my_pen.setWidth(1);



m_rect=new QGraphicsRectItem (0,0,0,0);
m_rect->setPen(my_pen);
//m_rect->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsMovable);

//QRectF tmp_Rect(0,0,width_rect ,width_rect);
//qgraphicsitem_cast<QGraphicsRectItem*>(m_rect)->setRect(tmp_Rect.normalized());
//addItem(m_rect);

}


void My_scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{


    if (event->buttons()==Qt::LeftButton && !m_start_is_checked) {

      //  QModelIndex index = model.index(i, j, QModelIndex());
       int x=event->scenePos().y()/width_rect;
       int y= event->scenePos().x()/width_rect;
       emit GetIndex(index_start,x,y);
       if (index_start.data().toInt()!=black_level){
       m_start_is_checked=true;
       my_pen.setColor(Qt::white );
       my_pen.setWidth(1);
       my_brush.setColor(Qt::cyan );
       fillChanges(index_start);
       }


    }

    else if (event->buttons()==Qt::LeftButton && m_start_is_checked && !m_finish_is_checked){

        int x=event->scenePos().y()/width_rect;
        int y= event->scenePos().x()/width_rect;
        emit GetIndex(index_finish,x,y);

        if (index_finish.data().toInt()!=black_level){
           m_finish_is_checked=true;


           my_pen.setColor(Qt::white );
           my_pen.setWidth(1);
           my_brush.setColor(Qt::darkGreen);

        if (index_finish==index_start) {
        m_start_is_checked=false;
        m_finish_is_checked=false;


        fillChanges(index_start);
        emit GetIndex(index_start,0,0);
        emit GetIndex(index_finish,0,0);
        }
    fillChanges(index_finish);
        }
    }

    else if (event->buttons()==Qt::LeftButton && m_start_is_checked && m_finish_is_checked){

        QModelIndex index_tmp;
        int x=event->scenePos().y()/width_rect;
        int y= event->scenePos().x()/width_rect;
        emit GetIndex(index_tmp,x,y);

        if (index_finish==index_tmp) {
        m_start_is_checked=false;
        m_finish_is_checked=false;
        fillChanges(index_finish);
        emit GetIndex(index_finish,0,0);
        m_start_is_checked=true;

        }

    }

    if (event->buttons()==Qt::RightButton){
        QModelIndex index_tmp;
        int x=event->scenePos().y()/width_rect;
        int y= event->scenePos().x()/width_rect;
        emit GetIndex(index_tmp,x,y);

        if (index_tmp!=index_start && index_tmp!=index_finish ){
         my_brush.setColor(Qt::black);
         my_pen.setColor(Qt::black);
         my_pen.setWidth(1);
//         m_rect->setPen(my_pen);


        if (index_tmp.isValid()) {
             QAbstractItemModel *model = const_cast<QAbstractItemModel*>(index_tmp.model());
              if (model) {
                  model->setData(index_tmp, 0, Qt::EditRole);
                  emit BlackAreas(true);
              }
          }
        }
    }

//qDebug()<<index_start.data().toInt()<<index_finish.data().toInt();


emit Start_Finish_Points(index_start,index_finish);



// QModelIndex index_tmp2;
//  QModelIndex index_tmp3;
//emit GetIndex(index_tmp2,2,2);
//  emit GetIndex(index_tmp3,5,5);
//// qDebug()<<index_tmp2.data().toInt();
//emit Start_Finish_Points_many(1,index_tmp2,index_tmp3);

 //===



  if (m_start_is_checked && m_finish_is_checked)  {
    emit enableGo(true);
  } else {
       emit enableGo(false);
  }

  if (m_start_is_checked)  {
    emit enableTrace(true);
  } else {
       emit enableTrace(false);
  }



QGraphicsScene::mousePressEvent(event);
}


void My_scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    QCoreApplication::processEvents();  //обработать все события

    if (m_tracing){

   /*     timer_interval=100;//index_start.data().toInt();
        killTimer(timer);
        timer=startTimer(timer_interval)*/;
//        qDebug()<<timer_interval;

    int x=event->scenePos().y()/width_rect;
    int y= event->scenePos().x()/width_rect;
    QModelIndex index_tmp;
    emit GetIndex(index_tmp,x,y);
    if (index_tmp==index_start) {
        m_tracing=false;
        emit ReachNotToTrace();
        //killTimer(timer);
    }

    else {
    emit GetIndex(index_finish,x,y);

    if (index_finish!=index_tracing  && index_finish!=index_start && index_finish.data().toInt()!=black_level){         //данное условие, чтобы квадратик-finish пропадал при перемещении, не оставляя следа
        m_finish_is_checked=false;
        m_start_is_checked=false;
        if (index_tracing.isValid()){

        fillChanges(index_tracing);
        }
    }


    if (index_finish.data().toInt()!=black_level && index_finish!=index_start){
        m_start_is_checked=true;
        m_finish_is_checked=true;

       my_pen.setColor(Qt::white );
       my_pen.setWidth(1);
       my_brush.setColor(Qt::darkGreen);

       fillChanges(index_finish);

       if (index_finish!=index_tracing){       //чтобы пересчитывалось только при переходе на другой квадрат
         emit Start_Finish_Points(index_start,index_finish);

       //    QCoreApplication::processEvents();  //обработать все события

          emit findTheWay();        //если для таймера, то убрать

     //      killTimer(timer);
     //      timer=startTimer(timer_interval);

        }

      }
    if(index_finish.data().toInt()!=black_level)        //для удаления квадратика-finish при пересечении black
index_tracing=index_finish;
    }
    }
QGraphicsScene::mouseMoveEvent(event);
}


void My_scene::timerEvent(QTimerEvent *event)
{

 //+  emit findTheWay();

}
