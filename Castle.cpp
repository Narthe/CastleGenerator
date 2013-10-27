#include "Castle.h"

Castle::Castle(void)
{
	
}

Castle::~Castle(void)
{

}

void Castle::generateWall(SETTINGS settings)
{
	fillPositions(settings.wall_length); //initialisation liste positions
	int pos;
	srand((unsigned)time(0));

	Tower *t;
	//Affectation des positions des tours
	for (int i = 0; i < settings.wall_tower_number; i++)
	{
		pos = rand() % m_positions.size(); //on récupère une position aléatoire qui n'a pas déjà été choisie
		t = new Tower(m_positions[pos], "tower");
		m_wall.push_back(*t); //on insère dans le vector une nouvelle tour avec la position choisie
		m_positions.erase(m_positions.begin() + pos); //on supprime la position de la liste des positions pour éviter tout conflit de position
	}

	Door *d;
	//Affectation des positions des portes
	for (int j = 0; j < settings.door_number; j++)
	{
		pos = rand() % m_positions.size(); //on récupère une position aléatoire qui n'a pas déjà été choisie
		d = new Door(m_positions[pos], "door");
		m_wall.push_back(*d); //on insère dans le vector une nouvelle porte avec la position choisie
		m_positions.erase(m_positions.begin() + pos); //on supprime la position de la liste des positions pour éviter tout conflit de position
	}

	int wall_number = settings.wall_length - settings.door_number - settings.wall_tower_number;
	Wall *w;
	//Affectation des positions des murs
	for (unsigned int k = 0; k < wall_number; k++)
	{
		pos = rand() % m_positions.size(); //on récupère une position aléatoire qui n'a pas déjà été choisie
		w = new Wall(m_positions[pos], "wall");
		m_wall.push_back(*w); //on insère dans le vector un nouveau mur avec la position choisie
		m_positions.erase(m_positions.begin() + pos); //on supprime la position de la liste des positions pour éviter tout conflit de position
	}

	//On trie notre vector selon la position des blocs
	sort(m_wall.begin(), m_wall.end());
}

void Castle::toString()
{
	for (int i = 0; i < m_wall.size(); i++)
	{
		m_wall.at(i).toString();
    }
}

void Castle::fillPositions(int n)
{
	for (int i = 0; i < n; i++)
	{
		m_positions.push_back(i);
	}
}