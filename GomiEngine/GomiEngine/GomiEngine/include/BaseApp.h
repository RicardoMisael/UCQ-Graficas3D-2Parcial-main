#pragma once
#include <SFML/Graphics.hpp>
#include "Prerequisites.h"
#include <Window.h>
#include "ShapeFactory.h"
#include "Actor.h"
#include "GUI.h"
#include "Services/NotificationSystem.h"

class BaseApp {
public:
    BaseApp() = default;
    ~BaseApp();

    // Funcion principal para ejecutar la aplicacion en main
    int run();

    // Funcion de inicializacion
    bool initialize();

    // Funcion que se actualiza en cada frame
    void update();

    // Funcion para renderizar contenido en pantalla
    void render();

    // Limpia y libera los recursos utilizados
    void cleanup();

    // Actualiza el movimiento del objeto circulo
    void updateMovement(float deltaTime, EngineUtilities::TSharedPointer<Actor> circle);

    // Controla el movimiento del circulo
    void MovimientoCirculo(float deltaTime, EngineUtilities::TSharedPointer<Actor> Circle);

    int ActualPosition = 0; // Posicion actual de los waypoints

private:
    Window* m_window = nullptr;
    EngineUtilities::TSharedPointer<Actor> Triangle;
    EngineUtilities::TSharedPointer<Actor> Circle;
    EngineUtilities::TSharedPointer<Actor> Track;
    std::vector<EngineUtilities::TSharedPointer<Actor>> m_actors;

    // Variable para el seguimiento de waypoints
    int currentWaypoint = 0;

    // Lista de posiciones de waypoints para el movimiento
    std::vector<sf::Vector2f> waypoints = {
        {720.0f, 350.0f},
        {720.0f, 260.0f},
        {125.0f, 50.0f},
        {70.0f, 120.0f},
        {70.0f, 450.0f},
        {400.0f, 350.0f},
        {550.0f, 500.0f},
        {650.0f, 550.0f},
        {720.0f, 450.0f}
    };

    sf::Texture Mario;
    sf::Texture texture;

    GUI m_GUI;
};

















