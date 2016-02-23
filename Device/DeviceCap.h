#ifndef DEVICE_CAP_H_H
#define DEVICE_CAP_H_H

class CDeviceCap
{
public:
    CDeviceCap();
    virtual ~CDeviceCap();
    
    static CDeviceCap& Instance();

    void doSomething();

private:
};


#endif