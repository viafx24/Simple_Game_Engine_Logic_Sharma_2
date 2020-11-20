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

	std::vector<SwagBall> swagBalls; // swag veut dire style en anglais (probablement des formes différentes)
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

	// savoir si c'est la fin du jeu: premier const : le booleen renvoyé n'a pas été changé (je crois)
	// deuxième const (la méthode ne change rien au variables privés de l'objet): c'est juste un accesseur.
	// eperuette: je sais pas encore (sans doute on précise qu'on ne veut pas copier la réponse dans une nouvelle variable
	// mais simplement avoir une réference sur la variable retournée.

	const bool& getEndGame() const;

	//Modifiers

	//Functions

	// savoir si le jeux est en train de tourner (semble redondant avec le précedent et je ne vois pas pourquoi pas mis en accesseur)
	const bool running() const;

	// definis les events de base (fermeture fenetre)
	void pollEvents();

	void spawnSwagBalls();// crée une nouvelle boule toute les 10 secondes si nombre max pas atteint.
	const int randBallType() const;
	void updatePlayer();
	void updateCollision();
	void updateGui();
	void update();

	void renderGui(sf::RenderTarget* target);
	void render();
};
