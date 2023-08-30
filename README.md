# Cpp_MatchThreePuzzle_Qt

Cpp- Qt6를 이용한 MatchThreePuzzle 게임 제작해보기

## Qt란

초기에는 크로스플랫폼 GUI 라이브러리로 시작했고 UI 개발 도구,
번역 작업을 위한 도구와 C++ 개발에 필요한 많은 기능(UI, XML, 네트워크, SVG, Animation, Container Class 등등)을 제공하는 범용적인 응용프로그램 프레임워크

## Qt 사용 이유

OpenGL, DirectX와 같이 그래픽 모듈은 선행할게 많음. 현재 cpp의 클래스, 헤더 등 구분등을 게임에서 어떤식으로 나누나에 대해 배우기 위해 해보는 프로젝트 이므로,
사용이 보다 용이하고, 멀티플랫폼을 지원하는 Qt를 사용하기로 한다.
실제 아직도 Qt Framework를 이용해 만들어진 프로그램이 많으므로 추후에도 도움이 될거라 생각했다.

## 프로젝트 내용.

Consts.h -> 프로젝트에서 공용으로 사용되는 공통 변수들을 저장(BOARD_SIZE, Img_path등..)

board.h & board.cpp -> match three puzzle을 플레이하는 보드에 필요한 함수들을 구성 ( 보드 구성, remove Item 등...)

main.cpp -> main.cpp

Item.h & Item.cpp -> QGraphicsPixmapItem을 상속받아 내부 아이템 요소들의 변수를 따로 제작해줌. (모든 item들이 MouseEvent를 상속받기 위해)
-> mousePressEvent, mouseReleaseEvent 를 override해서 구현. qDebug

## 배운점

EventListener\* \_listener; 에서 생성자에서 초기화 후 사용하려 할때, 실수로 초기화를 안했던 문제가 있었다.
이 이후코드에서는 빈 메모리에 접근하여 강제종료를 일으켰고 강제종료된 프로그램이 안사라져 곤란했었다... 메모리 사용은 항상 조심하자.

## 주요 코드 설명

완성 후 기술

#### 보드 생성

#### Item 움직이기

#### Item 삭제 (3개 이상이 맞춰줬을떄 삭제하기)

##### 아이템 3개이상을 맞추기 위해 요소하나하나를 넣어주기
MatchSet = std::set<std::pair<int,int>> 이다

'''

MatchSet Board::matchedItems() const
{
MatchSet matched; //3개이상 뭉치는것들이 들어갈것
for (int row = 0; row < \_items.size(); ++row) // 9\*9 기준으로 \_items.size()는 9이다. (햇갈리지 말자)
{
for(int column = 0; column < \_items[row].size(); ++column)
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

'''

##### overloading 개념으로 row, column이 넘어왔을때 검사하기 위함.

'''

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
'''

##### 세로로 3개이상 같은것이 있나 검사하는 코드 (이하 matchedItemVertical 은 생략하기)

'''
MatchSet Board::matchedItemHorizontal(int row, int column) const // 수평으로 맞는거 구하기
{
Item\* item = \_items[row][column];
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
'''

##### 보드 초기화 시키기

'''
void Board::refreshBoard()
{
MatchSet m = matchedItems();
for(const auto& match : m)
{
removeItem(match.first, match.second);
}

}
'''
