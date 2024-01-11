#pragma once
class card
{

private:
	CImage CardImage;
	CRect size;
	int Width;
	int Height;
public:
	card(CString str);
	void SetSize(int x, int y);
	void Draw(CPaintDC dc);
	inline int GetX() { return size.left; }
	inline int GetY() { return size.top; }
	inline int GetWidth() { return Width; }
	inline int GetHeight() { return Height; }
	inline CImage GetImage() { return CardImage; }
	~card();
};

