#pragma once
#include "Bitard.h"
#include "attack.h"
#include "enemy.h"
#include<vector>

using namespace sf;


class game
{
private:
	RenderWindow* window;

	std::map<std::string, Texture*> textures;
	std::vector<attack*> bullets;
	//
	bool introduction = false;
	Texture introT;
	Sprite intro;

	Font fontMain;
	Text point_T;

	Texture gameOverT;
	Sprite gameOver;

	//BG
	Texture BGt;
	Sprite BG;

	//stuff
	unsigned points;
	Texture skull;
	Sprite skullD;
	Text skullT;
	Clock deadline;

	player* PLAYER;
	RectangleShape hpBar;
	RectangleShape hbBarBACK;
	//enemy
	float spawn_timer;
	float spawnTmax;
	std::vector<enemy*> enemies;
	enemy* ENEMY;

	//fun)
	void initWin(); //initialize window

	void initTextures();

	void initTextStuff(); //GUi
	void initBG();
	void initSystem();

	void initplayer();
	void initEnemy();

public: //bublic)
	game();
	virtual ~game();


	//fun)
	void run();


	void upd_PollEvents();
	void upd_input();

	void updateTextS();//gui
	//void updateBG();

	void upd_collisions();
	void upd_bullets();
	void upd_enemies();
	void upd_combat();

	void renderIntro();
	void renderTexts();
	void renderBG();

	void upd();
	void ren();

};
