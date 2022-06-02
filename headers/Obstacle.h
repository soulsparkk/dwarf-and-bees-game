#pragma once

#include <Character.h>

class Obstacle{
    private:
    public:
        Obstacle(float x, float y);
        virtual ~Obstacle();
        sf::Sprite sprite;
        sf::Texture texture;

        void initTexture();
        void setPosition(float x, float y);
        bool isInWindow();
        const sf::FloatRect getBounds() const;
};
