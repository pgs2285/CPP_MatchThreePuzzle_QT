#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <QtWidgets/QGraphicsPixmapItem>
#include <QtWidgets/QGraphicsScene>
#include "random"
#include <QtWidgets/QGraphicsRectItem>      // Item을 묶기위함.

class Board
{
    private:
    QGraphicsScene* _scene;
    QGraphicsRectItem _root;                                  // board 의 item을 한번에 묶어줄 변수
    std::vector<std::vector<QGraphicsPixmapItem*>> _items;    // 추후에 비어있는 상황을 대비해서 포인터로 받자.
    std::random_device _rand;
    std::mt19937 _gen;
    // random_device를 통해서 랜덤한 시드값을 가져오고 mt19937이라는 알고리즘을 통해서 랜덤숫자 만듬.
    // random_device를 그대로 사용하지 않는 이유는 속도에서 이점을 얻기 위해서.

    public:

        Board(QGraphicsScene* scene);
        ~Board();
        void addItem(int row, int column);
        void removeItem(int row, int column);
};

#endif // BOARD_H
