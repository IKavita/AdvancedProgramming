#pragma once
#include <iomanip>

class GameComponent {
	public:
		GameComponent() {
			id = ++instances; // will give a unique id number each time
		};
		virtual void Update(const tm* time) {
			std::cout << "ID : " << id << " Updated @ " << std::put_time(time, "%X") << std::endl; // printing id and current time
		};
	private:
		// initialising variables
		int id = 0;
		static int instances; // total number of instances instantiated from two component classes
};

int GameComponent::instances;