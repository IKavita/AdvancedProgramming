#pragma once
#include "GameComponent.h"
#include <thread>

int update_amount = 5;
typedef void (*FP)(); // a typedef representing a type of function that returns void and has no parameters

class Game {
public:
	Game(int maxComponents) {};
	void Add(GameComponent* gameComponent) {
		components[componentCount++] = gameComponent; // adds new gameComponent object to array of gamecomponent pointers
	};
	void Run();
	void SetInitialise(FP init) { initialise = init; }; // assigns pointer function to the initialise data member
	void SetTerminate(FP term) { terminate = term; }; // assigns pointer function to the terminate data member
private:
	GameComponent* components[2]; // initialising array
	int componentCount = 0;
	FP initialise; // pointer for initialise
	FP terminate; // pointer for terminate
	const int TICKS_1000MS = 1000;
};

void Game::Run() {
	initialise();
	for (int i = 0; i < update_amount; i++) {
		for (int i = 0; i < componentCount; i++) {  // loops through component array
			auto currentTime = chrono::system_clock::now();
			auto inTimeT = chrono::system_clock::to_time_t(currentTime);
			tm* time = localtime(&inTimeT); // getting current time
			components[i]->Update(time); // invoking game component's update member function with current time
		}
		chrono::milliseconds sleep(TICKS_1000MS);
		this_thread::sleep_for(sleep); // updates once every second
	}
	terminate(); // terminates pointer address
};