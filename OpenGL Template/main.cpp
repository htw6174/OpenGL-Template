#include "Engine.h"
#include "TestGame.h"


int main(void) {

	TestGame game;

	Engine* engine = new Engine(&game);

	engine->Start();
}