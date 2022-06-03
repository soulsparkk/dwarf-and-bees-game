#pragma once
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Character{
    private:     

        int attackCooldown;
        float grassY;
        float gravitationForce;
        

        int hp;
        int hpMax;
        float movementSpeed;

    public:
        Character();
        virtual ~Character();
        bool isInTheAir;
        bool isFalling;
        bool isGettingDamage;
        bool isMovingRight;
        bool isLookingRight;
        bool isMovingLeft;
        float scaleCoeff;
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Sprite spriteLeft;
        sf::Texture textureLeft;
        
        sf::Texture jumpTexture;
        sf::Texture jumpTextureLeft;
        sf::Texture movingRightTexture;
        sf::Texture movingRight2Texture;
        sf::Texture movingLeftTexture;
        sf::Texture movingLeft2Texture;

        sf::Clock clock;

        bool canAttack();

        void update();
        void render(sf::RenderTarget& target);
        void initVariables();
        void initTexture();
        void initSprite();
        void applyGravitationForce();
        int getHp();
        void updateHp(float newHp);

        void move(const float dirX, const float dirY);
        void jump();
};


