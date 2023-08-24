#include "item.h"
#include "Consts.h"
#include <QtWidgets/QGraphicsSceneEvent>
#include <QDebug>

Item::Item(const std::string& path, int row, int column, QGraphicsRectItem* root)
    : QGraphicsPixmapItem(
        QPixmap(path.c_str()).scaled(Consts::ITEM_SIZE, Consts::ITEM_SIZE),root),
        _path(path),
        _row(row),
        _column(column)

{

}

int Item::getColumn() const
{
    return _column;
}

std::string Item::getPath() const
{
    return _path;
}

int Item::getRow() const
{
    return _row;
}

void Item::setColumn(int column)
{
    _column = column;
}

void Item::setRow(int row)
{
    _row = row;
}

void Item::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    _pressPos = event -> pos();
    qDebug() << "Pressed : " <<event->pos();
}

void Item::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{

    _pressPos = event -> pos();
    qDebug() << "Released : " <<event->pos();
};
