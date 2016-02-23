/*
    Windows消息处理

*/
#ifndef WND_MESSAGE_HANDLE_H
#define WND_MESSAGE_HANDLE_H



//// 声明
typedef bool (*WndMsg)(const WPARAM& wParam, const LPARAM& lParam);



class CWndMessageHandle
{
public:
    void init();

    bool handleMessage(); //没人处理就返回false, 调用默认的win函数

public:
    //// 具体的消息
    

private:
    void registerMessageHandle();

    //
    // wnd -> / /
};


#endif