#ifndef _L_GUI_MGR_H
#define _L_GUI_MGR_H

class cGuiControl;
class cGuiForm;

class cGuiMgr
{
private:
    cGuiMgr();
public:
    
    virtual ~cGuiMgr();

    static cGuiMgr& Instance(){
        static cGuiMgr inst;
        return inst;
    }

    bool Init();

    void Update();
    void Draw();

    // 层次
    void Resort();

    // 数据
    void AddCtrl(cGuiControl *pCtrl); //加一个对话框.. 后面再考虑id
    void RemoveCtrl(unsigned int id);


    // 消息处理
    int OnMouseMove(const int& x, const int& y, const unsigned int& nFlag);
    int OnLButtonUp(const int& x, const int& y, const unsigned int& nFlag);
    int OnLButtonDown(const int& x, const int& y, const unsigned int& nFlag);

private:
    template<typename T>
    void ForEachUI(T fn){
        for ( std::list<cGuiControl*>::iterator itr = _listCtrl.begin();
            itr != _listCtrl.end();
            ++itr)
        {
            ((*itr)->*fn)();
        }
    }

    template<typename T>
    int ForEachUIMsg2(T fn, const int& x, const int& y, const unsigned int& nFlag){
        for ( std::list<cGuiControl*>::iterator itr = _listCtrl.begin();
            itr != _listCtrl.end();
            ++itr)
        {
            if( ((*itr)->*fn)(x, y, nFlag) == 0)
                return 0;
        }

        return 1;
    }

    //cGuiForm* _pRoot;
    std::list<cGuiControl*> _listCtrl;
};


#endif