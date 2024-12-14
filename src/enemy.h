#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include<string>
#include<sstream>
#include<map>
#include <chrono>

using namespace sf;

class enemy
{
private:
	unsigned pointCount;
	int type;
	int a_type;

	Texture lection1;
	Texture laba;
	Texture letuchka;
	Texture coffee;
	Texture ChatGPT;
	Sprite shape;
	float spid;
	int hp;
	int hpMAX;
	float damage;
	int points;


	void initShape();
	void initVar();

public:
	enemy(float pX, float pY);
	virtual ~enemy();

	const FloatRect getBounds_e() const;
	const int& getPoints() const;
	float getDamage();

	//fun

	int getType();
	int getHP();
	void eraseHP(int damage);
	void upd_enem();
	void render_enemy(RenderTarget* target);
};

