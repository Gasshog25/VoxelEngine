#include "FPSCounter.h"


FPSCounter::FPSCounter() :
    fps(0),
    elapseTime(0),
    lastTime(std::chrono::high_resolution_clock::now())
{ 
    this->fpsBuffer = RingBuffer<double>(100);
    this->elapseTimeBuffer = RingBuffer<double>(100);
}

void FPSCounter::newFrame() {
    this->lastTime = std::chrono::high_resolution_clock::now();
}

void FPSCounter::endFrame() {
    auto currentTime = std::chrono::high_resolution_clock::now();
    this->elapseTime = currentTime - this->lastTime;
    this->fps = 1.0e9 / this->elapseTime.count();
}

void FPSCounter::endFrame(int maxFPS) {
    this->endFrame();

    auto timeToWait = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(1.0 / maxFPS) - this->elapseTime);
    if (timeToWait.count() > 0) {
        std::this_thread::sleep_for(timeToWait);
    }
    auto elapse = std::chrono::high_resolution_clock::now() - this->lastTime;
    this->fps = 1.0e9 / elapse.count();
}


void FPSCounter::updateBuffers() {
    this->fpsBuffer.push(this->fps);
    this->elapseTimeBuffer.push(this->elapseTime.count());
}