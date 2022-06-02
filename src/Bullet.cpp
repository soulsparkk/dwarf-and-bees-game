#include "Bullet.h"



Bullet::Bullet(bool enemy, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed)
{
    this->enemy = enemy;
    this->isAffected = false;
    if (this->enemy){
        this->texture.loadFromFile("images/bullet21.png");
        this->shape.setTexture(this->texture);
        this->shape.setPosition(pos_x, pos_y);
        this->shape.setScale(sf::Vector2f(0.5f, 0.5f));
    } else {
        this->texture.loadFromFile("images/flower.png");
        this->shape.setTexture(this->texture);
        this->shape.setPosition(pos_x, pos_y);
        this->shape.setScale(sf::Vector2f(0.7f, 0.7f));
    }
	
	
	this->direction.x = dir_x;
	this->direction.y = dir_y;
	this->movementSpeed = movement_speed;
}

Bullet::~Bullet()
{

}

const sf::FloatRect Bullet::getBounds() const
{
	return this->shape.getGlobalBounds();
}

void Bullet::update()
{
	this->shape.move(this->movementSpeed * this->direction);
}

void Bullet::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
} 


bool Bullet::isInWindow(){
    if (this->getBounds().left < 800.f && this->getBounds().left + this->getBounds().width > 0.f){
        return true;
    } else {
        return false;
    }
}