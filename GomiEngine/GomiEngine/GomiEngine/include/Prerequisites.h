#pragma once

// Librerias STD
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <thread>
#include <map>
#include <fstream> 

// Third Parties
#include <SFML/Graphics.hpp>
#include "Memory\TSharedPointer.h"
#include "Memory\TWeakPointer.h"
#include "Memory\TStaticPtr.h"
#include "Memory\TUniquePtr.h"

// Imgui
#include <imgui.h>
#include <imgui-SFML.h>

// Enums
enum ShapeType {
    EMPTY = 0,
    CIRCLE = 1,
    RECTANGLE = 2,
    TRIANGLE = 3
};

enum ConsolErrorType {
    NORMAL = 0,
    WARNING = 1,
    ERROR = 2
};

// Macro para liberar recursos de manera segura
#define SAFE_PTR_RELEASE(x) if(x != nullptr) { delete x; x = nullptr; }

#define MESSAGE(classObj, method, state)                      \
{                                                             \
    std::ostringstream os_;                                   \
    os_ << classObj << "::" << method << " : "                \
        << "[CREACION DE RECURSO" << ": " << state << "] \n"; \
    std::cerr << os_.str();                                   \
}

#define ERROR(classObj, method, errorMSG)                         \
{                                                                 \
    std::ostringstream os_;                                       \
    os_ << "ERROR : " << classObj << "::" << method << " : "      \
        << " Error en los datos de los parametros [" << errorMSG << "] \n"; \
    std::cerr << os_.str();                                       \
    exit(1);                                                      \
}
