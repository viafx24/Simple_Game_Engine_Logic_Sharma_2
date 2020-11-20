#include "SwagBall.h"

void SwagBall::initShape(const sf::RenderWindow& window)
{
	// choix d'un rayon aleatoire
	this->shape.setRadius(static_cast<float>(rand()%10+10));
	
	sf::Color color;
	switch (this->type)
	{
	case DEFAULT:// equivalent � this->type=0
		// choix de couleur aleatoire
		color = sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
		break;
	case DAMAGING:// equivalent � this->type=1
		color = sf::Color::Red;
		// on met une petit bordure sympa
		this->shape.setOutlineColor(sf::Color::White);
		this->shape.setOutlineThickness(2.f);
		break;
	case HEALING:// equivalent � this->type=2
		color = sf::Color::Green;
		this->shape.setOutlineColor(sf::Color::White);
		this->shape.setOutlineThickness(2.f);
		break;
	}
	// on pense � effectivement appliquer la couleur choisi � la forme 
	this->shape.setFillColor(color);
	this->shape.setPosition(
		// il est important de comprendre pourquoi on fait un cast de type float
		// getsize et getglobalbound.width vont renvoyer lors de la soustraction un entier
		// mais si on change la taille de l'�cran, grosse r�duction par exemple, l'entier ne marchera plus
		// il faut un float pour que les elements restent correctement plac� (entre 0 et 1 pixel dans le cas
		// extreme d'une reduction d'ecran � un pixel).
		// la soustraction a pour but de s'assurer que l'objet apparait � l'ecran.

		sf::Vector2f(
			static_cast<float>(rand() % window.getSize().x - this->shape.getGlobalBounds().width), 
			static_cast<float>(rand() % window.getSize().y - this->shape.getGlobalBounds().height)
		)
	);
}


// il s'agit ici d'un constructeur: on rep�re les ":" avant type qui... signifie qu'on peut indiquer le
// le type lors de la cr�ation de l'objet?? je ne sais plus trop. C'est en g�n�ral utilis� pour �viter d'avoir
// � �crire this->type= type dans les accolades mais du coup ici c'est un peu inutile car on met quand m�me
// des accolades (de toute fa�on toujours obligatoire m�me vide) avec l'appel de la m�thode initShape

SwagBall::SwagBall(const sf::RenderWindow& window, int type)
	: type(type)
{
	this->initShape(window);
}
// destructeur (on verifiera quand et comment il est appel�)
SwagBall::~SwagBall()
{

}

// accesseur: toujours cette nuance pas encore bien clair entre premier const et dernier.
const sf::CircleShape SwagBall::getShape() const
{
	return this->shape;
}

const int & SwagBall::getType() const
{
	return this->type;
}

void SwagBall::update()
{

}

void SwagBall::render(sf::RenderTarget & target)
{
	target.draw(this->shape);
}
