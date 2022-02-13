#include "Player.hpp"

Player::Player(glm::vec2 coords, SpriteRenderer *renderer) : Sprite{coords, renderer}
{
    this->hitboxSize = glm::vec2(32.0f, 128.0f);
    this->spriteSize = glm::vec2(255.0f, 170.0f);
    this->animator = new Animator(this->spriteSize);
    this->respawnCoords = coords;
    this->health = 50;
    this->maxHealth = 100;
    this->mana = 30;
    this->maxMana = 30;
    this->speed = 600.0f;
    this->jumpForce = 1100.0f;

    Cooldowns cooldowns = {
        {"attack",
         {{"timer", 0.0f},
          {"cooldown", 30.0f}}},
        {"aerial_slash",
         {{"timer", 0.0f},
          {"cooldown", 200.0f}}},
        {"switch_stance",
         {{"timer", 0.0f},
          {"cooldown", 100.0f}}},
        {"dialog",
         {{"timer", 0.0f},
          {"cooldown", 60.0f}}},
        {"entrance_interaction",
         {{"timer", 0.0f},
          {"cooldown", 30.0f}}},
    };
    this->cooldownManager = new CooldownManager(cooldowns);
    this->updateStore();
}

void Player::updateStore()
{
    PlayerStats status;
    status.currentHP = this->health;
    status.currentMP = this->mana;
    status.maxHP = this->maxHealth;
    status.maxMP = this->maxMana;

    PlayerStore::setPlayerStats(status);
}

void Player::update(GLfloat dt)
{
    this->enableGravity(dt);
    this->handleIdling();
    if (this->hasState(GROUNDED))
    {
        this->cooldownManager->clearCooldown("aerial_slash");
    }
    else
    {
        if (this->hasState(FALLING))
        {
            if (this->gravityForce > 0)
            {
                this->textureName = "player_fall";
                if (this->hasState(ATTACK_STANCE))
                {
                    this->textureName = "player_unsheathed_fall";
                }
            }
            else
            {
                this->textureName = "player_jump";
                if (this->hasState(ATTACK_STANCE))
                {
                    this->textureName = "player_unsheathed_jump";
                }
            }
        }
    }
    if (!this->hasState(AERIAL_ATTACKING) && !this->hasState(ATTACKING))
    {
        this->handleMoving(dt);
    }
    this->handleJumping();
    this->handleStanceSwitching();
    this->handleAttacking();
    this->checkMapObjectsCollisions();

    Sprite::update(dt);
    if (this->health <= 0)
    {
        this->die();
    }
}

void Player::checkMapObjectsCollisions()
{
    this->collidedEntrance = "";

    for (const auto &mapObject : MapManager::getInteractionObjects())
    {
        glm::vec2 objSize(mapObject->GetWidth(), mapObject->GetHeight());
        glm::vec2 objCoords(mapObject->GetX(), mapObject->GetY());

        if (Physics::collides(this->coords, this->hitboxSize, objCoords, objSize))
        {
            // do something
            if (mapObject->GetName() == "entrance")
            {
                this->collidedEntrance = mapObject->GetProperties().GetStringProperty("entrance_to");
            }
        }
    }

    for (const auto &mapObject : MapManager::getLevelTransitionObjects())
    {
        glm::vec2 objSize(mapObject->GetWidth(), mapObject->GetHeight());
        glm::vec2 objCoords(mapObject->GetX(), mapObject->GetY());

        if (Physics::collides(this->coords, this->hitboxSize, objCoords, objSize))
        {
            const std::string levelTransition = mapObject->GetProperties().GetStringProperty("level_transition");
            const std::string playerSpawn = mapObject->GetProperties().GetStringProperty("player_spawn");
            MapManager::loadMap(levelTransition);
            this->coords = MapManager::getPlayerSpawnPoint(playerSpawn);
            this->respawnCoords = this->coords;
        }
    }

    for (const auto &mapObject : MapManager::getNpcObjects())
    {
        glm::vec2 objSize(mapObject->GetWidth(), mapObject->GetHeight());
        glm::vec2 objCoords(mapObject->GetX(), mapObject->GetY());

        if (Physics::collides(this->coords, this->hitboxSize, objCoords, objSize))
        {
            if (!DialogStore::isDialogOpen())
            {
                std::string dialogueIdentifier = mapObject->GetProperties().GetStringProperty("dialogue");
                DialogStore::setDialogIdentifer(dialogueIdentifier);
            }
        }
    }
}

void Player::handleInput(std::map<UserInput, GLboolean> keys)
{

    if (keys[MOVE_RIGHT] && !this->hasState(AERIAL_ATTACKING))
    {
        this->direction = 1;
        this->removeState(IDLE);
        this->addState(MOVING);
    }
    else if (keys[MOVE_LEFT] && !this->hasState(AERIAL_ATTACKING))
    {
        this->direction = -1;
        this->removeState(IDLE);
        this->addState(MOVING);
    }

    if (!keys[MOVE_RIGHT] && !keys[MOVE_LEFT])
    {
        this->removeState(MOVING);
        this->addState(IDLE);
    }

    if (keys[JUMP] && this->hasState(GROUNDED))
    {
        this->addState(JUMPING);
    }

    if (
        keys[SWITCH_STANCE] &&
        !this->hasState(SWITCHING_STANCE) &&
        !this->hasState(ATTACKING) &&
        !this->cooldownManager->hasCooldown("switch_stance"))
    {
        this->cooldownManager->setCooldown("switch_stance");
        if (this->hasState(ATTACK_STANCE))
        {
            this->addState(SWITCHING_STANCE);
            this->addState(SWITCHING_TO_IDLE_STANCE);
        }
        else
        {
            this->addState(SWITCHING_STANCE);
            this->addState(SWITCHING_TO_ATTACK_STANCE);
        }
    }

    if (keys[ATTACK] && this->hasState(ATTACK_STANCE) && !this->hasState(SWITCHING_STANCE))
    {
        if (!this->hasState(JUMPING) && !this->hasState(FALLING))
        {
            if (!this->cooldownManager->hasCooldown("attack"))
            {
                this->removeState(IDLE);
                this->addState(ATTACKING);
            }
        }
        else if (this->hasState(FALLING))
        {
            if (!this->cooldownManager->hasCooldown("aerial_slash"))
            {
                this->removeState(IDLE);
                this->addState(AERIAL_ATTACKING);
            }
        }
    }

    if (keys[INTERACT])
    {
        if (DialogStore::getDialogIdentifier() != "")
        {
            if (!this->cooldownManager->hasCooldown("dialog"))
            {
                if (DialogStore::isDialogOpen())
                {
                    if (DialogStore::hasDebounceFinished())
                    {
                        DialogStore::advanceDialog();
                    }
                    else
                    {
                        DialogStore::skipDebounce();
                    }

                    if (DialogStore::isDialogFinished())
                    {
                        DialogStore::closeDialog();
                    }
                }
                else
                {
                    DialogStore::openDialog();
                }
                this->cooldownManager->setCooldown("dialog");
            }
        }
        if (this->collidedEntrance != "" && !this->cooldownManager->hasCooldown("entrance_interaction"))
        {
            bool playerHasEntered = Util::existsInVector(MapStore::getCollisionContext(), MapManager::getVisibleLayers());

            if (!playerHasEntered)
            {
                MapStore::setCollisionContext(this->collidedEntrance);
            }
            std::string interiorLayer = MapStore::getCollisionContext();
            std::string exteriorLayer = interiorLayer.substr(0, interiorLayer.find("_interior"));

            MapManager::setLayerVisibility(interiorLayer, !playerHasEntered);
            MapManager::setLayerVisibility(exteriorLayer, playerHasEntered);

            if (playerHasEntered)
            {
                MapStore::setCollisionContext("");
            }

            this->cooldownManager->setCooldown("entrance_interaction");
        }
    }
}

void Player::handleIdling()
{
    if (this->hasState(IDLE))
    {
        this->textureName = "player_idle";

        if (this->hasState(ATTACK_STANCE))
        {
            this->textureName = "player_idle_attack_stance";
        }
    }
}

void Player::handleMoving(GLfloat dt)
{
    if (this->hasState(MOVING))
    {
        this->move(dt);
        if (this->hasState(GROUNDED))
        {
            this->textureName = "player_run";
            if (this->hasState(ATTACK_STANCE))
            {
                this->textureName = "player_run_attack_stance";
            }
        }
    }
}

void Player::handleJumping()
{
    if (this->hasState(JUMPING))
    {
        this->jump();
    }
}

void Player::handleStanceSwitching()
{
    this->removeState(IDLE);
    if (this->hasState(SWITCHING_TO_ATTACK_STANCE))
    {
        this->textureName = "player_unsheathe";

        if (this->animator->hasAnimationFinished(this->textureName))
        {
            this->removeState(SWITCHING_STANCE);
            this->removeState(SWITCHING_TO_ATTACK_STANCE);
            this->addState(ATTACK_STANCE);
            this->addState(IDLE);
        }
    }
    else if (this->hasState(SWITCHING_TO_IDLE_STANCE))
    {
        this->textureName = "player_sheathe";

        if (this->animator->hasAnimationFinished(this->textureName))
        {
            this->removeState(SWITCHING_STANCE);
            this->removeState(SWITCHING_TO_IDLE_STANCE);
            this->removeState(ATTACK_STANCE);
            this->addState(IDLE);
        }
    }
}

void Player::handleAttacking()
{
    if (this->hasState(ATTACK_STANCE))
    {
        if (this->hasState(ATTACKING))
        {
            this->textureName = "player_attack";
            if (this->animator->hasAnimationFinished(this->textureName) || !this->hasState(GROUNDED))
            {
                this->removeState(ATTACKING);
                this->addState(IDLE);
                this->cooldownManager->setCooldown("attack");
            }
        }
        else if (this->hasState(AERIAL_ATTACKING))
        {
            this->textureName = "player_aerial_slash";
            this->gravityForce = -60;
            if (this->animator->hasAnimationFinished(this->textureName))
            {
                this->removeState(AERIAL_ATTACKING);
                this->addState(IDLE);
                this->cooldownManager->setCooldown("aerial_slash");
            }
        }
    }
}

void Player::takeDamage(GLint damage)
{
    this->health -= damage;
    this->updateStore();
}

void Player::die()
{
    this->coords = this->respawnCoords;
    this->health = this->maxHealth;
    this->updateStore();
}