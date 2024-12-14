#include "bitard.h"

using namespace sf;

void player::initVariables() {
	this->spid = 10.f;
	this->KDmax = 15.f;
	this->KD = 0.f;
	this->hpMAX = 50.f;
	this->hpp = this->hpMAX;
	this->ATT = 10;
}

void player::initTextr() {
	//zagruzhaem texturu
	if (!(this->korobka_t.loadFromFile("textures/player.jpg"))) {
		std::cout << "player texture err" << "\n";
	}
}

void player::initSpr() {
	this->korobka_s.setTexture(this->korobka_t);
}

player::player()
{
	this->initVariables();
	this->initTextr();
	this->initSpr();
}

player::~player()
{

}


const Vector2f& player::getPos() const {
	return this->korobka_s.getPosition();
}

FloatRect player::getBounds() const {
	return this->korobka_s.getGlobalBounds();
}

void player::setPosition(const Vector2f pos)
{
	this->korobka_s.setPosition(pos);
}

void player::setPosition(const float x, const float y)
{
	this->korobka_s.setPosition(x, y);
}

int player::DAMAGE()
{
	return ATT;
}


//fun
void player::movin_p(const float dirX, const float dirY) {
	this->korobka_s.move(this->spid * dirX, this->spid * dirY);
}

const bool player::ableATT() {

	if (this->KD >= this->KDmax) {
		this->KD = 0.f;
		return true;
	}
	else {
		return false;
	}

}

void player::upd_KD() {
	if (this->KD < this->KDmax) {
		this->KD += 0.5f;
	}
}

void player::upd_p() {
	this->upd_KD();
}

void player::ren_p(RenderTarget& target) {
	target.draw(this->korobka_s);
}
