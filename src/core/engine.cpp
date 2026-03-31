#include "core/engine.h"

Engine::Engine() {
    // initialize the window from the game_config.json
    m_window = std::make_unique<GameWindow>(800, 600, "The Slot Game");
}

Engine::~Engine() = default;

void Engine::run() {
    while (m_window->isOpen()) {
        m_window->pollEvents();
        update();
        render();
    }
}

void Engine::update() {
    // TODO: ADD GAME LOGIC (SPINNING REELS, CHECKING PAYLINES, ETC.)
}

void Engine::render() {
    // Have the window draw itself
    m_window->render();
}