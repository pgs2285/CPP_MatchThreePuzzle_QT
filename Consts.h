#ifndef CONSTS_H
#define CONSTS_H

#include <string>

namespace Consts{
// 맥북 전용 경로
    const std::string img_path[] =
        {
            "/Users/bagjiseong/Documents/GitHub/Cpp_MatchThreePuzzle_Qt/characterImg/Cat_Avatar_Rounded.png",
            "/Users/bagjiseong/Documents/GitHub/Cpp_MatchThreePuzzle_Qt/characterImg/Chick_Avatar_Rounded.png",
            "/Users/bagjiseong/Documents/GitHub/Cpp_MatchThreePuzzle_Qt/characterImg/Fox_Avatar_Rounded.png",
            "/Users/bagjiseong/Documents/GitHub/Cpp_MatchThreePuzzle_Qt/characterImg/Pig_Avatar_Rounded.png",
            "/Users/bagjiseong/Documents/GitHub/Cpp_MatchThreePuzzle_Qt/characterImg/Rabbit_Avatar_Rounded.png"
    };

// 윈도우 전용경로

//const std::string img_path[] =
//        {
//        "C:/Users/user/Desktop/MatchThreePuzzleQT/Cpp_MatchThreePuzzle_Qt/characterImg/Cat_Avatar_Rounded.png",
//        "C:/Users/user/Desktop/MatchThreePuzzleQT/Cpp_MatchThreePuzzle_Qt/characterImg/Chick_Avatar_Rounded.png",
//        "C:/Users/user/Desktop/MatchThreePuzzleQT/Cpp_MatchThreePuzzle_Qt/characterImg/Fox_Avatar_Rounded.png",
//        "C:/Users/user/Desktop/MatchThreePuzzleQT/Cpp_MatchThreePuzzle_Qt/characterImg/Pig_Avatar_Rounded.png",
//        "C:/Users/user/Desktop/MatchThreePuzzleQT/Cpp_MatchThreePuzzle_Qt/characterImg/Rabbit_Avatar_Rounded.png"

//    };

    const int BOARD_SIZE = 10;
    const int img_count = 5;
    const int ITEM_SIZE = 60;
    const int AnimationTime = 50;

}

#endif // CONSTS_H
