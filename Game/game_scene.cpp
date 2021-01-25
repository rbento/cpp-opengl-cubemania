
#include "game_scene.h"

const float GameScene::kFixedZPosition = -110.0f;
const float GameScene::kScoreBonus = 100.0f;
const float GameScene::kEnemySpeedIncrement = 5.0f;
const float GameScene::kAnchorInitialX = -30.0f;
const float GameScene::kAnchorInitialY = 15.0f;
const float GameScene::kAnchorGapY = 10.0f;

GameScene::GameScene() 
{
	setupAnchors();
	setupColors();

	Logger::msg("A GameScene was created.");
}

GameScene::~GameScene()
{
	Logger::msg("A GameScene was created.");
}

void GameScene::initialize() 
{
	mSound = SoundManager::instance();
	mText = TextManager::instance();
	mInput = InputManager::instance();
	mCamera = (Camera*) Entity::findByTag("camera");

	mCamera->transform()->rotation.y -= 90.0f;
	mCamera->speed = 1.0f;

	mShowDebugInfo = false;

	mPreviousState = kNone;
	mCurrentState = kMenu;
}

void GameScene::cleanup() 
{
}

void GameScene::loadContent() 
{
	string paths[1] = {"Resources/Textures/Skybox/"};
	int choice = 0;

	mSkybox = new Skybox(80000.0f, paths[choice]);

	mCannon = new Cannon();
	mShot = new Shot();

	mBmKosmonauts = mSound->loadMusic("Resources/Sounds/soKosmonauts.mp3");
	mBmPantheon = mSound->loadMusic("Resources/Sounds/soPantheon.mp3");

	mFxOption = mSound->loadSoundEffect("Resources/Sounds/seOption.wav");
	mFxSelect = mSound->loadSoundEffect("Resources/Sounds/seSelect.wav");

	mFxBombDrop = mSound->loadSoundEffect("Resources/Sounds/seBombDrop.wav");
	mFxCannonSpawn = mSound->loadSoundEffect("Resources/Sounds/seCannonSpawn.wav");
	mFxCannonShot = mSound->loadSoundEffect("Resources/Sounds/seCannonShot.wav");
	mFxCannonExplosion = mSound->loadSoundEffect("Resources/Sounds/seCannonExplosion.wav");
	mFxLifeGained = mSound->loadSoundEffect("Resources/Sounds/seLifeGained.wav");
	mFxMultiplier = mSound->loadSoundEffect("Resources/Sounds/seMultiplier.wav");
	mFxEnemySpawn = mSound->loadSoundEffect("Resources/Sounds/seEnemySpawn.wav");
	mFxEnemyHit = mSound->loadSoundEffect("Resources/Sounds/seEnemyHit.wav");
	mFxWarning = mSound->loadSoundEffect("Resources/Sounds/seWarning.wav");

	mSprMenu = new Sprite("Resources/Textures/txMenu.png", 512.0f, 512.0f);
	mSprInfo = new Sprite("Resources/Textures/txInfo.png", 512.0f, 512.0f);
	mSprPaused = new Sprite("Resources/Textures/txPaused.png", 512.0f, 512.0f);
	mSprGameOver = new Sprite("Resources/Textures/txGameOver.png", 512.0f, 512.0f);
	mSprReady = new Sprite("Resources/Textures/txReady.png", 512.0f, 512.0f);
	mSprCursor = new Sprite("Resources/Textures/txCursor.png", 16.0f, 16.0f);
}

void GameScene::unloadContent() 
{
	delete mSprCursor;
	delete mSprReady;
	delete mSprGameOver;
	delete mSprPaused;
	delete mSprInfo;
	delete mSprMenu;

	delete mFxBombDrop;
	delete mFxCannonSpawn;
	delete mFxCannonShot;
	delete mFxCannonExplosion;
	delete mFxLifeGained;
	delete mFxMultiplier;
	delete mFxEnemySpawn;
	delete mFxEnemyHit;
	delete mFxWarning;

	delete mFxSelect;
	delete mFxOption;

	delete mBmPantheon;
	delete mBmKosmonauts;

	delete mShot;
	delete mCannon;

	delete mSkybox;
}

void GameScene::reset() 
{
	mSkybox->transform()->rotation.x = -90.0f;

	mCursorIndex = 0;

	mCursorPos[0] = 197.0f;
	mCursorPos[1] = 179.0f;
	mCursorPos[2] = 161.0f;

	mSprMenu->transform()->position.x = 400;
	mSprMenu->transform()->position.y = 300;

	mSprInfo->transform()->position.x = 400;
	mSprInfo->transform()->position.y = 300;
	mSprInfo->hide();

	mSprPaused->transform()->position.x = 400;
	mSprPaused->transform()->position.y = 300;
	mSprPaused->hide();

	mSprGameOver->transform()->position.x = 400;
	mSprGameOver->transform()->position.y = 300;
	mSprGameOver->hide();

	mSprReady->transform()->position.x = 400;
	mSprReady->transform()->position.y = 300;
	mSprReady->hide();

	mSprCursor->transform()->position.x = 208.0f;
	mSprCursor->transform()->position.y = mCursorPos[0];

	mShot->transform()->position.x = 1.5f;
	mShot->transform()->position.y = -21.0f;
	mShot->transform()->position.z = -111.0f;

	mCannon->transform()->position.x = 1.5f;
	mCannon->transform()->position.y = -20.8f;
	mCannon->transform()->position.z = -111.0f;

	mCurrentWaveCount = kMinWaveCount;
	mCurrentBombCount = kMinBombCount;

	mCurrentWave = 0;
	mLives = 2;
	mMultiplier = kMinMultiplier;
	mScore = 0;
	mLifeUpCountDown = 3;

	mFiring = false;

	if (mPreviousState == kNone)
	{
		mBmPantheon->fadeIn(1000);
	}
}

void GameScene::restart() 
{
	for (vector<Bomb*>::iterator it = mBombs.begin(); it != mBombs.end(); ++it)
	{
		(*it)->isDying = true;
	}

	for (vector<Enemy*>::iterator it = mEnemies.begin(); it != mEnemies.end(); ++it)
	{
		(*it)->isDying = true;
	}

	for (deque<Enemy*>::iterator it = mWave.begin(); it != mWave.end(); ++it)
	{
		(*it)->isDying = true;
	}

	reset();
	mBmKosmonauts->fadeIn(3000);
	changeState(kStarting);
}

void GameScene::changeState(const GameState& newState)
{
	mPreviousState = mCurrentState;
	mCurrentState = newState;
}

void GameScene::update(const Time& _time)  
{
	mSkybox->transform()->rotation.z += 0.004f;
	mSkybox->transform()->position = mCamera->transform()->position;

	if (mCurrentState == kPaused) return;

	if (mCurrentState == kOver)
	{
		mSprCursor->show();
		mSprGameOver->show();
		mBmKosmonauts->fadeOut(3000);
	};

	if (mCurrentState == kStarting)
	{
		if (mCamera->transform()->rotation.y <= 0.0f)
		{
			mCamera->turnRight();
			mCamera->moveForward();
		}

		static Uint32 nextStartTimeout = 0;
		if (nextStartTimeout == 0)
		{
			nextStartTimeout = _time.present + 3000;
			mSprReady->show();
		}

		if (_time.present > nextStartTimeout)
		{
			changeState(kPlay);
			nextStartTimeout = 0;
			mNextMultiplierTimeout = _time.present + kMultiplierDuration;
			mBmKosmonauts->fadeIn(1000);
			mSprReady->hide();
		}
	}

	clearEnemies();
	clearBombs();
	clearScores();

	updateEnemies(_time);
	updateBombs(_time);
	updateCannon(_time);
	updateScores(_time);

	updateRules(_time);
	updateHud(_time);

	debugInfo(_time);
}

void GameScene::updateHud(const Time& _time)
{
	if (mCurrentState == kMenu || mCurrentState == kInfo)
	{
		return;
	}

	static Color gray = Color(0.6f, 0.6f, 0.6f, 0.8f);
	static Color orange = Color(1.0f, 0.5f, 0.0f, 0.8f);

	mText->placeAt("life", gray, 20, 586);
	mText->placeAt(to_string((long long)mLives), orange, 50, 586);

	mText->placeAt("wave", gray, 80, 586);
	mText->placeAt(to_string((long long)mCurrentWave), orange, 119, 586);

	mText->placeAt("multiplier", gray, 150, 586);
	mText->placeAt(to_string((long long)mMultiplier), orange, 218, 586);

	mText->placeAt("score", gray, 250, 586);
	mText->placeAt(to_string((long long)mScore), orange, 293, 586);
}

void GameScene::updateRules(const Time& _time)
{
	if (mCurrentState != kPlay)
	{
		return;
	}

	if (isCurrentWaveDefeated())
	{
		advanceWave();
	}

	if (shouldSpawnEnemy())
	{
		spawnEnemy(_time);
	}

	if (_time.present > mNextMultiplierTimeout)
	{
		increaseMultiplier();
		mNextMultiplierTimeout = _time.present + kMultiplierDuration;
	}
}

void GameScene::updateEnemies(const Time& _time)
{
	for (vector<Enemy*>::iterator it = mEnemies.begin(); it != mEnemies.end(); ++it) 
	{
		(*it)->update(_time);
	}
}

void GameScene::updateBombs(const Time& _time)
{
	static bool droppedBombs = false;
	for (vector<Bomb*>::iterator it = mBombs.begin(); it != mBombs.end(); ++it) 
	{
		Bomb* bomb = (*it);
		bomb->update(_time);

		if (!droppedBombs && bomb->isFalling)
		{
			mFxBombDrop->play();
			droppedBombs = true;
		}

		if (mCurrentState == kPlay && !mCannon->wasHit && bomb->getComponent<CollisionComponent>()->collidesWith(*mCannon))
		{
			mCannon->wasHit = true;
			bomb->isDying = true;
			takeLife();
			resetMultiplier();

			if (mLives == 1)
			{
				mFxWarning->play();
			}

			else if (mLives == 0)
			{
				changeState(kOver);
			}
		}
	}
}

void GameScene::updateScores(const Time& _time)
{
	for (vector<Score*>::iterator it = mScores.begin(); it != mScores.end(); ++it) 
	{
		(*it)->update(_time);
	}
}

void GameScene::updateCannon(const Time& _time)
{
	mCannon->update(_time);

	if (mFiring)
	{
		mShot->transform()->position.y += 26.0f * _time.delta;

		if (mShot->transform()->position.y >= 30.0f)
		{
			resetShot();
		}
		else
		{
			for (vector<Enemy*>::iterator it = mEnemies.begin(); it != mEnemies.end(); ++it) 
			{
				Enemy* enemy = (*it);

				if (mShot->getComponent<CollisionComponent>()->collidesWith(*enemy))
				{
					int score = getNextScore();
					Vector2 pos(mCamera->worldToScreen(enemy->transform()->position));
					addScore(score, pos.x, pos.y, _time.present); 
					enemy->isDying = true;
					resetShot();
					mFxEnemyHit->play();
				}
			}
		}
	}
}

void GameScene::resetShot()
{
	mShot->transform()->position.y = -20.5f;
	mShot->transform()->position.x = mCannon->transform()->position.x;
	mFiring = false;
}

void GameScene::debugInfo(const Time& _time)
{
	if (!mShowDebugInfo) 
	{
		return;
	}

	static Color yellow = Color(1.0f, 1.0f, 0.6f, 0.7f);

	mText->placeAt("enemy count: " + to_string((long long) mEnemies.size()), yellow, 20, 560);
	mText->placeAt("wave count: " + to_string((long long) mWave.size()), yellow, 20, 540);
	mText->placeAt("score count: " + to_string((long long) mScores.size()), yellow, 20, 520);
	mText->placeAt("bomb count: " + to_string((long long) mBombs.size()), yellow, 20, 500);
	mText->placeAt("entity count: " + to_string((long long) Entity::count()), yellow, 20, 480);
	mText->placeAt("cannon position: " + mCannon->transform()->position.toString(), yellow, 20, 440);
	mText->placeAt("shot position: " + mShot->transform()->position.toString(), yellow, 20, 420);
	mText->placeAt("time: " + _time.toString(), yellow, 20, 380);
}

void GameScene::input() 
{
	if (mInput->keyPressed(SDLK_F11))
	{
		mShowDebugInfo = !mShowDebugInfo;
	}

	switch(mCurrentState)
	{
	case kMenu :
		{
			if (mInput->keyPressed(SDLK_ESCAPE))
			{
				mInput->pushEvent(SDL_QUIT);
			}

			if (mInput->keyPressed(SDLK_UP) || mInput->keyPressed(SDLK_w))
			{
				mCursorIndex--;
				rotatei(mCursorIndex, 0, 2);
				mSprCursor->transform()->position.y =  mCursorPos[mCursorIndex];
				mFxOption->play();
			}

			if (mInput->keyPressed(SDLK_DOWN) || mInput->keyPressed(SDLK_s))
			{
				mCursorIndex++;
				rotatei(mCursorIndex, 0, 2);
				mSprCursor->transform()->position.y =  mCursorPos[mCursorIndex];
				mFxOption->play();
			}

			if (mInput->keyPressed(SDLK_RETURN))
			{
				switch (mCursorIndex)
				{
				case 0 : 
					{
						mSprMenu->hide();
						mSprCursor->hide();
						mFxSelect->play();
						restart();
						mBmPantheon->fadeOut(1000);
					} break;
				case 1 : 
					{
						mSprMenu->hide();
						mSprInfo->show();
						mFxSelect->play();
						changeState(kInfo);
					} break;
				case 2 : 
					{
						mInput->pushEvent(SDL_QUIT);
					} break;
				}
			}
		}
		break;

	case kInfo:
		{
			if (mInput->keyPressed(SDLK_ESCAPE) || mInput->keyPressed(SDLK_RETURN))
			{
				mSprMenu->show();
				mSprInfo->hide();
				mFxSelect->play();
				changeState(kMenu);
			}
		}
		break;

	case kPlay:
		{

			if (mInput->keyPressed(SDLK_ESCAPE))
			{
				mSprPaused->show();
				mSprCursor->show();
				changeState(kPaused);
			}

			float x = mCannon->transform()->position.x;

			if (mInput->keyHeld(SDLK_LEFT))
			{
				x -= 0.6f;
				clampf(x, -24.0f, 29.0f);
				mCannon->transform()->position.x = x;
			}

			if (mInput->keyHeld(SDLK_RIGHT))
			{
				x += 0.6f;
				clampf(x, -24.0f, 29.5f);
				mCannon->transform()->position.x = x;
			}

			if (mInput->keyPressed(SDLK_SPACE))
			{
				if (!mFiring)
				{
					mFxCannonShot->play();
					mFiring = true;
				}
			}

			if (!mFiring)
			{
				mShot->transform()->position.x = x;				
			}
		}
		break;

	case kPaused:
		{
			if (mInput->keyPressed(SDLK_ESCAPE))
			{
				mCursorIndex = 0;
				mSprCursor->transform()->position.y =  mCursorPos[mCursorIndex];
				mSprCursor->hide();
				mSprPaused->hide();
				changeState(kPlay);
			}

			if (mInput->keyPressed(SDLK_UP))
			{
				mCursorIndex--;
				rotatei(mCursorIndex, 0, 2);
				mSprCursor->transform()->position.y =  mCursorPos[mCursorIndex];
				mFxOption->play();
			}

			if (mInput->keyPressed(SDLK_DOWN))
			{
				mCursorIndex++;
				rotatei(mCursorIndex, 0, 2);
				mSprCursor->transform()->position.y =  mCursorPos[mCursorIndex];
				mFxOption->play();
			}

			if (mInput->keyPressed(SDLK_RETURN))
			{
				switch (mCursorIndex)
				{
				case 0 :
					{
						mSprPaused->hide();
						mSprCursor->hide();
						changeState(kPlay);
					} break;
				case 1 : 
					{
						mSprPaused->hide();
						mSprCursor->hide();
						restart();
					} break;
				case 2 : 
					{
						mCursorIndex = 0;
						mSprCursor->transform()->position.y =  mCursorPos[mCursorIndex];
						mSprPaused->hide();
						mSprMenu->show();
						changeState(kMenu);
						mBmKosmonauts->fadeOut(2000);
						mBmPantheon->fadeIn(3000);
					} break;
				}
			}
		}
		break;

	case kOver:
		{
			if (mInput->keyPressed(SDLK_UP))
			{
				mCursorIndex--;
				rotatei(mCursorIndex, 0, 1);
				mSprCursor->transform()->position.y =  mCursorPos[mCursorIndex];
				mFxOption->play();
			}

			if (mInput->keyPressed(SDLK_DOWN))
			{
				mCursorIndex++;
				rotatei(mCursorIndex, 0, 1);
				mSprCursor->transform()->position.y =  mCursorPos[mCursorIndex];
				mFxOption->play();
			}

			if (mInput->keyPressed(SDLK_RETURN))
			{
				switch (mCursorIndex)
				{
				case 0 :
					{
						mSprGameOver->hide();
						mSprCursor->hide();
						restart();
					} break;
				case 1 : 
					{
						mCursorIndex = 0;
						mSprCursor->transform()->position.y =  mCursorPos[mCursorIndex];
						mSprGameOver->hide();
						mSprMenu->show();
						changeState(kMenu);
						mBmPantheon->fadeIn(2000);
					} break;
				}
			}
		}
		break;
	}
}

void GameScene::setupAnchors()
{
	float x = kAnchorInitialX;
	float y = kAnchorInitialY;
	float z = kFixedZPosition;

	for (int i = 0; i < kMaxAnchorRows; ++i)
	{
		mAnchors[i] = Vector3(x, y, z);
		y -= kAnchorGapY;
	}
}

void GameScene::setupColors()
{
	mColors[0] = Color(1.0f, 1.0f, 1.0f, 1.0f);
	mColors[1] = Color(0.0f, 1.0f, 1.0f, 1.0f);
	mColors[2] = Color(1.0f, 0.0f, 1.0f, 1.0f);
	mColors[3] = Color(0.0f, 0.0f, 1.0f, 1.0f);
	mColors[4] = Color(1.0f, 0.0f, 0.0f, 1.0f);
	mColors[5] = Color(1.0f, 1.0f, 0.0f, 1.0f);
	mColors[6] = Color(0.5f, 1.0f, 0.0f, 1.0f);
}

Vector3 GameScene::getRandomAnchor()
{
	int index = nextRandomIndexBetween(0, kMaxAnchorRows - 1);

	return mAnchors[index];
}

Color GameScene::getColor(int index)
{
	if (index < 0 || index >= kMaxColors)
	{
		return Color(0.0f, 0.0f, 0.0f, 1.0f);
	}

	return mColors[index];
}

void GameScene::createWave()
{
	static float speedFactor[10] = {0.01f, 0.02f, 0.04f, 0.06f, 0.08f, 0.1f, 0.2f, 0.4f, 0.7f, 0.9f};

	for (deque<Enemy*>::iterator it = mWave.begin(); it != mWave.end(); )
	{
		delete (*it);
		it = mWave.erase(it);
	}

	mWave.clear();

	int counter = 0;
	while (counter < mCurrentWaveCount)
	{
		Enemy* enemy = new Enemy();
		enemy->transform()->position = getRandomAnchor();
		int speedIndex = nextInt(0, 9);
		float vspeed = nextFloat(2.0f, 12.0f);
		enemy->speed = vspeed + ((mCurrentWaveCount / 9) + speedFactor[speedIndex]);
		mWave.push_back(enemy);
		counter++;
	}
}

Vector3* GameScene::getAnchors()
{
	return mAnchors;
}

bool GameScene::isCurrentWaveDefeated()
{
	return mEnemies.empty() && mWave.empty();
}

void GameScene::advanceWave()
{
	mLifeUpCountDown--;
	if (mLifeUpCountDown <= 0)
	{
		mLifeUpCountDown = 3;
		mLives++;
		mFxLifeGained->play();
	}

	mCurrentWaveCount++;
	clampi(mCurrentWaveCount, kMinWaveCount, kMaxWaveCount);

	mCurrentBombCount++;
	clampi(mCurrentBombCount, kMinBombCount, kMaxBombCount);

	mCurrentWave++;

	createWave();
}

void GameScene::takeLife()
{
	mLives--;
	clampi(mLives, 0, kMaxLives);
	mFxCannonExplosion->play();
}

void GameScene::increaseMultiplier()
{
	mMultiplier++;
	clampi(mMultiplier, kMinMultiplier, kMaxMultiplier);
	mFxMultiplier->play();
}

void GameScene::resetMultiplier()
{
	mMultiplier = kMinMultiplier;
}

void GameScene::addScore(int _value, float _x, float _y, Uint32 _time)
{
	mScore += _value;
	mScores.push_back(new Score(to_string((long long) _value), _x, _y, _time));
}

void GameScene::clearScores()
{
	for (vector<Score*>::iterator it = mScores.begin(); it != mScores.end();) {
		if ((*it)->done())
			it = mScores.erase(it);
		else
			++it;
	}
}

int GameScene::getNextScore()
{
	return kScoreValue * mMultiplier;
}

bool GameScene::shouldSpawnEnemy()
{
	if(mEnemies.empty())
	{
		return true;
	}

	int ecount = mEnemies.size();

	if (ecount < kMaxEnemies)
	{
		return true;
	}

	for (int i = 0; i < ecount; ++i)
	{
		if (mEnemies[i]->isDead)
		{
			return true;
		}
	}

	return false;
}

void GameScene::clearEnemies()
{
	for (vector<Enemy*>::iterator it = mEnemies.begin(); it != mEnemies.end();) 
	{
		if ((*it)->isDead)
		{
			delete (*it);
			it = mEnemies.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void GameScene::spawnEnemy(const Time& _time)
{
	static Uint32 spawnDelay[10] = {400, 800, 900, 1000, 1200, 1500, 1600, 1700, 1800, 2000};

	if (!mWave.empty())
	{
		Enemy* spawningEnemy = mWave.front();

		int spawnIndex = nextInt(0, 9);
		Uint32 timeout = _time.present + spawnDelay[spawnIndex];

		spawningEnemy->spawnTimeout = timeout;

		if (spawningEnemy->isBomber)
		{
			loadBombs(spawningEnemy, timeout);
		}		

		mEnemies.push_back(spawningEnemy);
		mWave.pop_front();
		mFxEnemySpawn->play();
	}
}

void GameScene::loadBombs(Enemy* _owner, Uint32 _timeout)
{
	static Uint32 deliveryDelay[6] = {1000, 1500, 2000, 3000, 4000, 5000};
	int deliveryIndex = nextInt(0, 5);

	Uint32 timeout = _timeout + deliveryDelay[deliveryIndex];

	int counter = 0;
	while(counter < mCurrentBombCount)
	{
		Bomb* bomb = new Bomb(_owner);
		bomb->setDeliveryTimeout(timeout);
		mBombs.push_back(bomb);
		counter++;
	}
}

void GameScene::clearBombs()
{
	for (vector<Bomb*>::iterator it = mBombs.begin(); it != mBombs.end(); )
	{
		if ((*it)->isDead)
		{
			delete (*it);
			it = mBombs.erase(it);
		}
		else
		{
			it++;
		}
	}
}
