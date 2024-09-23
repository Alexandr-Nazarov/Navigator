#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QObject>
#include <QtWidgets>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
  //  explicit TableModel(QObject *parent = nullptr);

private:
    int m_nRows;
    int m_nColumns;
    QHash<QModelIndex,QVariant> m_hash;
   // QList<int>m_list;

public:
    TableModel (int nRows, int nColums, QObject*pobj=0):QAbstractTableModel(pobj), m_nRows(nRows), m_nColumns(nColums){}

    int columnCount(const QModelIndex &) const { return m_nColumns; }
    int rowCount(const QModelIndex &) const {return m_nRows; }

    void set_Rows(int rows){ m_nRows=rows;}
    void set_Columns(int columns){ m_nColumns=columns;}
    void clear_Hash(){m_hash.clear(); m_nRows=0; m_nColumns=0;}

    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
    virtual QVariant data(const QModelIndex &index, int role) const;


    Qt::ItemFlags flags (const QModelIndex& index) const{
        Qt::ItemFlags flags=QAbstractTableModel::flags(index);
        return index.isValid()?(flags|Qt::ItemIsEditable):flags;
    }

signals:

void dataChanged(const QModelIndex &,const QModelIndex &);


};

#endif // TABLEMODEL_H
