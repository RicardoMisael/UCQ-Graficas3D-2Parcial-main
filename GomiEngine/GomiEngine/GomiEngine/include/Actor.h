#pragma once
#include "Prerequisites.h"
#include "Entity.h"
#include "ShapeFactory.h"
#include "Transform.h"

class Actor : public Entity {
public:
    /**
     * @brief Constructor por defecto para Actor.
     */
    Actor() = default;

    explicit Actor(std::string actorName);

    /**
     * @brief Destructor virtual para liberar recursos.
     */
    virtual ~Actor() = default;

    /**
     * @brief Actualiza el estado del actor.
     * @param deltaTime Tiempo transcurrido desde la ultima actualizacion.
     */
    void update(float deltaTime) override;

    /**
     * @brief Renderiza el actor en el contexto de la ventana.
     * @param window Contexto del dispositivo para operaciones graficas.
     */
    void render(Window& window) override;

    /**
     * @brief Libera los recursos asociados al actor.
     */
    void destroy();

    /**
     * @brief Obtiene el nombre del actor.
     * @return Nombre del actor.
     */
    std::string getName() const;

    /**
     * @brief Busca un componente especifico del actor.
     * @tparam T Tipo del componente que se desea obtener.
     * @return Un puntero compartido al componente o nullptr si no se encuentra.
     */
    template <typename T>
    EngineUtilities::TSharedPointer<T> getComponent();

private:
    std::string m_name = "Actor"; ///< Nombre del actor.
};

/**
 * @brief Busca y retorna un componente especifico del actor, segun el tipo proporcionado.
 * @tparam T Tipo de componente a buscar.
 * @return Puntero compartido al componente o un TSharedPointer vacio si no se encuentra.
 */
template<typename T>
inline EngineUtilities::TSharedPointer<T> Actor::getComponent() {
    for (auto& component : components) {
        auto specificComponent = component.template dynamic_pointer_cast<T>();
        if (specificComponent) {
            return specificComponent;
        }
    }
    // Retorna un TSharedPointer vacio si no se encuentra el componente
    return EngineUtilities::TSharedPointer<T>();
}
