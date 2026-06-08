#include "laser.h"
#include <sgg/graphics.h>
#include "gamestate.h"
#include "util.h"

void Laser::update(float dt)
{
	float delta_time = dt / 1000.0f;
	const float velocity = 2.5f;

	//If the ID is 0 then the laser comes from the player and it has to go up, towards the aliens
	if (ID == 0) {
		pos_y -= velocity * delta_time;
	}
	//Else the laser comes from the mystery ship and it has to go down, towards the player 
	else pos_y += velocity * delta_time;
	
	
	GameObject::update(dt);
	

}

//The laser's initialization
void Laser::init()
{
	pos_y = 100.f;
	pos_x = 100.f;
	active = false;

	width = .05f;
	height = .7f;

	laser_brush.outline_opacity = 0.0f;
	if (ID == 0) {
		SETCOLOR(laser_brush.fill_color, .8f, .8f, .0f);
	}
	else SETCOLOR(laser_brush.fill_color, .8f, .1f, .3f);
	laser_brush.fill_opacity = 1.f;
	laser_brush.outline_width = width;

}

void Laser::draw()
{
	graphics::drawRect(pos_x, pos_y, width, height, laser_brush);

	if (state->debugging) debugDraw();
}

void Laser::debugDraw()
{
	graphics::Brush debug_brush;
	SETCOLOR(debug_brush.fill_color, 1.f, 0.f, 0);
	SETCOLOR(debug_brush.outline_color, 1.f, 0.f, 0);
	debug_brush.fill_opacity = 0.4f;
	debug_brush.outline_opacity = 1.f;
	graphics::drawRect(pos_x, pos_y, width, height, debug_brush);

}
