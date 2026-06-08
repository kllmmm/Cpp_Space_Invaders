#pragma once

#include "gameobject.h"
#include "box.h"
#include <sgg/graphics.h>

class Player : public GameObject, public Box {
	
	graphics::Brush player_brush;
	
	int hp = 3;
	float width = 0.3f;
	float height = 0.2f;

public:
	Player(std::string name) : GameObject(name) {}
	void update(float dt) override;
	void init() override;
	void draw() override;

	void setHp(int hp) { this->hp = hp; }
	int getHp() { return hp; }
	float getPosY() { return pos_y; }
	float getPosX() { return pos_x; }
	void setPosX(float x) { pos_x = x; }
	void setPosY(float y) { pos_y = y; }
	float getWidth() { return width; }
	float getHeight() { return height; }

protected:
	void debugDraw();

};