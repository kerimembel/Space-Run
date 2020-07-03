//-----------------------------------------------------------------
// Background Object
// C++ Source - Background.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Background.h"

//-----------------------------------------------------------------
// Background Constructor(s)/Destructor
//-----------------------------------------------------------------
Background::Background(int iWidth, int iHeight, COLORREF crColor)
{
	// Initialize the member variables
	m_iWidth = iWidth;
	m_iHeight = iHeight;
	m_crColor = crColor;
	m_pBitmap = NULL;
}

Background::Background(Bitmap* pBitmap)
{
	// Initialize the member variables
	m_crColor = 0;
	m_pBitmap = pBitmap;
	m_iWidth = pBitmap->GetWidth();
	m_iHeight = pBitmap->GetHeight();
}

Background::~Background()
{
}

//-----------------------------------------------------------------
// Background General Methods
//-----------------------------------------------------------------
void Background::Update()
{
	m_slide += 4;
	// Do nothing since the basic background is not animated
}

int pmod(int num, int m) {
	int result;
	result = num % m;
	if (result < 0) result += m;
	return result;
}

void Background::Draw(HDC hDC)
{
	// Draw the background
	if (m_pBitmap != NULL) {
		m_pBitmap->Draw(hDC, pmod(-m_slide, 800), 0);
		m_pBitmap->Draw(hDC, pmod(-m_slide, 800) - 800, 0);
	}
	else
	{
		RECT    rect = { 0, 0, m_iWidth, m_iHeight };
		HBRUSH  hBrush = CreateSolidBrush(m_crColor);
		FillRect(hDC, &rect, hBrush);
		DeleteObject(hBrush);
	}
}
