#include "Game.h"

void Game::initVariables(){
    this->window = nullptr;
    
}
void Game::initWindow(){
    const sf::String title = "My game";
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    this->window = new sf::RenderWindow(this->videoMode, title, sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(40);
    this->window->setVerticalSyncEnabled(false);

    this->isGameEnded = false;

    this->font.loadFromFile("fonts/font.TTF");
    this->score.setFont(this->font);
    this->score.setCharacterSize(48);
    this->score.setFillColor(sf::Color::Black);
    this->score.setPosition(sf::Vector2f(5.f, 0.f));

    this->hp.setFont(this->font);
    this->hp.setCharacterSize(48);
    this->hp.setFillColor(sf::Color::Red);
    this->hp.setPosition(sf::Vector2f(590.f, 0.f));

    this->GameOver.setFont(this->font);
    this->GameOver.setCharacterSize(60);
    this->GameOver.setFillColor(sf::Color::Red);
    this->GameOver.setPosition(sf::Vector2f(200.f, 280.f));
    this->GameOver.setString("Game Over");
}

void Game::initWorld(){
    this->skyTex.loadFromFile("images/sky4.png");
    this->grassTex.loadFromFile("images/grass.png");
    this->forestTex.loadFromFile("images/trees.png");
    this->bloodTex.loadFromFile("images/damage.png");

    this->blood.setTexture(this->bloodTex);
    this->blood.setScale(sf::Vector2f(1.2f, 1.2f));
    this->blood.setPosition(sf::Vector2f(20.f,0.f));

    this->grassTex.setRepeated(true);
    this->skyTex.setRepeated(true);
    this->forestTex.setRepeated(true);
	this->sky.setTexture(this->skyTex);
	this->grass.setTexture(this->grassTex);
	this->forest.setTexture(this->forestTex);
    this->forest.setColor(sf::Color(255, 255, 255, 210));
    

    // this->sky.setScale(sf::Vector2f(1.3f, 1.3f));
    this->grass.setPosition(sf::Vector2f(0.f, 65.f));
    this->forest.setPosition(sf::Vector2f(0.f, 2.f));

    this->parallaxShader.loadFromMemory(
        "uniform float offset;"

        "void main() {"
        "    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;"
        "    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
        "    gl_TexCoord[0].x = gl_TexCoord[0].x + offset;" // magic
        "    gl_FrontColor = gl_Color;"
        "}"
        , sf::Shader::Vertex);
    this->offset = 0.f;
}


void Game::initEnemies(){
    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setFillColor(sf::Color::Cyan);
    this->enemy.setOutlineColor(sf::Color::Green);
    this->enemy.setOutlineThickness(10.f);
}

void Game::initCharacter(){
    this->character = new Character();
}


Game::Game(){
    this->initVariables();
    this->initWindow();
    this->initWorld();
    this->initEnemies();
    this->initCharacter();
    
}

Game::~Game(){
    delete this->window;
    delete this->character;
}


void Game::updatePollEvents(){
    while (this->window->pollEvent(this->event))
        { 
            switch (this->event.type)
                {
                    case sf::Event::Closed:
                        this->window->close();
                        break;
                    case sf::Event::KeyPressed:
                        if(this->event.key.code == sf::Keyboard::Escape)
                            this->window->close();
                        break;
                }
        }        
}

void Game::updateCharacter(){
    this->character->isMovingRight = false;
    this->character->isMovingLeft = false;
}

void Game::updateInput(){
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        this->character->isLookingRight = false;
        this->offset = this->offset -= 0.0002f;
        this->character->isMovingLeft = true;
        for (auto const& x : this->obstacles){
            x.second->sprite.move(sf::Vector2f(5.f,0.f));
        }
        for (auto const& x : this->enemies){
            x.second->sprite.move(sf::Vector2f(5.f,0.f));
        }
        // for (auto const& bullet : this->bullets){
        //     bullet->shape.move(sf::Vector2f(1.7f,0.f));
        // }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        this->character->isLookingRight = true;
        this->offset = this->offset += 0.0002f;
        this->character->isMovingRight = true;
        for (auto const& x : this->obstacles){
            x.second->sprite.move(sf::Vector2f(-5.f,0.f));
        }
        for (auto const& x : this->enemies){
            x.second->sprite.move(sf::Vector2f(-5.f,0.f));
        }
        // for (auto const& bullet : this->bullets){
        //     bullet->shape.move(sf::Vector2f(-1.7f,0.f));
        // }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (!this->character->isFalling)){
        if (this->character->sprite.getGlobalBounds().top >= 100){
            this->character->move(0.f, -2.00001f);
            this->character->isInTheAir = true;
        } else {
            this->character->isInTheAir = true;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
        float dir_x = 1.f;
        if (!this->character->isLookingRight){
            dir_x = -1.f;
        }
        if (this->character->canAttack()){
            this->bullets.push_back(
                new Bullet(false,
                this->character->sprite.getPosition().x + this->character->sprite.getGlobalBounds().width/2.f, 
                this->character->sprite.getPosition().y + 50.f, dir_x, 0.f, 5.f)
            );
        }
	}
    

}

void Game::updateMousePos(){
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}

void Game::updateScore(){
    this->score.setString("Score:" + std::to_string(int(this->offset * 1000)));
}

void Game::updateHp(){
    float hp = this->character->getHp();
    this->character->isGettingDamage = false;
    for (auto const& x : this->obstacles)
    {
        if (this->character->sprite.getGlobalBounds().intersects(x.second->sprite.getGlobalBounds())){
            hp -= 1;
            this->character->isGettingDamage = true;
            break;
        }
    }

    for (auto *bullet : this->bullets)
    {
        if (bullet->enemy && !bullet->isAffected){
            if (this->character->sprite.getGlobalBounds().intersects(bullet->getBounds())){
                bullet->isAffected = true;
                hp -= 1;
                this->character->isGettingDamage = true;
                break;
            }
        }
    }
    this->character->updateHp(hp);
    this->hp.setString("HP: " + std::to_string(this->character->getHp()));

    if (this->character->getHp() <= 0){
        this->isGameEnded = true;
    }

}

void Game::createObstacle(){
    int index = int(this->offset * 1000 / 20) + 300;

    if ((this->obstacles.find(index) == obstacles.end()) && (index > 300)){
        int v1 = rand() % 300 + index;
        Obstacle *obstacle = new Obstacle(v1 + 400, 422.f);
        this->obstacles.insert(std::pair<int, Obstacle*>(index,obstacle));
    } 
}

void Game::createEnemy(){
    int index = int(this->offset * 1000 / 20) + 300;

    if ((this->enemies.find(index) == enemies.end()) && (index > 300)){
        int x = rand() % 300 + index;
        int y = rand() % 100 + 170;
        Enemy *enemy = new Enemy(x + 400, y);
        this->enemies.insert(std::pair<int, Enemy*>(index,enemy));
    } 
}

void Game::updateBullets()
{
	for (auto *bullet : this->bullets)
	{
		bullet->update();
	}
}

void Game::updateEnemies()
{
	for (auto const& x : this->enemies)
    {
        if (x.second->isInWindow() && x.second->isAlive()){
            if (x.second->canAttack()){
                float x1 = x.second->getBounds().left;
                float x2 = x.second->getBounds().top;
                float x3 = this->character->sprite.getPosition().x - x.second->getBounds().left + 25;
                float x4 = this->character->sprite.getPosition().y - x.second->getBounds().top + 20;
                this->bullets.push_back(new Bullet(true,x1,x2,x3,x4,0.02f));
            }
            int hp = x.second->getHp();
            for (auto *bullet : this->bullets)
            {
                if (bullet->isInWindow() && !bullet->enemy){
                    if (x.second->getBounds().intersects(bullet->getBounds())){
                        bullet->isAffected = true;
                        hp -= 1;
                        x.second->updateHp(hp);
                    }
                }
            }
        }
    }
}

void Game::update(){
    this->updateCharacter();
    this->updatePollEvents();
    this->updateInput();
    this->updateMousePos();
    this->updateEnemies();
    this->updateScore();
    this->updateHp();
    this->createObstacle();
    this->createEnemy();
    this->updateBullets();
}

void Game::renderBackground(){
    this->parallaxShader.setUniform("offset", this->offset / 20 * 100);
    this->window->draw(this->sky, &this->parallaxShader);
    this->parallaxShader.setUniform("offset", this->offset / 10  * 100);
    this->window->draw(this->forest, &this->parallaxShader);
    this->parallaxShader.setUniform("offset", this->offset / 2  * 100);
    this->window->draw(this->grass, &this->parallaxShader);
}

void Game::renderEnemies(){
    for (auto const& x : this->enemies)
    {
        if (x.second->isInWindow() && x.second->isAlive()){
                this->window->draw(x.second->sprite);
                x.second->hpText.setString(std::to_string(int(x.second->getHp())));
                x.second->hpText.setPosition(sf::Vector2f(x.second->getBounds().left + 35, x.second->getBounds().top - 50));
                this->window->draw(x.second->hpText);
        }
    }
}

void Game::renderScoreAndHp(){
    this->window->draw(this->score);
    this->window->draw(this->hp);
}

void Game::renderObstacles(){
    for (auto const& x : this->obstacles)
    {
        if (x.second->isInWindow())
            this->window->draw(x.second->sprite);
    }
}

void Game::renderBlood(){
    if (this->character->isGettingDamage){
        this->window->draw(this->blood);
    }
}

void Game::renderBullets(){
    for (auto *bullet : this->bullets)
	{
		if (bullet->isInWindow() && !bullet->isAffected){
		    bullet->render(this->window);
        }
	}
}

void Game::renderCharacter(){
    this->character->render(*this->window);
    this->character->applyGravitationForce();
}

void Game::render(){
    this->window->clear();

    this->renderBackground();
    this->renderScoreAndHp();
    this->renderObstacles();
    this->renderEnemies();
    this->renderBlood();
    this->renderCharacter();
    this->renderBullets();
    this->window->display();
}




void Game::run(){
    while (this->window->isOpen())
    {
        if (!this->isGameEnded){
            this->update();
            this->render();
        }
        else {
            this->window->clear();
            this->window->draw(this->GameOver);
            this->score.setColor(sf::Color::Red);
            this->window->draw(this->score);
            this->window->display();
                while (this->window->pollEvent(this->event))
                    {
                        switch (this->event.type)
                        {
                            case sf::Event::Closed:
                                this->window->close();
                                break;
                            case sf::Event::KeyPressed:
                                if(this->event.key.code == sf::Keyboard::Escape)
                                    this->window->close();
                                break;
                        }
                }
        }
    }
}
