#include "attack.h"

attack::attack() {

}

//ne constructor!!! peregruzka
attack::attack(Texture* bull_t, float pX, float pY, float dirX, float dirY, float  bullet_speed) {
	this->bull.setTexture(*bull_t);
	this->bull.setScale(0.05f, 0.05f);

	this->bull.setPosition(pX, pY);

	this->dir.x = dirX;
	this->dir.y = dirY;
	this->bullet_speed = bullet_speed;
}

attack::~attack() {

}


const FloatRect attack::getBounds() const {
	return this->bull.getGlobalBounds();
}

//fun(

void attack::upd_bull() {
	//moving bullet
	this->bull.move(this->bullet_speed * this->dir);
}

void attack::render_bull(RenderTarget* target) {
	target->draw(this->bull);
}
