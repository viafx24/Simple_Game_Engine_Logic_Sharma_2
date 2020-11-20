#include "Player.h"

void Player::initVariables()
{
	this->movementSpeed = 5.f;
	this->hpMax = 10;
	this->hp = hpMax;
}

void Player::initShape()
{
	// on retrouve notre couleur verte et la taille du rectanble pour lequel on utilise un Vector2f
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setSize(sf::Vector2f(50.f, 50.f));
}

Player::Player(float x, float y)
{
	this->shape.setPosition(x, y);

	this->initVariables();
	this->initShape();
}

Player::~Player()
{

}

//Accessors

// pour gérer les collisions on va appeler this->player.getShape
// c'est un appel en dehors de  la classe player (dans la classe game)
// on ne peut donc pas atteindre this->shape qui est private
// on crée donc un accesseur non modifiable qui renvoie simplement this->shape
// ce qui est renvoyé est une réference pour eviter la copie de l'objet.

const sf::RectangleShape & Player::getShape() const
{
	return this->shape;
}

// même logique pour cet accesseur
const int & Player::getHp() const
{
	return this->hp;
}

// même logique pour cet accesseur
const int & Player::getHpMax() const
{
	return this->hpMax;
}

//Functions

// en rajoutant const avant le int damage, on s'assure que la méthode ne modifiera pas damage


void Player::takeDamage(const int damage)
{
	if (this->hp > 0)
		this->hp -= damage;

	if (this->hp < 0)
		this->hp = 0;
}

void Player::gainHealth(const int health)
{
	if (this->hp < this->hpMax)
		this->hp += health;

	if (this->hp > this->hpMax)
		this->hp = this->hpMax;
}

void Player::updateInput()
{
	//Keyboard input
	//j'ai remplacé par les valeurs françaises. (ZQSD): tout est OK, j'ai verifié.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		this->shape.move(-this->movementSpeed, 0.f);// gauche
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->shape.move(this->movementSpeed, 0.f);// droite
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		this->shape.move(0.f, -this->movementSpeed);// haut
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->shape.move(0.f, this->movementSpeed);// bas
	}
}

void Player::updateWindowBoundsCollision(const sf::RenderTarget * target)
{
	// le but est d'empecher le joueur de sortir de l'écran
	//Left
	if (this->shape.getGlobalBounds().left <= 0.f)

		// shape.getGlobalBounds().top est bizarre mais je pense que c'est simplement
		// pour récuperer le y qui n'a pas changé (et qui est toujours le coin superieur gauche (seul le superieur
		// nous interesse ici.
	
		this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);
	//Right: on adapte ensuite avec une soustraction pour récuperer la valeur de droite
	if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x)
		this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);
	//Top
	if (this->shape.getGlobalBounds().top <= 0.f)
		this->shape.setPosition(this->shape.getGlobalBounds().left, 0.f);
	//Bottom: idem petite manip pour utiliser la valeur en y du bas et non du haut pour que l'on voit toujours
	// le player à l'ecran.
	if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y)
		this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height);
}

void Player::update(const sf::RenderTarget* target)
{
	this->updateInput();

	//Window bounds collision
	this->updateWindowBoundsCollision(target);
}

void Player::render(sf::RenderTarget * target)
{

	// on comprend mieux ici l'utilisation de target car Player n'a pas d'objet windows donc on ne peut pas
	// faire this->window
	// on récupère donc une réference sur la fénètre ou plus exactement sur une classe parente de la fenètre
	// ca je ne sais pas trop pourquoi car on envoie bien une fenètre (j'imagine qu'on a le droit d'envoyer
	// un objet de classe fille si une classe mère est attendu. je ne sais pas trop.

	target->draw(this->shape);
}
