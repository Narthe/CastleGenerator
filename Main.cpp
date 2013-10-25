using namespace std;
#include "Engine.h"
 
int main()
{
	bool running = true;
	Engine eng;
	eng.Setup();
	while(running){
		eng.Update();
		eng.Render();
	}
    return 0;
}