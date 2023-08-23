
#include <QApplication>       // Application
#include <QGraphicsScene>     // Object를 띄우기 위한 Scene
#include <QGraphicsRectItem>  // Item
#include <QGraphicsView>      // 화면 floating 하기 위함
//#include <QDesktopWidget>             // qt6 부터 QScreen으로 대체되었다
#include <QScreen>
#include <QGraphicsPixmapItem>

#include <random>
#include "board.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);         // Application
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect geometry = screen->geometry();
    // QGuiApplication의 primaryScreen()으로 주 화면을 얻은 다음, 해당 화면의 geometry() 메서드를 이용하여 기하학적 영역에 대한 정보를 QRect 타입의 변수인 geometry에 저장
    QGraphicsScene scene;               // 여기에 만든 오브젝트들이 담긴다.
    scene.setSceneRect(geometry);       // 좌표기준을 primaryScreen으로 변경 없으면 0,0(가운데)가 기준이되버린다.

    Board board(&scene);

    // 현재 scene안에 rect가 포함되어 있으나 viewing역할은 없다. 이상태면 백그라운드로만 돌아감
    QGraphicsView view(&scene);         //
    view.showFullScreen();
    // 비로소 화면에 넘겨졌다. Cpp는 메모리 절약을 위해 주소값을 넘겨주는 경우가 많으므로 익숙해지자.
    

    return a.exec();
}
