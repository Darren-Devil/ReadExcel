#include "tableview.h"
#include <QDebug>
#include <QAxObject>

TableView::TableView(QWidget *parent):QTableView(parent)
{
}

void TableView::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        setCurrentIndex(QModelIndex());
        QTableView::mousePressEvent(event);
        QModelIndex index=currentIndex();
        if(index.row()<0&&index.column()<0)
            return;
        emit leftClicked(index);
        qDebug()<<"左击一下";
    }
}

void TableView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        qDebug()<<"左击两下";
        emit leftdoubleClicked();
    }
}
