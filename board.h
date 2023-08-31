#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <set>
#include <QtWidgets/QGraphicsPixmapItem>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsRectItem>      // Item을 묶기위함.
#include "random"
#include "item.h"

using MatchPair = std::pair<int, int>;
using MatchSet = std::set<MatchPair>;

class Board : public Item::EventListener
{

    private:
    QGraphicsScene* _scene;
    QGraphicsRectItem _root;                                  // board 의 item을 한번에 묶어줄 변수
    std::vector<std::vector<Item*>> _items;    // 추후에 비어있는 상황을 대비해서 포인터로 받자.
    std::random_device _rand;
    std::mt19937 _gen;
    // random_device를 통해서 랜덤한 시드값을 가져오고 mt19937이라는 알고리즘을 통해서 랜덤숫자 만듬.
    // random_device를 그대로 사용하지 않는 이유는 속도에서 이점을 얻기 위해서.

    public:

        Board(QGraphicsScene* scene);
        ~Board();
        void addItem(int row, int column);
        void removeItem(int row, int column);
        virtual void itemDragEvent(Item* item, Item::Direction dir) override;
        void exchangeItems(int row0, int row1, int column0, int column1);
        bool refreshBoard();
        void moveItem(Item* item, int row, int column);
        void moveItem(int fromRow, int fromColumn, int toRow, int toColumn);
        MatchSet matchedItems() const;    // set을 사용해서 return 값 내부에 확실히 중복값이 없게 함.
        MatchSet matchedItems(int row, int column) const;
        MatchSet matchedItemHorizontal(int row, int column) const;
        MatchSet matchedItemVertical(int row, int column) const;
};

#endif // BOARD_H
