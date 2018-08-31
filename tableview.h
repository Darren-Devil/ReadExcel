#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QMouseEvent>
#include <QTableView>
#include <QAbstractTableModel>

#pragma execution_character_set("utf-8")


class TableView : public QTableView
{
    Q_OBJECT
public:
    explicit TableView(QWidget *parent = 0);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

signals:
    void leftClicked(const QModelIndex &index);
    void leftdoubleClicked();

};

#endif // TABLEVIEW_H
