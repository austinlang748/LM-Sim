#include "uiInteract.h"
using namespace std;

class Thrust
{
public:
	Thrust()
	{
		mainEngine = false;
		clockwise = false;
		counterClockwise = false;
	}

	void rotation()
	{
		
	}

	void mainEngineThrust()
	{

	}

	bool isMain()
	{
		return mainEngine;
	}

	bool isClock()
	{
		return clockwise;
	}

	bool isCounter()
	{
		return counterClockwise;
	}

	void update(const Interface* pUI)
	{
		// move the ship around
		if (pUI->isRight())
			counterClockwise = true;
		if (pUI->isLeft())
			clockwise = true;
		if (pUI->isDown())
			mainEngine = true;
	}

private:
	bool mainEngine;
	bool clockwise;
	bool counterClockwise;
};
