#include "item.h"
#include "Consts.h"
#include <QtWidgets/QGraphicsSceneEvent>
#include <QDebug>

Item::Item(EventListener* listener,const std::string& path, int row, int column, QGraphicsRectItem* root)
    : QGraphicsPixmapItem(
        QPixmap(path.c_str()).scaled(Consts::ITEM_SIZE, Consts::ITEM_SIZE),root),
        _listener(listener),
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
//    qDebug() << "Pressed : " <<event->pos();
}

void Item::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{

    QPointF releasePos = event -> pos();
    QPointF diff = releasePos - _pressPos;
    Direction dir;
    if(diff.x() == 0 && diff.y() == 0) return;  // 움직이지 않았을 때
    if(qAbs(diff.x()) > qAbs(diff.y()))     // 수평이동값이 수직이동값보다 클 경우에,
    {
        if(diff.x() > 0)                    // 오른쪽으로 간 경우.
        {
            dir = Direction::Right;
        }
        else{                               // 왼쪽으로 갈 경우.
            dir = Direction::Left;
        }
    }else{                                  // 수직 이동값이 수평이동값 보다 큰 경우에.
        if(diff.y() > 0)
        {
            dir = Direction::Down;
        }else{
            dir = Direction::Up;
        }

    }
    _listener->itemDragEvent(this, dir);
//    qDebug() << "Released : "<< this <<event->pos();
};
