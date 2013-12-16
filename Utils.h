#ifndef UTILS_H
#define UTILS_H
	#ifdef VAR_GLOBALES
	bool readyForRedraw = false;
	#else
	extern bool readyForRedraw = false;
	#endif
#endif