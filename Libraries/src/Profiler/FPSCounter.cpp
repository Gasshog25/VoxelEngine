#include "FPSCounter.h"


FPSCounter::FPSCounter() :
    fps(0),
    elapseTime(0),
    lastTime(std::chrono::high_resolution_clock::now())
{ 
    this->fpsBuffer.Init(this->BufferSize);
    this->elapseTimeBuffer.Init(this->BufferSize);
}

void FPSCounter::Destroy() {
    this->fpsBuffer.Destroy();
    this->elapseTimeBuffer.Destroy();
}

void FPSCounter::newFrame(int maxFPS) {
    frame++;
    // Calcul ElapseTime
    auto currentTime = std::chrono::high_resolution_clock::now();
    this->elapseTime = currentTime - this->lastTime;
    this->fps = 1.0e9 / this->elapseTime.count();

    // Sleep if needed
    auto timeToWait = std::chrono::duration<double>(1.0 / maxFPS -  1.1 / (this->avgFps * 0.5 + this->fps * 0.5));
    if (timeToWait.count() > 0) {
        std::this_thread::sleep_for(std::chrono::duration_cast<std::chrono::milliseconds>(timeToWait));
	
        // Update FPS
        currentTime = std::chrono::high_resolution_clock::now();
        auto elapse = currentTime - this->lastTime;
        this->fps = 1.0e9 / elapse.count();
    }

    // Update lastTime
    this->lastTime = currentTime;
    
    // Update Buffers
    this->updateBuffers();
}



void FPSCounter::updateBuffers() {
    
    this->fpsBuffer.push(this->fps);
    this->elapseTimeBuffer.push(this->elapseTime.count());
}


void FPSCounter::UpdateStat() {
    this->avgFps = this->fpsBuffer.getAverage();
    this->maxFps = this->fpsBuffer.getMax();
    this->minFps = this->fpsBuffer.getMin();
    
    this->avgElapseTimens = this->elapseTimeBuffer.getAverage();
    this->maxElapseTimens = this->elapseTimeBuffer.getMax();
    this->minElapseTimens = this->elapseTimeBuffer.getMin();
}   