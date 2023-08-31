#include "item.h"
#include "Consts.h"
#include <QtWidgets/QGraphicsSceneEvent>
#include <QDebug>
#include <QtWidgets/QGraphicsItemAnimation>

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

void Item::moveTo(double toX, double toY)
{
    double diffX = toX - x();
    double diffY = toY - y();   // 거리가 먼 만큼 이동해야하므로, diff를 구해주자.

    double time = 0;
    time+= qAbs(diffX) / Consts::BOARD_SIZE * Consts::AnimationTime; // qAbs(diffX) / boardsize하면 개수가 나올것이고, 거기에 animationtime을 곱한다.
    time+= qAbs(diffY) / Consts::BOARD_SIZE * Consts::AnimationTime; // 어차피 상,하,좌,우 만 움직이므로 diffX,diffY중 하나는 0일거기때문에 둘다 time에서 관리
    QTimeLine* timer = new QTimeLine(time);     //시간만큼 애니메이션을 이용한다.
    QGraphicsItemAnimation* animation = new QGraphicsItemAnimation();
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
