

#ifndef _TEXT_MGR_H
#define _TEXT_MGR_H


class CTextMgr
{
public:
    CTextMgr();
    virtual ~CTextMgr();
    static CTextMgr& Instance(){
        static CTextMgr inst;
        return inst;
    }

    void TextOut(const int& x, const int &y, const char* str);
    void SetFont( /* …Ë÷√≤Œ ˝ */ ); //

private:


    ///
};


#endif