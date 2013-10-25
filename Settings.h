#pragma once
//This class gathers all the parameters we can provide to the generating function of
//the castle
enum ASPECT
{
	light_stone,
	dark_stone,
	wood,
	sand,
	glass
};

struct SETTINGS
{
	unsigned int wall_length;            //taille en blocs du mur du chateau
	unsigned int wall_tower_number;      //nombre de tour le long du mur
	unsigned int inside_tower_number;    //nombre de tour dans l'enceinte du chateau
	unsigned int door_number;            //nombre de portes intégrées au mur
	ASPECT material;                   //materiau dans lequel le chateau est construit
};