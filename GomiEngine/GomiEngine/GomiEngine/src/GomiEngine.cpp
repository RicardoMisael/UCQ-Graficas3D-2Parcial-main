#include "Application.h"
#include <SFML/Graphics.hpp>
#include "AppWindow.h"

sf::RenderWindow* mainWindow;
//sf::CircleShape* drawingShape;

int
main() {
	Application appInstance;
	return appInstance.execute();
}
