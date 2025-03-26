#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include <QDir>
#include <QTableWidget>
#include <QHeaderView>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLabel>


class Menu : public QDialog
{
    Q_OBJECT
private:
    QTableWidget* table;
public:
    explicit Menu(QWidget *parent = nullptr);

    void fill(const QVector<QDir>& , const QStringList&);

public slots:
    void closeEvent(QCloseEvent*) override;
};

#endif
