#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "SDLGame.h"

using namespace std;
//Modelo do jogo de oficina, s� inclu� o restante para o replay e o menu
//S� usei uma classe, pois ela j� estava criada, e s� me aproveitei das variaveis criadas para criar a posi��o do inimigo (aprendendo a usar ainda)
int main(int argc, char** argv)
{

	SDLGame game;

	if (game.CreateGame() != 0)
	{
		cout << "J� deu merda" << endl;
	}
	else
	{
		srand(time(0));
		game.Run();
	}
	game.Destroy();

	return 0;
}
