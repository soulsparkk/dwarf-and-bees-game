
#include<Character.h>


class Bullet
{
private:

    sf::Texture texture;

	sf::Vector2f direction;
	float movementSpeed;

public:
	Bullet();
	Bullet(bool enemy, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
	virtual ~Bullet();
	sf::Sprite shape;
    
	const sf::FloatRect getBounds() const;
    bool enemy;
	void update();
	void render(sf::RenderTarget* target);
    void initTexture();
    bool isInWindow();
    bool isAffected;
};