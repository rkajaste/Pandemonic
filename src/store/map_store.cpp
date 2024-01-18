#include "store/map_store.h"

std::string MapStore::collisionContext = "";

void MapStore::setCollisionContext(std::string newContext)
{
    collisionContext = newContext;
}

std::string MapStore::getCollisionContext()
{
    return collisionContext;
}