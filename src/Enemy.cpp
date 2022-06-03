#include "Enemy.h"

Enemy::Enemy(float x, float y){
    this->hp = 100;
    this->isCounted = false;
    this->initTexture();
    this->sprite.setTexture(this->texture);
    this->sprite.setScale(0.8f, 0.8f);
    this->sprite.setPosition(sf::Vector2f(x, y));

    this->font.loadFromFile("fonts/font.TTF");
    this->hpText.setFont(this->font);
    this->hpText.setCharacterSize(50);
    this->hpText.setFillColor(sf::Color::Red);
    this->clock.restart();
}

Enemy::~Enemy(){
}

void Enemy::initTexture(){
    this->texture.loadFromFile("images/bee.png");
}

const sf::FloatRect Enemy::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

float Enemy::getHp(){
    return this->hp;
}

void Enemy::updateHp(int newHp){
    this->hp = newHp;
}

bool Enemy::isInWindow(){
    if (this->getBounds().left < 1920.f && this->getBounds().left + this->getBounds().width > 0.f){
        return true;
    } else {
        return false;
    }
}

bool Enemy::canAttack(){
    
    if (this->clock.getElapsedTime().asMilliseconds() < 2000){
        return false;
    } else {
        this->clock.restart();
        return true;
    }
}

bool Enemy::isAlive(){
    if (this->hp > 0){
        return true;
    } else {
        return false;
    }
}