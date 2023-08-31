#ifndef ITEM_H
#define ITEM_H

#include <QtWidgets/QGraphicsPixmapItem>
#include <string>

class Item : public QGraphicsPixmapItem, public QObject
{

public:

    enum Direction{
        Left,Right,Up,Down
    };

    class EventListener{            // 이벤트 전달해주는 listener제작.
    public:
        virtual void itemDragEvent(Item* item, Direction dir) = 0;
        virtual void itemMoveFinished(Item* item) = 0;
    };

    Item(EventListener* listener,const std::string& path, int row, int column, QGraphicsRectItem* root);




    // getter
    std::string getPath() const;
    int getRow() const;
    int getColumn() const;
    // setter
    void setRow(int row);
    void setColumn(int column);
    void moveTo(double toX, double toY);
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    // 각각 마우스를 눌렀을떄 좌표와 땠을때 좌표를 불러온다.
private:
    EventListener* _listener;
    std::string _path;
    int _row;
    int _column;
    QPointF _pressPos;

public:

};

#endif // ITEM_H
