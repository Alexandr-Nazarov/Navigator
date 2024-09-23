#include "tablemodel.h"


//TableModel::TableModel(QObject *parent) : QObject(parent)
//{

//}

//TableModel::TableModel(int nRows, int nColumns,  QObject *pobj=0) : QAbstractListModel(pobj), m_nRows(nRows), m_nColumns(nColumns)
//{

//}


bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

   if (index.isValid()&& role==Qt::EditRole) {

        m_hash[index]=value;
        emit dataChanged(index,index);
        return true;
   }
   return false;
}


QVariant TableModel::data(const QModelIndex &index, int role) const
{

        if (!index.isValid()) {
                   return QVariant();
               }
  //  QString str=QString("%1,%2").arg(index.row()+1).arg(index.column()+1);

        QString str;//="ddf";
    return (role==Qt::DisplayRole || role==Qt::EditRole)?m_hash.value(index, QVariant(str)):QVariant() ;



}


