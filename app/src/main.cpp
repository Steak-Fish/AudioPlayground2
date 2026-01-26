#include <stdio.h>
#include <iostream>
#include <cmath>
#include <atomic>
#include <iostream>
#include <thread>

#include "Playground.hpp"
#include "imgui.h"
#include "engine.hpp"

void gameLogic(const Nova::FrameCtx&, void* userData) {
    Playground& playground = *reinterpret_cast<Playground*>(userData);

    playground.render();
}

int main(void) {

    Nova::EngineConfig config;
    Playground playground = Playground();
    config.userData = &playground;
    config.appMajorVer = 1;
    config.appMinorVer = 0;
    config.appPatchVer = 0;
    config.title = "Audio Playground 2";

    Nova::Engine engine(config);

    engine.loop(gameLogic);

    return 0;
}