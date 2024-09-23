#include "my_way.h"

My_Way::My_Way(QObject *parent) : QObject(parent)
{

}


void My_Way::Prorisovka(){
     for(auto x :m_way){

      emit PaintingWay(x);
     }
}


void My_Way::Napravlenie(){
    if (m_point_start.row()>m_point_finish.row()){
        m_napr.x_napr=-1;
    } else  if (m_point_start.row()<m_point_finish.row()) m_napr.x_napr=1;
      else  if (m_point_start.row()==m_point_finish.row()) m_napr.x_napr=0;


    if (m_point_start.column()>m_point_finish.column()){
        m_napr.y_napr=-1;
    } else if (m_point_start.column()<m_point_finish.column()) m_napr.y_napr=1;
      else if (m_point_start.column()==m_point_finish.column()) m_napr.y_napr=0;

}

void My_Way::FindingGType(){

    Napravlenie();
//---------Г-тип
  {  m_way_tmp.clear();
    dlina_puti=0;
    int x1_graf=m_point_start.row();
    int y1_graf=m_point_start.column();

    int x2_graf=m_point_finish.row();
    int y2_graf=m_point_finish.column();//!

    int i=0;
    for (/*x1_graf*/; x1_graf!=x2_graf+m_napr.x_napr; x1_graf=m_napr.x_napr+x1_graf){
    QModelIndex index_tmp;
    emit GetIndex(index_tmp,x1_graf,y1_graf);
    m_way_tmp[i]=index_tmp;
 //   qDebug()<<m_way_tmp[i].data().toInt();
     i++;
    }
    for (y1_graf+=m_napr.y_napr;y1_graf!=y2_graf+m_napr.y_napr;y1_graf=m_napr.y_napr+y1_graf){
     QModelIndex index_tmp;
     emit GetIndex(index_tmp,x1_graf -m_napr.x_napr ,y1_graf); //!
     m_way_tmp[i]=index_tmp;
 //    qDebug()<<m_way_tmp[i].data().toInt();
     i++;
    }
    {
    QModelIndex index_tmp;
    emit GetIndex(index_tmp,m_point_start.row(),m_point_start.column());
    m_way_tmp[i]=index_tmp;
    i++;
    }

    for(auto x:m_way_tmp ){
        dlina_puti+=x.data().toInt();
    }
    if (dlina_puti<=ShortyWay) {
        m_way=std::move(m_way_tmp);
        ShortyWay=dlina_puti;
        emit Way_long(dlina_puti);
        m_str.clear();
        m_str="GTypeByAlgorithm";
        emit AlgName(m_str);

    }
    }
//--------- в другую сторону
  {  m_way_tmp.clear();
    dlina_puti=0;
    int x1_graf=m_point_start.row();
    int y1_graf=m_point_start.column();

    int x2_graf=m_point_finish.row();
    int y2_graf=m_point_finish.column();//!

    int i=0;
    for (/*x1_graf*/; y1_graf!=y2_graf+m_napr.y_napr; y1_graf=m_napr.y_napr+y1_graf){
    QModelIndex index_tmp;
    emit GetIndex(index_tmp,x1_graf,y1_graf);
    m_way_tmp[i]=index_tmp;
  //  qDebug()<<m_way_tmp[i].data().toInt();
     i++;
    }
    for (x1_graf+=m_napr.x_napr;x1_graf!=x2_graf+m_napr.x_napr;x1_graf=m_napr.x_napr+x1_graf){
     QModelIndex index_tmp;
     emit GetIndex(index_tmp,x1_graf,y1_graf-m_napr.y_napr);
     m_way_tmp[i]=index_tmp;
  //   qDebug()<<m_way_tmp[i].data().toInt();
     i++;
    }

    {
    QModelIndex index_tmp;
    emit GetIndex(index_tmp,m_point_start.row(),m_point_start.column());
    m_way_tmp[i]=index_tmp;
    i++;
    }

    for(auto x:m_way_tmp ){
        dlina_puti+=x.data().toInt();
    }
    if (dlina_puti<=ShortyWay) {
        m_way=std::move(m_way_tmp);
        ShortyWay=dlina_puti;
        emit Way_long(dlina_puti);
        m_str.clear();
        m_str="GTypeByAlgorithm";
        emit AlgName(m_str);
    }
}

   // qDebug()<<dlina_puti;
  //    qDebug()<<m_way[i].data().toInt();
  //  qDebug()<<m_napr.x_napr<<m_napr.y_napr;
}


void My_Way::FindingStepType(){
       Napravlenie();
  {      m_way_tmp.clear();
        dlina_puti=0;
        int x1_graf=m_point_start.row();
        int y1_graf=m_point_start.column();

        int x2_graf=m_point_finish.row();
        int y2_graf=m_point_finish.column();
    int i=0;
    QModelIndex index_tmp;
    emit GetIndex(index_tmp,x1_graf,y1_graf);
    m_way_tmp[i]=index_tmp;


    while((x1_graf!=x2_graf)||(y1_graf!=y2_graf)){
        if (x1_graf!=x2_graf){
            x1_graf=m_napr.x_napr+x1_graf;
            i++;
            QModelIndex index_tmp;
            emit GetIndex(index_tmp,x1_graf,y1_graf);
            m_way_tmp[i]=index_tmp;
        }
        if (y1_graf!=y2_graf){
            y1_graf=m_napr.y_napr+y1_graf;
            i++;
            QModelIndex index_tmp;
            emit GetIndex(index_tmp,x1_graf,y1_graf);
            m_way_tmp[i]=index_tmp;
        }
    }
    for(auto x:m_way_tmp ){
        dlina_puti+=x.data().toInt();
    }
    if (dlina_puti<=ShortyWay) {
        m_way=std::move(m_way_tmp);
        ShortyWay=dlina_puti;
        emit Way_long(dlina_puti);
        m_str.clear();
        m_str="StepByAlgorithm";
        emit AlgName(m_str);
    }
  }
//--в другую сторону
{   m_way_tmp.clear();
    dlina_puti=0;
    int x1_graf=m_point_start.row();
    int y1_graf=m_point_start.column();

    int x2_graf=m_point_finish.row();
    int y2_graf=m_point_finish.column();
    int i=0;
    QModelIndex index_tmp;
    emit GetIndex(index_tmp,x1_graf,y1_graf);
    m_way_tmp[i]=index_tmp;
    while((x1_graf!=x2_graf)||(y1_graf!=y2_graf)){
        if (y1_graf!=y2_graf){
            y1_graf=m_napr.y_napr+y1_graf;
            i++;
            QModelIndex index_tmp;
            emit GetIndex(index_tmp,x1_graf,y1_graf);
            m_way_tmp[i]=index_tmp;
        }
        if (x1_graf!=x2_graf){
            x1_graf=m_napr.x_napr+x1_graf;
            i++;
            QModelIndex index_tmp;
            emit GetIndex(index_tmp,x1_graf,y1_graf);
            m_way_tmp[i]=index_tmp;
        }
    }
    for(auto x:m_way_tmp ){
        dlina_puti+=x.data().toInt();
    }
    if (dlina_puti<=ShortyWay) {
        m_way=std::move(m_way_tmp);
        ShortyWay=dlina_puti;
        emit Way_long(dlina_puti);
        m_str.clear();
        m_str="StepByAlgorithm";
        emit AlgName(m_str);
    }

}
}

void My_Way::FindingByMinNear(){

            m_way_tmp.clear();
            dlina_puti=0;
            int x1_graf=m_point_start.row();
            int y1_graf=m_point_start.column();

            int x2_graf=m_point_finish.row();
            int y2_graf=m_point_finish.column();

            int i =0;
            int povtor_rand=0;

            My_napr old_napr{0,0};

            My_napr rand_napr{1,1};


            //стр 1087 ?
            QModelIndex index_tmp;
            emit GetIndex(index_tmp,x1_graf,y1_graf);
            m_way_tmp[i]=index_tmp;

            QModelIndex index_1;
            QModelIndex index_2;
            QModelIndex index_3;
            QModelIndex index_4;

            while((x1_graf!=x2_graf)||(y1_graf!=y2_graf)){

              emit GetIndex(index_1,x1_graf-1,y1_graf);
              emit GetIndex(index_2,x1_graf,y1_graf-1);
              emit GetIndex(index_3,x1_graf,y1_graf+1);
              emit GetIndex(index_4,x1_graf+1,y1_graf);

            if ((index_1.data()<=index_2.data())&&
                (index_1.data()<=index_3.data())&&
                (index_1.data()<=index_4.data()))
            {
                m_napr.x_napr=-1;
                m_napr.y_napr=0;
            }

            else if ((index_4.data()<=index_2.data())&&
                (index_4.data()<=index_3.data())&&
                (index_4.data()<=index_1.data()))
            {
                m_napr.x_napr=1;
                m_napr.y_napr=0;
            }

           else if ((index_2.data()<=index_3.data())&&
                (index_2.data()<=index_4.data())&&
                (index_2.data()<=index_1.data()))
            {
                m_napr.x_napr=0;
                m_napr.y_napr=-1;
            }

           else if ((index_3.data()<=index_2.data())&&
                (index_3.data()<=index_4.data())&&
                (index_3.data()<=index_1.data()))
            {
                m_napr.x_napr=0;
                m_napr.y_napr=1;
            }

            //дополнение к проверке повтора пути

            if((m_napr.x_napr*rand_napr.x_napr!=0)||(m_napr.y_napr*rand_napr.y_napr!=0)){
                m_napr.x_napr=m_napr.x_napr*rand_napr.x_napr;
                m_napr.y_napr=m_napr.y_napr*rand_napr.y_napr;
            } else
            {
                m_napr.x_napr=rand_napr.x_napr;
                m_napr.y_napr=rand_napr.y_napr;
            }

            //проверка повтора пути ближайших точек

            if ((m_napr.y_napr==0)&&(m_napr.x_napr+old_napr.x_napr==0)){
                 m_napr.x_napr=0;
                 if (index_2.data()<=index_3.data())
                     m_napr.y_napr=-1;
                 else
                     m_napr.y_napr=1;

            QModelIndex index_old;
            emit GetIndex(index_old,x1_graf+old_napr.x_napr,y1_graf);
            if ((index_old.data().toInt()<=index_2.data().toInt())&&(index_old.data().toInt()<=index_3.data().toInt())){
                m_napr.y_napr=0;
                m_napr.x_napr=old_napr.x_napr;
            } else m_napr.x_napr=0;  //1151

            }

            if ((m_napr.x_napr==0)&&(m_napr.y_napr+old_napr.y_napr==0)){
                m_napr.y_napr=0;
                if (index_1.data().toInt()<=index_4.data().toInt())
                    m_napr.x_napr=-1;
                else m_napr.x_napr=1;

            QModelIndex index_old;
            emit GetIndex(index_old,x1_graf,y1_graf+old_napr.y_napr);
               if ((index_old.data().toInt()<=index_1.data().toInt())&&(index_old.data().toInt()<=index_4.data().toInt())){
                   m_napr.x_napr=0;
                   m_napr.y_napr=old_napr.y_napr;
               } else m_napr.y_napr=0; //1167

            }

        //проверка условия на выхода за границы
           if (x1_graf+m_napr.x_napr<0){
               m_napr.x_napr=0;
               if (index_2.data().toInt()<=index_3.data().toInt()){
                   m_napr.y_napr=-1;
               } else m_napr.y_napr=1;
               if (m_napr.y_napr+old_napr.y_napr==0)
                   m_napr.y_napr=(-1)*m_napr.y_napr;
               QModelIndex index_napr;
               emit GetIndex(index_napr,x1_graf,y1_graf+m_napr.y_napr);
               if (index_4.data().toInt()<=index_napr.data().toInt()) {
                   m_napr.x_napr=1;
                   if(m_napr.x_napr+old_napr.x_napr!=0)
                       m_napr.y_napr=0;
                   else m_napr.x_napr=0;
               }
           } //1190

          QModelIndex index_XY;
          emit GetXY(index_XY);
      //    qDebug()<<index_XY.row()<<index_XY.column();

          if (x1_graf+m_napr.x_napr>index_XY.row()) {   //1193
              m_napr.x_napr=0;
              if (index_2.data().toInt()<=index_3.data().toInt()){
                  m_napr.y_napr=-1;
              } else m_napr.y_napr=1;
              if (m_napr.y_napr+old_napr.y_napr==0)
                  m_napr.y_napr=(-1)*m_napr.y_napr;   //1202
              QModelIndex index_napr;
              emit GetIndex(index_napr,x1_graf,y1_graf+m_napr.y_napr);
              if(index_1.data().toInt()<=index_napr.data().toInt()){
                  m_napr.x_napr=-1;
                  if(m_napr.x_napr+old_napr.x_napr!=0)
                      m_napr.y_napr=0;
                  else m_napr.x_napr=0;
              }
          }

          if(y1_graf+m_napr.y_napr<0){       //1213
          m_napr.y_napr=0;
          if(index_1.data().toInt()<=index_4.data().toInt()){
              m_napr.x_napr=-1;
          } else m_napr.x_napr=1;
          if(m_napr.x_napr+old_napr.x_napr==0)
          m_napr.x_napr=(-1)*m_napr.x_napr;
          QModelIndex index_napr;
          emit GetIndex(index_napr,x1_graf+m_napr.x_napr,y1_graf);
          if (index_3.data().toInt()<=index_napr.data().toInt()) {
              m_napr.y_napr=1;
              if (m_napr.y_napr+old_napr.y_napr!=0)
                  m_napr.x_napr=0;
              else
                  m_napr.y_napr=0;
           }
          }

          if (y1_graf+m_napr.y_napr>index_XY.column()){         //1234
              m_napr.y_napr=0;
              if(index_1.data().toInt()<=index_4.data().toInt()){
                  m_napr.x_napr=-1;
              } else
                  m_napr.x_napr=1;
              if (m_napr.x_napr+old_napr.x_napr==0)
                  m_napr.x_napr=(-1)*m_napr.x_napr;
              QModelIndex index_napr;
              emit GetIndex(index_napr,x1_graf+m_napr.x_napr,y1_graf);
              if (index_2.data().toInt()<=index_napr.data().toInt()) {
                  m_napr.y_napr=-1;
                  if (m_napr.y_napr+old_napr.y_napr!=0)
                      m_napr.x_napr=0;
                  else
                      m_napr.y_napr=0;
              }
          }

          //проверка на угловых точках
          if ((x1_graf+m_napr.x_napr<0)&&(y1_graf==0)){
              m_napr.x_napr=0;
              m_napr.y_napr=1;
              if (m_napr.y_napr+old_napr.y_napr==0){
                  m_napr.y_napr=0;
                  m_napr.x_napr=1;
              }
          }
          if ((y1_graf+m_napr.y_napr<0)&&(x1_graf==0)){
              m_napr.y_napr=0;
              m_napr.x_napr=1;
              if (m_napr.x_napr+old_napr.x_napr==0){
                  m_napr.x_napr=0;
                  m_napr.y_napr=1;
              }
          }
          if ((x1_graf+m_napr.x_napr>index_XY.row())&&(y1_graf==0)){
              m_napr.x_napr=0;
              m_napr.y_napr=1;
              if (m_napr.y_napr+old_napr.y_napr==0){
                  m_napr.y_napr=0;
                  m_napr.x_napr=-1;
              }
          }
          if((y1_graf+m_napr.y_napr<0)&&(x1_graf==index_XY.row())){
              m_napr.y_napr=0;
              m_napr.x_napr=-1;
              if (m_napr.x_napr+old_napr.x_napr==0){
                  m_napr.x_napr=0;
                  m_napr.y_napr=1;
              }
          }
          if ((x1_graf+m_napr.x_napr<0)&&(y1_graf==index_XY.column())){
              m_napr.x_napr=0;
              m_napr.y_napr=-1;
              if (m_napr.y_napr+old_napr.y_napr==0){
                  m_napr.y_napr=0;
                  m_napr.x_napr=1;
              }
          }
           if((y1_graf+m_napr.y_napr>index_XY.column())&&(x1_graf==0)){
               m_napr.y_napr=0;
               m_napr.x_napr=1;
               if (m_napr.x_napr+old_napr.x_napr==0){
                   m_napr.x_napr=0;
                   m_napr.y_napr=-1;
               }
           }
           if((x1_graf+m_napr.x_napr>index_XY.row())&&(y1_graf==index_XY.column())){
               m_napr.x_napr=0;
               m_napr.y_napr=-1;
               if (m_napr.y_napr+old_napr.y_napr==0){
                   m_napr.y_napr=0;
                   m_napr.x_napr=-1;
               }
           }
           if((y1_graf+m_napr.y_napr>index_XY.column())&&(x1_graf==index_XY.row())){
               m_napr.y_napr=0;
               m_napr.x_napr=-1;
               if (m_napr.x_napr+old_napr.x_napr==0){
                   m_napr.x_napr=0;
                   m_napr.y_napr=-1;
               }
           }

           //проверка на нахождение рядом с финишом 1340
           if((x1_graf+1==x2_graf)&&(y1_graf==y2_graf)){
               m_napr.x_napr=1;
               m_napr.y_napr=0;
           }
           if((x1_graf-1==x2_graf)&&(y1_graf==y2_graf)){
               m_napr.x_napr=-1;
               m_napr.y_napr=0;
           }
           if((x1_graf==x2_graf)&&(y1_graf+1==y2_graf)){
               m_napr.x_napr=0;
               m_napr.y_napr=1;
           }
           if((x1_graf==x2_graf)&&(y1_graf-1==y2_graf)){
               m_napr.x_napr=0;
               m_napr.y_napr=-1;
           }

           //выбор, когда 2 рядом одинаковые на выбор  1366             //? перепроверить, если будет ошибка
           // или это проверка на дом?
           {
               QModelIndex index_napr;
               emit GetIndex(index_napr,x1_graf+m_napr.x_napr,y1_graf+m_napr.y_napr);
               if (/*(dom==true)&&*/(index_napr.data().toInt()==0)){
                   old_napr.x_napr=m_napr.x_napr;
                   old_napr.y_napr=m_napr.y_napr;
                   m_napr.x_napr=0;
                   m_napr.y_napr=0;
                   povtor_rand=0;
                   rand_napr.x_napr=1;
                   rand_napr.y_napr=1;
               }
               x1_graf=m_napr.x_napr+x1_graf;
               y1_graf=m_napr.y_napr+y1_graf;

               old_napr.x_napr=m_napr.x_napr;
               old_napr.y_napr=m_napr.y_napr;
           }
           //проверка повтора пути   1383                             (1384-1390)    ??
           {
               povtor_rand=rand()%4;

               if (povtor_rand==0){
               rand_napr.x_napr=-1;
               rand_napr.y_napr=0;
               }
               if (povtor_rand==1){
               rand_napr.x_napr=1;
               rand_napr.y_napr=0;
               }
               if (povtor_rand==2){
               rand_napr.x_napr=0;
               rand_napr.y_napr=1;
               }
               if (povtor_rand==3){
               rand_napr.x_napr=0;
               rand_napr.y_napr=-1;
               }
           }
           //1429
           {
           i++;
           QModelIndex index_tmp;
           emit GetIndex(index_tmp,x1_graf,y1_graf);
           m_way_tmp[i]=index_tmp;
          }
           //зачем-то вводил i_pogreshnost                                            ?это для повторов расчетов
    //    qDebug()<<m_way_tmp[i].data().toInt();
  }
            m_str.clear();
        //    m_str="Near";


            for(auto x:m_way_tmp ){
                dlina_puti+=x.data().toInt();
            }
            StrippingLoops();                  //!
            StraightThePath();

            if (dlina_puti<ShortyWay) {
                m_str_2.clear();
                m_str_2="Near"+m_str;
                m_way=std::move(m_way_tmp);
                ShortyWay=dlina_puti;
                emit Way_long(dlina_puti);
                emit AlgName(m_str_2);
               }

//                 DrawingWay(true);
//                 Prorisovka();
//                 DrawingWay(false);


//            for (int i=0; i< m_way.size();i++)
//                qDebug()<<m_way[i].data();


}


void My_Way::StrippingLoops(){  //убираю петли //2009


     m_way_zach.clear();

     { int j=0;
      for (int i=0;i<m_way_tmp.size();i++){
          if (m_way_tmp[i].isValid()/*data().toInt()!=0*/)
          m_way_zach.insert(j,m_way_tmp[i]);
          j++;
      }
     }


     int dlina_puti_strip=0;

    int size= m_way_zach.size();

     for(int i=0;i!=m_way_zach.size()/*size*/;i++){
        if(m_way_zach[i].isValid()/*data().toInt()!=0*/)
          for (int k=m_way_zach.size()/*size*/-i;k!=/*0*/2;k--){
              if (((m_way_zach[i].row()==m_way_zach[i+k].row())&&((m_way_zach[i].column()==m_way_zach[i+k].column()+1) ||
                                                                   (m_way_zach[i].column()==m_way_zach[i+k].column()-1))&&
                   (m_way_zach[i].row()!=0)&&(m_way_zach[i+k].row()!=0))
                      || ((m_way_zach[i].column()==m_way_zach[i+k].column())&&((m_way_zach[i].row()==m_way_zach[i+k].row()+1) ||
                                                                              (m_way_zach[i].row()==m_way_zach[i+k].row()-1))&&
                         (m_way_zach[i].column()!=0)&&(m_way_zach[i+k].column()!=0))){         //2083-2099

                  for (int j=1;j<k;j++){
                      m_way_zach.remove(i+j);
                  }

//                  for(int j=1;j<k;j++)
//                  {
//                   QHash<int,QModelIndex>::iterator it_1 = m_way_zach.find(i+j);            //-
//                   m_way_zach.erase(it_1);
//                  }

              }
          }
     }
     for(auto x:m_way_zach ){
              dlina_puti_strip+=x.data().toInt();
          }

          if ((dlina_puti_strip<dlina_puti)&&(dlina_puti_strip!=0)) {
              m_way_tmp.clear();


        int j=0;
        for (int i=0;i<m_way_zach.capacity();i++){
            if (m_way_zach[i].isValid()/*data().toInt()!=0*/){
            m_way_tmp.insert(j,m_way_zach[i]);
              j++;
            }
         }

    //    m_way_zach.clear();
        m_str+="+Knots";
      //  emit AlgName(m_str);
     //   dlina_puti=dlina_puti_strip;
       }
dlina_puti=dlina_puti_strip;
m_way_zach.clear();
}




void My_Way::StraightThePath(){                             //2196
        m_way_straight.clear();

       { int j=0;
        for (int i=0;i<m_way_tmp.size();i++){
            if (m_way_tmp[i].isValid()/*.data().toInt()!=0*/)
            m_way_straight.insert(j,m_way_tmp[i]);
            j++;
        }
       }

        int dlina_puti_straight=0;
        int size= m_way_straight.size();


        for(int i=0;i!=/*m_way_tmp.size()*/size;i++){
          //    if(m_way_zach[i].isValid()/*data().toInt()!=0*/)
             for (int k=/*m_way_tmp.size()*/size-i;k!=0;k--){
            //     emit GetIndex(index_1,x1_graf-1,y1_graf);
                 QModelIndex index; emit GetIndex(index,(m_way_straight[i].row()+m_way_straight[i+k].row())/2 /*-1*/,
                                                (m_way_straight[i].column()+m_way_straight[i+k].column())/2 /*-1*/);
//                 QModelIndex index_2; emit GetIndex(index,(m_way_straight[i].row()+m_way_straight[i+k].row())/2 -1,
//                                                (m_way_straight[i].column()+m_way_straight[i+k].column())/2 -1);


                   if ((((m_way_straight[i].row()==m_way_straight[i+k].row())&&(( m_way_straight[i].column()== (m_way_straight[i+k].column()+2))||
                                                                                 ( m_way_straight[i].column()== (m_way_straight[i+k].column()-2)))&&
                         (( m_way_straight[i].row()!=0))&&(( m_way_straight[i+1].row()!=0)))||
                         (( m_way_straight[i].column()== m_way_straight[i+k].column())&&(( m_way_straight[i].row()== (m_way_straight[i+k].row()+2))||
                                                                                 ( m_way_straight[i].row()== (m_way_straight[i+k].row()-2)))&&
                         (( m_way_straight[i].column()!=0))&&((m_way_straight[i+1].column()!=0))))
                                                              && (index.data().toInt()!=0)
                                                              /*&& (index_2.data().isValid())*/ ){           //2261



                         for (int j=1/*i*/;j<k;j++){
                           m_way_straight.remove(i+j);
                       }
                            m_way_straight.insert(i+1,index);
//                           for(int j=1;j<k;j++)
//                           if (m_way_straight[i+j].data().toInt()!=0)
//                           {
//                            QHash<int,QModelIndex>::iterator it_1 = m_way_straight.find(i+j);            //заменил цикл выше
//                            m_way_straight.erase(it_1);
//                           }



//                       QModelIndex index_1;                                                                             //ТУТ ПОДУМАТЬ!
//              //         emit GetIndex(index_1,m_way_straight[i+1].row()-1, m_way_straight[i+1].column()-1);
//        emit GetIndex(index_1,(m_way_straight[i].row()+m_way_straight[i+k].row())/2, (m_way_straight[i].column()+m_way_straight[i+k].column())/2);
//             //     if (index_1.data().toInt()!=0)            //?
//                  m_way_straight.insert(i+1,index_1);
            }
          }
        }

        for(auto x:m_way_straight ){
                 dlina_puti_straight+=x.data().toInt();
             }


             if ((dlina_puti_straight<dlina_puti)&&(dlina_puti_straight!=0)) {
                 m_way_tmp.clear();


           int j=0;
           for (int i=0;i<m_way_straight.capacity();i++){
               if (m_way_straight[i].isValid()/*data().toInt()!=0*/) {
                   m_way_tmp.insert(j,m_way_straight[i]);
                   j++;
            }
           }


      //     m_way_straight.clear();
           m_str+="+Strght";
       //    emit AlgName(m_str);
     //      dlina_puti=dlina_puti_straight;

          }
//             for(int i=0;i!=m_way_tmp.size();i++){
//                    qDebug()<<m_way_tmp[i].data().toInt();
//                     }
 m_way_straight.clear();
dlina_puti=dlina_puti_straight;
}


void My_Way::FindingByRandom(){

            m_way_tmp.clear();
            dlina_puti=0;
            int x1_graf=m_point_start.row();
            int y1_graf=m_point_start.column();

            int x2_graf=m_point_finish.row();
            int y2_graf=m_point_finish.column();

            int i =0;
            int rand_napr=0;

            My_napr old_napr{0,0};

          //  My_napr rand_napr{1,1};



            QModelIndex index_tmp;
            emit GetIndex(index_tmp,x1_graf,y1_graf);
            m_way_tmp[i]=index_tmp;

            QModelIndex index_1;
            QModelIndex index_2;
            QModelIndex index_3;
            QModelIndex index_4;

            while((x1_graf!=x2_graf)||(y1_graf!=y2_graf)){

                rand_napr=rand()%4;
                switch (rand_napr) {
                case 0:
                    m_napr.x_napr=-1;
                    m_napr.y_napr=0;
                    break;
                case 1:
                    m_napr.x_napr=1;
                    m_napr.y_napr=0;
                    break;
                case 2:
                    m_napr.x_napr=0;
                    m_napr.y_napr=1;
                    break;
                case 3:
                    m_napr.x_napr=0;
                    m_napr.y_napr=-1;
                    break;
               }

              emit GetIndex(index_1,x1_graf-1,y1_graf);
              emit GetIndex(index_2,x1_graf,y1_graf-1);
              emit GetIndex(index_3,x1_graf,y1_graf+1);
              emit GetIndex(index_4,x1_graf+1,y1_graf);




            //проверка повтора пути ближайших точек

            if ((m_napr.y_napr==0)&&(m_napr.x_napr+old_napr.x_napr==0)){            //1529
                 m_napr.x_napr=0;
                 if (index_2.data()<=index_3.data())
                     m_napr.y_napr=-1;
                 else
                     m_napr.y_napr=1;

            QModelIndex index_old;
            emit GetIndex(index_old,x1_graf+old_napr.x_napr,y1_graf);
            if ((index_old.data().toInt()<=index_2.data().toInt())&&(index_old.data().toInt()<=index_3.data().toInt())){
                m_napr.y_napr=0;
                m_napr.x_napr=old_napr.x_napr;
            } else m_napr.x_napr=0;  //1542

            }

            if ((m_napr.x_napr==0)&&(m_napr.y_napr+old_napr.y_napr==0)){
                m_napr.y_napr=0;
                if (index_1.data().toInt()<=index_4.data().toInt())
                    m_napr.x_napr=-1;
                else m_napr.x_napr=1;

            QModelIndex index_old;
            emit GetIndex(index_old,x1_graf,y1_graf+old_napr.y_napr);
               if ((index_old.data().toInt()<=index_1.data().toInt())&&(index_old.data().toInt()<=index_4.data().toInt())){
                   m_napr.x_napr=0;
                   m_napr.y_napr=old_napr.y_napr;
               } else m_napr.y_napr=0; //1558

            }

        //проверка условия на выхода за границы     1561
           if (x1_graf+m_napr.x_napr<0){
               m_napr.x_napr=0;
               if (index_2.data().toInt()<=index_3.data().toInt()){
                   m_napr.y_napr=-1;
               } else m_napr.y_napr=1;
               if (m_napr.y_napr+old_napr.y_napr==0)
                   m_napr.y_napr=(-1)*m_napr.y_napr;
               QModelIndex index_napr;
               emit GetIndex(index_napr,x1_graf,y1_graf+m_napr.y_napr);
               if (index_4.data().toInt()<=index_napr.data().toInt()) {
                   m_napr.x_napr=1;
                   if(m_napr.x_napr+old_napr.x_napr!=0)
                       m_napr.y_napr=0;
                   else m_napr.x_napr=0;
               }
           } //1580

          QModelIndex index_XY;
          emit GetXY(index_XY);
      //    qDebug()<<index_XY.row()<<index_XY.column();

          if (x1_graf+m_napr.x_napr>index_XY.row()) {   //1583
              m_napr.x_napr=0;
              if (index_2.data().toInt()<=index_3.data().toInt()){
                  m_napr.y_napr=-1;
              } else m_napr.y_napr=1;
              if (m_napr.y_napr+old_napr.y_napr==0)
                  m_napr.y_napr=(-1)*m_napr.y_napr;   //1593
              QModelIndex index_napr;
              emit GetIndex(index_napr,x1_graf,y1_graf+m_napr.y_napr);
              if(index_1.data().toInt()<=index_napr.data().toInt()){
                  m_napr.x_napr=-1;
                  if(m_napr.x_napr+old_napr.x_napr!=0)
                      m_napr.y_napr=0;
                  else m_napr.x_napr=0;
              }
          }

          if(y1_graf+m_napr.y_napr<0){       //1604
          m_napr.y_napr=0;
          if(index_1.data().toInt()<=index_4.data().toInt()){
              m_napr.x_napr=-1;
          } else m_napr.x_napr=1;
          if(m_napr.x_napr+old_napr.x_napr==0)
          m_napr.x_napr=(-1)*m_napr.x_napr;
          QModelIndex index_napr;
          emit GetIndex(index_napr,x1_graf+m_napr.x_napr,y1_graf);
          if (index_3.data().toInt()<=index_napr.data().toInt()) {
              m_napr.y_napr=1;
              if (m_napr.y_napr+old_napr.y_napr!=0)
                  m_napr.x_napr=0;
              else
                  m_napr.y_napr=0;
           }
          }

          if (y1_graf+m_napr.y_napr>index_XY.column()){         //1625
              m_napr.y_napr=0;
              if(index_1.data().toInt()<=index_4.data().toInt()){
                  m_napr.x_napr=-1;
              } else
                  m_napr.x_napr=1;
              if (m_napr.x_napr+old_napr.x_napr==0)
                  m_napr.x_napr=(-1)*m_napr.x_napr;
              QModelIndex index_napr;
              emit GetIndex(index_napr,x1_graf+m_napr.x_napr,y1_graf);
              if (index_2.data().toInt()<=index_napr.data().toInt()) {
                  m_napr.y_napr=-1;
                  if (m_napr.y_napr+old_napr.y_napr!=0)
                      m_napr.x_napr=0;
                  else
                      m_napr.y_napr=0;
              }
          }

          //проверка на угловых точках
          if ((x1_graf+m_napr.x_napr<0)&&(y1_graf==0)){
              m_napr.x_napr=0;
              m_napr.y_napr=1;
              if (m_napr.y_napr+old_napr.y_napr==0){
                  m_napr.y_napr=0;
                  m_napr.x_napr=1;
              }
          }
          if ((y1_graf+m_napr.y_napr<0)&&(x1_graf==0)){
              m_napr.y_napr=0;
              m_napr.x_napr=1;
              if (m_napr.x_napr+old_napr.x_napr==0){
                  m_napr.x_napr=0;
                  m_napr.y_napr=1;
              }
          }
          if ((x1_graf+m_napr.x_napr>index_XY.row())&&(y1_graf==0)){
              m_napr.x_napr=0;
              m_napr.y_napr=1;
              if (m_napr.y_napr+old_napr.y_napr==0){
                  m_napr.y_napr=0;
                  m_napr.x_napr=-1;
              }
          }
          if((y1_graf+m_napr.y_napr<0)&&(x1_graf==index_XY.row())){
              m_napr.y_napr=0;
              m_napr.x_napr=-1;
              if (m_napr.x_napr+old_napr.x_napr==0){
                  m_napr.x_napr=0;
                  m_napr.y_napr=1;
              }
          }
          if ((x1_graf+m_napr.x_napr<0)&&(y1_graf==index_XY.column())){
              m_napr.x_napr=0;
              m_napr.y_napr=-1;
              if (m_napr.y_napr+old_napr.y_napr==0){
                  m_napr.y_napr=0;
                  m_napr.x_napr=1;
              }
          }
           if((y1_graf+m_napr.y_napr>index_XY.column())&&(x1_graf==0)){
               m_napr.y_napr=0;
               m_napr.x_napr=1;
               if (m_napr.x_napr+old_napr.x_napr==0){
                   m_napr.x_napr=0;
                   m_napr.y_napr=-1;
               }
           }
           if((x1_graf+m_napr.x_napr>index_XY.row())&&(y1_graf==index_XY.column())){
               m_napr.x_napr=0;
               m_napr.y_napr=-1;
               if (m_napr.y_napr+old_napr.y_napr==0){
                   m_napr.y_napr=0;
                   m_napr.x_napr=-1;
               }
           }
           if((y1_graf+m_napr.y_napr>index_XY.column())&&(x1_graf==index_XY.row())){
               m_napr.y_napr=0;
               m_napr.x_napr=-1;
               if (m_napr.x_napr+old_napr.x_napr==0){
                   m_napr.x_napr=0;
                   m_napr.y_napr=-1;
               }
           }

           //проверка на нахождение рядом с финишом 1731
           if((x1_graf+1==x2_graf)&&(y1_graf==y2_graf)){
               m_napr.x_napr=1;
               m_napr.y_napr=0;
           }
           if((x1_graf-1==x2_graf)&&(y1_graf==y2_graf)){
               m_napr.x_napr=-1;
               m_napr.y_napr=0;
           }
           if((x1_graf==x2_graf)&&(y1_graf+1==y2_graf)){
               m_napr.x_napr=0;
               m_napr.y_napr=1;
           }
           if((x1_graf==x2_graf)&&(y1_graf-1==y2_graf)){
               m_napr.x_napr=0;
               m_napr.y_napr=-1;
           }

           //выбор, когда 2 рядом одинаковые на выбор  1366             //? перепроверить, если будет ошибка
           // или это проверка на дом?
           {                                                            //1175
               QModelIndex index_napr;
               emit GetIndex(index_napr,x1_graf+m_napr.x_napr,y1_graf+m_napr.y_napr);
               if (/*(dom==true)&&*/(index_napr.data().toInt()==0)){
                   old_napr.x_napr=m_napr.x_napr;
                   old_napr.y_napr=m_napr.y_napr;
                   m_napr.x_napr=0;
                   m_napr.y_napr=0;
               //    povtor_rand=0;
               //    rand_napr.x_napr=1;
               //    rand_napr.y_napr=1;
               }
               x1_graf=m_napr.x_napr+x1_graf;
               y1_graf=m_napr.y_napr+y1_graf;

               old_napr.x_napr=m_napr.x_napr;
               old_napr.y_napr=m_napr.y_napr;

           }
           //1768

           {
           i++;
           QModelIndex index_tmp;
           emit GetIndex(index_tmp,x1_graf,y1_graf);
           m_way_tmp[i]=index_tmp;
          }

  }
            m_str.clear();
        //    m_str="Random";


            for(auto x:m_way_tmp ){
                dlina_puti+=x.data().toInt();
            }
           StrippingLoops();                  //!
           StraightThePath();


            if (dlina_puti<ShortyWay) {
                m_str_2.clear();
                m_str_2="Random"+m_str;
                m_way=std::move(m_way_tmp);
                ShortyWay=dlina_puti;
                emit Way_long(dlina_puti);
                emit AlgName(m_str_2);
               }



}


void My_Way::Dijkstra_way_like_4_square(){          //первый вариант. не используется. не работатет по петлям. просто для сохранности

    int x1_graf=m_point_start.row();
    int y1_graf=m_point_start.column();


    int x2_graf=m_point_finish.row();
    int y2_graf=m_point_finish.column();

    QModelIndex index_XY;
    emit GetXY(index_XY);

    arr_dijkstra.clear();
    //---создаю матрицу для алгоритма
    QVector<QVector<Dijkstra_Point>>arr_dijkstra;

    int num=0;
    arr_dijkstra.reserve(index_XY.row());

    for (int i=0; i<=index_XY.row();i++){
          QVector<Dijkstra_Point> temp_vector;
          temp_vector.reserve(index_XY.column());
        for (int j=0;j<=index_XY.column();j++){

        QModelIndex index_tmp;
        emit GetIndex(index_tmp,i,j);

        num++;

      //  dijkstra_point.number=num;
//        if (index_tmp.data().toInt()==0)
//            dijkstra_point.point_is_enable=false;
//        else
        dijkstra_point.point_is_enable=true;

        dijkstra_point.point_label=0;
        dijkstra_point.edge_length=index_tmp.data().toInt();
        if (dijkstra_point.edge_length==0) dijkstra_point.point_is_enable=false;

        temp_vector.push_back(dijkstra_point);

    }
        arr_dijkstra.push_back(temp_vector);
        temp_vector.clear();
    }
   //---

  //  qDebug()<<arr_dijkstra[x1_graf][y1_graf].edge_length<<" "<<x1_graf;

     arr_dijkstra[x1_graf][y1_graf].point_label= arr_dijkstra[x1_graf][y1_graf].edge_length;

    /////////////
    //  V  //  //
    /////////////
    //    //   //
    /////////////
     for (int i=x1_graf;i>=0;i--)
        for (int j=y1_graf;j>=0;j--)
          if (arr_dijkstra[i][j].point_is_enable)
        {
              if (j-1>=0)             //левая клетка
              {
                if (arr_dijkstra[i][j-1].point_label==0 && arr_dijkstra[i][j-1].point_is_enable ) {
                    arr_dijkstra[i][j-1].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i][j-1].edge_length;
                    }
                else {  if (arr_dijkstra[i][j-1].point_is_enable)
                            if (arr_dijkstra[i][j-1].point_label>arr_dijkstra[i][j].point_label+arr_dijkstra[i][j-1].edge_length)
                                arr_dijkstra[i][j-1].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i][j-1].edge_length;
                }
              }


              if (j+1<index_XY.column())             //правая клетка
              {
                if (arr_dijkstra[i][j+1].point_label==0 && arr_dijkstra[i][j+1].point_is_enable) {
                    arr_dijkstra[i][j+1].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i][j+1].edge_length;
                    }
                else {  if (arr_dijkstra[i][j+1].point_is_enable)
                            if (arr_dijkstra[i][j+1].point_label>arr_dijkstra[i][j].point_label+arr_dijkstra[i][j+1].edge_length)
                                arr_dijkstra[i][j+1].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i][j+1].edge_length;
                }
              }
              if (i-1>=0)             //верхняя клетка
              {
                if (arr_dijkstra[i-1][j].point_label==0 && arr_dijkstra[i-1][j].point_is_enable) {
                    arr_dijkstra[i-1][j].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i-1][j].edge_length;
                    }
                else {  if (arr_dijkstra[i-1][j].point_is_enable)
                            if (arr_dijkstra[i-1][j].point_label>arr_dijkstra[i][j].point_label+arr_dijkstra[i-1][j].edge_length)
                                arr_dijkstra[i-1][j].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i-1][j].edge_length;
                }
              }
              if (i+1<index_XY.row())             //нижняя клетка
              {
                if (arr_dijkstra[i+1][j].point_label==0 && arr_dijkstra[i+1][j].point_is_enable) {
                    arr_dijkstra[i+1][j].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i+1][j].edge_length;
                    }
                else {  if (arr_dijkstra[i+1][j].point_is_enable)
                            if (arr_dijkstra[i+1][j].point_label>arr_dijkstra[i][j].point_label+arr_dijkstra[i+1][j].edge_length)
                                arr_dijkstra[i+1][j].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i+1][j].edge_length;
                }
              }
        arr_dijkstra[i][j].point_is_enable=false;
        }


//         for (int i=0;i<=x1_graf;i++) {
//             for (int j=0;j<=y1_graf;j++){
//                  qDebug()<<arr_dijkstra[i][j].point_label;}
//              qDebug()<<"\n";
//         }



     /////////////
     //     //  //
     /////////////
     // V  //   //
     /////////////
      for (int i=x1_graf;i<=index_XY.row();i++)
         for (int j=y1_graf;j>=0;j--)
           if (arr_dijkstra[i][j].point_is_enable)
         {
               if (j-1>=0)             //левая клетка
               {
                 if (arr_dijkstra[i][j-1].point_label==0 && arr_dijkstra[i][j-1].point_is_enable) {
                     arr_dijkstra[i][j-1].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i][j-1].edge_length;
                     }
                 else {  if (arr_dijkstra[i][j-1].point_is_enable)
                             if (arr_dijkstra[i][j-1].point_label>arr_dijkstra[i][j].point_label+arr_dijkstra[i][j-1].edge_length)
                                 arr_dijkstra[i][j-1].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i][j-1].edge_length;
                 }
               }


               if (j+1<=index_XY.column())             //правая клетка
               {
                 if (arr_dijkstra[i][j+1].point_label==0 && arr_dijkstra[i][j+1].point_is_enable) {
                     arr_dijkstra[i][j+1].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i][j+1].edge_length;
                     }
                 else {  if (arr_dijkstra[i][j+1].point_is_enable)
                             if (arr_dijkstra[i][j+1].point_label>arr_dijkstra[i][j].point_label+arr_dijkstra[i][j+1].edge_length)
                                 arr_dijkstra[i][j+1].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i][j+1].edge_length;
                 }
               }
               if (i-1>=0)             //верхняя клетка
               {
                 if (arr_dijkstra[i-1][j].point_label==0 && arr_dijkstra[i-1][j].point_is_enable) {
                     arr_dijkstra[i-1][j].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i-1][j].edge_length;
                     }
                 else {  if (arr_dijkstra[i-1][j].point_is_enable)
                             if (arr_dijkstra[i-1][j].point_label>arr_dijkstra[i][j].point_label+arr_dijkstra[i-1][j].edge_length)
                                 arr_dijkstra[i-1][j].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i-1][j].edge_length;
                 }
               }
               if (i+1<=index_XY.row())             //нижняя клетка
               {
                 if (arr_dijkstra[i+1][j].point_label==0 && arr_dijkstra[i+1][j].point_is_enable) {
                     arr_dijkstra[i+1][j].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i+1][j].edge_length;
                     }
                 else {  if (arr_dijkstra[i+1][j].point_is_enable)
                             if (arr_dijkstra[i+1][j].point_label>arr_dijkstra[i][j].point_label+arr_dijkstra[i+1][j].edge_length)
                                 arr_dijkstra[i+1][j].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i+1][j].edge_length;
                 }
               }
         arr_dijkstra[i][j].point_is_enable=false;
         }

      /////////////
      //    // V //
      /////////////
      //    //   //
      /////////////
       for (int i=x1_graf;i>=0;i--)
          for (int j=y1_graf;j<=index_XY.column();j++)
            if (arr_dijkstra[i][j].point_is_enable)
          {
                if (j-1>=0)             //левая клетка
                {
                  if (arr_dijkstra[i][j-1].point_label==0 && arr_dijkstra[i][j-1].point_is_enable) {
                      arr_dijkstra[i][j-1].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i][j-1].edge_length;
                      }
                  else {  if (arr_dijkstra[i][j-1].point_is_enable)
                              if (arr_dijkstra[i][j-1].point_label>arr_dijkstra[i][j].point_label+arr_dijkstra[i][j-1].edge_length)
                                  arr_dijkstra[i][j-1].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i][j-1].edge_length;
                  }
                }


                if (j+1<=index_XY.column())             //правая клетка
                {
                  if (arr_dijkstra[i][j+1].point_label==0 && arr_dijkstra[i][j+1].point_is_enable) {
                      arr_dijkstra[i][j+1].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i][j+1].edge_length;
                      }
                  else {  if (arr_dijkstra[i][j+1].point_is_enable)
                              if (arr_dijkstra[i][j+1].point_label>arr_dijkstra[i][j].point_label+arr_dijkstra[i][j+1].edge_length)
                                  arr_dijkstra[i][j+1].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i][j+1].edge_length;
                  }
                }
                if (i-1>=0)             //верхняя клетка
                {
                  if (arr_dijkstra[i-1][j].point_label==0 && arr_dijkstra[i-1][j].point_is_enable) {
                      arr_dijkstra[i-1][j].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i-1][j].edge_length;
                      }
                  else {  if (arr_dijkstra[i-1][j].point_is_enable)
                              if (arr_dijkstra[i-1][j].point_label>arr_dijkstra[i][j].point_label+arr_dijkstra[i-1][j].edge_length)
                                  arr_dijkstra[i-1][j].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i-1][j].edge_length;
                  }
                }
                if (i+1<=index_XY.row())             //нижняя клетка
                {
                  if (arr_dijkstra[i+1][j].point_label==0 && arr_dijkstra[i+1][j].point_is_enable) {
                      arr_dijkstra[i+1][j].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i+1][j].edge_length;
                      }
                  else {  if (arr_dijkstra[i+1][j].point_is_enable)
                              if (arr_dijkstra[i+1][j].point_label>arr_dijkstra[i][j].point_label+arr_dijkstra[i+1][j].edge_length)
                                  arr_dijkstra[i+1][j].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i+1][j].edge_length;
                  }
                }
          arr_dijkstra[i][j].point_is_enable=false;
          }

      /////////////
      //    //   //
      /////////////
      //    // V //
      /////////////
       for (int i=x1_graf;i<=index_XY.row();i++)
          for (int j=y1_graf;j<=index_XY.column();j++)
            if (arr_dijkstra[i][j].point_is_enable)
          {
                if (j-1>=0)             //левая клетка
                {
                  if (arr_dijkstra[i][j-1].point_label==0 && arr_dijkstra[i][j-1].point_is_enable) {
                      arr_dijkstra[i][j-1].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i][j-1].edge_length;
                      }
                  else {  if (arr_dijkstra[i][j-1].point_is_enable)
                              if (arr_dijkstra[i][j-1].point_label>arr_dijkstra[i][j].point_label+arr_dijkstra[i][j-1].edge_length)
                                  arr_dijkstra[i][j-1].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i][j-1].edge_length;
                  }
                }


                if (j+1<=index_XY.column())             //правая клетка
                {
                  if (arr_dijkstra[i][j+1].point_label==0 && arr_dijkstra[i][j+1].point_is_enable) {
                      arr_dijkstra[i][j+1].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i][j+1].edge_length;
                      }
                  else {  if (arr_dijkstra[i][j+1].point_is_enable)
                              if (arr_dijkstra[i][j+1].point_label>arr_dijkstra[i][j].point_label+arr_dijkstra[i][j+1].edge_length)
                                  arr_dijkstra[i][j+1].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i][j+1].edge_length;
                  }
                }

                if (i-1>=0)             //верхняя клетка
                {
                  if (arr_dijkstra[i-1][j].point_label==0 && arr_dijkstra[i-1][j].point_is_enable) {
                      arr_dijkstra[i-1][j].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i-1][j].edge_length;
                      }
                  else {  if (arr_dijkstra[i-1][j].point_is_enable)
                              if (arr_dijkstra[i-1][j].point_label>arr_dijkstra[i][j].point_label+arr_dijkstra[i-1][j].edge_length)
                                  arr_dijkstra[i-1][j].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i-1][j].edge_length;
                  }
                }

                if (i+1<=index_XY.row())             //нижняя клетка
                {
                  if (arr_dijkstra[i+1][j].point_label==0 && arr_dijkstra[i+1][j].point_is_enable) {
                      arr_dijkstra[i+1][j].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i+1][j].edge_length;
                      }
                  else {  if (arr_dijkstra[i+1][j].point_is_enable)
                              if (arr_dijkstra[i+1][j].point_label>arr_dijkstra[i][j].point_label+arr_dijkstra[i+1][j].edge_length)
                                  arr_dijkstra[i+1][j].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i+1][j].edge_length;
                  }
                }
          arr_dijkstra[i][j].point_is_enable=false;
          }



//    for (int i=0;i<=index_XY.row();i++) {
//        for (int j=0;j<=index_XY.column();j++){
//             qDebug()<<arr_dijkstra[i][j].point_label;}
//         qDebug()<<"\n";
//    }


       //вывод пути
       m_way_tmp.clear();

       int tmp_summa_way=arr_dijkstra[x2_graf][y2_graf].point_label;
       int k=0;
       int i=x2_graf;
       int j=y2_graf;
       while(tmp_summa_way>=0){

           tmp_summa_way=tmp_summa_way-arr_dijkstra[i][j].edge_length;

           if (i-1>=0){
           if (arr_dijkstra[i][j].point_label-arr_dijkstra[i][j].edge_length==arr_dijkstra[i-1][j].point_label )
            {
               i--;
               QModelIndex index_tmp;
               emit GetIndex(index_tmp,i,j);
               m_way_tmp.insert(k,index_tmp);
               k++;
               continue;
            }
           }
           if (i+1<=index_XY.row()){
           if (arr_dijkstra[i][j].point_label-arr_dijkstra[i][j].edge_length==arr_dijkstra[i+1][j].point_label )
             {
               i++;
               QModelIndex index_tmp;
               emit GetIndex(index_tmp,i,j);
               m_way_tmp.insert(k,index_tmp);
               k++;
               continue;
             }
           }
           if (j-1>=0){
           if (arr_dijkstra[i][j].point_label-arr_dijkstra[i][j].edge_length==arr_dijkstra[i][j-1].point_label )
            {
               j--;
               QModelIndex index_tmp;
               emit GetIndex(index_tmp,i,j);
               m_way_tmp.insert(k,index_tmp);
               k++;
               continue;
            }
           }
           if (j+1<=index_XY.column()){
           if (arr_dijkstra[i][j].point_label-arr_dijkstra[i][j].edge_length==arr_dijkstra[i][j+1].point_label )
            {
               j++;
               QModelIndex index_tmp;
               emit GetIndex(index_tmp,i,j);
               m_way_tmp.insert(k,index_tmp);
               k++;
               continue;
            }
           }

//           QModelIndex index_tmp;
//           emit GetIndex(index_tmp,i,j);
//           m_way_tmp.insert(k,index_tmp);
//           k++;

           {
           QModelIndex index_tmp;
           emit GetIndex(index_tmp,m_point_finish.row(),m_point_finish.column());
           m_way_tmp[k]=index_tmp;
           k++;
           }

       }



    //передача пути
       if (arr_dijkstra[x2_graf][y2_graf].point_label<ShortyWay) {
           m_str_2.clear();
           m_str_2="4_Square_Alg";
           m_way=std::move(m_way_tmp);
           ShortyWay=arr_dijkstra[x2_graf][y2_graf].point_label;
           emit Way_long(arr_dijkstra[x2_graf][y2_graf].point_label);
           emit AlgName(m_str_2);
          }


}


void My_Way::Dijkstra_krest_proverka(int i, int j){

    QModelIndex index_XY;
    emit GetXY(index_XY);



    if (arr_dijkstra[i][j].point_is_enable)
  {
        if (j-1>=0)             //левая клетка
        {
          if (arr_dijkstra[i][j-1].point_label==0) {
              arr_dijkstra[i][j-1].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i][j-1].edge_length;
               number_global++;
              }
          else { if (arr_dijkstra[i][j-1].point_is_enable)
                      if (arr_dijkstra[i][j-1].point_label>=arr_dijkstra[i][j].point_label+arr_dijkstra[i][j-1].edge_length)
                          arr_dijkstra[i][j-1].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i][j-1].edge_length;

          }
        }


        if (j+1<=index_XY.column())             //правая клетка
        {
          if (arr_dijkstra[i][j+1].point_label==0) {
              arr_dijkstra[i][j+1].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i][j+1].edge_length;
               number_global++;
              }
          else {if (arr_dijkstra[i][j+1].point_is_enable)
                      if (arr_dijkstra[i][j+1].point_label>=arr_dijkstra[i][j].point_label+arr_dijkstra[i][j+1].edge_length)
                          arr_dijkstra[i][j+1].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i][j+1].edge_length;

          }
        }
        if (i-1>=0)             //верхняя клетка
        {
          if (arr_dijkstra[i-1][j].point_label==0) {
              arr_dijkstra[i-1][j].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i-1][j].edge_length;
              number_global++;
              }
          else {if (arr_dijkstra[i-1][j].point_is_enable)
                      if (arr_dijkstra[i-1][j].point_label>=arr_dijkstra[i][j].point_label+arr_dijkstra[i-1][j].edge_length)
                          arr_dijkstra[i-1][j].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i-1][j].edge_length;

          }
        }
        if (i+1<=index_XY.row())             //нижняя клетка
        {
          if (arr_dijkstra[i+1][j].point_label==0 ) {
              arr_dijkstra[i+1][j].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i+1][j].edge_length;
              number_global++;
              }
          else { if (arr_dijkstra[i+1][j].point_is_enable)
                      if (arr_dijkstra[i+1][j].point_label>=arr_dijkstra[i][j].point_label+arr_dijkstra[i+1][j].edge_length)
                          arr_dijkstra[i+1][j].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i+1][j].edge_length;

          }
        }
  arr_dijkstra[i][j].point_is_enable=false;

    }


}

void My_Way::Dijkstra_way(){



    int x1_graf=m_point_start.row();
    int y1_graf=m_point_start.column();


    int x2_graf=m_point_finish.row();
    int y2_graf=m_point_finish.column();

    QModelIndex index_XY;
    emit GetXY(index_XY);

    //---создаю матрицу для Деикстры
   // QVector<QVector<Dijkstra_Point>>arr_dijkstra;

    arr_dijkstra.clear();

//    arr_dijkstra.reserve(index_XY.row());             //подумать над этим потом
//    for (int i=0;i<index_XY.row();i++){
//         arr_dijkstra[i].reserve(index_XY.column());
//    }

    int num=0;
    arr_dijkstra.reserve(index_XY.row());
    for (int i=0; i<=index_XY.row();i++){
          QVector<Dijkstra_Point> temp_vector;
          temp_vector.reserve(index_XY.column());
        for (int j=0;j<=index_XY.column();j++){

        QModelIndex index_tmp;
        emit GetIndex(index_tmp,i,j);

        num++;

        dijkstra_point.point_is_enable=true;

        dijkstra_point.point_label=0;
        dijkstra_point.edge_length=index_tmp.data().toInt();
        if (dijkstra_point.edge_length==0) dijkstra_point.point_is_enable=false;

        temp_vector.push_back(dijkstra_point);

    }

        arr_dijkstra.push_back(temp_vector);
        temp_vector.clear();
    }
   //---



     arr_dijkstra[x1_graf][y1_graf].point_label= arr_dijkstra[x1_graf][y1_graf].edge_length;

     number_global=1;


     //===находим следующую ближайшую вершину           //алгоритм Дейкстры не через матрицу связей, а через 4х связный массив. поэтому сам алгоритм иной, но смысл один

        {
             int i=0,j=0;

           for (int m=1;m<=number_global;m++){
                int min=MaxBig;
           for (int i2=0;i2<=index_XY.row();i2++){
           for (int j2=0;j2<=index_XY.column();j2++) {

           if (arr_dijkstra[i2][j2].point_is_enable && arr_dijkstra[i2][j2].point_label) {        //если у вершины с номером К ее метка меньшая из остальных и эйбл, то передаем ее К
                 if (min>=arr_dijkstra[i2][j2].point_label ) {
                     min=arr_dijkstra[i2][j2].point_label;
                     i=i2; j=j2;
                    }
           }
           }
           }
            Dijkstra_krest_proverka(i,j);
            if (dom || map) emit Progress((m+1)*100/(number_global));
            else
            emit Progress((m+1)*100/(index_XY.row()*index_XY.column()));
           }
        }

   //=========



//    for (int i=0;i<=index_XY.row();i++) {
//        for (int j=0;j<=index_XY.column();j++){
//             qDebug()<<arr_dijkstra[i][j].point_label;}
//         qDebug()<<"\n";
//    }


       //вывод пути
       m_way_tmp.clear();

       int tmp_summa_way=arr_dijkstra[x2_graf][y2_graf].point_label;
       int k=0;
       int i=x2_graf;
       int j=y2_graf;
       while(tmp_summa_way>=0){

           tmp_summa_way=tmp_summa_way-arr_dijkstra[i][j].edge_length;

           if (i-1>=0){
           if (arr_dijkstra[i][j].point_label-arr_dijkstra[i][j].edge_length==arr_dijkstra[i-1][j].point_label )
            {
               i--;
               QModelIndex index_tmp;
               emit GetIndex(index_tmp,i,j);
               m_way_tmp.insert(k,index_tmp);
               k++;
               continue;
            }
           }
           if (i+1<=index_XY.row()){
           if (arr_dijkstra[i][j].point_label-arr_dijkstra[i][j].edge_length==arr_dijkstra[i+1][j].point_label )
             {
               i++;
               QModelIndex index_tmp;
               emit GetIndex(index_tmp,i,j);
               m_way_tmp.insert(k,index_tmp);
               k++;
               continue;
             }
           }
           if (j-1>=0){
           if (arr_dijkstra[i][j].point_label-arr_dijkstra[i][j].edge_length==arr_dijkstra[i][j-1].point_label )
            {
               j--;
               QModelIndex index_tmp;
               emit GetIndex(index_tmp,i,j);
               m_way_tmp.insert(k,index_tmp);
               k++;
               continue;
            }
           }
           if (j+1<=index_XY.column()){
           if (arr_dijkstra[i][j].point_label-arr_dijkstra[i][j].edge_length==arr_dijkstra[i][j+1].point_label )
            {
               j++;
               QModelIndex index_tmp;
               emit GetIndex(index_tmp,i,j);
               m_way_tmp.insert(k,index_tmp);
               k++;
               continue;
            }
           }

//           QModelIndex index_tmp;
//           emit GetIndex(index_tmp,i,j);
//           m_way_tmp.insert(k,index_tmp);
//           k++;


           {
           QModelIndex index_tmp;
           emit GetIndex(index_tmp,m_point_finish.row(),m_point_finish.column());
           m_way_tmp[k]=index_tmp;
           k++;
           }

       }



    //передача пути
       if (arr_dijkstra[x2_graf][y2_graf].point_label<ShortyWay) {
           m_str_2.clear();
           m_str_2="Dijkstra_Alg";
           m_way=std::move(m_way_tmp);
           ShortyWay=arr_dijkstra[x2_graf][y2_graf].point_label;
           emit Way_long(arr_dijkstra[x2_graf][y2_graf].point_label);
           emit AlgName(m_str_2);
          }

}

void My_Way::NextStepByTracing(){

    if (m_way[/*m_way.size()-zdvig-1*/zdvig/*+1*/]==m_point_finish){
         m_str_2.clear();
         m_str_2="REACHED!";
         emit AlgName(m_str_2);
         emit Reached(true);
         killTimer(timer);
     }
else
  //  if (m_way[/*m_way.size()-4-*/zdvig]!=m_point_finish)
    {

        killTimer(timer);
    //  emit Timer_lapse(timer_interval);
      timer_interval=m_point_start.data().toInt();

        timer=startTimer(timer_interval);
        timer_interval=m_point_start.data().toInt();




    //чтобы пропадал след
    emit Checked(false);
    DrawingWay(true);
    emit PaintingWay(m_point_start);
    DrawingWay(false);
    //--

    emit Checked(true);
    emit AlgBrush(Qt::cyan );   
    m_point_start=m_way[m_way.size()-3-zdvig];
    DrawingWay(true);
    emit PaintingWay(m_point_start);
    DrawingWay(false);
    emit Set_Start_Finish_Points(m_point_start ,m_point_finish);
  //  qDebug()<<m_point_start;
  }

}


void My_Way::timerEvent(QTimerEvent *event)
{
    zdvig++;
  //  timer_interval=m_point_start.data().toInt();
    NextStepByTracing();

}

void My_Way::Create_matrix_for_Dijkstra_faster(){
    QModelIndex index_XY;
    emit GetXY(index_XY);

    //---создаю матрицу для Деикстры


    arr_dijkstra.clear();

    arr_dijkstra.reserve(index_XY.row());
    for (int i=0; i<=index_XY.row();i++){
          QVector<Dijkstra_Point> temp_vector;
          temp_vector.reserve(index_XY.column());
        for (int j=0;j<=index_XY.column();j++){

        QModelIndex index_tmp;
        emit GetIndex(index_tmp,i,j);

        dijkstra_point.point_is_enable=true;
        dijkstra_point.point_label=0;
        dijkstra_point.edge_length=index_tmp.data().toInt();
        if (dijkstra_point.edge_length==0) dijkstra_point.point_is_enable=false;

        temp_vector.push_back(dijkstra_point);

    }
        arr_dijkstra.push_back(temp_vector);
        temp_vector.clear();
    }

}


void My_Way::Dijkstra_fast_krest_proverka(int& i, int &j){



    QModelIndex index_XY;
    emit GetXY(index_XY);


    if (arr_dijkstra[i][j].point_is_enable)
  {
        if (j-1>=0)             //левая клетка
        {
          if (arr_dijkstra[i][j-1].point_label==0) {
              arr_dijkstra[i][j-1].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i][j-1].edge_length;
               number_global++;

              }
          else  if ((arr_dijkstra[i][j-1].point_is_enable) &&(arr_dijkstra[i][j-1].point_label>=arr_dijkstra[i][j].point_label+arr_dijkstra[i][j-1].edge_length)){
                          arr_dijkstra[i][j-1].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i][j-1].edge_length;

            }

        }


        if (j+1<=index_XY.column())             //правая клетка
        {
          if (arr_dijkstra[i][j+1].point_label==0) {
              arr_dijkstra[i][j+1].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i][j+1].edge_length;
               number_global++;

              }
          else if ((arr_dijkstra[i][j+1].point_is_enable)&&(arr_dijkstra[i][j+1].point_label>=arr_dijkstra[i][j].point_label+arr_dijkstra[i][j+1].edge_length)) {
                          arr_dijkstra[i][j+1].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i][j+1].edge_length;

            }

        }
        if (i-1>=0)             //верхняя клетка
        {
          if (arr_dijkstra[i-1][j].point_label==0) {
              arr_dijkstra[i-1][j].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i-1][j].edge_length;
              number_global++;

              }
          else if ((arr_dijkstra[i-1][j].point_is_enable)&&(arr_dijkstra[i-1][j].point_label>=arr_dijkstra[i][j].point_label+arr_dijkstra[i-1][j].edge_length)){
                          arr_dijkstra[i-1][j].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i-1][j].edge_length;

              }

        }
        if (i+1<=index_XY.row())             //нижняя клетка
        {
          if (arr_dijkstra[i+1][j].point_label==0 ) {
              arr_dijkstra[i+1][j].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i+1][j].edge_length;
              number_global++;

              }
          else  if ((arr_dijkstra[i+1][j].point_is_enable)&& (arr_dijkstra[i+1][j].point_label>=arr_dijkstra[i][j].point_label+arr_dijkstra[i+1][j].edge_length)){
                          arr_dijkstra[i+1][j].point_label=arr_dijkstra[i][j].point_label+arr_dijkstra[i+1][j].edge_length;

                }

        }
  arr_dijkstra[i][j].point_is_enable=false;


    }

}



void My_Way::Dijkstra_way_faster(){

    int x1_graf=m_point_start.row();
    int y1_graf=m_point_start.column();


    int x2_graf=m_point_finish.row();
    int y2_graf=m_point_finish.column();

    QModelIndex index_XY;
    emit GetXY(index_XY);

    //обнуляю enable в матрице
    for (int i=0; i<=index_XY.row();i++){
        for (int j=0;j<=index_XY.column();j++){
              arr_dijkstra[i][j].point_label=0;
              if ( arr_dijkstra[i][j].edge_length==0)  arr_dijkstra[i][j].point_is_enable=false;
              else arr_dijkstra[i][j].point_is_enable=true;
        }
    }
    //---

     arr_dijkstra[x1_graf][y1_graf].point_label= arr_dijkstra[x1_graf][y1_graf].edge_length;

     number_global=1;


     //===находим следующую ближайшую вершину           //алгоритм Дейкстры не через матрицу связей, а через 4х связный массив. поэтому сам алгоритм иной, но смысл один

        {
             int i=0,j=0;

           for (int m=1;m<=number_global;m++){
                 int min_dij=MaxBig;

           for (int i2=0;i2<=index_XY.row();i2++){

           for (int j2=0;j2<=index_XY.column();j2++) {

           if (arr_dijkstra[i2][j2].point_is_enable && arr_dijkstra[i2][j2].point_label) {        //если у вершины с номером К ее метка меньшая из остальных и эйбл, то передаем ее К
                if (min_dij>=arr_dijkstra[i2][j2].point_label ) {
                     min_dij=arr_dijkstra[i2][j2].point_label;
                     i=i2; j=j2;
                    }

           }
           }
           }


//         if (!Qset_for_fast_point_dij.empty()) {

//           /*QSet<Point_for_Fast_Dijkstra>::const_iterator*/
//            auto first_element=Qset_for_fast_point_dij.begin();
//            i=(*first_element).Get_X();
//            j=(*first_element).Get_Y();
//            Qset_for_fast_point_dij.erase(first_element);
//         }

            Dijkstra_fast_krest_proverka(i,j);
// +           if (dom || map) emit Progress((m+1)*100/(number_global));
//  +         else
//   +         emit Progress((m+1)*100/(index_XY.row()*index_XY.column()));
           }
        }

   //=========

       //вывод пути
       m_way_tmp.clear();

       int tmp_summa_way=arr_dijkstra[x2_graf][y2_graf].point_label;
       int k=0;
       int i=x2_graf;
       int j=y2_graf;
       while(tmp_summa_way>=0){

           tmp_summa_way=tmp_summa_way-arr_dijkstra[i][j].edge_length;

           if (i-1>=0){
           if (arr_dijkstra[i][j].point_label-arr_dijkstra[i][j].edge_length==arr_dijkstra[i-1][j].point_label )
            {
               i--;
               QModelIndex index_tmp;
               emit GetIndex(index_tmp,i,j);
               m_way_tmp.insert(k,index_tmp);
               k++;
               continue;
            }
           }
           if (i+1<=index_XY.row()){
           if (arr_dijkstra[i][j].point_label-arr_dijkstra[i][j].edge_length==arr_dijkstra[i+1][j].point_label )
             {
               i++;
               QModelIndex index_tmp;
               emit GetIndex(index_tmp,i,j);
               m_way_tmp.insert(k,index_tmp);
               k++;
               continue;
             }
           }
           if (j-1>=0){
           if (arr_dijkstra[i][j].point_label-arr_dijkstra[i][j].edge_length==arr_dijkstra[i][j-1].point_label )
            {
               j--;
               QModelIndex index_tmp;
               emit GetIndex(index_tmp,i,j);
               m_way_tmp.insert(k,index_tmp);
               k++;
               continue;
            }
           }
           if (j+1<=index_XY.column()){
           if (arr_dijkstra[i][j].point_label-arr_dijkstra[i][j].edge_length==arr_dijkstra[i][j+1].point_label )
            {
               j++;
               QModelIndex index_tmp;
               emit GetIndex(index_tmp,i,j);
               m_way_tmp.insert(k,index_tmp);
               k++;
               continue;
            }
           }


           {
           QModelIndex index_tmp;
           emit GetIndex(index_tmp,m_point_finish.row(),m_point_finish.column());
           m_way_tmp[k]=index_tmp;
           k++;
           }

       }



    //передача пути
   //+    if (arr_dijkstra[x2_graf][y2_graf].point_label<ShortyWay) {
//+           m_str_2.clear();
//+           m_str_2="Dijkstra_Alg_Fast";
           m_way=std::move(m_way_tmp);
         //+  ShortyWay=arr_dijkstra[x2_graf][y2_graf].point_label;
       //+    emit Way_long(arr_dijkstra[x2_graf][y2_graf].point_label);
        //+   emit AlgName(m_str_2);
 //+         }

}
