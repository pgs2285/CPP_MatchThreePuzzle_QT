#include "board.h"
#include "Consts.h"
#include "item.h"
#include "QDebug"

Board::Board(QGraphicsScene* scene)
    : _scene(scene), _gen(_rand()), _moveCount(0)
{
    _scene -> addItem(&_root);

    _root.setX(_scene->sceneRect().width() / 2 - (Consts::BOARD_SIZE / 2 * Consts::ITEM_SIZE) ); // 맥북에서는 싱글모니터니까 /2 , 듀얼모니터환경에선 오른쪽기준 * 1.5
    _root.setY(_scene->sceneRect().height() / 2 - (Consts::BOARD_SIZE / 2 * Consts::ITEM_SIZE) );
    for(int row = 0; row < Consts::BOARD_SIZE; ++row)
    {
        std::vector<Item*> _row(Consts::BOARD_SIZE); // 보드의 사이즈를 미리 지정해둔다.
        _items.push_back(_row);
        for(int column = 0; column < Consts::BOARD_SIZE; ++column)
        {
            addItem(row,column);
        }
    }

    refreshBoard();
}

void Board::addItem(int row, int column) // column에 이미지를 넣어주기 위함.
{

    // device 와 gen은 한번만 뽑는게 (시드) 나을거같으니 생성자로 빼준다.
    std::uniform_int_distribution<int> randomNum(0, Consts::img_count - 1);

    const std::string& path = Consts::img_path[randomNum(_gen)];

    Item* item = new Item(this, path, row, column, &_root);
    item->setPos(column * Consts::ITEM_SIZE , row * Consts::ITEM_SIZE);


    _items[row][column] = item;        // push_back 안하고 이렇게 가능한건 vector의 크기를 지정해서 그럼.
                                        // 추후 재활용 할거니 일단 이렇게 적어두자.
}

Board::~Board()
{
    for(int row = 0; row < Consts::BOARD_SIZE; row++)
    {
        for (int column = 0; column < Consts::BOARD_SIZE; column++)
        {
            removeItem(row,column);
        }
    }
}
MatchSet Board::matchedItems() const
{
    MatchSet matched;       //3개이상 뭉치는것들이 들어갈것
    for (int row = 0; row < _items.size(); ++row)       // 9*9 기준으로 _items.size()는 9이다. (햇갈리지 말자)
    {
        for(int column = 0; column < _items[row].size(); ++column)
        {
            MatchSet m = matchedItems(row, column);
            if(m.size() >= 3)
            {
                matched.insert(m.begin(), m.end());
            }
        }
    }
    return matched;
}

MatchSet Board::matchedItems(int row, int column) const
{
    MatchSet horizontalMatched = matchedItemHorizontal(row, column);
    MatchSet verticalMatched = matchedItemVertical(row, column);

    MatchSet matched;
    if(horizontalMatched.size() >= 3)
    {
        matched.insert(horizontalMatched.begin(), horizontalMatched.end());
    }else if(verticalMatched.size() >= 3)
    {
        matched.insert(verticalMatched.begin(), verticalMatched.end());
    }

    return matched;

}

MatchSet Board::matchedItemHorizontal(int row, int column) const        // 수평으로 맞는거 구하기
{
    Item* item = _items[row][column];
    if(item == nullptr) return {};

    MatchSet Matched;
    for(int i = column - 1; i >= 0; --i)
    {
        if(_items[row][i] != nullptr && _items[row][i]->getPath() == item->getPath())   // 비어있지않고 이미지가 같다면. (경로가 같다면)
        {
            Matched.insert({row , i});      // pair를 대입하고
        }
        else{
            break;                              // 아니면 break 하기
        }
    }

    for(int i = column + 1; i < Consts::BOARD_SIZE; ++i)
    {
        if(_items[row][i] != nullptr && _items[row][i]->getPath() == item->getPath())   // 비어있지않고 이미지가 같다면. (경로가 같다면)
        {
            Matched.insert({row , i});      // pair를 대입하고
        }
        else{
            break;                              // 아니면 break 하기
        }
    }

    if(Matched.size() + 1 >= 3) // 매칭 완료
    {
        Matched.insert({row, column});      // 자기자신은 빠져있으므로 포함시켜준다
        return Matched;
    }
    else{
        return {};
    }
}


MatchSet Board::matchedItemVertical(int row, int column) const
{
    Item* item = _items[row][column];
    if(item == nullptr) return {};

    MatchSet Matched;
    for(int i = row - 1; i >= 0; --i)
    {
        if(_items[i][column] != nullptr && _items[i][column]->getPath() == item->getPath())   // 비어있지않고 이미지가 같다면. (경로가 같다면)
        {
            Matched.insert({i , column});      // pair를 대입하고
        }
        else{
            break;                              // 아니면 break 하기
        }
    }

    for(int i = row + 1; i < Consts::BOARD_SIZE; ++i)
    {
        if(_items[i][column] != nullptr && _items[i][column]->getPath() == item->getPath())   // 비어있지않고 이미지가 같다면. (경로가 같다면)
        {
            Matched.insert({i , column});      // pair를 대입하고
        }
        else{
            break;                              // 아니면 break 하기
        }
    }

    if(Matched.size() + 1 >= 3) // 매칭 완료
    {
        Matched.insert({row, column});      // 자기자신은 빠져있으므로 포함시켜준다
        return Matched;
    }
    else{
        return {};
    }
}



void Board::itemDragEvent(Item* item, Item::Direction dir)
{
//    qDebug() << item << " : " << static_cast<int>(dir) ;
    int column0 = item->getColumn();
    int row0 = item->getRow();
    int column1 = column0;
    int row1 = row0;

    switch(dir)
    {
    case Item::Direction::Left:
        column1--;
        break;
    case Item::Direction::Right:
        column1++;
        break;
    case Item::Direction::Up:
        row1--;
        break;
    case Item::Direction::Down:
        row1++;
        break;
    }
    if(row1 < 0 || column1 < 0) return;
    if(row1 >= Consts::BOARD_SIZE || column1 >= Consts::BOARD_SIZE) return;
    Item* item0 = item;
    Item* item1 = _items[row1][column1];
    if(item1 == nullptr || item0 == nullptr)
        return;
    exchangeItems(row0, row1, column0, column1);
}

void Board::itemMoveFinished(Item *item)
{
    if(--_moveCount>0)
        return;


    refreshBoard();

}
void Board::exchangeItems(int row0, int row1, int column0, int column1){
    Item* item0 = _items[row0][column0];
    Item* item1 = _items[row1][column1];

    moveItem(item1, row0, column0);
    moveItem(item0, row1, column1);


}

bool Board::refreshBoard()
{
    // 위에있는 Item들 아래로 내려주기
    MatchSet m = matchedItems();
    if(m.size() < 3) return false;
    for(const auto& match : m)
    {
        removeItem(match.first, match.second);
    }
    for(int column = 0; column < _items[0].size(); ++column)
    {
        for(int row = _items.size() - 1; row >= 0; --row) //아래서부터 탐색을해야 내려오는것까지 빠짐없이 체크한다.
        {
            if(_items[row][column] != nullptr) continue;
            else{
                for(int i = row - 1; i >= 0; i--)
                {
                    if(_items[i][column] != nullptr)
                    {
                        moveItem(i,column, row, column);
                        _items[i][column] = nullptr;
                        break;
                    }

                }
            }
        }

    }
    // 빈칸 채우기
    std::vector<int> emptyCounts;
    for(int column = 0; column < _items[0].size(); ++column)
    {
        int emptyCount = 0;
        for(int row = 0; row < _items.size(); ++row)
        {
            if(_items[row][column] == nullptr) emptyCount++;
            else break;
        }
        emptyCounts.push_back(emptyCount);
    }

    for(int row = 0; row <_items.size(); ++row)
    {
        for(int column = 0; column <_items[0].size(); ++column)
        {
            if(_items[row][column] == nullptr)
            {
                addItem(row, column);
                Item* item = _items[row][column];
                item->setY(item->y() - emptyCounts[column] * Consts::ITEM_SIZE);
                moveItem(row, column, row, column);
            }
        }
    }
    return true;

}
void Board::moveItem(Item* item, int row, int column)
{
    item->setColumn(column);
    item->setRow(row);
/*    item->setPos();   */  // 실제 화면에 보이는 값을 바꿔준다
    item->moveTo(column * Consts::ITEM_SIZE , row * Consts::ITEM_SIZE);
    _items[row][column] = item;                                             // 관리하고 있는 2차원 vector값을 바꿔준다.
    _moveCount++;
}

void Board::moveItem(int fromRow, int fromColumn, int toRow, int toColumn)
{
    Item* item = _items[fromRow][fromColumn];
    if(item == nullptr) return;
    moveItem(item,toRow,toColumn);

}

void Board::removeItem(int row, int column){
    auto* item = _items[row][column];
    if(item == nullptr) return;
    _items[row][column] = nullptr;
//    item -> setParentItem(nullptr);     // nullptr로 부모님을 뺴주고,(인데 삭제하면 자동으로 부모에서빠지니 굳이인가 싶다)
    _scene->removeItem(item);           // 아이템 제거후

    delete item;                        // 메모리에서 해제해줌.
}
