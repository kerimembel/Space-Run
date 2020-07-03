//-----------------------------------------------------------------
// Space Run Application
// C++ Source - SpaceRun.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "SpaceRun.h"
#include <string> // For string append func.
#include <fstream> // To read and write highscore

//-----------------------------------------------------------------
// Game Engine Functions
//-----------------------------------------------------------------
int bmpCounter = 1;

BOOL GameInitialize(HINSTANCE hInstance)
{
	// Create the game engine
	_pGame = new GameEngine(hInstance, TEXT("Space Run"),
		TEXT("Space Run"), IDI_SPACERUN, IDI_SPACERUN_SM, 800, 500);
	if (_pGame == NULL)
		return FALSE;

	// Set the frame rate
	_pGame->SetFrameRate(25);

	// Store the instance handle
	_hInstance = hInstance;

	return TRUE;
}

void GameStart(HWND hWindow)
{
	// Seed the random number generator
	srand(GetTickCount());

	// Create the offscreen device context and bitmap
	_hOffscreenDC = CreateCompatibleDC(GetDC(hWindow));
	_hOffscreenBitmap = CreateCompatibleBitmap(GetDC(hWindow),
		_pGame->GetWidth(), _pGame->GetHeight());
	SelectObject(_hOffscreenDC, _hOffscreenBitmap);

	// Create and load the bitmaps
	HDC hDC = GetDC(hWindow);
	_pShipBitmap = new Bitmap(hDC, IDB_SHIP, _hInstance);
	_pMeteorBitmap = new Bitmap(hDC, IDB_METEOR, _hInstance);
	_pMeteor2Bitmap = new Bitmap(hDC, IDB_METEOR2, _hInstance);
	_pSmShipBitmap = new Bitmap(hDC, IDB_SMSHIP, _hInstance);
	_pMissileBitmap = new Bitmap(hDC, IDB_MISSILE, _hInstance);
	_pBlobboBitmap = new Bitmap(hDC, IDB_BLOBBO, _hInstance);
	_pBMissileBitmap = new Bitmap(hDC, IDB_BMISSILE, _hInstance);
	_pTimmyBitmap = new Bitmap(hDC, IDB_TIMMY, _hInstance);
	_pTMissileBitmap = new Bitmap(hDC, IDB_TMISSILE, _hInstance);
	_pSmExplosionBitmap = new Bitmap(hDC, IDB_SMEXPLOSION, _hInstance);
	_pLgExplosionBitmap = new Bitmap(hDC, IDB_EXPLOSION, _hInstance);
	_pGameOverBitmap = new Bitmap(hDC, IDB_GAMEOVER, _hInstance);
	_pHearthBitmap = new Bitmap(hDC, IDB_HEARTH, _hInstance);
	_pWall1Bitmap = new Bitmap(hDC, IDB_WALL1, _hInstance);
	_pWall2Bitmap = new Bitmap(hDC, IDB_WALL2, _hInstance);
	_pWall3Bitmap = new Bitmap(hDC, IDB_WALL3, _hInstance);
	_pWall4Bitmap = new Bitmap(hDC, IDB_WALL4, _hInstance);
	_pWall5Bitmap = new Bitmap(hDC, IDB_WALL5, _hInstance);
	_pWall6Bitmap = new Bitmap(hDC, IDB_WALL6, _hInstance);
	_pWall7Bitmap = new Bitmap(hDC, IDB_WALL7, _hInstance);
	_pWall8Bitmap = new Bitmap(hDC, IDB_WALL8, _hInstance);
	_shipexplosionBitmap = new Bitmap(hDC, IDB_SHIPEXPLOSION, _hInstance);
	_pimmunityEffectBitmap = new Bitmap(hDC, IDB_IMMUNITYEFFECT, _hInstance);
	

	_pEnd = new Bitmap(hDC, IDB_END, _hInstance);
	_bEnd = new Bitmap(hDC, IDB_END, _hInstance);

	_pGrenadeBitmap = new Bitmap(hDC, IDB_LASER, _hInstance);
	_pSmGrenadeBitmap = new Bitmap(hDC, IDB_SMGRENADE, _hInstance);
	_pLittleMineBitmap = new Bitmap(hDC, IDB_LITTLEMINE, _hInstance);

	
	_pBackground = new Background(new Bitmap(hDC, IDB_MENU, _hInstance));
	
	// Create the starry background
	_pBackground2 = new Background(new Bitmap(hDC, IDB_BACKGROUND, _hInstance));
	
	// Set the initial cursor essentials
	tx = 250; ty = 250;
	angle = 0;
	right_t = false;
	size_T = 72;


	// Play the background music
	_pGame->PlayMIDISong(TEXT("Music.mid"));

	// Start the game
	NewGame();
}

void GameEnd()
{
	// Close the MIDI player for the background music
	_pGame->CloseMIDIPlayer();

	// Cleanup the offscreen device context and bitmap
	DeleteObject(_hOffscreenBitmap);
	DeleteDC(_hOffscreenDC);

	// Cleanup the bitmaps
	delete _pShipBitmap;
	delete _pSmShipBitmap;
	delete _pMissileBitmap;
	delete _pBlobboBitmap;
	delete _pBMissileBitmap;
	delete _pTimmyBitmap;
	delete _pTMissileBitmap;
	delete _pSmExplosionBitmap;
	delete _pLgExplosionBitmap;
	delete _pGameOverBitmap;
	delete _pimmunityEffectBitmap;
	delete _shipexplosionBitmap;
	delete _pWall1Bitmap;
	delete _pWall2Bitmap;
	delete _pWall3Bitmap;
	delete _pWall4Bitmap;
	delete _pWall5Bitmap;
	delete _pWall6Bitmap;
	delete _pWall7Bitmap;
	delete _pWall8Bitmap;
	delete _pGrenadeBitmap;
	delete _pSmGrenadeBitmap;
	delete _pEnd;
	delete _bEnd;
	delete _pLittleMineBitmap;

	// Cleanup the background
	delete _pBackground;

	// Cleanup the sprites
	_pGame->CleanupSprites();

	// Cleanup the game engine
	delete _pGame;
}

void GameActivate(HWND hWindow)
{
	// Resume the background music
	_pGame->PlayMIDISong(TEXT(""), FALSE);
}

int readHighscore() {
	int score;
	std::fstream f;
	f.open("highestscore.txt", std::fstream::in);
	if (!f)
		score = 0;
	
	f >> score;

	f.close();

	return score;
}
void writeHighScore(int score)
{
	std::fstream f;
	f.open("highestscore.txt", std::fstream::out | std::fstream::trunc);

	f << score;
		
	f.close();
}

void GameDeactivate(HWND hWindow)
{
	// Pause the background music
	_pGame->PauseMIDISong();
}

void GamePaint(HDC hDC)
{
	if (menuControl) {
		_pBackground->Draw(hDC);
	}
	else {
			// Draw the background
		_pBackground->Draw(hDC);

		// Draw the walls
		RECT testPos = _pShipSprite->GetPosition(); //ship position
		temp = 0;							//for wall bmp (1-2-3-4-5-6-7-8)

		for ( i = 0; i < 16; i++)
		{
			for ( j = 0; j < 10; j++)
			{
				if (_wallArray[i][j] != 0) {
					if (bmpCounter < 15) {
						_pWall1Bitmap->Draw(hDC, _wallMapCounter + i * 50, j * 50, TRUE);
					}
					else if (bmpCounter < 30) {
						_pWall2Bitmap->Draw(hDC, _wallMapCounter + i * 50, j * 50, TRUE);
					}
					else if (bmpCounter < 45) {
						_pWall3Bitmap->Draw(hDC, _wallMapCounter + i * 50, j * 50, TRUE);
					}
					else if (bmpCounter < 60) {
						_pWall4Bitmap->Draw(hDC, _wallMapCounter + i * 50, j * 50, TRUE);
					}
					else if (bmpCounter < 75) {
						_pWall5Bitmap->Draw(hDC, _wallMapCounter + i * 50, j * 50, TRUE);
					}
					else if (bmpCounter < 90) {
						_pWall6Bitmap->Draw(hDC, _wallMapCounter + i * 50, j * 50, TRUE);
					}
					else if (bmpCounter < 105) {
						_pWall7Bitmap->Draw(hDC, _wallMapCounter + i * 50, j * 50, TRUE);
					}
					else if (bmpCounter < 120) {
						_pWall8Bitmap->Draw(hDC, _wallMapCounter + i * 50, j * 50, TRUE);
					}
					else if (bmpCounter < 135) {
						_pWall7Bitmap->Draw(hDC, _wallMapCounter + i * 50, j * 50, TRUE);
					}
					else if (bmpCounter < 150) {
						_pWall6Bitmap->Draw(hDC, _wallMapCounter + i * 50, j * 50, TRUE);
					}
					else if (bmpCounter < 165) {
						_pWall5Bitmap->Draw(hDC, _wallMapCounter + i * 50, j * 50, TRUE);
					}
					else if (bmpCounter < 180) {
						_pWall4Bitmap->Draw(hDC, _wallMapCounter + i * 50, j * 50, TRUE);
					}
					else {
						_pWall3Bitmap->Draw(hDC, _wallMapCounter + i * 50, j * 50, TRUE);
					}


					if (_immunityCounter<0 && testPos.right >= _wallMapCounter + i * 50 && testPos.right <= _wallMapCounter + 50 + i * 50) {
						if ((testPos.top >= j * 50 + 5 && testPos.top <= 45 + j * 50) || (testPos.bottom >= j * 50 + 5 && testPos.bottom <= 45 + j * 50)) {
							wallCollision = true;
							if (!wallCollisionSecondControl) {
								wallCollisionPosition = { 0,testPos.top + 8,testPos.right - 12 , 0 };
								wallCollisionSecondControl = true;
							}
						}
					}
					if (_immunityCounter < 0 && testPos.left >= _wallMapCounter + i * 50 && testPos.left <= _wallMapCounter + 50 + i * 50 && _pShipSprite->GetVelocity().x < 0) {
						if ((testPos.top >= j * 50 + 5 && testPos.top <= 45 + j * 50) || (testPos.bottom >= j * 50 + 5 && testPos.bottom <= 45 + j * 50)) {

							wallCollision = true;
							if (!wallCollisionSecondControl) {
								wallCollisionPosition = { 0,testPos.top + 8,testPos.left - 12 , 0 };
								wallCollisionSecondControl = true;
							}
						}
					}
					if (_immunityCounter < 0 && testPos.top >= j * 50 && testPos.top <= 50 + j * 50) {
						if ((testPos.right >= _wallMapCounter + i * 50 + 5 && testPos.right <= _wallMapCounter + 45 + i * 50) || (testPos.left >= _wallMapCounter + i * 50 + 5 && testPos.left <= _wallMapCounter + 45 + i * 50)) {

							wallCollision = true;
							if (!wallCollisionSecondControl) {
								wallCollisionPosition = { 0,testPos.top - 10,testPos.right - 28 , 0 };
								wallCollisionSecondControl = true;
							}
						}

					}
					if (_immunityCounter < 0 && testPos.bottom >= j * 50 && testPos.bottom <= 50 + j * 50) {
						if ((testPos.right >= _wallMapCounter + i * 50 + 5 && testPos.right <= _wallMapCounter + 45 + i * 50) || (testPos.left >= _wallMapCounter + i * 50 + 5 && testPos.left <= _wallMapCounter + 45 + i * 50)) {

							wallCollision = true;
							if (!wallCollisionSecondControl) {
								wallCollisionPosition = { 0,testPos.bottom - 10,testPos.right - 28 , 0 };
								wallCollisionSecondControl = true;
							}
						}
					}
				}
			}
		}
		bmpCounter++;
		bmpCounter = bmpCounter % 196;

		// draw  immunity effect
		if (_immunityCounter >= 0) {
			_pimmunityEffectBitmap->Draw(hDC, _pShipSprite->GetPosition().left, _pShipSprite->GetPosition().top, TRUE);
		}
		// Draw the sprites
		_pGame->DrawSprites(hDC);

	

		// Draw the score
		TCHAR szText[64];
		RECT  rect = { 300, 0, 400, 40 };
		wsprintf(szText, "Score : %d", realScore);
		SetBkMode(hDC, TRANSPARENT);
		SetTextColor(hDC, RGB(255, 255, 255));
		DrawText(hDC, szText, -1, &rect, DT_SINGLELINE | DT_RIGHT | DT_VCENTER);

		// Draw the number of remaining lives (ships)
		for ( i = 0; i < _iNumLives; i++)
			_pSmShipBitmap->Draw(hDC, 490 + (_pSmShipBitmap->GetWidth() * i),
				10, TRUE);
		

		// Draw the game over message, if necessary
		if (_bGameOver) {
			_pGameOverBitmap->Draw(hDC, 260, 140, TRUE);
			
			TCHAR goText[64];
			RECT goRect = { 290, 300, 450, 350 };
			wsprintf(goText, "YOUR SCORE WAS : %d", realScore);
			SetBkMode(hDC, TRANSPARENT);
			SetTextColor(hDC, RGB(255, 192, 0));
			DrawText(hDC, goText, -1, &goRect, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
			goRect = { 290, 330, 490, 360 };
			wsprintf(goText, "HIGHEST SCORE WAS : %d", HighestScore);
			DrawText(hDC, goText, -1, &goRect, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
			goRect = { 290, 350, 490, 380 };
			wsprintf(goText, "PRESS ENTER TO RESTART!");
			DrawText(hDC, goText, -1, &goRect, DT_SINGLELINE | DT_LEFT | DT_VCENTER);

			if (realScore > HighestScore) {
				SetTextColor(hDC, RGB(286, 192, 69));
				goRect = { 310, 100, 520, 130 };
				wsprintf(goText, "NEW HIGHEST SCORE!!");
				DrawText(hDC, goText, -1, &goRect, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
				writeHighScore(realScore);
			}

		}

		// Draw the laser grenades
		for ( i = 0; i < _NumOfGrenades; i++)
			_pSmGrenadeBitmap->Draw(hDC, 0 + (_pSmGrenadeBitmap->GetWidth() * i),
				10, TRUE);
		// ***********************************

		cursor.x = tx + (size_T / 2);
		if (right_t) {
			cursor.y = (LONG)min((ty + 50), (ty - angle));
		}
		else {
			cursor.y = (LONG)max((ty - 50), (ty - angle));
		}

		//Draw angles of Bubble Gun
		if (GetAsyncKeyState(0x54) < 0 || GetAsyncKeyState(0x47) < 0) {

			HPEN pen1 = (HPEN)CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
			HBRUSH brush1 = (HBRUSH)CreateSolidBrush(RGB(64, 64, 255));
			SelectObject(hDC, pen1);
			SelectObject(hDC, brush1);

			MoveToEx(hDC, tx, ty, NULL);
			LineTo(hDC, cursor.x, cursor.y);
		}

	}
	
}

void GameCycle()
{
	if (!menuControl) {
		_NumOfGrenades = (_iScore / 100);
		RECT  rcPos = _pShipSprite->GetPosition();
		tx = rcPos.right - 13;
		ty = rcPos.top + 19;
		if (_iScore < 0) { _iScore = 0; };

		if (!_bGameOver)
		{
			// Randomly add aliens
			if ((rand() % _iDifficulty) == 0) {
				AddEnemy();
				//Send Health if not full 
				if (_iNumLives < MAX_HEALTH && rand() % 2 == 0)
					SendHeart();
			}

			// Update the background
			_pBackground->Update();

			//Add wall
			AddWall();

			// Update the sprites
			_pGame->UpdateSprites(_wallArray, _wallMapCounter, _pBlobboBitmap, _pTimmyBitmap);

			// Obtain a device context for repainting the game
			HWND  hWindow = _pGame->GetWindow();
			HDC   hDC = GetDC(hWindow);

			//Collision control (space ship -- wall)
			if (wallCollision && _immunityCounter<0) {

				// Move the ship back to the start
				_pShipSprite->SetPosition(30, 250);
				_immunityCounter = 200;
				// See if the game is over
				if (--_iNumLives == 0)
				{
					// Play the game over sound
					_pGame->PauseMIDISong();

					PlaySound((LPCSTR)IDW_GAMEOVER, _hInstance, SND_ASYNC |
						SND_RESOURCE);
					_bGameOver = TRUE;
					_pGame->CloseMIDIPlayer();

				}
				_shipexplosionBitmap->Draw(hDC, wallCollisionPosition.right, wallCollisionPosition.top, TRUE);
				wallCollision = false;
				wallCollisionSecondControl = false;
				Sleep(100);
			}

			// Paint the game to the offscreen device context
			GamePaint(_hOffscreenDC);

			// Blit the offscreen bitmap to the game screen
			BitBlt(hDC, 0, 0, _pGame->GetWidth(), _pGame->GetHeight(),
				_hOffscreenDC, 0, 0, SRCCOPY);

			// Cleanup
			ReleaseDC(hWindow, hDC);
		}
	}
}

void HandleKeys()
{
	if (!_bGameOver)
	{
		// Move the ship based upon left/right key presses
		POINT ptVelocity = _pShipSprite->GetVelocity();
		Sprite* temp = _pShipSprite;

		if (GetAsyncKeyState(VK_UP) < 0 || GetAsyncKeyState(0x57) < 0)
		{
			// Move up
			ptVelocity.y = max(ptVelocity.y - speedFactor, -6);
			_pShipSprite->SetVelocity(ptVelocity);
		}
		else if (GetAsyncKeyState(VK_DOWN) < 0 || GetAsyncKeyState(0x53) < 0)
		{
			// Move down
			ptVelocity.y = min(ptVelocity.y + speedFactor, 6);
			_pShipSprite->SetVelocity(ptVelocity);
		}
		else if (GetAsyncKeyState(VK_RIGHT) < 0 || GetAsyncKeyState(0x44) < 0)
		{
			// Move right
			ptVelocity.x = min(ptVelocity.x + speedFactor, 6);
			_pShipSprite->SetVelocity(ptVelocity);
		}
		else if (GetAsyncKeyState(VK_LEFT) < 0 || GetAsyncKeyState(0x41) < 0)
		{
			// Move left
			ptVelocity.x = max(ptVelocity.x - speedFactor, -6);
			_pShipSprite->SetVelocity(ptVelocity);
		}
		else
			_pShipSprite->SetVelocity(0, 0);
		
		// T
		if (GetAsyncKeyState(0x54) < 0 )
		{
			// Angle Left
			angle += 5;
			if (angle >= 50) angle = 50;
			right_t = false;
		}
		// G
		else if (GetAsyncKeyState(0x47) < 0  )
		{
			// Angle Right
			angle -= 5;
			if (angle <= -50) angle = -50;
			right_t = true;
		}
				

		// Fire missiles based upon spacebar presses
		if ((++_iFireInputDelay > 30  ) && GetAsyncKeyState(VK_SPACE) < 0)
		{
			// Create a new missile sprite
			RECT  rcBounds = { 2, 2, 800, 500 };
			RECT  rcPos = _pShipSprite->GetPosition();
			Sprite* pSprite = new Sprite(_pMissileBitmap, rcBounds, BA_DIE);
			pSprite->SetPosition(rcPos.right - 13, rcPos.top + 19);
			pSprite->SetVelocity(8, 0);
			_pGame->AddSprite(pSprite);

			// Play the missile (fire) sound
			/* PlaySound((LPCSTR)IDW_MISSILE, _hInstance, SND_ASYNC |
				SND_RESOURCE | SND_NOSTOP);
				*/
			// Reset the input delay
			_iFireInputDelay = 0;
		}
		// Fire grenade based upon G key presses
		else if ((++_iFireInputDelay > fireDispatcher) && GetAsyncKeyState('H') < 0 && _iScore >= 100) {
			fireDispatcher = 100;
			_iScore = _iScore - 100;

			_NumOfGrenades--;
			// Rect(int left, int top, int right, int bottom);
			// Create a new grenade sprite		
			RECT  rcPos = _pShipSprite->GetPosition();		
			RECT  rcBounds = { 2, 2, rcPos.right + 400 , 500 };
			Sprite* pSprite = new Sprite(_pGrenadeBitmap, rcBounds, BA_DIE);
			pSprite->SetPosition(rcPos.right + 5, rcPos.top - 110);
			pSprite->SetNumFrames(1);
			pSprite->SetVelocity(4, 0);
			_pGame->AddSprite(pSprite);
			// Play the missile (fire) sound
			PlaySound((LPCSTR)IDW_LASER, _hInstance, SND_ASYNC |
				SND_RESOURCE | SND_NOSTOP);

			// Reset the input delay
			_iFireInputDelay = 0;
		}
		// Bouncing shot upon Y key pressed
		else if ((++_iFireInputDelay > 70) && GetAsyncKeyState('Y') < 0 && _iScore >= 50) {
			_iScore = _iScore - 50;
			RECT  rcBounds = { 2, 2, 800, 500 };
			RECT  rcPos = _pShipSprite->GetPosition();
			Sprite* pSprite = new Sprite(_pLittleMineBitmap, rcBounds, BA_BOUNCE);
			pSprite->SetPosition(rcPos.right - 13, rcPos.top + 19);
			pSprite->SetVelocity((cursor.x - tx) / 5, (cursor.y - ty) / 5); /*/*/
			_pGame->AddSprite(pSprite);
			// Play the missile (fire) sound
			PlaySound((LPCSTR)IDW_MISSILE, _hInstance, SND_ASYNC |
				SND_RESOURCE | SND_NOSTOP);

			// Reset the input delay
			_iFireInputDelay = 0;
		}
	}

	// Start a new game based upon an Enter (Return) key press
	if (_bGameOver && (GetAsyncKeyState(VK_RETURN) < 0))
		// Start a new game
		NewGame();
}

void MouseButtonDown(int x, int y, BOOL bLeft)
{
	if (menuControl && x>=296 && x <=504 && y>=260 && y<=290) {
		menuControl = false;
		delete _pBackground;
		// Create the background
		_pBackground = _pBackground2;
	
	}
}

void MouseButtonUp(int x, int y, BOOL bLeft)
{
}

void MouseMove(int x, int y)
{
}

void HandleJoystick(JOYSTATE jsJoystickState)
{
}

BOOL SpriteCollision(Sprite* pSpriteHitter, Sprite* pSpriteHittee)
{
	
	// See if a player missile and an alien have collided
	Bitmap* pHitter = pSpriteHitter->GetBitmap();
	Bitmap* pHittee = pSpriteHittee->GetBitmap();

	//Collision with hearth. 
	if ((_iNumLives != MAX_HEALTH && pHittee == _pShipBitmap && pHitter == _pHearthBitmap)) {
		
		//If collided increase number of lives
		_iNumLives++;
		// Kill the hearth sprite
		if (pHitter == _pShipBitmap)
			pSpriteHittee->Kill();
		else
			pSpriteHitter->Kill();
	}

	// Mine hits end
	if (pHitter == _pLittleMineBitmap && pHittee == _pEnd) {
		pSpriteHitter->Kill();
	}
	else if (pHittee == _pLittleMineBitmap && pHitter == _pEnd) {
		pSpriteHittee->Kill();
	}
	else if (pHitter == _bEnd && pHittee == _pBlobboBitmap) {
		pSpriteHittee->Kill();
	}
	else if (pHittee == _bEnd && pHitter == _pBlobboBitmap) {
		pSpriteHitter->Kill();
	}
	else if ((pHitter == _pGrenadeBitmap && (pHittee == _pBlobboBitmap || pHittee == _pTimmyBitmap || pHittee == _pBMissileBitmap || pHittee == _pTMissileBitmap)) ) {
		// Play the small explosion sound
		PlaySound((LPCSTR)IDW_LASERHIT, _hInstance, SND_ASYNC |
			SND_RESOURCE);

		// Kill all hitters except granade 
		if (pHittee == _pGrenadeBitmap)
			pSpriteHitter->Kill();
		else {
			pSpriteHittee->Kill();
		}
		// Create a large explosion sprite at the alien's position
		RECT rcBounds = { 0, 0, 800	, 500 };
		RECT rcPos;
		if (pHitter == _pMissileBitmap)
			rcPos = pSpriteHittee->GetPosition();
		else
			rcPos = pSpriteHitter->GetPosition();

		Sprite* pSprite = new Sprite(_pLgExplosionBitmap, rcBounds);
		pSprite->SetNumFrames(7, TRUE);
		pSprite->SetPosition(rcPos.left, rcPos.top);
		_pGame->AddSprite(pSprite);

		_iScore += 15;
		realScore += 15;

	}

	else if ((pHitter == _pLittleMineBitmap && (pHittee == _pBlobboBitmap || pHittee == _pTimmyBitmap))) {

		// Play the small explosion sound
		PlaySound((LPCSTR)IDW_LGEXPLODE, _hInstance, SND_ASYNC |
			SND_RESOURCE);

		// If not meteor or grenade then kill both sprites	
		pSpriteHitter->Kill();
		pSpriteHittee->Kill();
		
		// Create a large explosion sprite at the alien's position
		RECT rcBounds = { 0, 0, 800	, 500 };
		RECT rcPos;
		if (pHitter == _pMissileBitmap)
			rcPos = pSpriteHittee->GetPosition();
		else
			rcPos = pSpriteHitter->GetPosition();

		Sprite* pSprite = new Sprite(_pLgExplosionBitmap, rcBounds);
		pSprite->SetNumFrames(7, TRUE);
		pSprite->SetPosition(rcPos.left, rcPos.top);
		_pGame->AddSprite(pSprite);
		
		//_iScore += 200;
		realScore += 200;
	}

	else if ((pHitter == _pMissileBitmap && (pHittee == _pBlobboBitmap || pHittee == _pTimmyBitmap || pHittee == _pMeteorBitmap || pHittee == _pMeteor2Bitmap)))
	{
		// Play the small explosion sound
		PlaySound((LPCSTR)IDW_LGEXPLODE, _hInstance, SND_ASYNC |
			SND_RESOURCE);

		// If not meteor or grenade then kill both sprites
		if(pHittee == _pMeteorBitmap || pHittee == _pMeteor2Bitmap)
			pSpriteHitter->Kill();
		else {
			pSpriteHitter->Kill();
			pSpriteHittee->Kill();
		}

		// Create a large explosion sprite at the alien's position
		RECT rcBounds = { 0, 0, 800	, 500 };
		RECT rcPos;
		if (pHitter == _pMissileBitmap)
			rcPos = pSpriteHittee->GetPosition();
		else
			rcPos = pSpriteHitter->GetPosition();

		Sprite* pSprite = new Sprite(_pLgExplosionBitmap, rcBounds);
		pSprite->SetNumFrames(7,TRUE);
		pSprite->SetPosition(rcPos.left, rcPos.top);
		_pGame->AddSprite(pSprite);


		_iScore += 25;
		realScore += 25;
		
	}
		
	_iDifficulty = max(80 - (realScore / 40), 30);


	// See if an enemy missile or meteor has collided with the ship
	if (_immunityCounter < 0 && ((pHitter == _pShipBitmap &&  (pHittee == _pBMissileBitmap ||
		 pHittee == _pTMissileBitmap || pHittee == _pMeteorBitmap || pHittee == _pMeteor2Bitmap || pHittee == _pBlobboBitmap))))
	{
		// Play the large explosion sound
		PlaySound((LPCSTR)IDW_LGEXPLODE, _hInstance, SND_ASYNC |
			SND_RESOURCE);

		// Kill the missile sprite
		if (pHitter == _pShipBitmap)
			pSpriteHittee->Kill();
		else
			pSpriteHitter->Kill();

		// Create a large explosion sprite at the ship's position
		RECT rcBounds = { 0, 0, 800, 500 };
		RECT rcPos;
		if (pHitter == _pShipBitmap)
			rcPos = pSpriteHitter->GetPosition();
		else
			rcPos = pSpriteHittee->GetPosition();

		Sprite* pSprite = new Sprite(_pLgExplosionBitmap, rcBounds);
		pSprite->SetNumFrames(7, TRUE);
		pSprite->SetPosition(rcPos.right, rcPos.top);
		_pGame->AddSprite(pSprite);

		// Move the ship back to the start
		_pShipSprite->SetPosition(30, 250);
		_immunityCounter = 200; 
		// See if the game is over
		if (--_iNumLives == 0)
		{
			// Play the game over sound
			_pGame->PauseMIDISong();

			PlaySound((LPCSTR)IDW_GAMEOVER, _hInstance, SND_ASYNC |
				SND_RESOURCE);
			_bGameOver = TRUE;

		}
	}

	return FALSE;
}

void SpriteDying(Sprite* pSprite)
{
	// See if an alien missile sprite is dying
	if (pSprite->GetBitmap() == _pBMissileBitmap ||
		pSprite->GetBitmap() == _pTMissileBitmap)
	{
		// Play the small explosion sound
		PlaySound((LPCSTR)IDW_SMEXPLODE, _hInstance, SND_ASYNC |
			SND_RESOURCE | SND_NOSTOP);

		// Create a small explosion sprite at the missile's position
		RECT rcBounds = { 0, 0, 800, 500 };
		RECT rcPos = pSprite->GetPosition();
		Sprite* pSprite = new Sprite(_pSmExplosionBitmap, rcBounds);
		pSprite->SetNumFrames(8, TRUE);
		pSprite->SetPosition(rcPos.left, rcPos.top);
		_pGame->AddSprite(pSprite);
	}
}

//-----------------------------------------------------------------
// Functions
//-----------------------------------------------------------------
void NewGame()
{
	HighestScore = readHighscore();

	//clear wall
	for ( i = 0; i < 16; i++)
	{
		for ( j = 0; j < 10; j++)
		{
			_wallArray[i][j] = 0;
		}
	}
	_wallMapCounter = 800;

	_immunityCounter = 200; //immunity  (during 200 px)
	// Clear the sprites
	_pGame->CleanupSprites();

	// Create the ship sprite
	RECT rcBounds = { 0, 0, 350, 490 };
	_pShipSprite = new Sprite(_pShipBitmap, rcBounds, BA_STOP);
	_pShipSprite->SetPosition(30, 250);
	_pShipSprite->SetNumFrames(4);
	_pGame->AddSprite(_pShipSprite);

	// Blobbo Ending collision
	rcBounds = { 0, 0, 800, 500 };
	Sprite* pSpriteK = new Sprite(_bEnd, rcBounds, BA_STOP);
	pSpriteK->SetPosition(10, 0);
	pSpriteK->SetVelocity(0, 0);
	_pGame->AddSprite(pSpriteK);

	// Ending collision
	rcBounds = { 0, 0, 800, 500 };
	pSpriteK = new Sprite(_pEnd, rcBounds, BA_STOP);
	pSpriteK->SetPosition(780, 0);
	pSpriteK->SetVelocity(0, 0);
	_pGame->AddSprite(pSpriteK);

	// Initialize the game variables
	_iFireInputDelay = 0;
	_iScore = 0;
	realScore = 0;
	_iNumLives = MAX_HEALTH;
	_iDifficulty = 80;
	_bGameOver = FALSE;

	// Play the background music
	//_pGame->PlayMIDISong();
}
void SendHeart() {

	// Create extra health for ship
	RECT          rcBounds = { 0, 0, 800, 500 };
	Sprite*  pSprite = NULL;

	pSprite = new Sprite(_pHearthBitmap, rcBounds, BA_DIE);
	pSprite->SetNumFrames(4);
	pSprite->SetPosition(800, (rand() % 500));
	pSprite->SetVelocity(-8, 0);
	_pGame->AddSprite(pSprite);

}

void AddEnemy()	
{
	// Create a new random alien sprite
	RECT          rcBounds = { 400, 0, 800, 500 };
	Sprite*  pSprite = NULL;
	//rand() % 3
	switch (rand() % 3)
	{
	case 0:
		// Blobbo
		rcBounds = { 0, 0, 800, 500 };
		pSprite = new EnemySprite(_pBlobboBitmap, rcBounds, BA_BOUNCE);
		pSprite->SetNumFrames(4);
		pSprite->SetPosition(800, (rand() % 500));
		pSprite->SetVelocity(-((rand() % 7) + 2), -((rand() % 7) + 1));
		break;
	case 1:
		// Meteor
		rcBounds = { 0, 0, 800, 500 };

		if (rand() % 2 == 0) {
			pSprite = new Sprite(_pMeteor2Bitmap, rcBounds, BA_DIE);
			pSprite->SetNumFrames(8);
			pSprite->SetPosition(800, _pShipSprite->GetPosition().top);
			pSprite->SetVelocity(-8, 0);
		}
		else {

			pSprite = new Sprite(_pMeteorBitmap, rcBounds, BA_DIE);
			pSprite->SetNumFrames(4);
			pSprite->SetPosition((rand() % 400) + 400, 0);
			pSprite->SetVelocity(-7, 3);
		}
		break;
	case 2:
		// Timmy
		pSprite = new EnemySprite(_pTimmyBitmap, rcBounds, BA_BOUNCE);
		pSprite->SetNumFrames(4);
		pSprite->SetPosition(800, (rand() % 500));
		pSprite->SetVelocity(-((rand() % 7) + 3), -((rand() % 7)));
		break;
	}

	// Add the alien sprite
	_pGame->AddSprite(pSprite);
}


SpaceRun::SpaceRun()
{
}


SpaceRun::~SpaceRun()
{
}

void AddWall() {

	//clear wall array 
	if (_wallMapCounter < -800) {
		for ( i = 0; i < 16; i++)
		{
			for ( j = 0; j < 10; j++)
			{
				_wallArray[i][j] = 0;
			}
		}
		_wallMapCounter = 800;
		
		int random = rand() % 6;
		if (random == 0) {
			_wallArray[0][0] = 1;
			_wallArray[1][0] = 1;
			_wallArray[2][0] = 1;
			_wallArray[3][0] = 1;
			_wallArray[4][0] = 1;
			_wallArray[5][0] = 1;
			_wallArray[6][0] = 1;

			_wallArray[1][1] = 1;
			_wallArray[2][1] = 1;
			_wallArray[3][1] = 1;
			_wallArray[4][1] = 1;
			_wallArray[5][1] = 1;

			_wallArray[2][2] = 1;
			_wallArray[3][2] = 1;
			_wallArray[4][2] = 1;

			_wallArray[3][3] = 1;

			_wallArray[5][9] = 1;
			_wallArray[6][9] = 1;
			_wallArray[7][9] = 1;
			_wallArray[8][9] = 1;
			_wallArray[9][9] = 1;
			_wallArray[10][9] = 1;
			_wallArray[11][9] = 1;

			_wallArray[6][8] = 1;
			_wallArray[7][8] = 1;
			_wallArray[8][8] = 1;
			_wallArray[9][8] = 1;
			_wallArray[10][8] = 1;

			_wallArray[7][7] = 1;
			_wallArray[8][7] = 1;
			_wallArray[9][7] = 1;

			_wallArray[8][6] = 1;
		}
		else if (random == 1) {
			_wallArray[4][3] = 1;
			_wallArray[4][4] = 1;
			_wallArray[4][5] = 1;
			_wallArray[4][6] = 1;

			_wallArray[5][3] = 1;
			_wallArray[5][4] = 1;
			_wallArray[5][5] = 1;
			_wallArray[5][6] = 1;


			_wallArray[15][0] = 1;
			_wallArray[15][1] = 1;
			_wallArray[15][2] = 1;
			_wallArray[15][3] = 1;

			_wallArray[14][0] = 1;
			_wallArray[14][1] = 1;
			_wallArray[14][2] = 1;

			_wallArray[13][0] = 1;
			_wallArray[13][1] = 1;

			_wallArray[12][0] = 1;

		}
		else if (random == 2) {

			_wallArray[0][0] = 1;
			_wallArray[1][0] = 1;
			_wallArray[2][0] = 1;

			_wallArray[0][1] = 1;
			_wallArray[1][1] = 1;

			_wallArray[0][2] = 1;



			_wallArray[7][7] = 1;
			_wallArray[7][8] = 1;
			_wallArray[7][9] = 1;

			_wallArray[6][8] = 1;
			_wallArray[6][9] = 1;

			_wallArray[5][9] = 1;


			_wallArray[15][0] = 1;
			_wallArray[15][1] = 1;
			_wallArray[15][2] = 1;

			_wallArray[14][0] = 1;
			_wallArray[14][1] = 1;

			_wallArray[13][0] = 1;

		}
		else if (random == 3) {




			_wallArray[1][3] = 1;

			_wallArray[2][2] = 1;
			_wallArray[2][3] = 1;
			_wallArray[2][4] = 1;

			_wallArray[3][3] = 1;





			_wallArray[11][6] = 1;

			_wallArray[12][5] = 1;
			_wallArray[12][6] = 1;
			_wallArray[12][7] = 1;

			_wallArray[13][6] = 1;


		}
		else if (random == 4) {
			_wallArray[0][0] = 1;
			_wallArray[1][0] = 1;
			_wallArray[2][0] = 1;
			_wallArray[3][0] = 1;
			_wallArray[4][0] = 1;


			_wallArray[15][1] = 1;
			_wallArray[15][2] = 1;
			_wallArray[15][7] = 1;
			_wallArray[15][8] = 1;
			_wallArray[14][1] = 1;
			_wallArray[14][2] = 1;
			_wallArray[14][7] = 1;
			_wallArray[14][8] = 1;

			_wallArray[0][9] = 1;
			_wallArray[1][9] = 1;
			_wallArray[2][9] = 1;
			_wallArray[3][9] = 1;
			_wallArray[4][9] = 1;


		}
		else if (random == 5) {

		for ( i = 0; i < 15; i++)
		{
			_wallArray[i][0] = 1;
			//_wallArray[i][1] = 1;

			//_wallArray[i][8] = 1;
			_wallArray[i][9] = 1;

		}
		_wallArray[1][1] = 1;
		_wallArray[2][1] = 1;
		_wallArray[3][1] = 1;
		_wallArray[2][2] = 1;

		_wallArray[8][1] = 1;
		_wallArray[9][1] = 1;
		_wallArray[10][1] = 1;
		_wallArray[9][2] = 1;

		_wallArray[4][8] = 1;
		_wallArray[5][8] = 1;
		_wallArray[6][8] = 1;
		_wallArray[5][7] = 1;

		_wallArray[12][8] = 1;
		_wallArray[13][8] = 1;
		_wallArray[14][8] = 1;
		_wallArray[13][7] = 1;

		}
	}
	_wallMapCounter = _wallMapCounter - 4;
	_immunityCounter = _immunityCounter - 4;

}