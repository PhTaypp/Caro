#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <SDL_mixer.h>

using namespace std;

const int SCREEN_WIDTH = 760;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "Game Caro";

void logSDLError(ostream& os, const string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();

SDL_Texture* loadTexture(const string &file, SDL_Renderer *ren);
SDL_Texture* loadTextureFromPNG(string path, SDL_Renderer* screen );

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
int checkWin(int a[20][20], int i, int j, int player, int _player);

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);
    bool close_game = false;
    while(!close_game)
    {
        SDL_Event e;
        SDL_Point point;
        SDL_Texture *Menu = loadTextureFromPNG("Menu.png", renderer);
        //load menu
        SDL_RenderClear(renderer);
        renderTexture(Menu, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        SDL_RenderPresent(renderer);
        bool in_game = false;
        while(!in_game)
        {
            while(SDL_PollEvent(&e) != 0)
            {
                if(e.key.keysym.sym == SDLK_e || e.type == SDL_QUIT)
                {
                    quitSDL(window, renderer);
                    return 0;
                }
                if (e.key.keysym.sym == SDLK_p)
                {
                    in_game = true;
                }
            }
        }
        SDL_Texture *background = loadTexture("ChessBoard.bmp", renderer);
        SDL_Texture *X_image = loadTextureFromPNG("X.png", renderer);
        SDL_Texture *O_image = loadTextureFromPNG("O.png", renderer);
        SDL_Texture *XWin_image = loadTextureFromPNG("XWin.png", renderer);
        SDL_Texture *OWin_image = loadTextureFromPNG("OWin.png", renderer);
        SDL_Texture *Draw_image = loadTextureFromPNG("Draw.png", renderer);
        SDL_Texture *playX_image = loadTexture("playX.bmp", renderer);
        SDL_Texture *playO_image = loadTexture("playO.bmp", renderer);

        if (background == nullptr || XWin_image == nullptr || OWin_image == nullptr || playX_image == nullptr || playO_image == nullptr || Draw_image == nullptr)
            {
            SDL_DestroyTexture(background);
            SDL_DestroyTexture(X_image);
            SDL_DestroyTexture(O_image);
            SDL_DestroyTexture(XWin_image);
            SDL_DestroyTexture(OWin_image);
            SDL_DestroyTexture(Draw_image);
            SDL_DestroyTexture(playX_image);
            SDL_DestroyTexture(playO_image);
            quitSDL(window, renderer);
            }

        if (X_image == nullptr || O_image == nullptr)
            {
            SDL_DestroyTexture(X_image);
            SDL_DestroyTexture(O_image);
            quitSDL(window, renderer);
            }

        SDL_RenderClear(renderer);
        renderTexture(background, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        renderTexture(playX_image, renderer, 600, 170, 150, 400);
        SDL_RenderPresent(renderer);

        int arr[20][20];
        for(int i = 0; i < 20; i++)
            {
                for(int j = 0; j < 20; j++)
                {
                arr[i][j] = 0;
                }
            }

        int i = 1;
        while(true && i <= 400)
            {
            SDL_Delay(10);
            if(SDL_WaitEvent(&e) == 0) continue;
            if(e.type == SDL_QUIT) break;
            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) break;
            if(e.type == SDL_MOUSEBUTTONDOWN)
            {
                point.x = e.button.x;
                point.y = e.button.y;
                int X = (int)(point.x /30)*30;
                int Y = (int)(point.y /30)*30;
                if(e.button.button == SDL_BUTTON_LEFT && i % 2 != 0 && point.x < 599 && arr[Y/30][X/30] == 0)
                {
                    renderTexture(X_image, renderer, X+3, Y+4, 24, 24);
                    renderTexture(playO_image, renderer, 600, 170, 150, 400);
                    SDL_RenderPresent(renderer);
                    arr[Y/30][X/30] = 1;
                    i++;
                    if(checkWin(arr, Y/30, X/30, 1, 2) == 1)
                    {
                        renderTexture(XWin_image, renderer, 50, 150, 500, 450);
                        break;
                    }
                }
                else if(e.button.button == SDL_BUTTON_LEFT && i % 2 == 0 && point.x < 599 && arr[Y/30][X/30] == 0)
                {
                    renderTexture(O_image, renderer, X+3, Y+4, 24, 24);
                    renderTexture(playX_image, renderer, 600, 170, 150, 400);
                    SDL_RenderPresent(renderer);
                    arr[Y/30][X/30] = 2;
                    i++;
                    if(checkWin(arr, Y/30, X/30, 2, 1) == 1)
                    {
                        renderTexture(OWin_image, renderer, 50, 150, 500, 450);
                        break;
                    }
                    if(i == 400)
                    {
                        renderTexture(Draw_image, renderer, 50, 190, 500, 160);
                    }
                }
            }
        }
        SDL_RenderPresent(renderer);
        waitUntilKeyPressed();

        SDL_DestroyTexture(background);
        SDL_DestroyTexture(X_image);
        SDL_DestroyTexture(O_image);
        SDL_DestroyTexture(playX_image);
        SDL_DestroyTexture(playO_image);
        SDL_DestroyTexture(Draw_image);
        SDL_DestroyTexture(XWin_image);
        SDL_DestroyTexture(OWin_image);

        SDL_RenderClear(renderer);
        renderTexture(Menu, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        SDL_RenderPresent(renderer);

        bool end_game = false;

        while (!end_game)
        {
            while(SDL_PollEvent(&e) != 0)
            {
                if(e.key.keysym.sym == SDLK_e || e.type == SDL_QUIT)
                {
                    quitSDL(window, renderer);
                    return 0;
                }
                if (e.key.keysym.sym == SDLK_p)
                {
                    end_game = true;
                }
            }
        }
    }
    quitSDL(window, renderer);
    return 0;
}

SDL_Texture* loadTexture(const string &file, SDL_Renderer *ren)
{
	SDL_Texture *texture = nullptr;
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
    SDL_SetColorKey( loadedImage, SDL_TRUE, SDL_MapRGB( loadedImage->format, 0, 0xFF, 0xFF ) );

	if (loadedImage != nullptr)
    {
        texture = SDL_CreateTextureFromSurface(ren, loadedImage);
        SDL_FreeSurface(loadedImage);
        if (texture == nullptr)
        {
            logSDLError(cout, "CreateTextureFromSurface");
        }
    }
	else
	{
		logSDLError(cout, "LoadBMP");
	}
	return texture;
}

SDL_Texture* loadTextureFromPNG(string path, SDL_Renderer* screen )
{
    SDL_Texture* new_texture = NULL;
	SDL_Surface* load_surface = IMG_Load(path.c_str());
	if (load_surface != NULL)
	{
		new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
		if (new_texture != NULL)
		SDL_FreeSurface(load_surface);
	}

	return new_texture;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
    dst.w = w;
    dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}
void logSDLError(ostream& os,
                 const string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) logSDLError(cout, "CreateWindow", true);


    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) logSDLError(cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}
void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(10);
    }
}


