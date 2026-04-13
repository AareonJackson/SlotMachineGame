#include "ui/game_window.h"
#include "core/rng.h"
#include <iostream>

GameWindow::GameWindow(int width, int height, const std::string &title)
    : m_window(sf::VideoMode(width, height), title) {
        m_window.setFramerateLimit(60);

        // Calculate a centered position for the 600x400 reel grid
        float gridWidth = 600.0f;
        float gridHeight = 400.0f;
        float startX = (width - gridWidth) / 2.0f;
        float startY = 50.0f; // Padding front the top

        m_reelView = std::make_unique<ReelView>(3, 3, startX, startY, gridWidth, gridHeight);

        // Setup initial dummy symbols so the grid looks populated when launching
        std::vector<std::vector<std::string>> initialSymbols = {
            {"SEVEN", "CHERRY", "BAR"},
            {"LEMON", "BELL", "SEVEN"},
            {"CHERRY", "BAR", "BELL"}
        };
    m_reelView->updateSymbols(initialSymbols);

    // Spin button setup
    float btnWidth = 200.0f;
    float btnHeight = 60.0f;
    float btnX = (width - btnWidth) / 2.0f; // Centered
    float btnY = startY + gridHeight + 40.0f; // Placed below the reels

    m_spinButton = std::make_unique<Button>(btnX, btnY, btnWidth, btnHeight, "SPIN!");

    // Define a spin click
    m_spinButton->setOnClick([this]() {
        std::cout << "Spin Button Clicked! Generating random spin..." << std::endl;
        // Secure random number generator
        RNG rng;

        // Define the available symbols on the slot machine
        std::vector<std::string> possibleSymbols = {"SEVEN", "CHERRY", "BAR", "LEMON", "BELL"};

        // A 3x3 matrix for the new spin
        std::vector<std::vector<std::string>> newSymbols(3, std::vector<std::string>(3));

        // Randomly fill the matrix using the RNG
        for (int reel = 0; reel < 3; ++reel) {
            for (int row = 0; row < 3; ++row) {
                int randomIndex = rng.getRandomInt(0, possibleSymbols.size() - 1);
                newSymbols[reel][row] = possibleSymbols[randomIndex];
            }
        }

        // Update the UI
        m_reelView->updateSymbols(newSymbols);
    });
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

        // Pass events to UI components
        if (m_spinButton) {
            m_spinButton->handleEvent(event, m_window);
        }
    }
    // Update UI components
    if (m_spinButton) {
        m_spinButton->update(sf::Mouse::getPosition(m_window));
    }
}

void GameWindow::render() {
    // Clear the screen with a casino green background color
    m_window.clear(sf::Color(34, 139, 34));

    // Draw the slot reels
    if (m_reelView) {
        m_reelView->draw(m_window);
    }

    if (m_spinButton) {
        m_spinButton->draw(m_window);
    }

    // Display window
    m_window.display();
}

sf::RenderWindow& GameWindow::getWindow() {
    return m_window;
}