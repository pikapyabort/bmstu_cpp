//
// Created by Denis Horn on 24.02.2022.
//
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    model = new XmlModel(this);
    view = new QTreeView(this);
    view->setModel(model);
    view->setContextMenuPolicy(Qt::CustomContextMenu);
    tabWgt = new QTabWidget();
    tabWgt->addTab(view, tr("Tab 1"));
    tabWgt->setCurrentIndex(tabWgt->indexOf(view));
    setCentralWidget(tabWgt);

    setupMenu();

    resize(800, 600);
    setWindowTitle("XML viewer");

    connect(view, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(customMenu(QPoint)));
}

void MainWindow::setupMenu(){
    menu = new QMenu("File", this);

    QAction* open     = new QAction(tr("Open")    , this);
    QAction* clearall = new QAction(tr("Close all"), this);
    QAction* exit     = new QAction(tr("Exit")      , this);

    menu->addAction(open);
    menu->addAction(clearall);
    menu->addAction(exit);

    menuBar()->addMenu(menu);

    connect(open    , SIGNAL(triggered()), this, SLOT(open()));
    connect(clearall, SIGNAL(triggered()), this, SLOT(clearAll()));
    connect(exit    , SIGNAL(triggered()), this, SLOT(exit()));
}

void MainWindow::open(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open xml File"), "", "XML (*.xml)");
    model->read(fileName);
    view->reset();
}

void MainWindow::closeFile(){
    auto* currView = qobject_cast<QTreeView*>(tabWgt->currentWidget());
    if (currView)
    {
        auto* currModel = dynamic_cast<XmlModel*>(currView->model());
        if (currModel)
        {
            auto currIndex = currView->currentIndex();
            currModel->removeRow(currIndex.row());
            view->reset();
        }
    }
}

void MainWindow::clearAll() {
    delete model;
    model = new XmlModel(this);
    view->setModel(model);
    view->reset();
    static int i = 1;
    tabWgt->setCurrentIndex(i);
    while (tabWgt->currentIndex()) {
        tabWgt->removeTab(tabWgt->currentIndex());
        tabWgt->setCurrentIndex(++i);
    }
    i = 1;
}

void MainWindow::exit() {
    close();
}

void MainWindow::customMenu(const QPoint &pos){
    if (view->currentIndex().parent() == view->rootIndex())
    {
        QMenu *menu = new QMenu(this);
        QAction* newTab    = new QAction(tr("Open in new Tab"), menu);
        QAction* closefile = new QAction(tr("Close" ), menu);

        connect(newTab   , SIGNAL(triggered()), this, SLOT(newTab()));
        connect(closefile, SIGNAL(triggered()), this, SLOT(closeFile()));

        menu->addAction(newTab);
        menu->addAction(closefile);
        menu->exec(view->viewport()->mapToGlobal(pos));
    }
}

void MainWindow::newTab()
{
    auto* currView = qobject_cast<QTreeView*>(tabWgt->currentWidget());
    if (currView) {
        auto* currModel = dynamic_cast<XmlModel*>(currView->model());
        if (currModel) {
            auto currIndex = currView->currentIndex();
            auto* newView = new QTreeView(tabWgt);
            auto* newModel = new XmlModel(newView);
            newView->setModel(newModel);
            static int i = 1;
            tabWgt->addTab(newView, tr("Tab ") + QString::number(++i));
            tabWgt->setCurrentIndex(tabWgt->indexOf(newView));
            auto* tmp = dynamic_cast<XmlModel*>(newView->model());
            if (tmp) {
                tmp->append(currIndex);
                currModel->removeRow(currIndex.row());
            }
            else return;
         }
         else return;
    }
    else return;
}

