#ifndef QVARIANTLISTLISTMODEL_H
#define QVARIANTLISTLISTMODEL_H

#include <QAbstractTableModel>
#include <QList>

class QVariantListListModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit QVariantListListModel(QObject *parent = 0);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void setVariantListListPtr(QList<QList<QVariant> >* ptr);
    void updateData();
private:
    QList<QList<QVariant> >* m_varListList;
    //QVariantList* m_varListList;
    int m_rowCount;// 行数
    int m_columnCount;// 列数
};

#endif // QVARIANTLISTLISTMODEL_H
