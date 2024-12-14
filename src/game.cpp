#include "game.h"

using namespace sf;

void game::initWin()
{
	this->window = new RenderWindow(VideoMode(800, 600), "Dopsa.exe", Style::Close | Style::Titlebar);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void game::initTextures() {
	this->textures["Bullets"] = new Texture();
	if (!(this->textures["Bullets"]->loadFromFile("textures/bullet.png"))) {
		std::cout << "no bullet texture((" << std::endl;
	}
}

void game::initTextStuff() {
	//intro
	this->introT.loadFromFile("textures/introduction.png");
	this->intro.setTexture(this->introT);

	//loadint text stuff and vsyakie igrovie shtuki(stuff)
	if (!(this->fontMain.loadFromFile("textures/pixel.ttf"))) {
		std::cout << "SRUFTU NE RABOTAYUT!!!";
	}

	this->point_T.setFont(this->fontMain);
	this->point_T.setCharacterSize(50);
	this->point_T.setFillColor(Color::White);

	//timer bar na samom dele. used to be hp bar
	this->hpBar.setSize(Vector2f(300.f, 25.f));
	this->hpBar.setFillColor(Color::White);
	this->hpBar.setPosition(Vector2f(455.f, 25.5f));

	this->hbBarBACK.setSize(Vector2f(310.f, 35.f));
	this->hbBarBACK.setFillColor(Color::Black);
	this->hbBarBACK.setPosition(Vector2f(450.f, 20.f));

	this->skull.loadFromFile("textures/DOPA.png");
	this->skullD.setTexture(this->skull);
	this->skullD.setScale(0.1f, 0.1f);
	this->skullD.setPosition(Vector2f(743.f, 5.f));
	this->skullT.setString("DOPSA");
	this->skullT.setFont(this->fontMain);
	this->skullT.setCharacterSize(20);
	this->skullT.setPosition(Vector2f(743.f, 60.f));
}

void game::initBG() {
	if (!(this->BGt.loadFromFile("textures/bg.jpg"))) {
		std::cout << "BG NE OTKRYLSYA" << std::endl;
	}
	this->BG.setTexture(this->BGt);
	this->BG.setScale(0.75f, 0.85f);
}

void game::initSystem()
{
	this->points = 0;
}


void game::initplayer() {
	this->PLAYER = new player();
	this->ENEMY = new enemy(20.f, 20.f);
}

void game::initEnemy() {
	this->spawnTmax = 50.f;
	this->spawn_timer = this->spawnTmax;

}

game::game()
{
	this->initWin();
	this->initTextures();
	this->initTextStuff();
	this->initBG();
	this->initSystem();
	this->initplayer();
	this->initEnemy();
}

game::~game()
{
	delete this->window;
	delete this->PLAYER;

	//udalenie textur
	for (auto& i : this->textures) {
		delete i.second;
	}

	for (auto* i : this->bullets) { //working with that vector
		delete i;
	}

	//delete enemies
	for (auto* i : this->enemies) {
		delete i;
	}
}


//zdec nacinauca funkcii
void game::run()
{
	while (this->window->isOpen()) {
		this->upd_PollEvents();

		if ((deadline.getElapsedTime().asSeconds() <= 150) and introduction) {
			this->upd();
		}
		this->ren();
	}
}


void game::upd_PollEvents() {
	Event ev1;
	while (this->window->pollEvent(ev1)) {
		if (ev1.type == Event::Closed) {
			this->window->close();
		}
		else if (ev1.type == Event::KeyPressed && ev1.key.code == Keyboard::Escape) {
			this->window->close();
		}
	}
}

void game::upd_input() {


	if (Keyboard::isKeyPressed(Keyboard::Key::A)) { //a is left (pbviously)
		this->PLAYER->movin_p(-1.f, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::D)) { //d is right (pbviously)
		this->PLAYER->movin_p(1.f, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::W)) { //w is up as always
		this->PLAYER->movin_p(0.f, -1.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::S)) { //s is down (ahaha no u) 
		this->PLAYER->movin_p(0.f, 1.f);
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::Enter) and this->PLAYER->ableATT()) {
		this->bullets.push_back(new attack(this->textures["Bullets"], this->PLAYER->getPos().x + 15.0f, this->PLAYER->getPos().y, 0.f, -1.f, 5.f));
	}
}

void game::updateTextS() {
	std::stringstream poi;
	poi << "Points: " << this->points;
	this->point_T.setString(poi.str());


	this->hpBar.setSize(Vector2f((300.f - 2 * (this->deadline.getElapsedTime().asSeconds())), this->hpBar.getSize().y));
	this->hpBar.setPosition(Vector2f((455.f + 2 * (this->deadline.getElapsedTime().asSeconds())), 25.5f));
}

void game::upd_collisions() {
	if (this->PLAYER->getBounds().left < 0.f) {
		this->PLAYER->setPosition(0.f, this->PLAYER->getBounds().top);
	}
	else if (this->PLAYER->getBounds().left + this->PLAYER->getBounds().width >= this->window->getSize().x) {
		this->PLAYER->setPosition(this->window->getSize().x - this->PLAYER->getBounds().width, this->PLAYER->getBounds().top);
	}

	if (this->PLAYER->getBounds().top < 0.f) {
		this->PLAYER->setPosition(this->PLAYER->getBounds().left, 0.f);
	}
	else if (this->PLAYER->getBounds().top + this->PLAYER->getBounds().height >= this->window->getSize().y) {
		this->PLAYER->setPosition(this->PLAYER->getBounds().left, this->window->getSize().y - this->PLAYER->getBounds().height);
	}

}
void game::upd_bullets() {

	unsigned counter = 0;
	for (auto* bullets : this->bullets) {
		bullets->upd_bull();


		if (bullets->getBounds().top + bullets->getBounds().height < 0.f) {
			//bullets dying 
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);

		}

		++counter;
	}
}

void game::upd_enemies() {

	//poyawlenie
	this->spawn_timer += 0.5f;
	if (this->spawn_timer >= this->spawnTmax) {
		this->enemies.push_back(new enemy(rand() % this->window->getSize().x - 20.f, -100.f));
		this->spawn_timer = 0.f;
	}

	//updating 
	unsigned counter = 0;
	for (auto* ENEMY : this->enemies) {
		ENEMY->upd_enem();


		if (ENEMY->getBounds_e().top > this->window->getSize().y) {
			//  enemy--
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			--counter;
		}

		++counter;
	}
}

void game::upd_combat() {
	for (int i = 0; i < this->enemies.size(); ++i) {

		bool isEnemyDestroyed = false;
		for (size_t o = 0; o < this->bullets.size() and !isEnemyDestroyed; o++) {
			if (this->enemies[i]->getBounds_e().intersects(this->bullets[o]->getBounds()) and this->enemies[i]->getType() != 10) {
				this->enemies[i]->eraseHP(this->PLAYER->DAMAGE());

				if (this->enemies[i]->getHP() <= 0) {
					this->points += this->enemies[i]->getPoints();
					delete this->enemies[i];
					this->enemies.erase(this->enemies.begin() + i);
				}

				delete this->bullets[o];
				this->bullets.erase(this->bullets.begin() + o);



				isEnemyDestroyed = true;
			}
		}
	}
}



void game::upd()
{
	this->upd_input();

	this->PLAYER->upd_p();

	this->upd_collisions();
	this->upd_bullets();

	this->upd_enemies();
	this->upd_combat();

	this->updateTextS();
	//this->updateBG();
}

void game::renderIntro()
{
	this->window->draw(this->intro);
}

void game::renderTexts() { //AND skull
	this->window->draw(this->point_T);
	this->window->draw(this->hbBarBACK);
	this->window->draw(this->hpBar);
	this->window->draw(this->skullD);
	this->window->draw(this->skullT);
}
void game::renderBG() {
	this->window->draw(this->BG);
}

void game::ren()
{
	this->window->clear();

	if (!introduction) {
		if (Keyboard::isKeyPressed(Keyboard::Key::Enter)) {
			introduction = true;
			this->deadline.restart();
		}
		else { // Если Enter не нажат, рендерим intro
			this->renderIntro();
		}
	}
	else {
		//tusa jusa


		this->renderBG();

		this->PLAYER->ren_p(*this->window);

		for (auto* j : this->bullets) {
			j->render_bull(this->window);
		}

		for (auto* enemy : this->enemies) {
			enemy->render_enemy(this->window);
		}


		this->renderTexts();
	}

	//game over
	if (this->deadline.getElapsedTime().asSeconds() > 250) {
		if (points >= 2500) {
			this->gameOverT.loadFromFile("textures/GE1.jpg");
			this->gameOver.setTexture(this->gameOverT);
			this->gameOver.setScale(0.9f, 0.945f);
		}
		else {
			this->gameOverT.loadFromFile("textures/BE1.jpg");
			this->gameOver.setTexture(this->gameOverT);
			this->gameOver.setScale(0.77f, 0.7f);
		}
		this->window->draw(this->gameOver);
	}

	this->window->display();

}
