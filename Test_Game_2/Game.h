#pragma once

#include<iostream>
#include<ctime>
#include<vector>
#include<sstream>

#include "Player.h"
#include "SwagBall.h"

class Game
{
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	bool endGame;
	sf::Event sfmlEvent;

	Player player;

	int points;

	sf::Font font;
	sf::Text guiText;
	sf::Text endGameText;

	std::vector<SwagBall> swagBalls; // swag veut dire style en anglais (probablement des formes diff�rentes)
	float spawnTimerMax; // spawn: reproduction donc reproduction des swagball j'imagine
	float spawnTimer;
	int maxSwagBalls;
	
	// 4 fonctions d'inilialisation: 

	void initVariables();
	void initWindow();
	void initFonts();
	void initText();

public:
	//Constructors and Destructors
	Game();
	~Game();

	//Accessors

	// savoir si c'est la fin du jeu: premier const : le booleen renvoy� n'a pas �t� chang� (je crois)
	// deuxi�me const (la m�thode ne change rien au variables priv�s de l'objet): c'est juste un accesseur.
	// eperuette: je sais pas encore (sans doute on pr�cise qu'on ne veut pas copier la r�ponse dans une nouvelle variable
	// mais simplement avoir une r�ference sur la variable retourn�e.

	const bool& getEndGame() const;

	//Modifiers

	//Functions

	// savoir si le jeux est en train de tourner (semble redondant avec le pr�cedent et je ne vois pas pourquoi pas mis en accesseur)
	const bool running() const;

	// definis les events de base (fermeture fenetre)
	void pollEvents();

	void spawnSwagBalls();// cr�e une nouvelle boule toute les 10 secondes si nombre max pas atteint.
	const int randBallType() const;
	void updatePlayer();
	void updateCollision();
	void updateGui();
	void update();

	void renderGui(sf::RenderTarget* target);
	void render();
};
