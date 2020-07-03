//-----------------------------------------------------------------
// Enemy Sprite Object
// C++ Source - EnemySprite.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "EnemySprite.h"
#include <cmath>

#define PI 3.14159265
//-----------------------------------------------------------------
// External Global Variables
//-----------------------------------------------------------------
extern Bitmap* _pBlobboBitmap;
extern Bitmap* _pBMissileBitmap;
extern Bitmap* _pTimmyBitmap;
extern Bitmap* _pTMissileBitmap;
extern int     _iDifficulty;
extern Sprite* _pShipSprite;
//-----------------------------------------------------------------
// EnemySprite Constructor(s)/Destructor
//-----------------------------------------------------------------
EnemySprite::EnemySprite(Bitmap* pBitmap, RECT& rcBounds,
	BOUNDSACTION baBoundsAction) : Sprite(pBitmap, rcBounds,
		baBoundsAction)
{
}

EnemySprite::~EnemySprite()
{
}

//-----------------------------------------------------------------
// EnemySprite General Methods
//-----------------------------------------------------------------
SPRITEACTION EnemySprite::Update()
{
	// Call the base sprite Update() method
	SPRITEACTION saSpriteAction;
	saSpriteAction = Sprite::Update();

	// See if the Enemy should fire a missile
	if ((rand() % 150) == 0)
		saSpriteAction |= SA_ADDSPRITE;

	return saSpriteAction;
}


Sprite* EnemySprite::AddSprite()
{
	// Create a new missile sprite
	RECT    rcBounds = { 7, 7, 800, 500 };
	RECT    rcPos = GetPosition();
	Sprite* pSprite = NULL;
	

	if (GetBitmap() == _pBlobboBitmap)
	{
		// Random missile
		pSprite = new Sprite(_pBMissileBitmap, rcBounds, BA_DIE);
		pSprite->SetVelocity(-8, (rand() % 2 == 0) ? 1 : -1);
	}
	else 
	{
		// Guided missile
		int x_pos = _pShipSprite->GetPosition().right;
		int y_pos = _pShipSprite->GetPosition().top;
		double value ,angle; 
		int speed = 10;
		pSprite = new Sprite(_pTMissileBitmap, rcBounds, BA_DIE);
		if (y_pos < rcPos.top) {	

			value = (rcPos.left - x_pos) / (rcPos.top - y_pos);
			angle = atan(value) * 180 / PI;
			if (sin(angle*PI / 180) < 0 && cos(angle*PI / 180) < 0)
				pSprite->SetVelocity(speed * sin(angle*PI / 180), speed * cos(angle*PI / 180));
			else if (sin(angle*PI / 180) < 0 && cos(angle*PI / 180) > 0)
				pSprite->SetVelocity(speed * sin(angle*PI / 180), -speed * cos(angle*PI / 180));
			else if (sin(angle*PI / 180) > 0 && cos(angle*PI / 180) < 0)
				pSprite->SetVelocity(-speed * sin(angle*PI / 180), speed * cos(angle*PI / 180));
			else
				pSprite->SetVelocity(-speed * sin(angle*PI / 180), -speed * cos(angle*PI / 180));
		}
		else if (y_pos > rcPos.top) {

			value = (rcPos.left - x_pos) / (rcPos.top - y_pos);
			angle = atan(value) * 180 / PI;
			if (sin(angle*PI / 180) < 0 && cos(angle*PI / 180) < 0)
				pSprite->SetVelocity(speed * sin(angle*PI / 180), -speed * cos(angle*PI / 180));
			else if (sin(angle*PI / 180) < 0 && cos(angle*PI / 180) > 0)
				pSprite->SetVelocity(speed * sin(angle*PI / 180), speed * cos(angle*PI / 180));
			else if (sin(angle*PI / 180) > 0 && cos(angle*PI / 180) < 0)
				pSprite->SetVelocity(-speed * sin(angle*PI / 180), -speed * cos(angle*PI / 180));
			else
				pSprite->SetVelocity(-speed * sin(angle*PI / 180), speed * cos(angle*PI / 180));
		}

		else 
			pSprite->SetVelocity(-speed, 0);

		
	}
	
	// Set the missile sprite's position and return it
	pSprite->SetPosition(rcPos.left, rcPos.top + 15);
	return pSprite;
}
