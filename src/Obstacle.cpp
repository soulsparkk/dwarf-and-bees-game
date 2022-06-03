#include "Obstacle.h"

Obstacle::Obstacle(float x, float y){
    this->initTexture();
    this->sprite.setTexture(this->texture);
    this->sprite.setScale(1.5f, 1.5f);
    this->sprite.setPosition(sf::Vector2f(x, y));
}

Obstacle::~Obstacle(){
}

void Obstacle::initTexture(){
    this->texture.loadFromFile("images/spikes.png");
}
const sf::FloatRect Obstacle::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

bool Obstacle::isInWindow(){
    if (this->getBounds().left < 1920.f && this->getBounds().left + this->getBounds().width > 0.f){
        return true;
    } else {
        return false;
    }
}
