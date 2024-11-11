﻿#pragma once
#include "Prerequisites.h"

class NotificationService {
private:
    // Constructor privado para evitar instancias m�ltiples
    NotificationService() {}
    // Eliminar el operador de copia y asignaci�n para evitar duplicaciones
    NotificationService(const NotificationService&) = delete;
    NotificationService& operator=(const NotificationService&) = delete;
public:
    static NotificationService& getInstance() {
        static NotificationService instance;
        return instance;
    }
    void addMessage(ConsolErrorType code, const std::string& message) {
        m_programMessages[code].push_back(message);
    }

    // Agregar un mensaje informativo
    void Log(const std::string& message) {
        ConsolErrorType code = ConsolErrorType::NORMAL;
        m_programMessages[code].push_back(message);
    }
    std::string getMessage(ConsolErrorType code) const {
        auto it = m_programMessages.find(code);
        if (it != m_programMessages.end()) {
            std::string combinedMessages;
            for (const auto& message : it->second) {
                combinedMessages += message + "\n";
            }
            return combinedMessages;
        }
        else {
            return "Message not found";
        }
    }
    void showAllMessages() const {
        for (const auto& pair : m_programMessages) {
            std::cout << "Code: " << pair.first << " - Messages: " << std::endl;
            for (const auto& message : pair.second) {
                std::cout << "   " << message << std::endl;
            }
        }
    }
    // M�todo para guardar los mensajes en un archivo
    void saveMessagesToFile(const std::string& filename) const {
      std::ofstream file(filename);
      if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo para guardar los mensajes." << std::endl;
        return;
      }
      for (const auto& pair : m_programMessages) {
        file << "Code: " << pair.first << " - Messages: " << std::endl;
        for (const auto& message : pair.second) {
          file << "   " << message << "\n";
        }
      }
      file.close();
      std::cout << "Mensajes guardados en el archivo: " << filename << std::endl;
    }

    std::map<ConsolErrorType, std::vector<std::string>>& getNotifications() {
        return m_programMessages;
    }
private:
    // Mapa para almacenar los mensajes del programa, cada c�digo de error tiene una lista de mensajes
    std::map<ConsolErrorType, std::vector<std::string>> m_programMessages;
};