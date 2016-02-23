
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
    _dwFrameInterval = 1000; //1��
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

    //����
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

//////////////// ���ɻ�������
//  ���չ�������������
void TetrisWorld::GenO(stTCube& cube)
{
    // ����
    cube.type = kCT_O;
    cube.dir = 0;
    cube._vecCube.push_back(stCube(0 + _width/2,_height-1, kTS_Fill));
    cube._vecCube.push_back(stCube(0 + _width/2+1,_height-1, kTS_Fill));
    cube._vecCube.push_back(stCube(0 + _width/2,_height-2, kTS_Fill));
    cube._vecCube.push_back(stCube(0 + _width/2+1,_height-2, kTS_Fill));

    // ����

    // �����ת����
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
                if (_bCurTCubeRun) //�з�����������
                {
                    printf("ʱ�䵽,�Զ�ִ����������\n");
                    PutACommand(kTC_Down);
                }
                else
                {
                    
                    //�����Ѿ���������Ϊһ��, ������һ������
                    GenATCube();
                    _bCurTCubeRun = true;
                }
                

                _dwFrameTimeTotal = 0;
            }
        }

        // ʱ�䵽һ֡�Ļ���Ĭ��ִ�� down, �������֡ʱ�����ܱ����õ�
    } while (0);
    
    
}


void TetrisWorld::PutATCube(const stTCube& cube)
{
    (*_pCurTCube) = cube;
    
    //todo: ������������ê�� �� ����һЩ��ص���Ϣ
    _bCurTCubeRun = true;
}

void TetrisWorld::PutACommand(eTCommand command)
{
    // todo: ������������Ϸ�����Ӱ��
    if (kTC_Down == command)
        CommandDown();
    else if (kTC_Left == command)
        CommandLeft();
    else if (kTC_Right == command)
        CommandRight();
    else if (kTC_Up == command)
        CommandTurnClock();     // ����:��, ��ִ����ת
    else if (kTC_TurnClockwise == command)
        CommandTurnClock();
    else if (kTC_TurnAnticlockwise == command)
        CommandTurnAntiClock();
}


int TetrisWorld::JudgeDoRemove()
{
    if(NULL == _pWorld)
        return 0;

    //�ж��ļ�����Ҫ����, �п�����1,2,4 �м��п���
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
            vecRemove.push_back(h); //��¼��Ҫ��������
        }
    }

    // ��ʼ����(������������)
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
{   //������..   ���²�����(�����ǵذ���)!
    if(NULL == _pCurTCube)
        return false;

    ////
    std::vector<stCube>& vec = _pCurTCube->_vecCube;
    int nSize = vec.size();
    bool bNeedKick = false;
    for (int i = 0; i < nSize; ++i)
    {
        // 1.�Ƿ�Խ�߽�
        if (vec[i].x < 0 || vec[i].x >= _width)
        {
            return true;
        }

        // todo: 2.ռ��?
        
    }

    return false;
}

///// ����Ĵ���
void TetrisWorld::CommandDown()
{
    std::vector<stCube>& vec = _pCurTCube->_vecCube;
    int nSize = vec.size();
    //�ж��Ƿ���½
    for (int i = 0; i < nSize; ++i)
    {
        const stCube& cube = vec[i];
        if (cube.y == 0
            || _pWorld[cube.y - 1][cube.x].state == kTS_Fill)
        {
            //!!������½, ��ǰ������������Ϊһ��
            for (int k = 0; k < nSize; ++k)
            {
                _pWorld[vec[k].y][vec[k].x] = vec[k];
            }
            _bCurTCubeRun = false;

            break;
        }
    }

    //���û����½,�򷽿��������һ��
    if (_bCurTCubeRun)
    {
        for (int i = 0; i < nSize; ++i){
            --vec[i].y;
        }
    }
    else
    {
        //todo:�ں�
        CubeBlend();

        //todo: �ж�����
        int nRemoveLine = JudgeDoRemove();
        if (nRemoveLine)
        {
            //todo: �����л�״̬Ϊ��������
        }
    }
}

bool TetrisWorld::CommandLeft()
{
    std::vector<stCube>& vec = _pCurTCube->_vecCube;
    int nSize = vec.size();
    //���ж��赲
    for (int i = 0; i < nSize; ++i)
    {
        const stCube& cube = vec[i];
        if (cube.x == 0
            || _pWorld[cube.y][cube.x-1].state == kTS_Fill)
        {
            return false;
        }
    }

    //���赲,������
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
    //���ж��赲
    for (int i = 0; i < nSize; ++i)
    {
        const stCube& cube = vec[i];
        if (cube.x == _width - 1
            || _pWorld[cube.y][cube.x+1].state == kTS_Fill)
        {
            return false;
        }
    }

    //���赲,������
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

        // �Ƿ�ǽ��(1.��������ת  2.ǽ��)
        // �������ǽ��,��ǽ��֮
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
        // ���������,��ԭ֮
        if (bWallKick == false)
        {
            // todo: ��ԭ
        }
    }
}

void TetrisWorld::CommandTurnAntiClock()
{

}