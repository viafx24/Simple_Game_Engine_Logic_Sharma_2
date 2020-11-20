// on notera ce choix de faire les includes de la SFML deux fois dans player et swagball. Je ne sais pas pourquoi.
// on voit l'interet du pragma once car dans game.h on appelle player.h et game.h donc evite la redondance.

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Player
{
private:
	// comme on l'a vu le joueur est un rectangle; on crée donc une forme RectangleShape nomme shape
	sf::RectangleShape shape;

	// il a une vitesse de deplacement, des points de vie et un nombre de point de vie max
	float movementSpeed;
	int hp;
	int hpMax;

	// deux fonctions d'initiliasation

	void initVariables();
	void initShape();

public:
	// on indique la position par defaut : en haut à gauche)
	Player(float x = 0.f, float y = 0.f);
	virtual ~Player();// destructeur virtuel et non pure virtuel: donc on peut l'utiliser.

	//Accessors
	// renvoie une reference sur la shape
	const sf::RectangleShape& getShape() const;
	const int& getHp() const;
	const int& getHpMax() const;

	//Functions
	void takeDamage(const int damage);
	void gainHealth(const int health);

	void updateInput();
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);
};

