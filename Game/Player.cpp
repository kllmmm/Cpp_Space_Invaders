#include "player.h"
#include <sgg/graphics.h>
#include "gamestate.h"
#include "util.h"

void Player::update(float dt)
{
	float delta_time = dt / 1000.0f;
	const float velocity = 4.0f;


	//The Player's movement	
	if (graphics::getKeyState(graphics::SCANCODE_A))
		pos_x -= velocity * delta_time;
	if (graphics::getKeyState(graphics::SCANCODE_D))
		pos_x += velocity * delta_time;
	if (graphics::getKeyState(graphics::SCANCODE_LEFT))
		pos_x -= velocity * delta_time;
	if (graphics::getKeyState(graphics::SCANCODE_RIGHT))
		pos_x += velocity * delta_time;

	GameObject::update(dt);
}

//The player's initialization
void Player::init()
{
	
	 pos_x = state->getCanvasWidth() / 2.0f;
	 pos_y = 7.0f;
	

	 player_brush.outline_opacity = 0.0f;
	 player_brush.texture = state->getFullAssetPath("spaceship.png");

}

//Draw the Player
void Player::draw()
{
	graphics::drawRect(pos_x, pos_y, width, height, player_brush);

	if (state->debugging) debugDraw();
}

void Player::debugDraw() {

	graphics::Brush debug_brush;
	SETCOLOR(debug_brush.fill_color, 0.f, 1.f, 0);
	SETCOLOR(debug_brush.outline_color, 0.f, 1.f, 0);
	debug_brush.fill_opacity = 0.4f;
	debug_brush.outline_opacity = 1.f;
	graphics::drawRect(pos_x, pos_y, width, height, debug_brush);

	char s[20];
	sprintf_s(s, "(%5.2f, %5.2f)", pos_x, pos_y);
	SETCOLOR(debug_brush.fill_color, 1, 0, 0);
	debug_brush.fill_opacity = 1.0f;
	graphics::drawText(pos_x - 0.5f, pos_y - 0.6f, 0.15f, s, debug_brush);

}
