#include "Character.h"


Character::Character(){
    this->movementSpeed = 5.0f;
    this->grassY = 495.0f;
    this->gravitationForce = 0.4f;
    this->isInTheAir = false;
    this->isGettingDamage = false;
    this->isFalling = false;
    this->isLookingRight = true;
    this->initTexture();
    this->initSprite();
    this->hp = 10000;
    this->clock.restart();
}

Character::~Character(){
}


void Character::render(sf::RenderTarget& target){
     if (this->isInTheAir && this->isLookingRight){
        this->sprite.setTexture(this->jumpTexture);
    } else if (this->isInTheAir && !this->isLookingRight) {
        this->sprite.setTexture(this->jumpTextureLeft);
    } else if (this->isInTheAir){
        this->sprite.setTexture(this->jumpTexture);
    } else if (this->isMovingRight){
        
        if (this->sprite.getTexture() == &this->movingRightTexture){
            this->sprite.setTexture(this->movingRight2Texture);
        } else{
            this->sprite.setTexture(this->movingRightTexture);
        }
    } else if (this->isMovingLeft){
        
        if (this->sprite.getTexture() == &this->movingLeftTexture){
            this->sprite.setTexture(this->movingLeft2Texture);
        } else{
            this->sprite.setTexture(this->movingLeftTexture);
        }
    } else if (this->isLookingRight){
        this->sprite.setTexture(this->texture);
    } else {
        this->sprite.setTexture(this->textureLeft);
    }
    target.draw(this->sprite);
}

void Character::update(){

}

void Character::initSprite(){
    this->scaleCoeff = 0.6f;
    this->sprite.setTexture(this->texture);
    this->sprite.setScale(sf::Vector2f(this->scaleCoeff, this->scaleCoeff));
    this->sprite.setPosition(sf::Vector2f(400.0f - this->texture.getSize().x / 2 * this->scaleCoeff, this->grassY - this->texture.getSize().y * this->scaleCoeff));
}

void Character::initTexture(){
    this->texture.loadFromFile("images/front_pers.png");
    this->textureLeft.loadFromFile("images/front_pers_left.png");
    this->jumpTexture.loadFromFile("images/jump_pers.png");
    this->jumpTextureLeft.loadFromFile("images/jump_pers2.png");
    this->movingRightTexture.loadFromFile("images/run1_right.png");
    this->movingRight2Texture.loadFromFile("images/run2_right.png");
    this->movingLeftTexture.loadFromFile("images/run1_left.png");
    this->movingLeft2Texture.loadFromFile("images/run2_left.png");
}


void Character::move(const float dirX, const float dirY){
    this->sprite.move(sf::Vector2f(this->movementSpeed * dirX, this->movementSpeed * dirY));
}

void Character::applyGravitationForce(){
    if (this->sprite.getGlobalBounds().top < 100){
        this->isFalling = true;
    }

    if (this->isInTheAir){
        if (this->sprite.getPosition().y < this->grassY){
            sprite.move(sf::Vector2f(0.f, this->gravitationForce * 10.f));
        }
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            this->isFalling = true;
        }
        
    }
    if (this->sprite.getPosition().y > this->grassY - this->texture.getSize().y * this->scaleCoeff){
        this->isInTheAir = false;
        this->isFalling = false;
        this->sprite.setPosition(sf::Vector2f(this->sprite.getPosition().x, this->grassY - this->texture.getSize().y * this->scaleCoeff));
    }
}


int Character::getHp(){
    return this->hp;
}

void Character::updateHp(float newHp){
    this->hp = newHp;
}

bool Character::canAttack(){
    
    if (this->clock.getElapsedTime().asMilliseconds() < 100){
        return false;
    } else {
        this->clock.restart();
        return true;
    }
}