/*
    ����Tetris World�Ļ���
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
    int _viewWidth;     //�ܿ�
    int _viewHeight;    //�ܸ�

    int _cubeSize;  //С���ӵĿ��..
    std::string _strCubeImage;  //��������
    std::string _strCubeBlend;  //���緽������

    

    // draw
    std::vector<iSprite*> _CCube;       //��ǰ����
    std::vector<iSprite*> _WCube;       //���緽��
public:
    TetrisWorldView();
    virtual ~TetrisWorldView();

    void init();

    void setViewRect(int x, int y, int width, int height);
    void setCubeSize(int s);
    
    //��������
    void setCubeImage(const char* szName);
    void setWCubeImage(const char* szName);

    void run(unsigned long dwElapse);
    void draw();
    


    ///////// ��Ӧ����
};

//} // end namespace Tetris


#endif