#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    menu = nullptr,
    fileIndex = 1;
    setWindowTitle("Notepad");
    resize(800, 600);
    makeTabWidget();
    makeFileExplorerDock();
    makeOpenedFilesDock();
    makeActions();
    makeMenuBar();
    makeToolBar();
    setCentralWidget(tabWgt);
    label = new QLabel(this);
    statusBar()->addPermanentWidget(label);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    bool flag = false;
    for (int i = 0; i < tabWgt->count(); ++i)
    {
        if (tabWgt->tabWhatsThis(i) != "Без изменений")
        {
            flag = true;
            break;
        }
    }
    if (flag)
    {
        SaveDialog *dialog = createDialog();
        dialog->setModal(true);
        if (dialog->exec() == QDialog::Rejected) {
            delete dialog;
            event->ignore();
            return;
        }
        event->accept();
        delete dialog;
    }
}


void MainWindow::makeTabWidget()
{
    tabWgt = new QTabWidget(this);
    tabWgt->setTabsClosable(true);
    tabWgt->setUsesScrollButtons(true);
    tabWgt->setMovable(true);
    connect(tabWgt, SIGNAL(tabCloseRequested(int)), this, SLOT(closeFile(int)));
}

void MainWindow::makeActions()
{    
    create   = new QAction(QIcon(":/icons/newfile.png"),       tr("Новый"));
    open     = new QAction(QIcon(":/icons/open.png"),      tr("Открыть"));
    save     = new QAction(QIcon(":/icons/save.png"),      tr("Сохранить"));
    saveAll  = new QAction(QIcon(":/icons/saveall.png"), tr("Сохранить все"));
    close    = new QAction(tr("Закрыть"));
    saveAs   = new QAction(tr("Сохранить как"));
    closeAll = new QAction(tr("Закрыть все"));
    exit     = new QAction(tr("Выход"));

    create  ->setShortcut(QKeySequence("CTRL+N"));
    open    ->setShortcut(QKeySequence("CTRL+O"));
    save    ->setShortcut(QKeySequence("CTRL+S"));
    saveAll ->setShortcut(QKeySequence("CTRL+SHIFT+S"));
    close   ->setShortcut(QKeySequence("CTRL+W"));
    saveAs  ->setShortcut(QKeySequence("CTRL+ALT+S"));
    closeAll->setShortcut(QKeySequence("CTRL+SHIFT+W"));
    exit    ->setShortcut(QKeySequence("CTRL+Q"));

    connect(create,   SIGNAL(triggered()), SLOT(createFile()));
    connect(open,     SIGNAL(triggered()), SLOT(openFile()));
    connect(save,     SIGNAL(triggered()), SLOT(saveFile()));
    connect(saveAll,  SIGNAL(triggered()), SLOT(saveAllFiles()));
    connect(close,    SIGNAL(triggered()), SLOT(closeFile()));
    connect(saveAs,   SIGNAL(triggered()), SLOT(saveFileAs()));
    connect(closeAll, SIGNAL(triggered()), SLOT(closeAllFiles()));
    connect(exit,     SIGNAL(triggered()), SLOT(closeWindow()));
}

void MainWindow::makeMenuBar() {
    QMenu* fileMenu = new QMenu(tr("Файл"),   this);
    QMenu* editMenu = new QMenu(tr("Правка"), this);
    QMenu* viewMenu = new QMenu(tr("Вид"),    this);

    fileMenu->addAction(create);
    fileMenu->addAction(open);
    fileMenu->addAction(save);
    fileMenu->addAction(saveAs);
    fileMenu->addAction(saveAll);
    fileMenu->addAction(close);
    fileMenu->addAction(closeAll);
    fileMenu->addAction(exit);

    editMenu->addAction(tr("Вырезать"),    this, SLOT(cut()),       QKeySequence("CTRL+X"));
    editMenu->addAction(tr("Копировать"),  this, SLOT(copy()),      QKeySequence("CTRL+C"));
    editMenu->addAction(tr("Вставить"),    this, SLOT(paste()),     QKeySequence("CTRL+V"));
    editMenu->addAction(tr("Удалить"),     this, SLOT(clear()),     QKeySequence("CTRL+DELETE"));
    editMenu->addAction(tr("Выбрать все"), this, SLOT(selectAll()), QKeySequence("CTRL+A"));

    viewMenu->addAction(fileExplorer->toggleViewAction());
    viewMenu->addAction(openedFiles->toggleViewAction());

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(editMenu);
    menuBar()->addMenu(viewMenu);
}

void MainWindow::makeToolBar() {
    QToolBar* toolBar = addToolBar(tr("Файл"));
    toolBar->addAction(create);
    toolBar->addAction(open);
    toolBar->addAction(save);
    toolBar->addAction(saveAll);
}

void MainWindow::makeFileExplorerDock() {
    filesModel = new QFileSystemModel(this);
    filesModel->setRootPath(QDir::rootPath());

    tree = new QTreeView(this);
    tree->setModel(filesModel);
    tree->setColumnHidden(1, true);
    tree->setColumnHidden(2, true);
    tree->setColumnHidden(3, true);
    tree->setHeaderHidden(true);
    connect(tree, SIGNAL(doubleClicked(QModelIndex)), SLOT(openFile(QModelIndex)));

    fileExplorer = new QDockWidget(tr("Проводник"), this);
    fileExplorer->setWidget(tree);
    fileExplorer->setMaximumWidth(700);
    fileExplorer->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);
    fileExplorer->hide();
    addDockWidget(Qt::LeftDockWidgetArea, fileExplorer);
}

void MainWindow::makeOpenedFilesDock()
{
    currFiles = new QListWidget(this);

    connect(tabWgt->tabBar(), SIGNAL(tabMoved(int, int)),             SLOT(changeTabIndex(int, int)));
    connect(tabWgt->tabBar(), SIGNAL(currentChanged(int)),            SLOT(changeCurrIndex(int)));
    connect(tabWgt->tabBar(), SIGNAL(tabCloseRequested(int)),         SLOT(changeIndexOnDelete()));
    connect(tabWgt->tabBar(), SIGNAL(tabMoved(int, int)),             SLOT(changeContainers(int, int)));
    connect(currFiles,        SIGNAL(itemClicked(QListWidgetItem*)),  SLOT(changeCurrIndex(QListWidgetItem*)));
    connect(currFiles,        SIGNAL(currentRowChanged(int)), tabWgt, SLOT(setCurrentIndex(int)));

    openedFiles = new QDockWidget(tr("Открытые файлы"), this);
    openedFiles->setWidget(currFiles);
    openedFiles->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);
    openedFiles->hide();
    addDockWidget(Qt::RightDockWidgetArea, openedFiles);
}

void MainWindow::createFile()
{
    Editor* editor = new Editor(this);
    QString name = "Безымянный" + QString::number(fileIndex);

    int index = tabWgt->addTab(editor, name);
    tabWgt->setCurrentIndex(index);
    tabWgt->setTabToolTip(index, "");
    tabWgt->setTabWhatsThis(index, "Без изменений");
    connect(editor, SIGNAL(textChanged()), SLOT(changeParameter()));

    QListWidgetItem* item = new QListWidgetItem;
    item->setText(tabWgt->tabText(index));
    item->setToolTip(tabWgt->tabToolTip(index));

    currFiles->addItem(item);
    changeCurrIndex(index);

    filepaths.push_back(QDir::current());
    filenames.push_back(name);
    fileIndex++;

    connect(editor, &Editor::cursorPositionChanged, this, &MainWindow::statusBarChange);
}

void MainWindow::openFile()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Выберите файл"), "");
    if (path.isEmpty())
    {
        QMessageBox::warning(this, tr("Ошибка"), tr("Такого пути не существует!"), QMessageBox::Ok);
        return;
    }
    openFile(path);
}

void MainWindow::openFile(QModelIndex index)
{
    if (!filesModel->isDir(index)) openFile(filesModel->filePath(index));
}

void MainWindow::openFile(const QString& path)
{
    for (int i = 0; i < tabWgt->count(); ++i)
    {
        if (tabWgt->tabToolTip(i) == path)
        {
            QMessageBox::warning(this, tr("Ошибка"), tr("Файл уже открыт!"), QMessageBox::Ok);
            return;
        }
    }

    QString name = path.section("/", -1, -1);
    QFile file(path);

    if (file.open(QIODevice::ReadOnly))
    {
        filepaths.push_back(QFileInfo(file).path());
        filenames.push_back(name);

        Editor* tmp = new Editor(this);
        QString buffer = file.readAll();
        QString extension = QFileInfo(name).suffix();

        if (!extension.isEmpty())
        {
            highlighter = new Highlighter(extension, tmp->document());
            if (!highlighter->isSupported()) delete highlighter;
        }
        file.close();
        tmp->appendPlainText(buffer);

        int index = tabWgt->addTab(tmp, name);
        tabWgt->setCurrentIndex(index);
        tabWgt->setTabWhatsThis(index, "Без изменений");
        tabWgt->setTabToolTip(index, path);

        QListWidgetItem* item = new QListWidgetItem;
        item->setText(tabWgt->tabText(index));
        item->setToolTip(tabWgt->tabToolTip(index));
        currFiles->addItem(item);
        changeCurrIndex(index);
        connect(tmp, SIGNAL(textChanged()), SLOT(changeParameter()));
        connect(tmp, &Editor::cursorPositionChanged, this, &MainWindow::statusBarChange);
    }
    else
    {
        QMessageBox::warning(this, tr("Ошибка"), tr("Не удается открыть файл!"), QMessageBox::Ok);
        return;
    }
}

void MainWindow::saveFile()
{
    if (tabWgt->tabToolTip(tabWgt->currentIndex()) == "")
    {
        saveFileAs();
        return;
    }
    QString path = tabWgt->tabToolTip(tabWgt->currentIndex());
    QFile file(path);
    if (file.open(QIODevice::WriteOnly))
    {
        Editor* curr = qobject_cast<Editor*>(tabWgt->currentWidget());
        if(curr)
        {
            Q_ASSERT(curr != nullptr);
            file.write(curr->document()->toPlainText().toUtf8());
            file.close();
            tabWgt->setTabWhatsThis(tabWgt->currentIndex(), "Без изменений");
            tabWgt->setTabText(tabWgt->currentIndex(), path.section("/", -1, -1));
        }
    }
    else
    {
        QMessageBox::warning(this, tr("Ошибка"), tr("Не удается сохранить файл!"), QMessageBox::Ok);
        return;
    }
}

void MainWindow::saveFileAs()
{
    QString name = tabWgt->tabText(tabWgt->currentIndex()).remove('*');
    QString path = QFileDialog::getSaveFileName(this, "Сохранить " + name, name);
    if (path.isEmpty()) return;
    if (QFileInfo(path).suffix().isEmpty()) path.append(".txt");
    else
    {
        QFile file(path);
        if (file.open(QIODevice::WriteOnly))
        {
            Editor* curr = qobject_cast<Editor*>(tabWgt->currentWidget());
            if(curr)
            {
                Q_ASSERT(curr != nullptr);
                file.write(curr->document()->toPlainText().toUtf8());
                file.close();
            }
        }
        else
        {
            QMessageBox::warning(this, tr("Ошибка"), tr("Не удается сохранить файл!"), QMessageBox::Ok);
            return;
        }
    }
    filepaths.replace(tabWgt->currentIndex(), QDir(QFileInfo(path).path()));
    filenames.replace(tabWgt->currentIndex(), QFileInfo(path).fileName());
    name = path.section("/", -1, -1);

    tabWgt->tabBar()->setTabText(tabWgt->currentIndex(), name);
    tabWgt->tabBar()->setTabToolTip(tabWgt->currentIndex(), path);
    tabWgt->setTabWhatsThis(tabWgt->currentIndex(), "Без изменений");
    saveFile();
}

void MainWindow::saveAllFiles()
{
    int index = tabWgt->currentIndex();
    for (int i = 0; i < tabWgt->count(); ++i)
    {
        tabWgt->setCurrentIndex(i);
        if (tabWgt->tabWhatsThis(tabWgt->currentIndex()) != "Без изменений") saveFile();
    }
    tabWgt->setCurrentIndex(index);
}

void MainWindow::closeFile()
{
    closeFile(tabWgt->currentIndex());
}

void MainWindow::closeFile(int index)
{
    if (tabWgt->tabWhatsThis(tabWgt->currentIndex()) != "Без изменений")
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Предупреждение"), tr("Сохранить перед закрытием?"),
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) saveFile();
    }
    filepaths.remove(index);
    filenames.removeAt(index);
    delete tabWgt->widget(index);
    deleteTab(index);
}

void MainWindow::closeAllFiles()
{
    bool flag = false;
    for (int i = 0; i < tabWgt->count(); ++i)
    {
        if (tabWgt->tabWhatsThis(i) != "Без изменений")
        {
            flag = true;
            break;
        }
    }
    if (flag)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Предупреждения"), tr("Сохранить изменения?"),
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) saveAllFiles();
    }
    filepaths.clear();
    filenames.clear();
    fileIndex = 1;
    while (tabWgt->count() > 0) delete tabWgt->widget(0);
    currFiles->clear();
}

void MainWindow::closeWindow()
{
    QStringList names;
    QVector<QDir> paths;

    if (menu) delete menu;
    menu = new Menu(this);
    menu->setWindowTitle(tr("Предупреждение"));

    for (int i = 0; i < tabWgt->count(); i++)
    {
        if (tabWgt->tabText(i).contains('*'))
        {
            filenames.push_back(names[i]);
            filepaths.push_back(paths[i]);
        }
    }

    if (paths.isEmpty()) QApplication::quit();
    else
    {
        menu->fill(paths, names);
        int event = menu->exec();
        if (event == QDialog::Accepted) saveAllFiles();
        if (event != -1) QApplication::quit();
    }
}

void MainWindow::deleteTab(int index)
{
    delete currFiles->takeItem(index);
}

void MainWindow::changeTabIndex(int from, int to)
{
    currFiles->insertItem(to, currFiles->takeItem(from));
    statusBarChange();
}

void MainWindow::changeCurrIndex(QListWidgetItem* item)
{
    tabWgt->setCurrentIndex(item->listWidget()->row(item));
    statusBarChange();
}

void MainWindow::changeCurrIndex(int index)
{
    currFiles->setCurrentRow(index);
    statusBarChange();
}

void MainWindow::changeIndexOnDelete()
{
    currFiles->setCurrentRow(currFiles->count() - 1);
    statusBarChange();
}

void::MainWindow::changeParameter()
{
    if (!(tabWgt->tabText(tabWgt->currentIndex())).contains("*"))
    {
        tabWgt->setTabWhatsThis(tabWgt->currentIndex(), "Изменения");
        tabWgt->setTabText(tabWgt->currentIndex(), tabWgt->tabText(tabWgt->currentIndex()) + "*");
    }
}

void MainWindow::changeContainers(int from, int to)
{
    QString name = filenames.at(from);
    filenames.replace(from, filenames.at(to));
    filenames.replace(to, name);

    QDir path = filepaths.at(from);
    filepaths.replace(from, filepaths.at(to));
    filepaths.replace(to, path);
}

void MainWindow::copy()
{
    Editor* editor = qobject_cast<Editor*>(tabWgt->currentWidget());
    if(editor)
    {
        Q_ASSERT(editor != nullptr);
        editor->copy();
    }
}

void MainWindow::cut()
{
    Editor* editor = qobject_cast<Editor*>(tabWgt->currentWidget());
    if(editor)
    {
        Q_ASSERT(editor != nullptr);
        editor->cut();
    }
}

void MainWindow::selectAll()
{
    Editor* editor = qobject_cast<Editor*>(tabWgt->currentWidget());
    if(editor)
    {
        Q_ASSERT(editor != nullptr);
        editor->copy();
    }
}

void MainWindow::paste()
{
    Editor* editor = qobject_cast<Editor*>(tabWgt->currentWidget());
    if(editor)
    {
        Q_ASSERT(editor != nullptr);
        editor->paste();
    }
}

void MainWindow::clear()
{
    Editor* editor = qobject_cast<Editor*>(tabWgt->currentWidget());
    if(editor)
    {
        Q_ASSERT(editor != nullptr);
        editor->clear();
    }
}

SaveDialog* MainWindow::createDialog()
{
    SaveDialog *dialog = new SaveDialog(this);
    connect(dialog->btnSave, SIGNAL(clicked()), this, SLOT(saveAllFiles()));
    int row = 0;
    for (int i = 0; i < currFiles->count(); ++i) {
        tabWgt->setCurrentIndex(i);
        if (tabWgt->tabWhatsThis(i) != "Без изменений") {
            QTableWidgetItem *file = new QTableWidgetItem(tabWgt->tabText(i));
            QTableWidgetItem *path = new QTableWidgetItem(filepaths.at(i).canonicalPath());
            dialog->table->insertRow(row);
            dialog->table->setItem(row, 0, file);
            dialog->table->setItem(row, 1, path);
            ++row;
        }
    }
    return dialog;
}

SaveDialog::SaveDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle(tr("Сохранить изменения?"));
    setFixedSize(500, 400);

    table = new QTableWidget;
    table->setColumnCount(2);
    table->setHorizontalHeaderLabels(QStringList() << tr("Файл") << tr("Путь"));
    table->setFixedSize(480, 300);
    table->horizontalHeader()->setStretchLastSection(true);
    table->verticalHeader()->hide();

    label = new QLabel(tr("Файлы с несохраненными изменениями:"));
    label->setFixedSize(400, 15);

    btnSave   = new QPushButton(tr("Сохранить все"));
    btnNoSave = new QPushButton(tr("Не сохранять"));
    btnCansel = new QPushButton(tr("Отмена"));
    btnSave  ->setFixedSize(155, 30);
    btnNoSave->setFixedSize(155, 30);
    btnCansel->setFixedSize(155, 30);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label, 0, 0);
    layout->addWidget(table, 1, 0, 1, 3);
    layout->addWidget(btnSave, 2, 0);
    layout->addWidget(btnNoSave, 2, 1);
    layout->addWidget(btnCansel, 2, 2);
    setLayout(layout);

    connect(btnSave,   SIGNAL(clicked()), this, SLOT(accept()));
    connect(btnNoSave, SIGNAL(clicked()), this, SLOT(accept()));
    connect(btnCansel, SIGNAL(clicked()), this, SLOT(reject()));
}

void MainWindow::statusBarChange() {
    Editor* curr = qobject_cast<Editor*>(tabWgt->currentWidget());
    if(curr) label->setText(QString("Строка: %1 Столбец: %2 ")
                            .arg((curr->cursorRect().bottom()-18)/16+1)
                            .arg((curr->cursorRect().left()-3)/4+1));
}
