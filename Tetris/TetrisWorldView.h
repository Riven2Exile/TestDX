/*
    负责Tetris World的绘制
*/

#ifndef TETRIS_WORLD_VIEW_H
#define TETRIS_WORLD_VIEW_H

#include <vector>
#include <string>

#include "TetrisWorld.h"

//namespace Tetris{

class iSprite;

class TetrisWorldView : public TetrisWorld
{
    TetrisWorld* _pT;
    int _x;
    int _y;
    int _viewWidth;     //总宽
    int _viewHeight;    //总高

    int _cubeSize;  //小格子的宽高..
    std::string _strCubeImage;  //纹理名字
    std::string _strCubeBlend;  //世界方块名字

    

    // draw
    std::vector<iSprite*> _CCube;       //当前方块
    std::vector<iSprite*> _WCube;       //世界方块
public:
    TetrisWorldView();
    virtual ~TetrisWorldView();

    void init();

    void setViewRect(int x, int y, int width, int height);
    void setCubeSize(int s);
    
    //设置纹理
    void setCubeImage(const char* szName);
    void setWCubeImage(const char* szName);

    void run(unsigned long dwElapse);
    void draw();
    


    ///////// 响应部分
};

//} // end namespace Tetris


#endif