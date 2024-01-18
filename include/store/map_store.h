#pragma once

#include <string>

class MapStore {
    public:
        static void setCollisionContext(std::string interior);
        static std::string getCollisionContext();
    private:
        MapStore(){};

        static std::string collisionContext;
};
