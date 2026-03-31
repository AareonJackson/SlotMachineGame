#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class GameWindow {
public:
    GameWindow(int width, int height, const std::string& title);
    ~GameWindow();

    bool isOpen() const;
    void pollEvents();
    void render();

    // Getter just in case I want to pass the window to other UI components later
    sf::RenderWindow& getWindow();

private:
    sf::RenderWindow m_window;
};
