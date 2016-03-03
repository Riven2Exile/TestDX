
#include "TetrisWorldView.h"
#include "TetrisWorld.h"
#include "..\iSprite.h"
#include "..\TextureMgr.h"
#include <algorithm>

//using namespace Tetris;

TetrisWorldView::TetrisWorldView():_x(0), _y(0), _viewWidth(0), _viewHeight(0)
{
    _pT = 0;

}

TetrisWorldView::~TetrisWorldView()
{
    for (unsigned int i = 0; i < _CCube.size(); ++i) {
        delete _CCube[i];
    }

    for (unsigned int i = 0; i < _WCube.size(); ++i) {
        delete _WCube[i];
    }
}

/////////////////
void TetrisWorldView::init()
{
    //做一些初始化~

    setViewRect(0, 0, _cubeSize* _width, _cubeSize* _height);

    //_TCube = CreateSprite(ST_MX, 4);
    for (int i = 0; i < 4; ++i)
    {
        _CCube.push_back(CreateSprite(ST_MX));
        _CCube[i]->LoadAImage("", g_pDevice);
        _CCube[i]->setTexture(CTextureMgr::instance().getTexture(_strCubeImage.c_str()));
        _CCube[i]->setWidth(_cubeSize);
        _CCube[i]->setHeight(_cubeSize);
        _CCube[i]->SetX(0);
        _CCube[i]->SetY(0);
    }
    
    int nsize = _height * _width;
    for (int i = 0; i < nsize; ++i)
    {
        _WCube.push_back(CreateSprite(ST_MX));
        _WCube[i]->LoadAImage("", g_pDevice);
        _WCube[i]->setTexture(CTextureMgr::instance().getTexture(_strCubeBlend.c_str()));
        _WCube[i]->setWidth(_cubeSize);
        _WCube[i]->setHeight(_cubeSize);
        _WCube[i]->SetX(_cubeSize * (i%_width));
        _WCube[i]->SetY(_viewHeight - _cubeSize * (i/_width));
        _WCube[i]->setVisible(false);
    }
}

void TetrisWorldView::setViewRect(int x, int y, int width, int height)
{
    _x = x;
    _y = y;
    _viewWidth = width;
    _viewHeight = height;
}
void TetrisWorldView::setCubeSize(int s)
{
    _cubeSize = s;
}


void TetrisWorldView::setCubeImage(const char* szName) {
    _strCubeImage = szName;
}
void TetrisWorldView::setWCubeImage(const char* szName) {
    _strCubeBlend = szName;
}

void TetrisWorldView::run(unsigned long dwElapse)
{
    TetrisWorld::Run(dwElapse);     //先调用父类


    //////1.  基础数据  转到  绘制的坐标
    //a.当前方块
    std::vector<stCube>& vCube = _pCurTCube->_vecCube;
    int nSize = vCube.size();
    for (int i = 0; i < nSize; ++i)
    {
        _CCube[i]->SetX(vCube[i].x * 36);
        _CCube[i]->SetY((20 - vCube[i].y) * 36 );  //宽 36


        _CCube[i]->setVisible(_bCurTCubeRun);
    }

    //b.世界方块 的是否显示
    for (int h = 0; h < _height; ++h)
    {
        for (int w = 0; w < _width; ++w)
        {
            int indexView = w + h * _width;
            if( kTS_Fill == _pWorld[h][w].state )
            {
                _WCube[indexView]->setVisible(true);
            }
            else if (kTS_Empty == _pWorld[h][w].state)
            {
                _WCube[indexView]->setVisible(false);
            }


            _WCube[indexView]->Update();
        }
    }
    

    // view 的 update
    //std::for_each(_CCube.begin(), _CCube.end(), std::mem_fun<void,iSprite>(&iSprite::Update) );
	for (const auto& var : _CCube )
	{
		(*var).Update();
	}

    /*_pT->_pCurTCube*/
}

void TetrisWorldView::draw()
{
    //////画背景

    //////画边框

    //////画Tetris
    //std::for_each(_WCube.begin(), _WCube.end(), std::mem_fun<void, iSprite>(&iSprite::Draw));

    //std::for_each(_CCube.begin(), _CCube.end(), std::mem_fun<void, iSprite>(&iSprite::Draw));

	for (const auto& var : _WCube)
	{
		(*var).Draw();
	}

	for (const auto& var : _CCube){
		(*var).Draw();
	}
}

