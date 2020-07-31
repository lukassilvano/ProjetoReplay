#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "SDLGame.h"

using namespace std;
//Modelo do jogo de oficina, só incluí o restante para o replay e o menu
//Só usei uma classe, pois ela já estava criada, e só me aproveitei das variaveis criadas para criar a posição do inimigo (aprendendo a usar ainda)
int main(int argc, char** argv)
{

	SDLGame game;

	if (game.CreateGame() != 0)
	{
		cout << "Já deu merda" << endl;
	}
	else
	{
		srand(time(0));
		game.Run();
	}
	game.Destroy();

	return 0;
}
