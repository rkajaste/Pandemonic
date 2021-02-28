#pragma once

struct PlayerStats {
    int maxHP;
    int currentHP;
    int maxMP;
    int currentMP;
};

class PlayerStore {
    public:
        static PlayerStats getPlayerStats();
        static void setPlayerStats(PlayerStats);
    private:
        PlayerStore(){};

        static PlayerStats playerStats;
};
