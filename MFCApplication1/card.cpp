#include "stdafx.h"
#include "card.h"


card::card(CString str)
{
	CardImage.Load(str);
}


void card::SetSize(int x, int y)
{
	Width = CardImage.GetWidth() / 2;
	Height = CardImage.GetHeight() / 2;
	size.SetRect(x, y, x + Width, y + Height);
	
}

void card::Draw(CPaintDC dc)
{
	CardImage.StretchBlt(dc, size.left, size.top, Width, Height);
}

card::~card()
{
}
