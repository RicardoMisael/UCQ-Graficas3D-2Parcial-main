#include "BaseApp.h"
#include "Services/NotificationSystem.h"

BaseApp::~BaseApp()
{
    // Save notification messages to file upon app destruction
    NotificationService::getInstance().saveMessagesToFile("LogData.txt");
}

int BaseApp::run() {
    NotificationService& notifier = NotificationService::getInstance();

    if (!initialize()) {
        notifier.addMessage(ConsolErrorType::ERROR, "Initialization failed. Check method validations.");
        notifier.saveMessagesToFile("LogData.txt");
        ERROR("BaseApp", "run", "Initialization failed. Check method validations.");
        return -1;  // Indicate error if initialization fails
    }
    else {
        notifier.addMessage(ConsolErrorType::NORMAL, "All programs were initialized correctly.");
    }

    m_GUI.init();

    // Main application loop
    while (m_window->isOpen()) {
        m_window->handleEvents();
        update();
        render();
    }

    cleanup();
    return 0;
}

bool BaseApp::initialize() {
    NotificationService& notifier = NotificationService::getInstance();
    m_window = new Window(1920, 1080, "Patas Engine");
    if (!m_window) {
        ERROR("BaseApp", "initialize", "Error on window creation, pointer is null.");
        return false;
    }

    // Track Actor Setup
    Track = EngineUtilities::MakeShared<Actor>("Track");
    if (Track.isNull()) {
        return false;
    }
    Track->getComponent<ShapeFactory>()->createShape(ShapeType::RECTANGLE);
    Track->getComponent<Transform>()->setPosition(sf::Vector2f(0.0f, 0.0f));
    Track->getComponent<Transform>()->setRotation(sf::Vector2f(0.0f, 0.0f));
    Track->getComponent<Transform>()->setScale(sf::Vector2f(11.0f, 12.0f));

    if (!texture.loadFromFile("Circuit.png")) {
        std::cout << "Texture load error!" << std::endl;
        return false;  // Error handling for texture load
    }
    Track->getComponent<ShapeFactory>()->getShape()->setTexture(&texture);

    // Circle Actor Setup
    Circle = EngineUtilities::MakeShared<Actor>("Circle");
    if (Circle.isNull()) {
        return false;
    }
    Circle->getComponent<ShapeFactory>()->createShape(ShapeType::CIRCLE);
    Circle->getComponent<Transform>()->setPosition(sf::Vector2f(200.0f, 200.0f));
    Circle->getComponent<Transform>()->setRotation(sf::Vector2f(0.0f, 0.0f));
    Circle->getComponent<Transform>()->setScale(sf::Vector2f(1.0f, 1.0f));

    if (!Mario.loadFromFile("Characters/tile000.png")) {
        std::cout << "Texture load error!" << std::endl;
        return false;  // Error handling for texture load
    }
    Circle->getComponent<ShapeFactory>()->getShape()->setTexture(&Mario);
    m_actors.push_back(Circle);

    // Triangle Actor Setup
    Triangle = EngineUtilities::MakeShared<Actor>("Triangle");
    if (Triangle.isNull()) {
        return false;
    }
    Triangle->getComponent<ShapeFactory>()->createShape(ShapeType::TRIANGLE);
    Triangle->getComponent<Transform>()->setPosition(sf::Vector2f(200.0f, 200.0f));
    Triangle->getComponent<Transform>()->setRotation(sf::Vector2f(0.0f, 0.0f));
    Triangle->getComponent<Transform>()->setScale(sf::Vector2f(1.0f, 1.0f));
    m_actors.push_back(Triangle);

    return true;
}

void BaseApp::update() {
    // Update window method
    m_window->update();

    // Mouse position for interaction or other purposes
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*m_window->getWindow());
    sf::Vector2f mousePosF(static_cast<float>(mousePosition.x),
        static_cast<float>(mousePosition.y));

    // Update Track, Triangle, and Circle actors
    if (!Track.isNull()) {
        Track->update(m_window->deltaTime.asSeconds());
    }
    if (!Triangle.isNull()) {
        Triangle->update(m_window->deltaTime.asSeconds());
    }
    if (!Circle.isNull()) {
        Circle->update(m_window->deltaTime.asSeconds());
        updateMovement(m_window->deltaTime.asSeconds(), Circle);
    }

    // Update all actors
    for (auto& actor : m_actors) {
        if (!actor.isNull()) {
            actor->update(m_window->deltaTime.asSeconds());
            if (actor->getName() == "Circle") {
                MovimientoCirculo(m_window->deltaTime.asSeconds(), actor);
            }
        }
    }
}

void BaseApp::MovimientoCirculo(float deltaTime, EngineUtilities::TSharedPointer<Actor> Circle) {
    if (Circle.isNull()) return;

    auto transform = Circle->getComponent<Transform>();
    if (transform.isNull()) return;

    sf::Vector2f targetPos = waypoints[ActualPosition];
    transform->Seek(targetPos, 200.0f, deltaTime, 10.0f);
    sf::Vector2f currentPos = transform->getPosition();
    float distanceToTarget = std::sqrt(std::pow(targetPos.x - currentPos.x, 2) + std::pow(targetPos.y - currentPos.y, 2));

    if (distanceToTarget < 10.0f) {
        ActualPosition = (ActualPosition + 1) % waypoints.size();
    }
}

void BaseApp::render() {
    NotificationService& notifier = NotificationService::getInstance();
    m_window->clear();

    // Render all actors
    if (!Track.isNull()) {
        Track->render(*m_window);
    }
    if (!Circle.isNull()) {
        Circle->render(*m_window);
    }
    if (!Triangle.isNull()) {
        Triangle->render(*m_window);
    }

    for (auto& actor : m_actors) {
        if (!actor.isNull()) {
            actor->render(*m_window);
        }
    }

    // Show render in ImGui
    m_window->renderToTexture();
    m_window->showInImGui();

    // Show console notifications
    m_GUI.console(notifier.getNotifications());

    // Show window hierarchy and inspector in GUI
    m_GUI.hierarchy(m_actors, selectedActorID);
    if (selectedActorID >= 0 && selectedActorID < m_actors.size()) {
        m_GUI.inspector(m_actors[selectedActorID]);
    }

    // Actor creation menu
    m_GUI.actorCreationMenu(m_actors);

    m_window->render();
    m_window->display();
}

void BaseApp::cleanup() {
    m_window->destroy();
    delete m_window;
}

void BaseApp::updateMovement(float deltaTime, EngineUtilities::TSharedPointer<Actor> circle) {
    if (!circle || circle.isNull()) return;

    auto transform = circle->getComponent<Transform>();
    if (transform.isNull()) return;

    sf::Vector2f targetPos = waypoints[currentWaypoint];
    transform->Seek(targetPos, 200.0f, deltaTime, 10.0f);

    sf::Vector2f currentPos = transform->getPosition();
    float distanceToTarget = std::sqrt(std::pow(targetPos.x - currentPos.x, 2) + std::pow(targetPos.y - currentPos.y, 2));

    if (distanceToTarget < 10.0f) {
        currentWaypoint = (currentWaypoint + 1) % waypoints.size();
    }
}
