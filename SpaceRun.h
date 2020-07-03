//----------------------------------------
// Space Run Application
// C++ Header - SpaceRun.h
//----------------------------------------

#pragma once

//----------------------------------------
// Include Files
//----------------------------------------
#include <windows.h>
#include "Resource.h"
#include "GameEngine.h"
#include "Bitmap.h"
#include "Sprite.h"
#include "Background.h"
#include "EnemySprite.h"

#define MAX_HEALTH	10
//----------------------------------------
// Global Variables
//----------------------------------------
HINSTANCE         _hInstance;
GameEngine*       _pGame;
HDC               _hOffscreenDC;
HBITMAP           _hOffscreenBitmap;
Bitmap*           _pShipBitmap;
Bitmap*           _pSmShipBitmap;
Bitmap*           _pMissileBitmap;
Bitmap*           _pBlobboBitmap;
Bitmap*           _pBMissileBitmap;
Bitmap*           _pTimmyBitmap;
Bitmap*           _pTMissileBitmap;
Bitmap*           _pSmExplosionBitmap;
Bitmap*           _pLgExplosionBitmap;
Bitmap*           _pGameOverBitmap;
Bitmap*           _pMeteorBitmap;
Bitmap*           _pMeteor2Bitmap;
Bitmap*           _pHearthBitmap;
Bitmap*           _pWall1Bitmap;
Bitmap*           _pWall2Bitmap;
Bitmap*           _pWall3Bitmap;
Bitmap*           _pWall4Bitmap;
Bitmap*           _pWall5Bitmap;
Bitmap*           _pWall6Bitmap;
Bitmap*           _pWall7Bitmap;
Bitmap*           _pWall8Bitmap;
Bitmap*           _pWall9Bitmap;
Bitmap*           _shipexplosionBitmap;
Bitmap*           _pimmunityEffectBitmap;


Bitmap* _pSmGrenadeBitmap;
Bitmap* _pGrenadeBitmap;
Bitmap* _pLittleMineBitmap;
Bitmap* _pEnd;
Bitmap* _bEnd;

POINT			  cursor;
int				  tx, ty;
int				  speed;
int				  size_T;
double		      angle;
bool			  right_t;
double			  pi = 3.14;
int				  _wallArray[16][10];
int				  _wallMapCounter;
int				  _immunityCounter; //active if greater than zero
int				  i, j;				// Loop variables			
int				  temp = 0;			//for wall bmp (1-2-3-4-5-6-7-8)
int fireDispatcher = 15;
BOOL wallCollision = false;
RECT  wallCollisionPosition = { 0, 0, 0, 0 };
BOOL wallCollisionSecondControl = false;
BOOL menuControl = true;
int speedFactor = 2;

Background*		  _pBackground;
Background*		  _pBackground2;
Sprite*           _pShipSprite;
Sprite*           _pMeteorSprite;

int               _iFireInputDelay,HighestScore;
int               _iNumLives, _iScore, _iDifficulty, _NumOfGrenades,realScore;
BOOL              _bGameOver;


//----------------------------------------
// Function Declarations
//----------------------------------------
void NewGame();
void AddEnemy();
void SendHeart();
void AddWall();
int readHighscore();
void writeHighScore(int score);

class SpaceRun
{
public:
	SpaceRun();
	~SpaceRun();
};
