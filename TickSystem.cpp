#include "TickSystem.h"
#include "EngineHandler.h"
#include "Timer.h"

TickSystem::TickSystem() : m_timer(new Timer(.1f)), m_tick(0)
{
    EngineHandler::onEarlyUpdate += EventHandler::bind(&TickSystem::update, this);
}
TickSystem::~TickSystem()
{
    EngineHandler::onEarlyUpdate -= EventHandler::bind(&TickSystem::update, this);
}

void TickSystem::update()
{
    if (m_timer->isTimerComplete())
    {
        m_tick++;

        onMiniEvent();
        if (m_tick % 2 == 0) onSmallEvent();
        if (m_tick % 5 == 0) onLittleEvent();
        if (m_tick % 10 == 0) onTickEvent();
        if (m_tick % 50 == 0) onLongEvent();
    }
}