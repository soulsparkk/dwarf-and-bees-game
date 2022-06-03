#pragma once

#include <Character.h>

class Enemy{
    private:
        sf::Font font;
    public:
        Enemy(float x, float y);
        int hp;
        virtual ~Enemy();
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Clock clock;
        const sf::FloatRect getBounds() const;

        sf::Text hpText;
        void initTexture();
        void setPosition(float x, float y);
        float getHp();
        void updateHp(int newHp);
        bool isInWindow();
        bool canAttack();
        bool isAlive();
        bool isCounted;
};
