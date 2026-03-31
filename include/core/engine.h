#pragma once
#include "ui/game_window.h"
#include <memory>

class Engine {
public:
    Engine();
    ~Engine();

    void run();

private:
    void update();
    void render();

    std::unique_ptr<GameWindow> m_window;
};