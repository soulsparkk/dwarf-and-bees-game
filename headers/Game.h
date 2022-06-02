
#pragma once

#include <Character.h>
#include <Obstacle.h>
#include <Bullet.h>
#include <Enemy.h>

class Game{
    private:
        sf::RenderWindow* window;
        sf::VideoMode videoMode;
        sf::Event event;
        sf::Vector2i mousePosWindow;
        sf::RectangleShape enemy;
        Character* character;
        std::map<int, Obstacle*> obstacles;
        std::map<int, Enemy*> enemies;
        sf::Texture skyTex;
        sf::Sprite sky;
        sf::Texture grassTex;
        sf::Sprite grass;
        sf::Texture bloodTex;
        sf::Sprite blood;

        sf::Texture bulletTex;

        sf::Font font;

        sf::Text score;
        sf::Text hp;
        sf::Text GameOver;

        std::vector<Bullet*> bullets;

        void initCharacter();
        void initVariables();
        void initWindow();
        void initEnemies();
        void initObstacles();
        
    public:
        Game();
        virtual ~Game();

        float offset;
        sf::Shader parallaxShader;
        const bool running() const;
        bool isGameEnded;

        void run();
        void updateMousePos();
        void updatePollEvents();
        void update();
        void updateScore();
        void updateInput();
        void updateEnemies();
        void updateCharacter();
        void render();
        void updateHp();

        void createObstacle();
        void createEnemy();

        void renderBackground();
        void renderCharacter();
        void updateBullets();
        void renderEnemies();
        void renderScoreAndHp();
        void renderObstacles();
        void renderEnemy();
        void renderBlood();
        void renderBullets();
        void initWorld();
};
