#define _CRT_SECURE_NO_WARNINGS // for use of localtime in game.h
#include <iostream>
#include "gameComponent.h"
#include "drawableGameComponent.h"
#include "game.h"

using namespace std;

void initialise() {
	cout << "Initialising Game..." << endl; // printing to show game is being initialised
};

void terminate() {
	cout << "Game Terminated." << endl; // printing to show game is being terminated
};

int main()
{
	Game game(NULL);

	game.SetInitialise(*initialise);
	game.SetTerminate(*terminate);

	GameComponent* gameComponent = new GameComponent(); // creating new game component object
	game.Add(gameComponent);

	DrawableGameComponent* drawableGameComponent = new DrawableGameComponent(0, 0); // creating new drawable game component object
	game.Add(drawableGameComponent);

	game.Run();
}