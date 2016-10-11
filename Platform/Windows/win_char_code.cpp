
#include "stdafx.h"
// #ifndef WIN_CHAR_CODE_H
// #define WIN_CHAR_CODE_H
#include "..\..\GUI\cGuiEdit.h"



//edit_char_code = &WideCharToMultiByte;


int fun_edit_char_code(unsigned int szIn, unsigned long sz_in, char* szOut, int outsize){

// 	static char wc[3] = "";
// 	WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, (LPCWCH)&szIn, sizeof(sz_in), wc, 3, NULL, NULL);
// 	printf("test->  %s\n", wc);

	return WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, (LPCWCH)&szIn, sizeof(sz_in), szOut, 3, NULL, NULL);
}

char_code edit_char_code = &fun_edit_char_code;


int rude_get_string_width(std::string& str){
	int width = 0;

	width = str.length() * 6;
// 	for (int i = 0; i < str.length(); ++i) {
// 		if (str.at(i) <= 0x7f)
// 		{
// 			width += 6; //12×ÖºÅ
// 		}
// 		else{
// 
// 		}
// 	}

	return width;
}

//#endif