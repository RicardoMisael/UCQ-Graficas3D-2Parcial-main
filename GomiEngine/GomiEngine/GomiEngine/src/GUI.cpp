#include "UserInterface.h"
#include "GameWindow.h"
#include "GameEntity.h"
#include "TransformComponent.h"
#include "Services/MessageSystem.h"

void
UserInterface::initialize() {
	// Configuración de estilo de la interfaz
	configureStyle();
}

void UserInterface::update()
{
}

void UserInterface::renderUI()
{
}

void
UserInterface::cleanup() {
}

void
UserInterface::configureStyle() {
	ImGuiStyle& currentStyle = ImGui::GetStyle();
	ImVec4* colorPalette = currentStyle.Colors;

	// Colores ajustados al estilo oscuro
	colorPalette[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);  // Fondo de ventana
	colorPalette[ImGuiCol_Border] = ImVec4(0.40f, 0.40f, 0.40f, 0.50f);  // Bordes
	colorPalette[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);  // Fondo de cuadros
	colorPalette[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);  // Hover sobre cuadros
	colorPalette[ImGuiCol_FrameBgActive] = ImVec4(0.34f, 0.34f, 0.34f, 1.00f);  // Cuadro activo
	colorPalette[ImGuiCol_TitleBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);  // Fondo del título
	colorPalette[ImGuiCol_TitleBgActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);  // Título activo
	colorPalette[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);  // Fondo de la barra de menús
	colorPalette[ImGuiCol_Button] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);  // Botón inactivo
	colorPalette[ImGuiCol_ButtonHovered] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);  // Botón hover
	colorPalette[ImGuiCol_ButtonActive] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);  // Botón activo
	colorPalette[ImGuiCol_Text] = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);  // Texto principal
	colorPalette[ImGuiCol_TextDisabled] = ImVec4(0.55f, 0.55f, 0.55f, 1.00f);  // Texto deshabilitado
	colorPalette[ImGuiCol_Header] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);  // Encabezado
	colorPalette[ImGuiCol_HeaderHovered] = ImVec4(0.34f, 0.34f, 0.34f, 1.00f);  // Encabezado hover
	colorPalette[ImGuiCol_HeaderActive] = ImVec4(0.45f, 0.45f, 0.45f, 1.00f);  // Encabezado activo
	colorPalette[ImGuiCol_ScrollbarBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);  // Fondo scrollbar
	colorPalette[ImGuiCol_ScrollbarGrab] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);  // Scrollbar inactivo
	colorPalette[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f); // Scrollbar hover
	colorPalette[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f); // Scrollbar activo
	colorPalette[ImGuiCol_CheckMark] = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);  // Marca de check

	// Ajustes de estilo general
	currentStyle.WindowRounding = 5.0f;   // Redondeo de bordes de ventanas
	currentStyle.FrameRounding = 5.0f;   // Redondeo de bordes de cuadros
	currentStyle.ScrollbarRounding = 5.0f;   // Redondeo de bordes de scrollbar
	currentStyle.GrabRounding = 5.0f;   // Redondeo de bordes de botones de agarrar
	currentStyle.FrameBorderSize = 1.0f;   // Grosor del borde de cuadros
	currentStyle.WindowBorderSize = 1.0f;   // Grosor del borde de ventanas
	currentStyle.PopupBorderSize = 1.0f;   // Grosor del borde de popups
}

void
UserInterface::consoleWindow(const std::map<ConsoleMessageType, std::vector<std::string>>& systemMessages) {
	ImGui::Begin("Console");
	static ImGuiTextFilter messageFilter; // Filtro de búsqueda
	messageFilter.Draw("Filter (\"error\", \"warning\", etc.)", 180.0f);
	ImGui::Separator();
	ImGui::BeginChild("MessageArea", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
	for (const auto& entry : systemMessages) {
		// Establece color según el tipo de mensaje
		ImVec4 textColor;
		switch (entry.first) {
		case ConsoleMessageType::ERROR:
			textColor = ImVec4(1.0f, 0.4f, 0.4f, 1.0f); // Rojo para errores
			break;
		case ConsoleMessageType::WARNING:
			textColor = ImVec4(1.0f, 1.0f, 0.4f, 1.0f); // Amarillo para advertencias
			break;
		case ConsoleMessageType::INFO:
		default:
			textColor = ImVec4(0.8f, 0.8f, 0.8f, 1.0f); // Gris para mensajes informativos
			break;
		}
		for (const auto& message : entry.second) {
			if (!messageFilter.PassFilter(message.c_str())) continue; // Filtrar mensajes según el filtro
			ImGui::PushStyleColor(ImGuiCol_Text, textColor);
			ImGui::Text("[%d] %s", entry.first, message.c_str());
			ImGui::PopStyleColor();
		}
	}
	if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
		ImGui::SetScrollHereY(1.0f);
	ImGui::EndChild();
	ImGui::End();
}

void UserInterface::actorHierarchy(const std::vector<EngineUtilities::TSharedPointer<GameEntity>>& entities, int& selectedEntityIndex) {
	ImGui::Begin("Actor Hierarchy");

	for (int i = 0; i < entities.size(); ++i) {
		if (!entities[i].isNull()) {
			if (ImGui::Selectable(entities[i]->getName().c_str(), selectedEntityIndex == i)) {
				selectedEntityIndex = i;  // Establecer actor seleccionado
			}
		}
	}

	ImGui::End();
}

void UserInterface::entityInspector(EngineUtilities::TSharedPointer<GameEntity> selectedEntity) {
	if (selectedEntity.isNull()) return;

	ImGui::Begin("Entity Inspector");

	ImGui::Text("Entity: %s", selectedEntity->getName().c_str());

	auto transformComp = selectedEntity->getComponent<TransformComponent>();
	if (!transformComp.isNull()) {
		sf::Vector2f position = transformComp->getPosition();
		sf::Vector2f scale = transformComp->getScale();

		// Mostrar y editar posición
		if (ImGui::InputFloat2("Position", reinterpret_cast<float*>(&position))) {
			transformComp->setPosition(position);
		}

		// Mostrar y editar escala
		if (ImGui::InputFloat2("Scale", reinterpret_cast<float*>(&scale))) {
			transformComp->setScale(scale);
		}

	}

	ImGui::End();
}

void UserInterface::actorCreationDialog(std::vector<EngineUtilities::TSharedPointer<GameEntity>>& entities) {
	static char entityName[128] = "";  // Nombre temporal del actor
	static int selectedShape = 0;     // 0: Rectángulo, 1: Círculo, 2: Triángulo

	ImGui::Begin("Create Actor");

	// Selección de nombre
	ImGui::InputText("Name", entityName, sizeof(entityName));

	// Selección de forma
	ImGui::Combo("Shape", &selectedShape, "Rectangle\0Circle\0Triangle\0");

	if (ImGui::Button("Create Actor")) {
		if (entityName[0] == '\0') {
			MessageSystem::sendErrorMessage("Please enter a valid name for the actor!");
		}
		else {
			std::string name(entityName);
			EngineUtilities::TSharedPointer<GameEntity> newEntity = std::make_shared<GameEntity>(name, selectedShape);
			entities.push_back(newEntity);
			MessageSystem::sendInfoMessage("Actor created successfully.");
		}
	}

	ImGui::End();
}
