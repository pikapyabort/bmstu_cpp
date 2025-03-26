//
// Created by Denis Horn on 24.02.2022.
//
#ifndef XMLMODEL_H
#define XMLMODEL_H

#include <QTreeView>
#include <QtXml/QDomDocument>
#include <QFile>
#include <QFileInfo>
#include <QAbstractItemModel>
#include <QWidget>
#include <QTextEdit>
#include <QMessageBox>
#include <QXmlStreamReader>
#include <QStandardItem>
#include <QStack>


class XmlModel: public QAbstractItemModel{
    Q_OBJECT

public:
    XmlModel(QObject* parent=nullptr);
    void append(const QModelIndex& index);
    void read(const QString& fileName);

    int rowCount(const QModelIndex &parent=QModelIndex()) const override;
    int columnCount(const QModelIndex &parent=QModelIndex()) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent=QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role=Qt::DisplayRole) const override;
    bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;

private:
    QStringList files{};
    QStandardItem *root{};
    QModelIndex currIndex{};
    void append(const QModelIndex& index, QStandardItem*);
};


#endif // XMLMODEL_H
