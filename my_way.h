#ifndef MY_WAY_H
#define MY_WAY_H

#include <QObject>
#include <QSet>
#include "tablemodel.h"
#include <iterator>

#define MaxBig 999999


struct Dijkstra_Point{
    bool point_is_enable{true};
    int point_label{0};
    int edge_length{0};
};



struct My_napr{
    int x_napr  :2;
    int y_napr  :2;
};


class My_Way : public QObject
{
    Q_OBJECT

private:

    QModelIndex m_point_start;
    QModelIndex m_point_finish;
    QHash<int,QModelIndex> m_way_tmp;
    QHash<int,QModelIndex> m_way;
    QHash<int,QModelIndex> m_way_zach;  //для зачистки петель
    QHash<int,QModelIndex> m_way_straight;  //для спрямления пути
    My_napr m_napr;
    unsigned long long  dlina_puti;
    unsigned long long ShortyWay;
    bool dom {false};
    bool map {false};
    int m_accuracy_val;    //точность вычисления
    QString m_str,m_str_2;
    Dijkstra_Point dijkstra_point;
    QVector<QVector<Dijkstra_Point>>arr_dijkstra;
    int number_global{0};

     int timer;
     int timer_interval{100};
     QModelIndex m_tmp_point_finish;
     int zdvig{0};

  //   QSet<Point_for_Fast_Dijkstra> Qset_for_fast_point_dij;


public:

    explicit My_Way(QObject *parent = nullptr);

      void Set_Point_start(QModelIndex& point) {m_point_start=point;}
      void Set_Point_finish(QModelIndex& point) {m_point_finish=point;}

      QModelIndex Get_Point_start(){return m_point_start;}              //поставить потом const
      QModelIndex Get_Point_finish(){return m_point_finish;}

      void FindingGType();
      void FindingStepType();
      void FindingByMinNear();
      void FindingByRandom();
      void Napravlenie();
      void Prorisovka();
      void StrippingLoops();
      void StraightThePath();
      void Dijkstra_krest_proverka(int,int);
      void Dijkstra_fast_krest_proverka(int&,int&);
      void Dijkstra_way();
      void Dijkstra_way_faster();

      void Dijkstra_way_like_4_square();
      void NextStepByTracing();


signals:
      void GetIndex(QModelIndex&,int,int);
      void PaintingWay(QModelIndex);
      void Way_long(int);
      void DrawingWay(bool);
      void GetXY(QModelIndex&);
      void Progress(int);
      void AlgName(QString);
      void DomIsTrue(bool);
      void AlgBrush(QColor);
      void Set_Start_Finish_Points(QModelIndex&,QModelIndex&);
      void Checked(bool);
      void Reached(bool);
      void Timer_lapse(int);

public slots:

    void Create_matrix_for_Dijkstra_faster();

    void Set_Accuracy_val(QString val) {m_accuracy_val=val.toInt();}

    void Get_Start_Finish_Points(QModelIndex& index_start,QModelIndex& index_finish){

        Set_Point_start(index_start);
        Set_Point_finish(index_finish);

    }



    void selected_Impassable(bool tmp){
        dom=tmp;
    }

    void clear_Way(){
        m_way.clear();
    }

    void map_is_selected(bool tmp){
        map=!tmp;
        emit DomIsTrue(true);
    }

    void map_is_not_selected(bool tmp){
        map=tmp;

      //  emit DomIsTrue(false);
    }




    void Finding_Way(){

        ShortyWay=-1;


        if (!dom && !map){
        FindingGType();
        FindingStepType();
        Dijkstra_way_like_4_square();
        }

        for (int i=0;i<m_accuracy_val;i++){

        if (!map){
        FindingByMinNear();
        }

        FindingByRandom();

        emit Progress((i+1)*100/m_accuracy_val);

        }
        emit AlgBrush(Qt::blue);
        DrawingWay(true);
        Prorisovka();
        DrawingWay(false);
    }

     void Finding_Dij_Way(){
         emit AlgBrush(Qt::darkMagenta);
         ShortyWay=-1;

         Dijkstra_way();

         DrawingWay(true);
         Prorisovka();
         DrawingWay(false);
     }




     void Finding_Tracing_Way(){

         ShortyWay=-1;
        // Dijkstra_way();
         Dijkstra_way_faster();
         zdvig=0;

        if (ShortyWay==(m_point_start.data().toInt()+m_point_finish.data().toInt())) {
            killTimer(timer);
            m_str_2.clear();
            m_str_2="REACHED!!";
            emit AlgName(m_str_2);
            emit Reached(true);
        } else
         { // timer_interval=m_point_start.data().toInt();        //-
           // killTimer(timer);                                   //-

          //  timer=startTimer(timer_interval);                   //-

              NextStepByTracing();
        }
}

     void ReachNotToTrace(){
         killTimer(timer);
         m_str_2.clear();
         m_str_2="REACHED!";
         emit AlgName(m_str_2);
     }


protected:
     virtual void timerEvent(QTimerEvent *event);
};

#endif // MY_WAY_H
