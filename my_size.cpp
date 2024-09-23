#include "my_size.h"

My_Size::My_Size(QWidget *parent) : QWidget(parent),model(0,0)
{

}


void My_Size::fill_Matrix(/*QVector<QVector<int>>& arr_tmp*/){
    int pogr=30;
      int tmp_rand=0;
      for (int i=0; i<X;++i) {
       //!   QVector<int> temp_vector;
          for (int j=0; j<Y;++j) {
              QModelIndex index = model.index(i, j, QModelIndex());

             if (uniform==false){
                 tmp_rand=1 + (rand() % 999);}
               else {
                   if ((i==0)&&(j==0)) {tmp_rand=1 + (rand() % 999);}
                   else {
                       tmp_rand=1 + (rand() % 999);

                        if ((j>0)&&(i==0)){
                           if (tmp_rand>=model.index(i,j-1).data().toInt()+pogr*10)
                               tmp_rand=model.index(i,j-1).data().toInt()+tmp_rand/pogr;
                           if (tmp_rand<model.index(i,j-1).data().toInt()-pogr*10)
                               tmp_rand=model.index(i,j-1).data().toInt()-tmp_rand/pogr;
                        } else
                        if ((i>0)&&(j==0)){
                               if (tmp_rand>=model.index(i-1,j).data().toInt()+pogr*10)
                                   tmp_rand=model.index(i-1,j).data().toInt()+tmp_rand/pogr;
                               if (tmp_rand<model.index(i-1,j).data().toInt()-pogr*10)
                                   tmp_rand=model.index(i-1,j).data().toInt()-tmp_rand/pogr;
                            } else
                            if ((i>0)&&(j>0)){
                                while (((tmp_rand>=(model.index(i-1,j).data().toInt()+pogr*10)) ||
                                        (tmp_rand>=(model.index(i,j-1).data().toInt()+pogr*10)))||
                                       ((tmp_rand<=(model.index(i-1,j).data().toInt()-pogr*10)) ||
                                        (tmp_rand<=(model.index(i,j-1).data().toInt()-pogr*10)))){
                                    tmp_rand=1 + (rand() % 999);
                                }
                            }
                        }
                 }

           model.setData(index, tmp_rand, Qt::EditRole);
         //  model.setData(index, QColor(Qt::red), Qt::BackgroundColorRole);                                               // ??
       //!    temp_vector.push_back(tmp_rand);              //нужен ли массив,если модель? может убрать вообще потом
          }
       //!   arr_tmp.push_back(temp_vector);
    }

      if (dom==true) {
          for (int i=0; i<X;++i) {
              for (int j=0; j<Y;++j) {
     int a1=(rand() % 999);
     int a2=(rand() % 999);
     QModelIndex index = model.index(i, j, QModelIndex());
     if (model.index(i,j).data().toInt()>=a1 && model.index(i,j).data().toInt()<=a2) model.setData(index, 0, Qt::EditRole);
        }
     }
   }


     //    qDebug()<<model.index(2,3).data(Qt::DisplayRole).toInt()  ;         //!!!!       //тут получаю значение индекса модели

         emit ModelCreate(model);


}


void My_Size:: fill_Map_Matrix(QString& file){                   //из скриншота
    QImage image=QImage(file/*"/C++/map_3.png"*/);
  //  image.load("/C++/map.png");
    model.set_Rows(image.height());
    model.set_Columns(image.width());
    X=image.height();
    Y=image.width();
    dom=true;
      for (int i=0; i<image.height();++i) {                                     //225,223-зел, 224-сер,213-син, 251-фон, 216-дор 227 228 232
                                                                                //50-100 ч 100-200 з  200-220 -с
          for (int j=0; j<image.width();++j) {
              QModelIndex index = model.index(i, j, QModelIndex());
               int pixel= qGray(image.pixel(j,i));
               if (pixel>=224 && pixel<= 250){                                                                  //230-250
               model.setData(index,1, Qt::EditRole);
               }



          }
    }

      QString tmp_x=QString::number(image.height());
      QString tmp_y=QString::number(image.width());
      emit XChanged(tmp_x);
      emit YChanged(tmp_y);

           emit ModelCreate(model);
}
