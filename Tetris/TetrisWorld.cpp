
#include "TetrisBase.h"
#include "TetrisWorld.h"


//using namespace Tetris;

TetrisWorld::TetrisWorld():_perHeight(4)
{
    _pWorld = NULL;
    _width = 0;
    _height = 0;
    _bCurTCubeRun = false;  

    _pCurTCube = new stTCube;
    _pNextTcbe = new stTCube;

    _state = kStop;

    _dwFrameTimeTotal = 0;
    _dwFrameInterval = 1000; //1秒
}

TetrisWorld::~TetrisWorld()
{
    if (_pWorld)
    {
        for (int i = 0; i < _height + _perHeight; ++i)
        {
            delete[] _pWorld[i];
        }

        delete[] _pWorld;
    }

    if(_pCurTCube){   delete _pCurTCube;  }

}

//////
void TetrisWorld::SetWorldSize(int width, int height)
{
    if (NULL == _pWorld)
    {
        _width = width;
        _height = height /*+ c_preHeight*/;

        _pWorld = new stCube*[_height+_perHeight];
        for (int i = 0; i < _height + _perHeight; ++i)
        {
            _pWorld[i] = new stCube[_width];
        }
    }
}

void TetrisWorld::GenATCube()
{
    eCubeType type = (eCubeType)(rand() % ((int)kCT_Max));

    //type = kCT_T;   // test

    PutATCube(*_pNextTcbe);

    //生成
    _pNextTcbe->_vecCube.clear();
    if(kCT_O == type)
        GenO(*_pNextTcbe);
    else if(kCT_I == type)
        GenI(*_pNextTcbe);
    else if(kCT_J == type)
        GenJ(*_pNextTcbe);
    else if(kCT_7 == type)
        Gen7(*_pNextTcbe);
    else if(kCT_S == type)
        GenS(*_pNextTcbe);
    else if(kCT_T == type)
        GenT(*_pNextTcbe);
    else if(kCT_Z == type)
        GenZ(*_pNextTcbe);
    
}

//////////////// 生成基本方块
//  按照规则是有所居中
void TetrisWorld::GenO(stTCube& cube)
{
    // 基本
    cube.type = kCT_O;
    cube.dir = 0;
    cube._vecCube.push_back(stCube(0 + _width/2,_height-1, kTS_Fill));
    cube._vecCube.push_back(stCube(0 + _width/2+1,_height-1, kTS_Fill));
    cube._vecCube.push_back(stCube(0 + _width/2,_height-2, kTS_Fill));
    cube._vecCube.push_back(stCube(0 + _width/2+1,_height-2, kTS_Fill));

    // 居中

    // 随机旋转方向
}

void TetrisWorld::GenI(stTCube& cube)
{
    /*  o
        o
        o
        o
    */
    cube.type = kCT_I;
    cube.dir = 0;
    cube._vecCube.push_back(stCube(0+ _width/2+1, _height-1, kTS_Fill));
    cube._vecCube.push_back(stCube(0+ _width/2+1, _height-2, kTS_Fill));
    cube._vecCube.push_back(stCube(0+ _width/2+1, _height-3, kTS_Fill));
    cube._vecCube.push_back(stCube(0+ _width/2+1, _height-4, kTS_Fill));
}

void TetrisWorld::GenJ(stTCube& cube)
{
    /*      0
            0
          0 0
    */
    cube.type = kCT_J;
    cube.dir = 0;
    cube._vecCube.push_back( stCube(0 + _width/2, _height-1, kTS_Fill) );
    cube._vecCube.push_back( stCube(0 + _width/2, _height-2, kTS_Fill) );
    cube._vecCube.push_back( stCube(0 + _width/2, _height-3, kTS_Fill) );
    cube._vecCube.push_back( stCube(0 + _width/2 - 1, _height-3, kTS_Fill) );
}
void TetrisWorld::Gen7(stTCube& cube)
{
    /*      0 0
              0
              0
    */
    cube.type = kCT_7;
    cube.dir = 0;
    cube._vecCube.push_back( stCube(0 + _width/2 - 1, _height-1, kTS_Fill) );
    cube._vecCube.push_back( stCube(0 + _width/2, _height-1, kTS_Fill) );
    cube._vecCube.push_back( stCube(0 + _width/2, _height-2, kTS_Fill) );
    cube._vecCube.push_back( stCube(0 + _width/2, _height-3, kTS_Fill) );
}
void TetrisWorld::GenS(stTCube& cube)
{
    /*      0 0
          0 0
    */
    cube.type = kCT_S;
    cube.dir = 0;
    cube._vecCube.push_back( stCube(0 + _width/2+1, _height-1, kTS_Fill) );
    cube._vecCube.push_back( stCube(0 + _width/2, _height-1, kTS_Fill) );
    cube._vecCube.push_back( stCube(0 + _width/2, _height-2, kTS_Fill) );
    cube._vecCube.push_back( stCube(0 + _width/2-1, _height-2, kTS_Fill) );
}
void TetrisWorld::GenT(stTCube& cube)
{
    /*      0 0 0
              0
    */
    cube.type = kCT_T;
    cube.dir = 0;
    cube._vecCube.push_back( stCube(0 + _width/2 - 1, _height-1, kTS_Fill) );
    cube._vecCube.push_back( stCube(0 + _width/2, _height-1, kTS_Fill) );
    cube._vecCube.push_back( stCube(0 + _width/2 + 1, _height-1, kTS_Fill) );
    cube._vecCube.push_back( stCube(0 + _width/2, _height-2, kTS_Fill) );
}
void TetrisWorld::GenZ(stTCube& cube)
{
    /*      0 0
              0 0
    */
    cube.type = kCT_Z;
    cube.dir = 0;
    cube._vecCube.push_back( stCube(0 + _width/2-1, _height-1, kTS_Fill) );
    cube._vecCube.push_back( stCube(0 + _width/2, _height-1, kTS_Fill) );
    cube._vecCube.push_back( stCube(0 + _width/2, _height-2, kTS_Fill) );
    cube._vecCube.push_back( stCube(0 + _width/2+1, _height-2, kTS_Fill) );
}

//////
void TetrisWorld::Start()
{
    _state = kRunning;
    
    GenATCube();    
    GenATCube();

}

void TetrisWorld::Run(unsigned long dwElapse)
{
    do 
    {
        if (kStop == _state) {
            break ;
        }
        else if (kRunning == _state)
        {
            _dwFrameTimeTotal += dwElapse;
            if (_dwFrameTimeTotal >= _dwFrameInterval)
            {
                if (_bCurTCubeRun) //有方块正在下落
                {
                    printf("时间到,自动执行向下命令\n");
                    PutACommand(kTC_Down);
                }
                else
                {
                    
                    //方块已经和世界融为一体, 生成下一个方块
                    GenATCube();
                    _bCurTCubeRun = true;
                }
                

                _dwFrameTimeTotal = 0;
            }
        }

        // 时间到一帧的话，默认执行 down, 而且这个帧时间是能被重置的
    } while (0);
    
    
}


void TetrisWorld::PutATCube(const stTCube& cube)
{
    (*_pCurTCube) = cube;
    
    //todo: 根据类型设置锚点 和 设置一些相关的信息
    _bCurTCubeRun = true;
}

void TetrisWorld::PutACommand(eTCommand command)
{
    // todo: 具体的命令对游戏世界的影响
    if (kTC_Down == command)
        CommandDown();
    else if (kTC_Left == command)
        CommandLeft();
    else if (kTC_Right == command)
        CommandRight();
    else if (kTC_Up == command)
        CommandTurnClock();     // 命令:上, 先执行旋转
    else if (kTC_TurnClockwise == command)
        CommandTurnClock();
    else if (kTC_TurnAnticlockwise == command)
        CommandTurnAntiClock();
}


int TetrisWorld::JudgeDoRemove()
{
    if(NULL == _pWorld)
        return 0;

    //判断哪几层需要消除, 有可能是1,2,4 中间有空行
    int removeLine = 0;
    std::vector<int> vecRemove;
    for (int h = 0; h < _height ; ++h)
    {
        bool bRemove = true;
        for (int w = 0 ; w < _width; ++w)
        {
            if (_pWorld[h][w].state != kTS_Fill)
            {
                bRemove = false;
                break;
            }
        }

        if (bRemove)
        {
            ++removeLine;
            vecRemove.push_back(h); //记录需要消除的行
        }
    }

    // 开始消除(从上往下消除)
    int nSize = (int)vecRemove.size();
    for ( int i = nSize-1; i >= 0; --i )
    {
        int rmLine = vecRemove[i];
        for (int l = rmLine; l < _height + _perHeight - 1; ++l)
        {
            bool bEmptyLine = true;
            for (int w = 0; w < _width; ++w)
            {
                _pWorld[l][w] = _pWorld[l+1][w];
                if (_pWorld[l+1][w].state == kTS_Fill)
                {
                    bEmptyLine = false;
                }
            }

            if (bEmptyLine)
            {
                break;
            }
        }
    }

    return removeLine;
}

void TetrisWorld::CubeBlend()
{
    for (int i = 0; i < _pCurTCube->_vecCube.size(); ++i)
    {
        const stCube& c = _pCurTCube->_vecCube[i];
        _pWorld[c.y][c.x].state = kTS_Fill;
    }
}

bool TetrisWorld::IfNeedWallKick()
{   //左右踢..   上下不可踢(上下是地板踢)!
    if(NULL == _pCurTCube)
        return false;

    ////
    std::vector<stCube>& vec = _pCurTCube->_vecCube;
    int nSize = vec.size();
    bool bNeedKick = false;
    for (int i = 0; i < nSize; ++i)
    {
        // 1.是否越边界
        if (vec[i].x < 0 || vec[i].x >= _width)
        {
            return true;
        }

        // todo: 2.占用?
        
    }

    return false;
}

///// 命令的处理
void TetrisWorld::CommandDown()
{
    std::vector<stCube>& vec = _pCurTCube->_vecCube;
    int nSize = vec.size();
    //判断是否着陆
    for (int i = 0; i < nSize; ++i)
    {
        const stCube& cube = vec[i];
        if (cube.y == 0
            || _pWorld[cube.y - 1][cube.x].state == kTS_Fill)
        {
            //!!可以着陆, 当前方块与世界融为一体
            for (int k = 0; k < nSize; ++k)
            {
                _pWorld[vec[k].y][vec[k].x] = vec[k];
            }
            _bCurTCubeRun = false;

            break;
        }
    }

    //如果没有着陆,则方块继续下移一格
    if (_bCurTCubeRun)
    {
        for (int i = 0; i < nSize; ++i){
            --vec[i].y;
        }
    }
    else
    {
        //todo:融合
        CubeBlend();

        //todo: 判断消除
        int nRemoveLine = JudgeDoRemove();
        if (nRemoveLine)
        {
            //todo: 可能切换状态为消除过程
        }
    }
}

bool TetrisWorld::CommandLeft()
{
    std::vector<stCube>& vec = _pCurTCube->_vecCube;
    int nSize = vec.size();
    //先判断阻挡
    for (int i = 0; i < nSize; ++i)
    {
        const stCube& cube = vec[i];
        if (cube.x == 0
            || _pWorld[cube.y][cube.x-1].state == kTS_Fill)
        {
            return false;
        }
    }

    //无阻挡,则左移
    for ( int i = 0; i < nSize; ++i)
    {
        --vec[i].x;
    }
    return true;
}

bool TetrisWorld::CommandRight()
{
    std::vector<stCube>& vec = _pCurTCube->_vecCube;
    int nSize = vec.size();
    //先判断阻挡
    for (int i = 0; i < nSize; ++i)
    {
        const stCube& cube = vec[i];
        if (cube.x == _width - 1
            || _pWorld[cube.y][cube.x+1].state == kTS_Fill)
        {
            return false;
        }
    }

    //无阻挡,则右移
    for ( int i = 0; i < nSize; ++i)
    {
        ++vec[i].x;
    }
    return true;
}

void TetrisWorld::CommandTurnClock()
{
    if (_pCurTCube)
    {
        _pCurTCube->ClockTurn();

        // 是否墙踢(1.不允许旋转  2.墙踢)
        // 如果可以墙踢,则墙踢之
        bool bWallKick = false;
        while(IfNeedWallKick())
        {
            if (CommandLeft() == false)
            {
                if (CommandRight() == false)
                {
                    break;
                }
            }

            bWallKick = true;
        }
        // 如果不可以,则还原之
        if (bWallKick == false)
        {
            // todo: 还原
        }
    }
}

void TetrisWorld::CommandTurnAntiClock()
{

}