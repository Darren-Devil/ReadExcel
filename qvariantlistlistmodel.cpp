#include "qvariantlistlistmodel.h"

QVariantListListModel::QVariantListListModel(QObject *parent)
    : QAbstractTableModel(parent)
    ,m_varListList(nullptr)
{
}

QVariant QVariantListListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(Qt::DisplayRole == role)
    {
        if(Qt::Horizontal == orientation)
        {
            return section + 1;
        }
        return section + 1;
    }
    return QVariant();
}

int QVariantListListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_rowCount;
    // FIXME: Implement me!
}

int QVariantListListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_columnCount;
    // FIXME: Implement me!
}

QVariant QVariantListListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || m_varListList == nullptr)
        return QVariant();
        
    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();
        
    const int row = index.row();
    const int col = index.column();
    
    if (row >= m_varListList->size() || row < 0)
        return QVariant();
        
    const auto& rowData = m_varListList->at(row);
    if (col >= rowData.size() || col < 0)
        return QVariant();
        
    return rowData.at(col);
}

void QVariantListListModel::setVariantListListPtr(QList<QList<QVariant> > *ptr)
{
    if(ptr == nullptr)
        return;
    m_varListList = ptr;
    updateData();
}

void QVariantListListModel::updateData()
{
    beginResetModel();
    
    if (m_varListList == nullptr) {
        m_rowCount = 0;
        m_columnCount = 0;
    } else {
        m_rowCount = m_varListList->size();
        m_columnCount = 0;
        
        // Find maximum column count more efficiently
        for(const auto& row : *m_varListList) {
            if(row.size() > m_columnCount) {
                m_columnCount = row.size();
            }
        }
    }
    
    endResetModel();
}
