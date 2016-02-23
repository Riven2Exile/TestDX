
#include "TetrisBase.h"

//using namespace Tetris;


void stTCube::Left(int value)
{
    int n = _vecCube.size();
    for (int i = 0; i < n; ++i)
    {
        _vecCube[i].x -= value;
    }
}

void stTCube::Right(int value)
{
    int n = _vecCube.size();
    for (int i = 0; i < n; ++i)
    {
        _vecCube[i].x += value;
    }
}

void stTCube::Down(int value)
{
    int n = _vecCube.size();
    for (int i = 0; i < n; ++i)
    {
        _vecCube[i].y -= value;
    }
}

void stTCube::ClockTurn()
{
    turnClock(*this);
}

void stTCube::AntiClockTurn()
{
    
}




///// 基本API
// 旋转 http://tetrisconcept.net/wiki/ARS

void turnI(stTCube& cube, int dir);
void turnS(stTCube& cube, int dir);
void turnZ(stTCube& cube, int dir);
void turnJ(stTCube& cube, int dir);
void turn7(stTCube& cube, int dir);
void turnT(stTCube& cube, int dir);
int turn4(int oldDir, int turnDir);



void turnClock(stTCube& cube)
{
    if (kCT_I == cube.type)
        turnI(cube, 1);
    else if (kCT_S == cube.type)
        turnS(cube, 1);
    else if (kCT_Z == cube.type)
        turnZ(cube, 1);
    else if (kCT_7 == cube.type)
        turn7(cube, 1);
    else if (kCT_J == cube.type)
        turnJ(cube, 1);
    else if (kCT_T == cube.type)
        turnT(cube, 1);
}

void turnAntiClock(stTCube& cube)
{
    
}

#define cubeX(index, v) cube._vecCube[index].x += v
#define cubeY(index, v) cube._vecCube[index].y += v

void turnI(stTCube& cube, int dir)
{
    if (cube.dir == 1) { //横 --> 竖
        cube._vecCube[0].x += 2;
        cube._vecCube[0].y += 1;

        cube._vecCube[1].x += 1;

        cube._vecCube[2].y -= 1;

        cube._vecCube[3].x -= 1;
        cube._vecCube[3].y -= 2;
        cube.dir = 0;
    }
    else { //竖 --> 横 
        cube._vecCube[0].x -= 2;
        cube._vecCube[0].y -= 1;

        cube._vecCube[1].x -= 1;
        
        cube._vecCube[2].y += 1;

        cube._vecCube[3].x += 1;
        cube._vecCube[3].y += 2;
        cube.dir = 1;
    }
}

void turnS(stTCube& cube, int dir){
    if (cube.dir == 0){ /*
         0 0   ==>   0 
       0 0           0 0
                       0       */
        cube._vecCube[0].x -= 2;
        cube._vecCube[0].y += 1;

        cube._vecCube[1].x -= 1;

        cube._vecCube[2].y += 1;

        cube._vecCube[3].x += 1;
        cube.dir = 1;
    }
    else{
        cube.dir = 0;

        cube._vecCube[0].x += 2;
        cube._vecCube[0].y -= 1;

        cube._vecCube[1].x += 1;

        cube._vecCube[2].y -= 1;

        cube._vecCube[3].x -= 1;
    }
}

void turnZ(stTCube& cube, int dir){
    if (cube.dir == 0){ /*
        0 0             0
          0 0   -->   0 0
                      0
                            */
        cube.dir = 1;

        cube._vecCube[0].x += 2;
        cube._vecCube[0].y += 1;

        cube._vecCube[1].x += 1;

        cube._vecCube[2].y += 1;

        cube._vecCube[3].x -= 1;
    }
    else{
        cube.dir = 0;
        cube._vecCube[0].x -= 2;
        cube._vecCube[0].y -= 1;

        cube._vecCube[1].x -= 1;

        cube._vecCube[2].y -= 1;

        cube._vecCube[3].x += 1;
    }
}
void turnJ(stTCube& cube, int dir){
    if (1 == dir) //顺时针
    {
        if (0 == cube.dir)
        {
            cube._vecCube[0].x += 1;
            cube._vecCube[0].y -= 2;

            cube._vecCube[1].y -= 1;

            cube._vecCube[2].x -= 1;

            cube._vecCube[3].y += 1;
        }
        else if (1 == cube.dir)
        {
            cube._vecCube[0].x -= 1;

            cube._vecCube[1].y += 1;

            cube._vecCube[2].x += 1;
            cube._vecCube[2].y += 2;

            cube._vecCube[3].x += 2;
            cube._vecCube[3].y += 1;
        }
        else if (2 == cube.dir)
        {
            cube._vecCube[0].x -= 1;
            cube._vecCube[0].y += 1;

            cube._vecCube[2].x += 1;
            cube._vecCube[2].y -= 1;

            cube._vecCube[3].y -= 2;
        }
        else if (3 == cube.dir)
        {
            cubeX(0, 1);
            cubeY(0, 1);

            cubeX(2, -1);
            cubeY(2, -1);

            cubeX(3, -2);
        }

        cube.dir = turn4(cube.dir, dir);
    }
}

void turn7(stTCube& cube, int dir){
    if (1 == dir) { // 顺时针
        if (0 == cube.dir){
            cubeX(0,2);
            cubeY(0,-1);

            cubeX(1,1);
            cubeY(1,-2);

            cubeY(2,-1);

            cubeX(3,-1);
        }
        else if (1 == cube.dir) {
            cubeY(0,-1);

            cubeX(1,-1);

            cubeY(2,1);

            cubeX(3,1);
            cubeY(3,2);
        }
        else if (2 == cube.dir) {
            cubeX(0,-2);

            cubeX(1,-1);
            cubeY(1, 1);

            cubeX(3, 1);
            cubeY(3, -1);
        }
        else if (3 == cube.dir) {
            cubeY(0, 2);

            cubeX(1,1);
            cubeY(1,1);

            cubeX(3,-1);
            cubeY(3,-1);
        }

        cube.dir = turn4(cube.dir, dir);
    }
}

void turnT(stTCube& cube, int dir){
    if (1 == dir) { // 顺时针
        if (0 == cube.dir) {
            cubeX(0,1);
            cubeY(0,1);

            cubeX(2,-1);
            cubeY(2,-1);

            cubeX(3,-1);
            cubeY(3,1);
        }
        else if (1 == cube.dir) {
            cubeX(0,1);
            cubeY(0,-2);

            cubeY(1,-1);

            cubeX(2,-1);

            cubeX(3,1);
        }
        else if (2 == cube.dir) {
            cubeX(0,-1);

            cubeY(1,1);

            cubeX(2,1);
            cubeY(2,2);

            cubeX(3,1);
        }
        else if (3 == cube.dir) {
            cubeX(0,-1);
            cubeY(0,1);

            cubeX(2,1);
            cubeY(2,-1);

            cubeX(3,-1);
            cubeY(3,-1);
        }

        cube.dir = turn4(cube.dir, dir);
    }
}

// 辅助:4方向转
int turn4(int oldDir, int turnDir){
    if (1 == turnDir) //顺时针
    {
        ++oldDir;
        if (oldDir >= 4)
        {
            oldDir = 0;
        }
    }
    else{ //逆时针
        --oldDir;
        if (oldDir < 0)
        {
            oldDir = 3;
        }
    }

    return oldDir;
}

#undef cubeX
#undef cubeY