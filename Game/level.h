#pragma once
#include "gameobject.h"
#include <sgg/graphics.h>
#include <list>
#include "alien.h"
#include "gamestate.h"
#include "laser.h"

class Level : public GameObject {

	graphics::Brush background_brush;

	float center_x = 5.0f;
	float center_y = 5.0f;

	std::vector<Box> barriers;
	const float barrier_width = .1f;
	const float barrier_height = state->getCanvasHeight() - 1.f;
	graphics::Brush barrier_brush;
	graphics::Brush debug_barrier_brush;

	std::vector<Box> lives;
	graphics::Brush lives_brush;

	std::vector<Alien> aliens;
	std::vector<std::string> alien_name;
	graphics::Brush alien_brush;

	void drawAliens(int i);
	void drawBarrier(int i);

	class Laser* laser1 = 0;
	class Laser* laser2 = 0;
	class Laser* laser3 = 0;
	std::vector<Laser*> lasers;

	float temp_time = .0f;
	float temp_time1 = 2.0f;
	float temp_time2 = 1.0f;
	float temp_time3 = 0.0f;

	float alien_time = .0f;
	class Laser* alien_laser = 0;

	int score = 0;
	int highscore;
	graphics::Brush score_brush;

	void checkCollisions();

	bool startscreen = true;
	bool gamescreen = false;
	bool endscreen = false;

public:

	void update(float dt) override;
	void init() override;
	void draw() override;
	Level(const std::string& name = "Level");
	~Level();

};