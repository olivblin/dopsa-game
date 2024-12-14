#pragma once
#include "attack.h"
using namespace sf;

class player
{
private:
	Sprite korobka_s;
	Texture korobka_t;

	float spid; //movement speed
	float hpMAX;
	float hpp;
	int ATT; //uron (damage)

	float KD; //cool down
	float KDmax;

	//fun
	void initVariables();
	void initTextr();
	void initSpr();

public:
	player();
	virtual ~player();

	const Vector2f& getPos() const;
	FloatRect getBounds() const;
	void setPosition(const Vector2f pos);
	void setPosition(const float x, const float y);
	const float getHP() const;
	const float getHPMAX() const;
	void setHP(const float HP);
	void loseHP(const float value);
	int DAMAGE();
	void increaseSPID();
	void increaseATT();

	//fun
	void movin_p(const float dirX, const float dirY);
	const bool ableATT();

	void upd_KD();

	void upd_p();
	void ren_p(sf::RenderTarget& target);
};
