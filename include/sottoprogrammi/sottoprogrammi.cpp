#include "sottoprogrammi.hpp"
#include <stdio.h>
#include "../constants/constants.hpp"
#include <SDL.h>
#include <iostream>
#include "../object/object.hpp"
#include "../character/character.hpp"
#include <random>
#include <SDL_ttf.h>
#include "../text/text.hpp"
#include <stdio.h>
#include <unistd.h>

using namespace std;

void free_args(int num_args, ...) {
    va_list args;
    va_start(args, num_args);

    for (int i = 0; i < num_args; i++) {
        void *ptr = va_arg(args, void *);
        free(ptr);
    }

    va_end(args);
}

SDL_Rect InizializePosition(SDL_Rect position){
    SDL_Rect ritorno;
    ritorno.x = position.x;
    ritorno.y = position.y;
    ritorno.w = position.w;
    ritorno.h = position.h;
    return ritorno;
}

SDL_Surface* InizializeSurface(int *r, const char* surface){
    SDL_Surface* ritorno;
    ritorno = SDL_LoadBMP(surface);
    if (!ritorno) {
        printf("Errore creazione map surface: %s\n", SDL_GetError());
        SDL_Quit();
        *r = 1;
    }
    if(r != NULL)
    cout << "Surface return " << *r << "\n";
    return ritorno;
}

SDL_Texture* InizializeTexture(int *r, SDL_Renderer* renderer, SDL_Surface* surface){
    SDL_Texture* ritorno;
    ritorno = SDL_CreateTextureFromSurface(renderer, surface);
    if (!ritorno) {
        printf("Errore creazione map texture: %s\n", SDL_GetError());
        SDL_Quit();
        *r = 1;
    }
    if(r != NULL)
    cout << "Texture return" << *r << "\n";
    return ritorno;
}

Object InitializeObject(int *r, const char* surface, SDL_Renderer* renderer, const char* stampa){
    Object ritorno;
    // Inizializzazione Surface
    ritorno.surface = InizializeSurface(r,surface);
    if(ritorno.surface == NULL){
        *r = 1;
    }
    //inizializzazione Texture
    ritorno.texture = InizializeTexture(r, renderer, ritorno.surface);
    ritorno.riuscita = 0;
    if(ritorno.texture == NULL){
        *r = 1;
    }
    return ritorno;
}

Character InizializeCharacter(int* riuscita, const char* surface, SDL_Renderer* renderer, SDL_Rect position, const char* stampa){
    Character ritorno;
    cout << "Initializing Proprieties\n";
    ritorno.proprieties = InitializeObject(riuscita, surface, renderer, stampa);
    ritorno.position = InizializePosition(position);
    ritorno.canShoot = true;
    return ritorno;
}  

LifeBar InizialazeLifeBar(SDL_Renderer* renderer, const char* frameImgPath, SDL_Rect position, const char* backgroundImgPath, const char* lifeImgPath){
    LifeBar ritorno;
    // Frame Image
    ritorno.frame.riuscita = 0;
    ritorno.frame = InitializeObject(&ritorno.frame.riuscita, frameImgPath, renderer, "Renderer");
    ritorno.framePosition = InizializePosition(position);
    // Background Image
    ritorno.background.riuscita = 0;
    ritorno.background = InitializeObject(&ritorno.background.riuscita, backgroundImgPath, renderer, "Background");
    ritorno.backgroundPosition = InizializePosition(position);
    // Life Image
    ritorno.lifeOBJ.riuscita = 0;
    ritorno.lifeOBJ = InitializeObject(&ritorno.background.riuscita, lifeImgPath, renderer, "Life");
    ritorno.lifePosition = InizializePosition(position);

    ritorno.life = ritorno.lifePosition.w;
    cout << "Barra inizializzata con:\nX:" << position.x << " Y:" << position.y << " W:" << position.w << " H:" << position.h << endl;
    return ritorno;
}

int RenderLifeBar(SDL_Renderer* renderer, SDL_Texture* backgroundT, SDL_Rect* backgroundP, SDL_Texture* lifeOBJT, SDL_Rect* lifeOBJP, SDL_Texture* frameT, SDL_Rect* frameP){
    
    if(SDL_RenderCopy(renderer, backgroundT, NULL, backgroundP) == 0){
        if(SDL_RenderCopy(renderer, lifeOBJT, NULL, lifeOBJP) == 0){
            if(SDL_RenderCopy(renderer, frameT, NULL, frameP) == 0){
            }
            else{
                cout << "Errore renderizzando: lifeOBJT";
                return -1;
            }
        }
        else{
            cout << "Errore renderizzando: lifeOBJT";
            return -1;
        }
    }
    else{
        cout << "Errore renderizzando: lifeOBJT";
        return -1;
    }
    return 0;
}

int impostaDelayProiettili(string difficulty) {
    random_device rd;
    mt19937 gen(rd());
    int min, max;

    if (difficulty == "easy") {
        // Set delay for Easy difficulty
        min = 500; max = 2000;
    } else if (difficulty == "medium") {
        // Set delay for Medium difficulty
        min = 300; max = 1000;
    } else if (difficulty == "hard") {
        // Set delay for Hard difficulty
        min = 150; max = 750;
    }
    uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

bool attendiInput(SDL_Renderer* renderer, const Object& finalScene, TextRenderer& finalText, int nEnemies, int width, int height, GameStatus gameStatus) {
    SDL_Event event;
    std::string enemiesDestroyed = std::to_string(nEnemies);
    bool yPremuto = false;

    while (true) {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, finalScene.texture, nullptr, nullptr);

        if (gameStatus == GameStatus::died) {
            finalText.renderText("You did: " + enemiesDestroyed, width / 2 - 5 - 100 - 36, height - 200, {255, 255, 255, 255});
        }

        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                // Se l'utente chiude la finestra, esci dal gioco
                SDL_DestroyRenderer(renderer);
                SDL_Quit();
                exit(0);
            } else if (event.type == SDL_KEYDOWN) {
                // Verifica se il tasto premuto è 'Y', 'Q' o 'Esc'
                if (event.key.keysym.sym == SDLK_y) {
                    yPremuto = true;
                    return yPremuto;
                } else if (event.key.keysym.sym == SDLK_q || event.key.keysym.sym == SDLK_ESCAPE) {
                    return false;
                } else if (gameStatus == GameStatus::quitted) {
                    return true;
                }
            }
        }

        // Aggiungi un breve ritardo per ridurre l'utilizzo della CPU
        SDL_Delay(10);
    }
}


string impostaDifficolta(SDL_Renderer *renderer, Object scene){
    string ret;
    SDL_Event event;
    bool inputValido = false;
    bool yPremuto = false;

    while (!inputValido) {
        while (SDL_PollEvent(&event) != 0) {
            SDL_RenderCopy(renderer, scene.texture, NULL, NULL);
            SDL_RenderPresent(renderer);
            if (event.type == SDL_QUIT) {
                SDL_DestroyRenderer(renderer);
                SDL_Quit();
                exit(-1);
            } else if (event.type == SDL_KEYDOWN) {
                // Verifica se il tasto premuto è 'Y' o 'Q'
                if (event.key.keysym.sym == SDLK_1) {
                    ret = "easy";
                    inputValido = true;
                } else if (event.key.keysym.sym == SDLK_2) {
                    ret = "medium";
                    inputValido = true;
                } else if(event.key.keysym.sym == SDLK_3){
                    ret = "hard";
                    inputValido = true;
                } else inputValido = false;
            }
        }
    }

    return ret;
}

void spawnNewEnemy(std::vector<Enemy>& enemies, SDL_Renderer* renderer, int enemyX, int enemyY, int bulletSpeed, int width, int height) {
    Enemy newEnemy(renderer, enemyX, enemyY, bulletSpeed, width, height, "./Sprites/enemy.bmp");
    SDL_Rect LifeBarPosition;
    LifeBarPosition.w = (width * ANY_LIFEBAR_SIZE_WIDHT) / 640;
    LifeBarPosition.h = (height * ANY_LIFEBAR_SIZE_HEIGHT) / 480;
    LifeBarPosition.x = ((width * (600 - LifeBarPosition.w)) / 640);
    LifeBarPosition.y = (height * 20) / 640;
    newEnemy.lifebar = InizialazeLifeBar(renderer, "./Sprites/frame.bmp", LifeBarPosition, "./Sprites/backgroundLife.bmp", "./Sprites/life.bmp");
    enemies.push_back(newEnemy);
}