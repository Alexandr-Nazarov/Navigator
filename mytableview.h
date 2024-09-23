#ifndef MYTABLEVIEW_H
#define MYTABLEVIEW_H
#include <QDebug>
#include "tablemodel.h"
#include <QTableView>
#include <QAbstractTableModel>
#include <QWidget>

class mytableview : public QTableView//QWidget
{
    Q_OBJECT
private:
  // QTableView tableView;

public:
    explicit mytableview(QWidget *parent = nullptr);




signals:
void dataChanged(const QModelIndex&);

public slots:

    void fill_table(TableModel& model){
             TableModel emptymodel(0,0);
             this->setModel(&emptymodel);

             this->setModel(&model);
             this->resizeColumnsToContents();
             this->resizeRowsToContents();
             this->reset();
             this->repaint();
    //    qDebug()<<"table";
  QObject::connect(&model,SIGNAL(dataChanged(const QModelIndex&,const QModelIndex&)),this, SLOT(updateData(const QModelIndex &, const QModelIndex &)));
    }

    void updateData(const QModelIndex &index_1, const QModelIndex &index_2){

        emit dataChanged(index_1);
    }

};

#endif // MYTABLEVIEW_H
