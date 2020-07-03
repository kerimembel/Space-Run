//-----------------------------------------------------------------
// Enemy Sprite Object
// C++ Header - EnemySprite.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <windows.h>
#include "Sprite.h"


//-----------------------------------------------------------------
// EnemySprite Class
//-----------------------------------------------------------------
class EnemySprite : public Sprite
{
public:
	// Constructor(s)/Destructor
	EnemySprite(Bitmap* pBitmap, RECT& rcBounds,
		BOUNDSACTION baBoundsAction = BA_STOP);
	virtual ~EnemySprite();

	// General Methods
	virtual SPRITEACTION  Update();
	virtual Sprite*       AddSprite();
};
