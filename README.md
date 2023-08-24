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

## 주요 코드 설명
완성 후 기술

