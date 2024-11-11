#pragma once
class Window;

/**
 * @enum ComponentType
 * @brief Tipos de componentes disponibles en el juego.
 */
enum ComponentType {
    NONE = 0,
    TRANSFORM = 1,
    SPRITE = 2,
    RENDERER = 3,
    PHYSICS = 4,
    AUDIOSOURCE = 5,
    SHAPE = 6,
    TEXTURE = 7
};

/**
 * @class Component
 * @brief Clase base abstracta para todos los componentes del juego.
 *
 * La clase Component define la interfaz basica que todos los componentes deben implementar,
 * permitiendo actualizar y renderizar el componente, asi como obtener su tipo.
 */
class Component {
public:
    /**
     * @brief Constructor por defecto.
     */
    Component() = default;

    /**
     * @brief Constructor que establece el tipo de componente.
     * @param type Tipo del componente.
     */
    explicit Component(const ComponentType type) : m_type(type) {}

    /**
     * @brief Destructor virtual para permitir la destruccion adecuada de clases derivadas.
     */
    virtual ~Component() = default;

    /**
     * @brief Metodo virtual puro para actualizar el componente.
     * @param deltaTime Tiempo transcurrido desde la ultima actualizacion.
     */
    virtual void update(float deltaTime) = 0;

    /**
     * @brief Metodo virtual puro para renderizar el componente.
     * @param window Contexto de ventana para operaciones graficas.
     */
    virtual void render(Window window) = 0;

    /**
     * @brief Obtiene el tipo del componente.
     * @return Tipo del componente.
     */
    ComponentType getType() const { return m_type; }

protected:
    ComponentType m_type; // Tipo de componente.
};
