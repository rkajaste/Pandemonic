#pragma once
#include <string>
#include <map>
#include <glad/glad.h>

typedef std::map<std::string, std::map<std::string, GLfloat>> Cooldowns; // {action: {timer: float, cooldown: float}}

class CooldownManager {
    public:
        CooldownManager(Cooldowns cooldowns): cooldowns(cooldowns){};

        void advanceCooldowns(GLfloat dt);
        void setCooldown(std::string action);
        void clearCooldown(std::string action);
        GLboolean hasCooldown(std::string action);
    private:
        Cooldowns cooldowns;
};
