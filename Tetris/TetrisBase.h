
#ifndef TETRIS_BASE_H
#define TETRIS_BASE_H

#include <vector>

//namespace Tetris{

// 俄罗斯方块类型
enum eCubeType{
    kCT_None = -1,
    kCT_I   = 0, 
    kCT_J   = 1,
    kCT_7   = 2,
    kCT_O   = 3,
    kCT_S   = 4,
    kCT_T   = 5,
    kCT_Z   = 6,

    kCT_Max,
};

enum eTState{
    kTS_Empty   = 0,
    kTS_Fill    = 1,


    kTS_Num,
};

// 基本小块
struct stCube{
    int x;
    int y;
    eTState state; // 0:无填充, 1:有填充

    stCube():x(0),y(0),state(kTS_Empty){
    }

    stCube(int _x, int _y, eTState _s){
        x = _x;
        y = _y;
        state = _s;
    }
};

// 俄罗斯方块
struct stTCube{
    eCubeType type;
    std::vector<stCube> _vecCube;
    int dir; //方向 [0-3]

    stTCube():type(kCT_None), dir(0){

    }

    void Left(int value = 1);   //左移value个单位(无判断阻挡)
    void Right(int value = 1);  //右移value个单位(无判断阻挡)
    void Down(int value = 1);   //下移value个单位(无判断阻挡)
    void ClockTurn();       //顺时针转
    void AntiClockTurn();   //逆时针转
};



///////////// 世界框架
const int c_width = 10;
const int c_height = 20;




///////////// 基本指令
enum eTCommand{
    kTC_None    = 0,
    kTC_Down    = 1,
    kTC_Up      = 2,
    kTC_Left    = 3,
    kTC_Right   = 4,
    kTC_TurnClockwise = 5,      //顺时针旋转
    kTC_TurnAnticlockwise = 6,  //逆时针旋转


    kTC_Max,
};






// 基本API


void turnClock(stTCube& cube);       //顺时针旋转
void turnAntiClock(stTCube& cube);   //逆时针旋转



//} //end namespace





#endif