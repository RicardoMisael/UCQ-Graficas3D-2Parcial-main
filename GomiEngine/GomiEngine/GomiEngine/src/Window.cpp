#include "GraphicsWindow.h"
#include "UI.h"
#include "SystemPrerequisites.h"
#include <SFML/Graphics.hpp>

GraphicsWindow::GraphicsWindow(int width, int height, const std::string& title) {
    m_sfWindow = new sf::RenderWindow(sf::VideoMode(width, height), title);

    if (!m_sfWindow) {
        ERROR("GraphicsWindow", "GraphicsWindow", "CHECK CONSTRUCTOR");
    }
    else {
        MESSAGE("GraphicsWindow", "GraphicsWindow", "OK");
    }

    // Iniciar recursos de ImGui
    ImGui::SFML::Init(*m_sfWindow);

    // Crear RenderTexture con las dimensiones de la ventana
    if (!m_renderTexture.create(width, height)) {
        ERROR("GraphicsWindow", "RenderTexture", "CHECK CREATION");
    }
}

GraphicsWindow::~GraphicsWindow() {
    ImGui::SFML::Shutdown();
    delete m_sfWindow;
}

void
GraphicsWindow::processEvents() {
    sf::Event event;
    while (m_sfWindow->pollEvent(event)) {
        // Procesar eventos de entrada en ImGui
        ImGui::SFML::ProcessEvent(event);
        switch (event.type) {
        case sf::Event::Closed:
            m_sfWindow->close();
            break;
        case sf::Event::Resized:
            // Obtener nuevo tamaño de la ventana
            unsigned int width = event.size.width;
            unsigned int height = event.size.height;

            m_view = m_sfWindow->getView();
            m_view.setSize(static_cast<float>(width), static_cast<float>(height));
            m_sfWindow->setView(m_view);

            // Actualizar RenderTexture si el tamaño de la ventana cambia
            m_renderTexture.create(width, height);
            break;
        }
    }
}

void
GraphicsWindow::clearWindow() {
    if (m_sfWindow != nullptr) {
        m_sfWindow->clear();
    }
    else {
        ERROR("GraphicsWindow", "clearWindow", "CHECK FOR WINDOW POINTER DATA");
    }
    if (m_renderTexture.getSize().x > 0 && m_renderTexture.getSize().y > 0) {
        m_renderTexture.clear();
    }
}

void
GraphicsWindow::show() {
    if (m_sfWindow != nullptr) {
        m_sfWindow->display();
    }
    else {
        ERROR("GraphicsWindow", "show", "CHECK FOR WINDOW POINTER DATA");
    }
}

bool
GraphicsWindow::isOpen() const {
    if (m_sfWindow != nullptr) {
        return m_sfWindow->isOpen();
    }
    else {
        ERROR("GraphicsWindow", "isOpen", "CHECK FOR WINDOW POINTER DATA");
        return false;
    }
}

void
GraphicsWindow::drawDrawable(const sf::Drawable& drawable) {
    // Dibujar sobre RenderTexture en vez de la ventana directamente
    if (m_renderTexture.getSize().x > 0 && m_renderTexture.getSize().y > 0) {
        m_renderTexture.draw(drawable);
    }
}

sf::RenderWindow*
GraphicsWindow::getRenderWindow() {
    if (m_sfWindow != nullptr) {
        return m_sfWindow;
    }
    else {
        ERROR("GraphicsWindow", "getRenderWindow", "CHECK FOR WINDOW POINTER DATA");
        return nullptr;
    }
}

void
GraphicsWindow::applyRenderToTexture() {
    // Renderizar todo en la textura antes de mostrarla
    m_renderTexture.display();
}

void GraphicsWindow::setCustomGUIStyle() {
    ImGuiStyle& style = ImGui::GetStyle();

    // Configuración general de bordes y tamaños
    style.WindowRounding = 8.0f;
    style.FrameRounding = 5.0f;
    style.ScrollbarRounding = 12.0f;
    style.GrabRounding = 5.0f;
    style.WindowBorderSize = 1.0f;
    style.FrameBorderSize = 1.0f;
    style.PopupBorderSize = 1.0f;
    style.WindowPadding = ImVec2(10, 10);

    // Colores estilo Mario Galaxy
    ImVec4* colors = style.Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.1f, 1.0f);       // Fondo ventana, azul oscuro
    colors[ImGuiCol_TitleBg] = ImVec4(0.1f, 0.1f, 0.4f, 1.0f);        // Fondo título, morado
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.2f, 0.2f, 0.6f, 1.0f);  // Fondo título activo
    colors[ImGuiCol_FrameBg] = ImVec4(0.0f, 0.0f, 0.2f, 1.0f);        // Fondo cuadro, azul oscuro
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.4f, 0.4f, 0.9f, 0.6f); // Fondo cuadro hover
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.6f, 0.6f, 1.0f, 0.6f);  // Fondo cuadro activo
    colors[ImGuiCol_Button] = ImVec4(0.2f, 0.2f, 0.5f, 1.0f);         // Color de botón
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.3f, 0.3f, 0.7f, 1.0f);  // Color de botón hover
    colors[ImGuiCol_ButtonActive] = ImVec4(0.4f, 0.4f, 0.8f, 1.0f);   // Color de botón activo
    colors[ImGuiCol_Text] = ImVec4(0.9f, 0.9f, 0.9f, 1.0f);           // Color de texto blanco
    colors[ImGuiCol_Border] = ImVec4(0.6f, 0.6f, 0.9f, 0.7f);         // Color borde, azul claro
    colors[ImGuiCol_CheckMark] = ImVec4(0.8f, 0.8f, 1.0f, 1.0f);      // Color marca de check
    colors[ImGuiCol_SliderGrab] = ImVec4(0.6f, 0.6f, 1.0f, 1.0f);     // Color de deslizador
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.8f, 0.8f, 1.0f, 1.0f); // Color deslizador activo
}

void GraphicsWindow::displayInImGui() {
    setCustomGUIStyle();  // Llama a la función para aplicar estilo
    const sf::Texture& texture = m_renderTexture.getTexture();
    ImVec2 size(texture.getSize().x, texture.getSize().y);

    // Panel de la escena
    ImGui::Begin("Scene");
    ImGui::Image((void*)(intptr_t)texture.getNativeHandle(), size, ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
}

void
GraphicsWindow::update() {
    // Almacena deltaTime una vez
    deltaTime = clock.restart();

    // Usa deltaTime para actualizar ImGui
    ImGui::SFML::Update(*m_sfWindow, deltaTime);
}

void GraphicsWindow::render() {
    ImGui::SFML::Render(*m_sfWindow);
}

void
GraphicsWindow::shutdown() {
    ImGui::SFML::Shutdown();
    SAFE_PTR_RELEASE(m_sfWindow);
}
