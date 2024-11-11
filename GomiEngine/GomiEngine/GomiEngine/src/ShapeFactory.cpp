#include "GeometricShapeFactory.h"

sf::Shape*
GeometricShapeFactory::generateShape(ShapeKind kindOfShape) {
    m_currentShapeType = kindOfShape;
    switch (kindOfShape) {
    case NONE: {
        return nullptr;
    }
    case CIRCLE: {
        sf::CircleShape* circleShape = new sf::CircleShape(10.0f);
        circleShape->setFillColor(sf::Color::White);
        m_currentShape = circleShape;
        return circleShape;
    }
    case RECTANGLE: {
        sf::RectangleShape* rectangleShape = new sf::RectangleShape(sf::Vector2(100.0f, 50.0f));
        rectangleShape->setFillColor(sf::Color::White);
        m_currentShape = rectangleShape;
        return rectangleShape;
    }
    case TRIANGLE: {
        sf::CircleShape* triangleShape = new sf::CircleShape(50.0f, 3);
        triangleShape->setFillColor(sf::Color::White);
        m_currentShape = triangleShape;
        return triangleShape;
    }
    default:
        return nullptr;
    }
}

void
GeometricShapeFactory::adjustPosition(float x, float y) {
    if (m_currentShape) {
        m_currentShape->setPosition(x, y);
    }
}

void
GeometricShapeFactory::adjustPosition(const sf::Vector2f& newPosition) {
    if (m_currentShape) {
        m_currentShape->setPosition(newPosition);
    }
}

void
GeometricShapeFactory::rotateShape(float angle) {
    if (m_currentShape) {
        m_currentShape->setRotation(angle);
    }
}

void
GeometricShapeFactory::scaleShape(const sf::Vector2f& scalingFactors) {
    if (m_currentShape) {
        m_currentShape->setScale(scalingFactors);
    }
}

void
GeometricShapeFactory::applyFillColor(const sf::Color& fillColor) {
    if (m_currentShape) {
        m_currentShape->setFillColor(fillColor);
    }
}
