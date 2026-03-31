#include "ui/game_window.h"

GameWindow::GameWindow(int width, int height, const std::string &title)
    : m_window(sf::VideoMode(width, height), title) {
        m_window.setFramerateLimit(60);
}

GameWindow::~GameWindow() {
    if (m_window.isOpen()) {
        m_window.close();
    }
}

bool GameWindow::isOpen() const {
    return m_window.isOpen();
}

void GameWindow::pollEvents() {
    sf::Event event;
    // Poll for events
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
        }
    }
}

void GameWindow::render() {
    // Clear the screen with a casino green background color
    m_window.clear(sf::Color(34, 139, 34));

    // TODO: Draw the slot & UI components

    // Display window
    m_window.display();
}

sf::RenderWindow& GameWindow::getWindow() {
    return m_window;
}