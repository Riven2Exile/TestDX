/*
    Windows��Ϣ����

*/
#ifndef WND_MESSAGE_HANDLE_H
#define WND_MESSAGE_HANDLE_H



//// ����
typedef bool (*WndMsg)(const WPARAM& wParam, const LPARAM& lParam);



class CWndMessageHandle
{
public:
    void init();

    bool handleMessage(); //û�˴���ͷ���false, ����Ĭ�ϵ�win����

public:
    //// �������Ϣ
    

private:
    void registerMessageHandle();

    //
    // wnd -> / /
};


#endif