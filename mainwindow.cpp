#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QElapsedTimer>
#include <QDebug>
#include "qvariantlistlistmodel.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
  ,m_xls(NULL)
{
    ui->setupUi(this);
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    QVariantListListModel* md = new QVariantListListModel(this);
    ui->tableView->setModel(md);
    md->setVariantListListPtr(&m_datas);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_open_triggered()
{
    QString xlsFile = QFileDialog::getOpenFileName(this, tr("Open Excel File"), QString(), "Excel Files (*.xls *.xlsx)");
    if(xlsFile.isEmpty())
        return;
        
    QElapsedTimer timer;
    timer.start();
    
    if(m_xls.isNull())
        m_xls.reset(new ExcelBase);
        
    if (!m_xls->open(xlsFile)) {
        qDebug() << "Failed to open Excel file:" << xlsFile;
        return;
    }
    
    qDebug() << "Open cost:" << timer.elapsed() << "ms";
    timer.restart();
    
    // Clear previous data
    m_datas.clear();
    
    // Read only the first sheet (index 1) instead of looping through all sheets
    if (m_xls->sheetCount() > 0) {
        m_xls->setCurrentSheet(1);
        m_xls->readAll(m_datas);
        qDebug() << "Current sheet:" << m_xls->currentSheetName();
    }
    
    qDebug() << "Read data cost:" << timer.elapsed() << "ms";
    timer.restart();
    
    QVariantListListModel* md = qobject_cast<QVariantListListModel*>(ui->tableView->model());
    if(md) {
        md->updateData();
    }
    
    qDebug() << "Show data cost:" << timer.elapsed() << "ms";
}

void MainWindow::on_action_write_triggered()
{
    QString xlsFile = QFileDialog::getSaveFileName(this, tr("Save Excel File"), "Change.xls", "Excel Files (*.xls *.xlsx)");
    if(xlsFile.isEmpty())
        return;
        
    QElapsedTimer timer;
    timer.start();
    
    if(m_xls.isNull())
        m_xls.reset(new ExcelBase);
        
    if (!m_xls->create(xlsFile)) {
        qDebug() << "Failed to create Excel file:" << xlsFile;
        return;
    }
    
    qDebug() << "Create cost:" << timer.elapsed() << "ms";
    timer.restart();
    
    // Generate test data more efficiently
    QList<QList<QVariant>> testData;
    testData.reserve(100); // Pre-allocate memory
    
    for(int i = 0; i < 100; ++i) {
        QList<QVariant> row;
        row.reserve(100); // Pre-allocate memory
        for(int j = 0; j < 100; ++j) {
            row.append(i * j);
        }
        testData.append(std::move(row)); // Use move semantics
    }
    
    if (!m_xls->setCurrentSheet(1)) {
        qDebug() << "Failed to set current sheet";
        return;
    }
    
    timer.restart();
    if (!m_xls->writeCurrentSheet(testData)) {
        qDebug() << "Failed to write data to sheet";
        return;
    }
    
    qDebug() << "Write cost:" << timer.elapsed() << "ms";
    timer.restart();
    
    m_xls->save();
    qDebug() << "Save cost:" << timer.elapsed() << "ms";
}
