#include "level.h"
#include "gamestate.h"
#include "player.h"
#include "alien.h"
#include "util.h"
#include "laser.h"
#include <fstream>
#include <string>
using namespace std;

//The level draws the aliens
void Level::drawAliens(int i)
{
	Alien& alien = aliens[i];
	float x = alien.getPos_x();
	float y = alien.getPos_y();
	float w = alien.getWidth();
	float h = alien.getHeight();
	alien_brush.texture = state->getFullAssetPath(alien_name[i]);

	graphics::drawRect(x, y, w, h, alien_brush);
	if (state->debugging) alien.debugDraw();
}

//Barrier draw
void Level::drawBarrier(int i)
{
	Box& barrier = barriers[i];


	graphics::drawRect(barrier.pos_x, barrier.pos_y, barrier.width, barrier.height, barrier_brush);

	if (state->debugging) graphics::drawRect(barrier.pos_x, barrier.pos_y, barrier.width, barrier.height, debug_barrier_brush);
}


//Level update
void Level::update(float dt)
{

	//Checks if the level is in the start screen and initializes the game if the user presses "SPACE" 
	if (startscreen) {
	
		if (graphics::getKeyState(graphics::SCANCODE_SPACE)) {
		
			startscreen = false;
			gamescreen = true;
			init();

		}
	
	}
	
	//The game update
	if (gamescreen) {

		//If the player is active it updates the player
		if (state->getPlayer()->isActive())
			state->getPlayer()->update(dt);


		//Checks if the alien is active and updates him. If the alien has passed a certain y posotion, it deactivates him
		for (auto& alien : aliens) {
			if (alien.getPos_y() >= 6.5f) { alien.setActive(false); }
			if (alien.isActive()) { alien.update(dt); }

		}

		//checks if all the aliens (not the mystery ship) are dead (deactivated)
		bool all_dead = true;

		for (auto& alien : aliens) {

			if (alien.isActive() && alien.getId() == 1) {
				all_dead = false;
				break;
			}
		}

		//if they are all dead, the mystery ship begins its descend
		if (all_dead) aliens.back().setId(3);

		temp_time += dt / 1000.0f;
		temp_time1 += dt / 1000.0f;
		temp_time2 += dt / 1000.0f;
		temp_time3 += dt / 1000.0f;

		//Every second the player ship fire a laser from its current position
		if (temp_time >= 1.f && state->getPlayer()->isActive()) {

			graphics::playSound(state->getFullAssetPath("laser.ogg"), 0.2f);

			if (temp_time1 >= 3.f) {
				lasers[0]->setPosX(state->getPlayer()->getPosX());
				lasers[0]->setPosY(state->getPlayer()->getPosY() - .5f);
				lasers[0]->setActive(true);
				temp_time1 = 0.f;
			}
			if (temp_time2 >= 3.f) {
				lasers[1]->setPosX(state->getPlayer()->getPosX());
				lasers[1]->setPosY(state->getPlayer()->getPosY() - .5f);
				lasers[1]->setActive(true);
				temp_time2 = 0.f;
			}
			if (temp_time3 >= 3.f) {
				lasers[2]->setPosX(state->getPlayer()->getPosX());
				lasers[2]->setPosY(state->getPlayer()->getPosY() - .5f);
				lasers[2]->setActive(true);
				temp_time3 = 0.f;
			}
			temp_time = 0.f;
		}

		alien_time += dt / 1000.f;
		//Every 2,5 seconds the mystery ship fires a laser
		if (alien_time >= 2.5f && aliens.back().isActive()) {

			alien_laser->setPosX(aliens.back().getPos_x());
			alien_laser->setPosY(aliens.back().getPos_y() + .5f);
			alien_laser->setActive(true);
			alien_time = .0f;

		}

		//laser update
		for (int i = 0; i <= 2; i++) {
			if (lasers[i]->isActive()) lasers[i]->update(dt);
		}

		if (alien_laser->isActive()) alien_laser->update(dt);

		//checking if they are collisions
		checkCollisions();

		//Showing the current score
		char s[20];
		sprintf_s(s, sizeof(s), "Score: %d", score);
		SETCOLOR(score_brush.fill_color, 1, 1, .5f);
		score_brush.fill_opacity = 1.0f;
		graphics::drawText(6.3f, 7.7f, 0.15f, s, score_brush);

		GameObject::update(dt);
	}

	bool flag = false;

	for (auto& alien : aliens) {
		if (!alien.isActive() && alien.getHp() >= 1) flag = true;
	}

	//if a game ending condition has been met, the game is over and the level goes to the ending screen
	if (gamescreen && ( !aliens.back().isActive() || !state->getPlayer()->isActive() || flag)) {
	
		gamescreen = false;
		endscreen = true;
		init();
		draw();
	
	}
}

//Level initialization
void Level::init()
{

	//start screen initialization
	if (startscreen) {
	
		background_brush.outline_opacity = 0.0f;
		background_brush.texture = state->getFullAssetPath("background.png");
	
	}

	//game initialization
	if (gamescreen) {
		background_brush.outline_opacity = 0.0f;
		background_brush.texture = state->getFullAssetPath("background.png");

		//constructing teh aliens
		float temp_x = 1.0f;
		float temp_y = -0.15f;
		float temp_w = 0.3f;
		float temp_h = 0.2f;
		float jx = 0.0f;
		float jy = 0.0f;
		int i = 1;
		int rows = 39;

		while (i <= rows * 3  - 13 * 3)
		{
			if (i % 13 == 1 && i != 1) {
				jy -= 0.25f;
				jx = 0.0f;
			}

			else if (i != 1) jx += 0.5f;



			if (i <= rows) {
				aliens.push_back(Alien(temp_x + jx, temp_y + jy, temp_w, temp_h, 1, 1));
				alien_name.push_back("alien_1.png");
			}

			else if (i <= rows * 2  - 13) {
				aliens.push_back(Alien(temp_x + jx, temp_y + jy, temp_w, temp_h, 2, 1));
				alien_name.push_back("alien_2.png");
			}

			else {
				aliens.push_back(Alien(temp_x + jx, temp_y + jy, temp_w, temp_h, 3, 1));
				alien_name.push_back("alien_3.png");
			}

			i++;
		}

		aliens.push_back(Alien(state->getCanvasWidth() / 2.f, 0.3f, temp_w, temp_h, 5, 2));
		alien_name.push_back("mystery.png");

		alien_brush.outline_opacity = 0.f;

		//constructing the barriers
		barriers.push_back(Box(7.5f, state->getCanvasHeight() / 2.f, barrier_width, barrier_height));
		barriers.push_back(Box(.5f, state->getCanvasHeight() / 2.f, barrier_width, barrier_height));

		//constructing the player's lasers and initializes them
		laser1 = new Laser("");
		laser2 = new Laser("");
		laser3 = new Laser("");
	
		lasers.push_back(laser1);
		lasers.push_back(laser2);
		lasers.push_back(laser3);

		for (auto& l : lasers)
			if (l) l->init();

		//constructing the mystery ship's lasers and initializes them
		alien_laser = new Laser("");
		alien_laser->setID(1);
		alien_laser->init();

		//constructing the lives of the player as player ships 
		lives.push_back(Box(1.f, state->getCanvasHeight() - .2f, state->getPlayer()->getWidth(), state->getPlayer()->getHeight()));
		lives.push_back(Box(1.3f, state->getCanvasHeight() - .2f, state->getPlayer()->getWidth(), state->getPlayer()->getHeight()));
		lives.push_back(Box(1.6f, state->getCanvasHeight() - .2f, state->getPlayer()->getWidth(), state->getPlayer()->getHeight()));

		//background music
		graphics::playMusic(state->getFullAssetPath("music.ogg"), 0.2f);
	}

	//ending screen initialization
	if (endscreen) {
	
		background_brush.outline_opacity = 0.0f;
		background_brush.texture = state->getFullAssetPath("background.png");

		//getting the highscore from the txt file and if the player's score is better, it replaces the old highscore with the new one and writes it back to the file 
		string file = "highscore.txt";

		ifstream inFile(file);
		if (inFile.is_open()); {
			inFile >> highscore;
			inFile.close();
		}

		if (highscore < score) highscore = score;
		ofstream outFile(file);
		if (outFile.is_open()) {
			outFile << highscore;
			outFile.close();
		}
	
	}


}

//Level draw
void Level::draw()
{

	//draw the start screen
	if (startscreen) {
		float width = state->getCanvasWidth();
		float height = state->getCanvasHeight();

		graphics::drawRect(width / 2.0f, height / 2.0f, width, height, background_brush);

		string ss = "SPACE INVADERS";
		char s[40];
		sprintf_s(s, sizeof(s), "%s", ss.c_str());
		SETCOLOR(score_brush.fill_color, 1, 1, 1);
		score_brush.fill_opacity = 1.0f;
		graphics::drawText(1.f , state->getCanvasHeight() / 2.f, 0.6f, s, score_brush);

		string rr = "Press SPACE to play.";
		char r[30];
		sprintf_s(r, sizeof(r), "%s", rr.c_str());
		SETCOLOR(score_brush.fill_color, 1, 1, 1.f);
		score_brush.fill_opacity = 1.0f;
		graphics::drawText(1.f, state->getCanvasHeight() / 2.f + .5f, .2f, r, score_brush);

	}

	//Draw the game
	if (gamescreen) {

		float width = state->getCanvasWidth();
		float height = state->getCanvasHeight();

		graphics::drawRect(width / 2.0f, height / 2.0f, width, height, background_brush);

		//player draw
		if (state->getPlayer()->isActive())
			state->getPlayer()->draw();

		//barrier draw
		SETCOLOR(barrier_brush.fill_color, .8f, .8f, .0f);
		SETCOLOR(barrier_brush.outline_color, .2f, .2f, .2f);
		barrier_brush.fill_opacity = 1.f;
		barrier_brush.outline_opacity = 1.f;
		barrier_brush.outline_width = 2.f;

		//debug barrier
		debug_barrier_brush.fill_opacity = 0.1f;
		SETCOLOR(debug_barrier_brush.fill_color, 0.2f, 1.f, .1f);
		SETCOLOR(debug_barrier_brush.outline_color, 0.3f, 1.f, .2f);

		for (int i = 0; i < barriers.size(); i++) drawBarrier(i);

		//lives draw
		lives_brush.outline_opacity = .0f;
		lives_brush.texture = state->getFullAssetPath("spaceship.png");
		for (auto& l : lives) graphics::drawRect(l.pos_x, l.pos_y, l.width, l.height, lives_brush);

		//alien draw
		for (int i = 0; i < aliens.size(); i++) {

			if (aliens[i].isActive()) drawAliens(i);

		}

		//player's and aliens's lasers draw
		for (auto& l : lasers)
			if (l) l->draw();

		alien_laser->draw();
	}

	//Drawing the end screen with the player's score and the highscore 
	if (endscreen) {
		float width = state->getCanvasWidth();
		float height = state->getCanvasHeight();

		graphics::drawRect(width / 2.0f, height / 2.0f, width, height, background_brush);

		string str = "Game Over.";
		char sss[20];
		sprintf_s(sss, sizeof(sss), "%s", str.c_str());
		SETCOLOR(score_brush.fill_color, 1, 1, .5f);
		score_brush.fill_opacity = 1.0f;
		graphics::drawText(1.f, state->getCanvasHeight() / 2.f - 0.5, .5f, sss, score_brush);

		char s[40];
		sprintf_s(s, sizeof(s), "Final Score: %d", score);
		SETCOLOR(score_brush.fill_color, 1, 1, .5f);
		score_brush.fill_opacity = 1.0f;
		graphics::drawText(1.f, state->getCanvasHeight() / 2.f, .5f, s, score_brush);

		char record[40];
		sprintf_s(record, sizeof(record), "High Score: %d", highscore);
		SETCOLOR(score_brush.fill_color, 1, 1, .5f);
		score_brush.fill_opacity = 1.0f;
		graphics::drawText(1.f, state->getCanvasHeight() / 2.f + .5f, .3f, record, score_brush);
	}

}

Level::Level(const std::string& name)
{
}

Level::~Level()
{
	
}

//Collisions
void Level::checkCollisions()
{

	//makes the player stay inside the barriers
	for (auto& barrier : barriers) {
	
		if (state->getPlayer()->intersect(barrier)) {
			if (state->getPlayer()->getPosX() > 7.3f) state->getPlayer()->setPosX(7.3f);
			if (state->getPlayer()->getPosX() < .7f) state->getPlayer()->setPosX(.7f);

		
		}
	}

	//if the player's laser hit an alien, the alien loses an hp point. If its hp hit 0, it gets killed (deactivated) 
	for (auto& alien : aliens) {
	
		for (auto& laser : lasers) {
		
			if (laser->intersect(alien) && alien.isActive() && alien.getPos_y() >= -.05f && alien.getId() != 2 /*if at least one alien is alive then the mystery ship cannot be hit*/) { //checks if the lasers intersect with the aliens, if the alien is active and in the frame then it registers a hit

				graphics::playSound(state->getFullAssetPath("explosion.ogg"), 0.2f);;
				alien.setHp(alien.getHp() - 1);
				if (alien.getHp() == 0) alien.setActive(false);
				laser->setPosX(100.f);
				laser->setPosY(100.f);
				if (alien.getId() == 1) score += 100;
				else score += 200; // the mystery ship gives a total of 1000 points if killed (it has 5 hp points)
				
		

			}
		}
	
	}

	//if the mystery ship's laser hit the player, the player loses an hp point. If their hp hit 0, they get killed (deactivated)
	bool condition = alien_laser->getPosY() >= state->getPlayer()->getPosY() - 0.4 //checks if the lasers' y position is the same as the top of the player's y position  
		&& alien_laser->getPosX() <= state->getPlayer()->getPosX() + .15f 
		&& alien_laser->getPosX() >= state->getPlayer()->getPosX() - .15f; //checks if the lasers' x position is inside the player's 'hitbox'
	
	if (condition) { //if the condition is true then it registers a hit

		graphics::playSound(state->getFullAssetPath("explosion.ogg"), 0.2f);;
		state->getPlayer()->setHp(state->getPlayer()->getHp() - 1);
		lives.erase(lives.end() - 1); //deletes a ship from the lives
		if (state->getPlayer()->getHp() == 0) state->getPlayer()->setActive(false);
		alien_laser->setPosX(100.f);
		alien_laser->setPosY(100.f);
	
	}

}
