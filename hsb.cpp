#include "hsb.h"

stHsb c_ZeroHSB;

inline void SwapRGB(int &a, int &b)  
{  
    a += b;  
    b = a - b;  
    a -= b;  
}  

inline void CheckRGB(int &Value)  
{  
    if (Value < 0) Value = 0;  
    else if (Value > 255) Value = 255;  
}  

inline void AssignRGB(BYTE &R, BYTE &G, BYTE &B, int intR, int intG, int intB)  
{  
    R = intR;  
    G = intG;  
    B = intB;  
}  

void SetBright(BYTE &R, BYTE &G, BYTE &B, int bValue)  
{  
    int intR = R;  
    int intG = G;  
    int intB = B;  
    if (bValue > 0)  
    {  
        intR = intR + (255 - intR) * bValue / 255;  
        intG = intG + (255 - intG) * bValue / 255;  
        intB = intB + (255 - intB) * bValue / 255;  
    }  
    else if (bValue < 0)  
    {  
        intR = intR + intR * bValue / 255;  
        intG = intG + intG * bValue / 255;  
        intB = intB + intB * bValue / 255;  
    }  
    CheckRGB(intR);  
    CheckRGB(intG);  
    CheckRGB(intB);  
    AssignRGB(R, G, B, intR, intG, intB);  
}  

void SetHueAndSaturation(BYTE &R, BYTE &G, BYTE &B, int hValue, int sValue)  
{  
    int intR = R;  
    int intG = G;  
    int intB = B;  

    if (intR < intG)  
        SwapRGB(intR, intG);  
    if (intR < intB)  
        SwapRGB(intR, intB);  
    if (intB > intG)  
        SwapRGB(intB, intG);  

    int delta = intR - intB;  
    if (!delta) return;  

    int entire = intR + intB;  
    int H, S, L = entire >> 1;  
    if (L < 128)  
        S = delta * 255 / entire;  
    else  
        S = delta * 255 / (510 - entire);  
    if (hValue)  
    {  
        if (intR == R)  
            H = (G - B) * 60 / delta;  
        else if (intR == G)  
            H = (B - R) * 60 / delta + 120;  
        else  
            H = (R - G) * 60 / delta + 240;  
        H += hValue;  
        if (H < 0) H += 360;  
        else if (H > 360) H -= 360;  
        int index = H / 60;  
        int extra = H % 60;  
        if (index & 1) extra = 60 - extra;  
        extra = (extra * 255 + 30) / 60;  
        intG = extra - (extra - 128) * (255 - S) / 255;  
        int Lum = L - 128;  
        if (Lum > 0)  
            intG += (((255 - intG) * Lum + 64) / 128);  
        else if (Lum < 0)  
            intG += (intG * Lum / 128);  
        CheckRGB(intG);  
        switch (index)  
        {  
        case 1:  
            SwapRGB(intR, intG);  
            break;  
        case 2:  
            SwapRGB(intR, intB);  
            SwapRGB(intG, intB);  
            break;  
        case 3:  
            SwapRGB(intR, intB);  
            break;  
        case 4:  
            SwapRGB(intR, intG);  
            SwapRGB(intG, intB);  
            break;  
        case 5:  
            SwapRGB(intG, intB);  
            break;  
        }  
    }  
    else  
    {  
        intR = R;  
        intG = G;  
        intB = B;  
    }  
    if (sValue)  
    {  
        if (sValue > 0)  
        {  
            sValue = sValue + S >= 255? S: 255 - sValue;  
            sValue = 65025 / sValue - 255;  
        }  
        intR += ((intR - L) * sValue / 255);  
        intG += ((intG - L) * sValue / 255);  
        intB += ((intB - L) * sValue / 255);  
        CheckRGB(intR);  
        CheckRGB(intG);  
        CheckRGB(intB);  
    }  
    AssignRGB(R, G, B, intR, intG, intB);  
}  

void hsb(BYTE& R, BYTE& G, BYTE& B, int hValue, int sValue, int bValue)
{
    if (sValue > 0 && bValue)
        SetBright(R, G, B, bValue);
    SetHueAndSaturation(R, G, B, hValue, sValue);
    if (bValue && sValue <= 0)
        SetBright(R, G, B, bValue);
}

// hValue [-360, 360]
// sValue [-255, 255]
// bValue [-255, 255]

void hsbColor565(WORD* clr, int hValue, int sValue, int bValue)
{
    BYTE R = ((*clr) << 0 >> 11);
    BYTE G = ((*clr) << 5 >> 10);
    BYTE B = ((*clr) << 11 >> 11);

    R = R << 3;
    G = G << 2;
    B = B << 3;

    hsb(R, G, B, hValue, sValue, bValue);

    R = R >> 3;
    G = G >> 2;
    B = B >> 3;

    *clr = (R << 11) + (G << 5) + (B);
}

void hsbColor4444(WORD* clr, int hValue, int sValue, int bValue)
{
    BYTE A = ((*clr) << 0 >> 12);
    BYTE R = ((*clr) << 4 >> 12);
    BYTE G = ((*clr) << 8 >> 12);
    BYTE B = ((*clr) << 12 >> 12);

    A = A << 4;
    R = R << 4;
    G = G << 4;
    B = B << 4;

    hsb(R, G, B, hValue, sValue, bValue);

    A = A >> 4;
    R = R >> 4;
    G = G >> 4;
    B = B >> 4;

    *clr = (A << 12) + (R << 8) + (G << 4) + (B);
}

void hsbColor8888(DWORD* clr, int hValue, int sValue, int bValue)
{
    BYTE A = (BYTE)((*clr) << 0 >> 24);
    BYTE R = (BYTE)((*clr) << 8 >> 24);
    BYTE G = (BYTE)((*clr) << 16 >> 24);
    BYTE B = (BYTE)((*clr) << 24 >> 24);

    hsb(R, G, B, hValue, sValue, bValue);

    *clr = (A << 24) + (R << 16) + (G << 8) + (B);
}