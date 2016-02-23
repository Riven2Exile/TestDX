
#ifndef _MY_CAMERA_H
#define _MY_CAMERA_H

#include <d3dx9math.h>


class CCamera
{
public:
    CCamera();
    virtual ~CCamera();



    void SetLookAt3Vecter(const D3DXVECTOR3& locate, const D3DXVECTOR3& lookAt, const D3DXVECTOR3& up);
    
    void SetLocate(D3DXVECTOR3 locate);

    D3DXVECTOR3 GetLocate();
    D3DXVECTOR3 GetLookAt();
    D3DXVECTOR3 GetUp();
    
    D3DXMATRIXA16 GetLookAtMatrix();

private:
    D3DXVECTOR3 _locate;
    D3DXVECTOR3 _lookAt;
    D3DXVECTOR3 _up;

};

#endif