#include "CooldownManager.hpp"

void CooldownManager::advanceCooldowns(GLfloat dt)
{
    for (Cooldowns::iterator element = cooldowns.begin(); element != cooldowns.end(); ++element)
    {
        GLfloat timer = cooldowns[element->first]["timer"];
        GLfloat cooldown = cooldowns[element->first]["cooldown"];
        cooldowns[element->first]["timer"] += 100.0f * dt;
        if (timer >= cooldown) {
            cooldowns[element->first]["timer"] = cooldown;
        }
    }
}

void CooldownManager::setCooldown(std::string action)
{
    cooldowns[action]["timer"] = 0.0f;
}

void CooldownManager::clearCooldown(std::string action)
{
    cooldowns[action]["timer"] = cooldowns[action]["cooldown"];
}

GLboolean CooldownManager::hasCooldown(std::string action)
{
    return cooldowns[action]["timer"] < cooldowns[action]["cooldown"];
}