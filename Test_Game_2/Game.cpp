#include "Game.h"

void Game::initVariables()
{
	this->endGame = false;
	this->spawnTimerMax = 10.f; // j'imagine 10 secondes
	this->spawnTimer = this->spawnTimerMax; // pourquoi l'initiliasé au max et pas à zero?
	this->maxSwagBalls = 10;
	this->points = 0;
}

void Game::initWindow()
{
	this->videoMode = sf::VideoMode(800, 600);
	this->window = new sf::RenderWindow(this->videoMode, "Game 2", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
	if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf"))
	{
		std::cout << " ! ERROR::GAME::INITFONTS::COULD NOT LOAD PixellettersFull.ttf" << "\n";
	}
}

void Game::initText()
{
	//Gui text init
	this->guiText.setFont(this->font);
	this->guiText.setFillColor(sf::Color::White);
	this->guiText.setCharacterSize(32);

	//End game text
	this->endGameText.setFont(this->font);
	this->endGameText.setFillColor(sf::Color::Red);
	this->endGameText.setCharacterSize(60);
	this->endGameText.setPosition(sf::Vector2f(20, 100));
	this->endGameText.setString("YOU ARE DEAD, EXIT THE GAME!");
}

//Constructors and Destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
}

Game::~Game()
{
	delete this->window;
}

// on verifiera que l'addresse de la variable renvoyé est la même
const bool & Game::getEndGame() const
{
	return this->endGame;
}

//Functions
const bool Game::running() const
{
	return this->window->isOpen() /*&& this->endGame == false*/;
}

void Game::pollEvents()
{
	// contrairement à ce que je croyais, le sfmlEvent n'est pas crée ici, il a été definis dans le .h
	while (this->window->pollEvent(this->sfmlEvent))
	{
		switch (this->sfmlEvent.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::spawnSwagBalls()
{
	//Timer
	if (this->spawnTimer < this->spawnTimerMax)
		this->spawnTimer += 1.f;// incrémente de 1 (seconde?) le timer.
	else
	{
		if (this->swagBalls.size() < this->maxSwagBalls)
		{
			// si la taille max n'est pas atteinte
			// on crée un objet swagball qu'on push dans le vecteur (swagBalls avec un"s")
			// on précise la fenètre d'accueil qui est en général un pointeur avec Suraj et 
			//on appelle une méthode qui sans doute choisi une forme aléatoire.

			this->swagBalls.push_back(SwagBall(*this->window, this->randBallType()));

			this->spawnTimer = 0.f; // cette fois ci le timer est remis à zero.
		}	
	}
}

const int Game::randBallType() const
{

	// le choix d'un nombre aléatoire entre 0 et 100 offre plus de flexibilité si on veut
	// changer la proba d'apparition a posteriori
	// 20% chance d'un objet créant des dommages; 20% de chance d'un objet qui soigne
	// 60% de chance d'un objet standard. Le dernier type dans enum n'est pas clair


	int type = SwagBallTypes::DEFAULT;
	
	int randValue = rand() % 100 + 1;
	if (randValue > 60 && randValue <= 80)
		type = SwagBallTypes::DAMAGING;
	else if (randValue > 80 && randValue <= 100)
		type = SwagBallTypes::HEALING;

	return type;
}

void Game::updatePlayer()
{
	this->player.update(this->window);
	// on va chercher le nombre de point de vie qui reste au jouer, si <0 partie perdu.
	if (this->player.getHp() <= 0)
		this->endGame = true;
}

void Game::updateCollision()
{
	//Check the collision
	for (size_t i = 0; i < this->swagBalls.size(); i++)
	{

		// on verifie si il y a collision entre le joueur (carré vert) et les swagball (une par une)
		// notons qu'on utilise intersect et non pas contains ici.
		// on notera que getShape est une méthodes de players. les autres méthodes sont de la SFML

		if (this->player.getShape().getGlobalBounds().intersects(this->swagBalls[i].getShape().getGlobalBounds()))
		{

			// accesseur getType de la classe swagball
			// il y a trois cas de figure: 
			// default permet d'amasser des points
			// damaging de perdre des points de vie
			// health d'en regagner.
			// les méthodes takedamage et gainhealth prennent un int en paramètre pour indiquer le gain (ici 1)


			switch (this->swagBalls[i].getType())
			{
			case SwagBallTypes::DEFAULT:
				this->points++;
				break;
			case SwagBallTypes::DAMAGING:
				this->player.takeDamage(1);
				break;
			case SwagBallTypes::HEALING:
				this->player.gainHealth(1);
				break;
			}

			//Remove the ball
			// pour effacer un element d'un vecteur au milieu on utilise erase
			// il faut ensuite utiliser un iterateur (automatiquement crée je crois en appelant 
			// la méthode begin; les iterateurs pour les vecteurs sont en random-access ce qui signifie
			// je crois qu'on peut utiliser le "+" pour atteindre l'element à supprimer. C'est le cas ici
			// avec le "+i"
			this->swagBalls.erase(this->swagBalls.begin() + i);			
		}
	}	
}

void Game::updateGui()
{
	// stringstream permet l'output comme l'input (il y a un o ou un i devant si on veut qu'une seule operation
	// possible.
	// l'avantage de l'usilitation d'un flux est sa flexibilité: on met ce qu' on veut dedans (string, int, float)
	// le tout sera convertit en string automatiquement en appelant la méthode str()

	std::stringstream ss;

	ss << " - Points: " << this->points << "\n"
		<< " - Health: " << this->player.getHp() << " / " << this->player.getHpMax() << "\n";

	// setString est une méthode SFMl pour la class text alors que ss.str() est une méthode de la STL
	// qui renvoie le flux sous forme de string

	this->guiText.setString(ss.str());
}

void Game::update()
{
	this->pollEvents();

	if (this->endGame == false)
	{
		this->spawnSwagBalls();
		this->updatePlayer();
		this->updateCollision();
		this->updateGui();
	}
}

// ecriture bizarre au cas où il ait une autre fenètre je crois (pour écrire dans l'autre; plus flexible)
void Game::renderGui(sf::RenderTarget* target)
{
	target->draw(this->guiText);
}

void Game::render()
{
	// on efface déja la fenètre
	this->window->clear();

	//on fait apparaitre le joueur (render est une méthode de player appelant "draw"
	this->player.render(this->window);

	// on fait apparaitre chaque swagballs
	for (auto i : this->swagBalls)
	{

		// idem : render est une méthode de swagball appelant "draw"
		i.render(*this->window);
	}

	//Render gui: il semble que tout les méthode render prefèrent utiliser target
	// et donc on retrouve souvent un target.draw
	this->renderGui(this->window);

	//Render end text: sauf ici où le draw est admis dans "this.windows" avec la deuxième fleche = pointeur
	if(this->endGame == true)
		this->window->draw(this->endGameText);


	// on finit par montrer notre image (troisième point de tout "render"
	this->window->display();
}

//Functions