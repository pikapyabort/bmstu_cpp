#pragma once

#include "xmlmodel.h"
#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QVBoxLayout>
#include <QFileDialog>

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    XmlModel* model;
    QTreeView* view;
    QMenu* menu;
    QTabWidget* tabWgt;
    void setupMenu();

private slots:
    void open();
    void closeFile();
    void clearAll();
    void newTab();
    void exit();
    void customMenu(const QPoint&);
};
