#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <ctime>
#include "Inimigo.h"
#define MENU 0
#define GAMEPLAY 1
#define REPLAY 2
using namespace std;

class SDLGame
{
public:
	SDLGame();
	~SDLGame();
		
	int CreateGame();
	void Destroy();
	void Run();
	void Replay();
	
private:
	SDL_Surface* surface;
	SDL_Texture* textureBarco;
	SDL_Texture* textureTiro;
	SDL_Texture* textureFundo;
	SDL_Texture* textureInimigo;
	SDL_Texture* textureStart;
	SDL_Texture* textureReplay;
	SDL_Texture* textureQuit;
	SDL_Texture* textureLogo;

	double deltaTime;
	const int windows_width = 860;
	const int windows_height = 600;
	bool quit;
	bool atirando;
	FILE* replay;
	int estadoJogo;
	int posX = 40;
	int posY = 310;
	int vel = 20;
	int tiroOnOff;
	int tiroX;
	int tiroY;
	int contador, finalGameplay;
	void Draw();
	void Update();
	void ProcessInput();
	void DesenhaFundo();
	void Atirando();
	void InimigoNaTela();
	void Frames();
	SDL_Window *win;
	SDL_Renderer *ren;
	SDL_Event e;

	Inimigo inim;
	bool inimigoVivo = false;
	int inimigoOnOff;
};

int SDLGame::CreateGame()
{
	
	//inicializa a tela do jogo e todas suas imagens apenas uma vez
	win = SDL_CreateWindow("Nome da janela", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windows_width, windows_height, 0);
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_SOFTWARE);

	surface = IMG_Load("../../ASSET/navio.png");
	textureLogo = SDL_CreateTextureFromSurface(ren, surface);

	surface = IMG_Load("../../ASSET/start.png");
	textureStart = SDL_CreateTextureFromSurface(ren, surface);

	surface = IMG_Load("../../ASSET/Replay.png");
	textureReplay = SDL_CreateTextureFromSurface(ren, surface);

	surface = IMG_Load("../../ASSET/quit.png");
	textureQuit = SDL_CreateTextureFromSurface(ren, surface);

	surface = IMG_Load("../../ASSET/barco1.png");
	textureBarco = SDL_CreateTextureFromSurface(ren, surface);

	surface = IMG_Load("../../ASSET/acqua.jpg");
	textureFundo = SDL_CreateTextureFromSurface(ren, surface);

	surface = IMG_Load("../../ASSET/balaCanhao.png");
	textureTiro = SDL_CreateTextureFromSurface(ren, surface);

	surface = IMG_Load("../../ASSET/Inimigo1.png");
	textureInimigo = SDL_CreateTextureFromSurface(ren, surface);

	fopen_s(&replay, "replay.txt", "w+");
	atirando = false;
	quit = false;
	contador = 0;
	estadoJogo = MENU;
	return 0;
}

void SDLGame::Frames()
{
	int fps = 60;
	int fpsMill = 1000 / fps;
	int currentFrameTime;
	double startTime = SDL_GetTicks();
	currentFrameTime = SDL_GetTicks();
	int pastTime = SDL_GetTicks() - currentFrameTime;
	if (fpsMill > pastTime)
		SDL_Delay(fpsMill - pastTime);
	double endTime = SDL_GetTicks();
	deltaTime = (endTime - startTime) / 1000;
}

void SDLGame::Atirando()
{
	if (atirando == true)
	{
		tiroX += vel;
		if (tiroX >= 850)
		{
			atirando = false;
		}
	}
	if (atirando == false)
	{
		fprintf(replay, " %d ", tiroOnOff = 1);
	}
	else
	{
		fprintf(replay, " %d ", tiroOnOff = 0);
	}
}

void SDLGame::InimigoNaTela()
{
	if (contador % 100 == 0)
	{
		inimigoVivo = true;
		if (inimigoVivo == true)
		{
			inim.x = rand() % windows_width;
			inim.y = rand() % windows_height;
		}
	}
	if ((inim.x < tiroX && (tiroX + 15 < (inim.x + 130))) || (inim.x + 100 < tiroX) && (tiroX + 15 < (inim.x + 100)))
	{
		if ((inim.y < tiroY && (tiroY + 15 < (inim.y + 130))) || (inim.y + 100 < tiroY) && (tiroY + 15 < (inim.y + 100)))
		{
			inimigoVivo = false;
			atirando = false;
		}
	}
	if (inimigoVivo == true)
	{
		fprintf(replay, " %d ", inimigoOnOff = 0);
		fprintf(replay, " %d ", inim.x);
		fprintf(replay, " %d ", inim.y);
	}
	else
	{
		fprintf(replay, " %d ", inimigoOnOff = 1);
	}
}

void SDLGame::Update()
{
	Atirando();
	InimigoNaTela();
	fprintf(replay, " %d ", posX);
	fprintf(replay, " %d ", posY);
	fprintf(replay, " %d ", tiroX);
	fprintf(replay, " %d ", tiroY);

	contador++;
	//cout << contador << endl;
}

void SDLGame::Draw()
{
	if (estadoJogo == MENU)
	{
		//Desenha Start
		SDL_Rect start = { 0, 0, 300, 300 };
		SDL_Rect start2 = { 50, 300, 200, 200 };
		SDL_RenderCopy(ren, textureStart, &start, &start2);
		//Desenha Replay
		SDL_Rect replay = { 0, 0, 256, 256 };
		SDL_Rect replay2 = { 300, 300, 200, 200 };
		SDL_RenderCopy(ren, textureReplay, &replay, &replay2);
		//Desenha Quit
		SDL_Rect quit = { 0, 0, 1024, 1024 };
		SDL_Rect quit2 = { 550, 300, 200, 200 };
		SDL_RenderCopy(ren, textureQuit, &quit, &quit2);
		//Desenha Logo
		SDL_Rect logo = { 0, 0, 476, 507 };
		SDL_Rect logo2 = { 300, 30, 250, 250 };
		SDL_RenderCopy(ren, textureLogo, &logo, &logo2);
	
	}
	else
	{
		//você chama o draw para chamar as imgs desejadas
		SDL_Rect barco = { 0, 0, 127, 100 };
		SDL_Rect barco2 = { posX, posY, 100, 100 };
		SDL_RenderCopy(ren, textureBarco, &barco, &barco2);
		if (inimigoVivo == true)
		{
			SDL_Rect ini = { 0, 0, 130, 83 };
			SDL_Rect ini2 = { inim.x, inim.y, 100, 100 };
			SDL_RenderCopy(ren, textureInimigo, &ini, &ini2);
		}
		if (atirando == true)
		{
			SDL_Rect tiro = { 0, 0, 183, 157 };
			SDL_Rect tiroConfig = { tiroX, tiroY, 15, 15 };
			SDL_RenderCopy(ren, textureTiro, &tiro, &tiroConfig);

		}
	}
}

void SDLGame::Replay()
{
	for (contador = 0; finalGameplay != contador; contador++)
	{
		Frames();
		//Escaneia se o tiro está ativado
		fscanf_s(replay, " %d ", &tiroOnOff);
		if (tiroOnOff == 0)
		{
			atirando = true;
		}
		if (tiroOnOff == 1)
		{
			atirando = false;
		}
		//Escaneia o inimigo e se está ativado
		fscanf_s(replay, " %d ", &inimigoOnOff);
		if (inimigoOnOff == 0)
		{
			fscanf_s(replay, " %d ", &inim.x);
			fscanf_s(replay, " %d ", &inim.y);
			inimigoVivo = true;
		}
		if (inimigoOnOff == 1)
		{
			inimigoVivo = false;
		}
		//Escaneia a posição do jogador
		fscanf_s(replay, " %d ", &posX);
		fscanf_s(replay, " %d ", &posY);
		//Escaneia a posição do tiro
		fscanf_s(replay, " %d ", &tiroX);
		fscanf_s(replay, " %d ", &tiroY);
		DesenhaFundo();
		Draw();
		SDL_RenderPresent(ren);
	}
	fclose(replay);
	estadoJogo = MENU;
}

void SDLGame::DesenhaFundo()
{
	SDL_Rect fnd1 = { 0, 0, 1600, 1067};
	SDL_RenderCopy(ren, textureFundo, &fnd1, 0);
}

void SDLGame::ProcessInput()
{
	//Pegando inputs
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)//Se evento de sair (clicou x)
		{
			quit = true;
		}
		if (estadoJogo == MENU)
		{
			if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEMOTION )
			{
				if (e.button.button == (SDL_BUTTON_LEFT))
				{
					//Get mouse position
					int x, y;
					SDL_GetMouseState(&x, &y);
					if ((x > 50 && x < 250) && (y > 300 && y < 500))
					{
						estadoJogo = GAMEPLAY;
					}
					if ((x > 300 && x < 500) && (y > 300 && y < 500))
					{
						estadoJogo = REPLAY;
					}
					if ((x > 550 && x < 700) && (y > 300 && y < 500))
					{
						quit = true;
					}
				}
			}
		}
		else 
		{
			if (e.type == SDL_KEYDOWN)
			{
				//e se essa tecla for para baixo
				if (e.key.keysym.sym == SDLK_RIGHT)
				{
					posX += vel;
				}
				if (e.key.keysym.sym == SDLK_LEFT)
				{
					posX -= vel;
				}
				if (e.key.keysym.sym == SDLK_UP)
				{
					posY -= vel;
				}
				if (e.key.keysym.sym == SDLK_DOWN)
				{
					posY += vel;
				}
				if (e.key.keysym.sym == SDLK_SPACE)
				{
					atirando = true;
					tiroX = posX + 50;
					tiroY = posY + 70;
				}
				else if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					rewind(replay);
					finalGameplay = contador;
					estadoJogo = MENU;
				}
			}
		}
	}
}

void SDLGame::Run()
{
	while (!quit)
	{
		if (estadoJogo == MENU)
			{
				DesenhaFundo();
				Draw();
				ProcessInput();
				SDL_RenderPresent(ren);
				
			}
		else if (estadoJogo == GAMEPLAY)
			{
				Frames();
				Update();
				ProcessInput();
				DesenhaFundo();
				Draw();
				SDL_RenderPresent(ren);
			}
		else if (estadoJogo == REPLAY)
			{
				Replay();
			}
	}
}

void SDLGame::Destroy()
{
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(ren);
}

SDLGame::SDLGame(){}

SDLGame::~SDLGame()
{
}