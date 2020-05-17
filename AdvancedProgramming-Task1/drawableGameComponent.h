#pragma once
#include "gameComponent.h"

using namespace std;


enum Direction : unsigned char {
	Left = 1,
	Right = 2,
	Up = 3,
	Down = 4,
};

class DrawableGameComponent : public GameComponent {
	public:
		const int SCREEN_HEIGHT = 20;
		const int SCREEN_WIDTH = 80;
		Direction direction;

		DrawableGameComponent(int X, int Y) { // assigning default values
			x = 0;
			y = 0;
			direction = Right;
		};

		void Update(const tm* eventTime) override;

	private:
		int x, y;
		string currentDirection;

		void ChangeDirection();
		void Draw() {
			cout << currentDirection << " --> " << "X:" << x << "  Y:" << y << endl; // printing the current direction and x/y values
		};
};

void DrawableGameComponent::Update(const tm* eventTime) {
	GameComponent::Update(eventTime); // invoking update method from game component (inherited)

	switch (direction) { // switch statement to increment/decrement x and y values based on current direction
	case Left:
		x--;
		if (x < 0) {
			x = 0;
		}
		currentDirection = "Left";
		break;

	case Right:
		x++;
		if (x > SCREEN_WIDTH) {
			x = SCREEN_WIDTH;
		}
		currentDirection = "Right";
		break;

	case Up:
		y++;
		if (y > SCREEN_HEIGHT) {
			y = SCREEN_HEIGHT;
		}
		currentDirection = "Up";
		break;

	case Down:
		y--;
		if (y < 0) {
			y = 0;
		}
		currentDirection = "Down";
		break;

	default:
		break;
	}
	Draw(); // invoking draw member function
	ChangeDirection(); // invoking changedirection member function
};

void DrawableGameComponent::ChangeDirection() {
	int randNo = (rand() % 4) + 1; // chooses a random number (between 1-4 as there are 4 directions)
	while (randNo == direction) // making sure direction is different to the current direction
		randNo = (rand() % 4) + 1;
	direction = static_cast<Direction>(randNo); // the new direction
};