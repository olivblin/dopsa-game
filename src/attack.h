#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace sf;

class attack
{
private:

	Sprite bull;
	//Texture* bull_t;
	Vector2f dir; //derection))
	float bullet_speed;

public:
	attack(); //constructor!!!

	attack(Texture* bull_t, float pX, float pY, float dirX, float dirY, float  bullet_speed);
	virtual ~attack();

	const FloatRect getBounds() const;

	void upd_bull();
	void render_bull(RenderTarget* target);
};

