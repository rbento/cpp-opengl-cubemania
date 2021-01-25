// Copyright (c) Rodrigo Bento. All Rights Reserved.

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include <deque>
#include <vector>
#include <string>

#include <GL/glut.h>

#include "camera.h"
#include "core_component.h"
#include "input_manager.h"
#include "text_manager.h"
#include "sound_manager.h"
#include "logger.h"

#include "skybox.h"
#include "sprite.h"

#include "cannon.h"
#include "shot.h"
#include "bomb.h"
#include "score.h"

#include "music.h"
#include "sound_effect.h"

using namespace math;
using namespace std;

enum GameState { kNone, kMenu, kInfo, kStarting, kPlay, kPaused, kOver, kQuit, kExit };

class GameScene : public CoreComponent
{
private:

	static const int kStartingLives = 3;
	static const int kStartingBombs = 3;
	static const int kMaxLives = 99;
	static const int kMinBombCount = 3;
	static const int kMaxBombCount = 24;
	static const int kMaxEnemies = 3;
	static const int kScoreValue = 10;
	static const int kMinMultiplier = 1;
	static const int kMaxMultiplier = 99;
	static const Uint32 kMultiplierDuration = 8000;

	static const int kMinWaveCount = 3;
	static const int kMaxWaveCount = 99;
	static const int kMaxColors = 7;
	static const int kSpawnPoints = 3;
	static const int kMaxColorIndex = kMaxColors - 1;

	static const float kFixedZPosition;
	static const float kScoreBonus;
	static const float kEnemySpeedIncrement;

	static const int kMaxAnchorRows = 3;
	static const float kAnchorInitialX;
	static const float kAnchorInitialY;
	static const float kAnchorGapY;

	Vector3 mAnchors[kMaxAnchorRows];
	Color mColors[kMaxColors];

	deque<Enemy*> mWave;
	vector<Enemy*> mEnemies;
	vector<Score*> mScores;
	vector<Bomb*> mBombs;

	int mCurrentWaveCount;
	int mCurrentBombCount;

	int mCurrentWave;
	int mLives;
	int mMultiplier;
	int mScore;

	GameState mPreviousState;
	GameState mCurrentState;

	TextManager* mText;
	InputManager* mInput;
	SoundManager* mSound;
	Camera* mCamera;

	Skybox* mSkybox;

	Cannon* mCannon;
	Shot* mShot;

	Sprite* mSprMenu;
	Sprite* mSprInfo;
	Sprite* mSprPaused;
	Sprite* mSprReady;
	Sprite* mSprGameOver;
	Sprite* mSprCursor;

	Music* mBmKosmonauts;
	Music* mBmPantheon;

	SoundEffect* mFxOption;
	SoundEffect* mFxSelect;

	SoundEffect* mFxBombDrop;
	SoundEffect* mFxCannonSpawn;
	SoundEffect* mFxCannonShot;
	SoundEffect* mFxCannonExplosion;
	SoundEffect* mFxLifeGained;
	SoundEffect* mFxMultiplier;
	SoundEffect* mFxEnemySpawn;
	SoundEffect* mFxEnemyHit;
	SoundEffect* mFxWarning;

	GLfloat mCursorPos[3];
	int mCursorIndex;

	Uint32 mNextMultiplierTimeout;
	int mLifeUpCountDown;

	bool mFiring;
	bool mShowDebugInfo;

private:

	void debugInfo(const Time&);

	void setupAnchors();
	void setupColors();

	Vector3* getAnchors();
	Color getColor(int index);

	void createWave();
	Vector3 getRandomAnchor();

	bool isCurrentWaveDefeated();
	void advanceWave();

	void loadBombs(Enemy* _owner, Uint32 _timeout);
	void clearBombs();

	void takeLife();
	void resetShot();

	void resetMultiplier();
	void increaseMultiplier();

	void addScore(int value, float x, float y, Uint32 time);
	int getNextScore();
	void clearScores();

	bool shouldSpawnEnemy();
	void spawnEnemy(const Time& _time);
	void clearEnemies();

	void updateEnemies(const Time& _time);
	void updateBombs(const Time& _time);
	void updateCannon(const Time& _time);
	void updateScores(const Time& _time);
	void updateRules(const Time& _time);
	void updateHud(const Time& _time);

public:

	GameScene();
	~GameScene();

	void changeState(const GameState& newState);

	void reset();
	void restart();

	void initialize();
	void cleanup();

	void loadContent();
	void unloadContent();

	void input();
	void update(const Time&);
};

#endif
