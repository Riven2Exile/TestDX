
#include "iSprite.h"

struct IDirect3DVertexBuffer9;
struct VertexS;

class CLineSprite
{
public:
	CLineSprite();
	virtual ~CLineSprite();
	void set_line(const int& x1, const int& y1, const int& x2, const int& y2);
	void set_color(const DWORD& c);
	void draw();

private:
	int _x1;
	int _y1;
	int _x2;
	int _y2;
	IDirect3DVertexBuffer9 *m_pVb;

	void *m_pTest; //自定义的顶点结构

	VertexS *m_pSelfVertex; //自定义的顶点结构，放在内存中
};