#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

enum SwagBallTypes {DEFAULT = 0, DAMAGING, HEALING, NROFTYPES};// Le quatrième type ne semble pas utilisé.

class SwagBall
{
private:

	// les swagball sont bien des cercles
	sf::CircleShape shape;
	int type; // sert comme entier pour l'enum (de 0 à 3)

	void initShape(const sf::RenderWindow& window);

public:
	SwagBall(const sf::RenderWindow& window, int type);
	virtual ~SwagBall();

	//Accessor
	const sf::CircleShape getShape() const;
	const int& getType() const;

	//Functions
	void update();
	void render(sf::RenderTarget& target);
};

