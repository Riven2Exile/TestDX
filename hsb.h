
#ifndef HSB_H
#define HSB_H


typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef unsigned char BYTE;


struct stHsb
{
    int hValue;
    int sValue;
    int bValue;

    inline stHsb(int h = 0, int s = 0, int b = 0) : hValue(h), sValue(s), bValue(b) {}
    inline bool isZero() const { return !hValue && !sValue && !bValue; }
    inline bool operator==(const stHsb& r) const
    {
        return (hValue == r.hValue && sValue == r.sValue && bValue == r.bValue);
    }
    inline bool operator!=(const stHsb& r) const
    {
        return !this->operator ==(r);
    }
    inline bool operator<(const stHsb& r) const
    {
        if (hValue != r.hValue)
            return hValue < r.hValue;
        if (sValue != r.sValue)
            return sValue < r.sValue;
        return bValue < r.bValue;
    }
    inline bool operator>(const stHsb& r) const
    {
        if (hValue != r.hValue)
            return hValue > r.hValue;
        if (sValue != r.sValue)
            return sValue > r.sValue;
        return bValue > r.bValue;
    }
    inline bool operator>=(const stHsb& r)
    {
        return this->operator ==(r) || this->operator >(r);
    }
    inline bool operator<=(const stHsb& r)
    {
        return this->operator ==(r) || this->operator <(r);
    }
};

extern stHsb c_ZeroHSB;

void hsbColor565(WORD* clr, int hValue, int sValue, int bValue);
void hsbColor4444(WORD* clr, int hValue, int sValue, int bValue);
void hsbColor8888(DWORD* clr, int hValue, int sValue, int bValue);



#endif