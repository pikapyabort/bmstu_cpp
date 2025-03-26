//
// Created by Denis Horn on 24.02.2022.
//
#include "xmlmodel.h"

XmlModel::XmlModel(QObject* parent) : QAbstractItemModel(parent)
{
    root = new QStandardItem();
}

bool XmlModel::removeRows(int row, int count, const QModelIndex& parent)
{
    QStandardItem *item = nullptr;
    QModelIndex index;
    if (parent.isValid())
    {
        item = static_cast<QStandardItem *>(parent.internalPointer());
        index = parent;
    }
    else
    {
        item = root;
        index = QModelIndex();
    }
    if (item)
    {
        auto first = row;
        beginRemoveRows(index, first, first + count - 1);
        item->removeRows(first, count);
        endRemoveRows();
        return true;
    }
    return false;
}

void XmlModel::append(const QModelIndex& index)
{
    root->setColumnCount(2);
    if (index.isValid())
    {
        beginResetModel();
        auto* tmp = static_cast<QStandardItem*>(index.internalPointer())->clone();
        if (tmp)
        {
            if (columnCount(index) == 2) {
                auto sibling = index.model()->index(index.row(), 1, index);
                auto sibling_tmp = static_cast<QStandardItem*>(sibling.internalPointer())->clone();
                root->appendRow({tmp, sibling_tmp});
            }
            else {
                root->appendRow(tmp);
            }
            append(index, tmp);
            endResetModel();
        }
    }
}

void XmlModel::read(const QString& name)
{
    for(int i = 0; i < files.size(); ++i)
    {
        if (files.at(i) == name)
        {
            qWarning("File is already opened");
            return;
        }
    }
    files.append(name);
    auto* reader = new QXmlStreamReader;
    QFile file(name);
    QFileInfo f(name);
    QStack<int> counter;
    QStack<int> layers;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning("Can not open file");
        return;
    }
    reader->setDevice(&file);
    auto first = new QStandardItem(f.fileName());
    root->appendRow(first);
    root->setColumnCount(2);
    QStandardItem* curr = first;
    int n = 0;
    QXmlStreamReader::TokenType token = reader->readNext();
    while (!reader->atEnd() && !reader->hasError())
    {
        if (token == QXmlStreamReader::StartElement)
        {
            ++n;
            auto text = reader->name().toString();
            if (text == "array")
            {
                if (layers.isEmpty() || n != layers.top())
                {
                    counter.append(0);
                    layers.append(n);
                }
                text = QString("Entry %1").arg(counter.top() + 1);
                ++counter.top();
            }
            auto node = new QStandardItem(text);
            token = reader->readNext();
            if (reader->atEnd() || reader->hasError()) break;
            if (token == QXmlStreamReader::Characters)
            {
                auto name = reader->text().toString();
                auto item = new QStandardItem(name);
                curr->appendRow({node, item});
                if (text == "FullName" || text == "Comment")
                {
                    setData(curr->index(), QVariant(name), Qt::DisplayRole);
                    curr->setData(QVariant(name), Qt::DisplayRole);
                }
            }
            else curr->appendRow(node);
            curr = node;
            continue;
        }
        if (token == QXmlStreamReader::EndElement)
        {
            --n;
            curr = curr->parent();
            auto text = reader->name().toString();
            if (text == "array" && n + 1 != layers.top())
            {
                counter.pop();
                layers.pop();
            }
        }
        token = reader->readNext();
    }
    if (reader->hasError())
    {
        qWarning("Something went wrong...");
        return;
    }
}

void XmlModel::append(const QModelIndex& sourceIndex, QStandardItem* item)
{
    if (sourceIndex.isValid())
    {
        for (int i = 0; i < rowCount(sourceIndex); ++i)
        {
            auto child = sourceIndex.model()->index(i, 0, sourceIndex);
            auto* tmp = static_cast<QStandardItem*>(child.internalPointer())->clone();
            if (tmp)
            {
                if (columnCount(sourceIndex) == 2) {
                    auto sibling = sourceIndex.model()->index(i, 1, sourceIndex);
                    auto sibling_tmp = static_cast<QStandardItem*>(sibling.internalPointer())->clone();
                    item->appendRow({tmp, sibling_tmp});
                }
                else item->appendRow(tmp);

                append(child, tmp);
            }
        }
    }
}


int XmlModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<QStandardItem*>(parent.internalPointer())->rowCount();
    return root->rowCount();
}

int XmlModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<QStandardItem*>(parent.internalPointer())->columnCount();
    return root->columnCount();
}

QModelIndex XmlModel::index(int row, int column, const QModelIndex &parent) const
{
    if (hasIndex(row, column, parent))
    {
        QStandardItem* parentItem;
        if (!parent.isValid())
            parentItem = root;
        else
            parentItem = static_cast<QStandardItem*>(parent.internalPointer());
        QStandardItem* descendantItem = parentItem->child(row, column);
        if (descendantItem)
            return createIndex(row, column, descendantItem);
    }
    return QModelIndex();
}

QModelIndex XmlModel::parent(const QModelIndex &index) const
{
    QStandardItem* child = static_cast<QStandardItem*>(index.internalPointer());
    QStandardItem* par = child->parent();
    if (par == root || child == root) return QModelIndex();
    else
    {
        return createIndex(par->row(), 0, par);
    }
}

QVariant XmlModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();
    if (role != Qt::DisplayRole) return QVariant();
    auto* item = static_cast<QStandardItem*>(index.internalPointer());
    return item->data(0);
}

QVariant XmlModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ((section == 0) && (role == Qt::DisplayRole)) {
        return tr("Title");
    } else if ((section == 1) && (role == Qt::DisplayRole)){
        return tr("Value");
    }
    return QAbstractItemModel::headerData(section, orientation, role);
}



