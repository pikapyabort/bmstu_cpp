#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "linenumberarea.h"
#include "editor.h"
#include "highlighter.h"
#include "menu.h"

#include <QMainWindow>
#include <QGridLayout>
#include <QTabWidget>
#include <QToolBar>
#include <QTabBar>
#include <QAction>
#include <QToolButton>
#include <QString>
#include <QMenu>
#include <QMessageBox>
#include <QErrorMessage>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QDockWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QTreeView>
#include <QFileSystemModel>
#include <QModelIndex>
#include <QCloseEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QList>
#include <QUrl>
#include <QDebug>
#include <QApplication>
#include <QMenuBar>
#include <QPushButton>
#include <QStatusBar>

class SaveDialog;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QTabWidget* tabWgt;
    Menu* menu;
    Highlighter* highlighter;

    QListWidget* currFiles;
    QFileSystemModel* filesModel;
    QTreeView* tree;
    int fileIndex;
    QDockWidget* openedFiles;
    QDockWidget* fileExplorer;
    QStringList filenames;
    QVector<QDir> filepaths;

    QLabel *label;

    QAction* create;
    QAction* open;
    QAction* close;
    QAction* save;
    QAction* saveAs;
    QAction* saveAll;
    QAction* closeAll;
    QAction* exit;

    void makeActions();
    void makeTabWidget();
    void makeMenuBar();
    void makeToolBar();
    void makeOpenedFilesDock();
    void makeFileExplorerDock();
    SaveDialog* createDialog();
    void statusBarChange();

protected:
    void closeEvent(QCloseEvent*) override; // ?

private slots:
    void createFile();
    void openFile();
    void openFile(const QString&);
    void openFile(QModelIndex);
    void closeFile();
    void closeFile(int);
    void saveFile();
    void saveFileAs();
    void saveAllFiles();
    void closeAllFiles();
    void closeWindow();

    void changeContainers(int, int);
    void changeParameter();

    void changeTabIndex(int, int);
    void deleteTab(int);
    void changeCurrIndex(int);
    void changeCurrIndex(QListWidgetItem*);
    void changeIndexOnDelete();

    void copy();
    void paste();
    void cut();
    void selectAll();
    void clear();

};

class SaveDialog: public QDialog
{
    Q_OBJECT
public:
    SaveDialog(QWidget *parent=0);
    QPushButton *btnSave;
    QTableWidget *table;
private:
    QLabel *label;
    QPushButton *btnNoSave;
    QPushButton *btnCansel;
};

#endif
