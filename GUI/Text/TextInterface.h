

/*
*/

#ifndef _TEXT_INTERFACE_H
#define _TEXT_INTERFACE_H



//要不要返回值?
void TextOutput(const int& x, const int &y, const char* str, struct FRECT* p_re_clip = NULL);

void TextSetColorNext(const unsigned long& dw); //设置文本颜色








void Textinterface_ResetTextoutOneFrame();



#endif