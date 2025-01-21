#include <thread>
#include <chrono>

#include "RingBuffer.h"

class FPSCounter
{
public:
    FPSCounter();

    void newFrame();
    void endFrame();
    void endFrame(int maxFPS);
    
public:
    double getFPS() { return this->fps; };
    
    std::chrono::duration<double, std::nano> getElapseTime() { return this->elapseTime; };
    double getElapseTimeInSeconds() { return this->elapseTime.count() / 1e9; };
    double getElapseTimeInMilliseconds() { return this->elapseTime.count() / 1e6; };
    double getElapseTimeInMicroseconds() { return this->elapseTime.count() / 1e3; };
    double getElapseTimeInNanoseconds() { return this->elapseTime.count(); };
    
    double getAverageFPS() { return this->fpsBuffer.getAverage(); };
    double getAverageElapseTime() { return this->elapseTimeBuffer.getAverage(); };
    double getAverageElapseTimeInSeconds() { return this->elapseTimeBuffer.getAverage() / 1e9; };
    double getAverageElapseTimeInMilliseconds() { return this->elapseTimeBuffer.getAverage() / 1e6; };
    double getAverageElapseTimeInMicroseconds() { return this->elapseTimeBuffer.getAverage() / 1e3; };
    double getAverageElapseTimeInNanoseconds() { return this->elapseTimeBuffer.getAverage(); };

private:
    void updateBuffers();

private:
    double fps;
    std::chrono::duration<double, std::nano> elapseTime;

    std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;

    RingBuffer<double> fpsBuffer;
    RingBuffer<double> elapseTimeBuffer;
};