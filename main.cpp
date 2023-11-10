// C Inlcudes
#include <windows.h>
#include "./include/sdl/include/SDL2/SDL.h"
#include "./include/sdl/include/SDL2/SDL_ttf.h"
#include "./include/sdl/include/SDL2/SDL_mixer.h"
#include "./include/sdl/include/SDL2/SDL_image.h"

// C++ Includes
#include <vector>
#include <iostream>
#include <sstream>

// Custom Includes
#include "include/bullet/bullet.hpp"
#include "include/enemy/enemy.hpp"
#include "include/character/character.hpp"
#include "include/lifeBar/lifeBar.hpp"
#include "include/object/object.hpp"
#include "include/constants/constants.hpp"
#include "include/sottoprogrammi/sottoprogrammi.hpp"
#include "include/text/text.hpp"

// Namespaces
using namespace std;

// Intestazione Main
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    bool yPremuto;
    bool Quit = false;
    GameStatus status;
    do{
        Quit = false;
        AllocConsole();
        freopen("CONOUT$", "w", stdout);
        int width = 640, height = 480;
        bool backSlashN = true;
        int nEnemies = 0;
        int whoWon = 0;

        // Inizializzazione SDl
        cout << "Inizializzazione SDL\n";
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            cout << "Errore inizializzazione SDL: " << SDL_GetError() << endl;
            return 1;
        }

        // Inizializza finestra SDL
        cout << "Creazione finestra\n";
        SDL_Window* window = SDL_CreateWindow("Shooting Brutto", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
        if (!window) {
            cout << "Errore creazione finestra: " << SDL_GetError() << endl;
            SDL_Quit();
            return 1;
        }

        // Inizializzazione Render
        cout << "Inizializzazione Render\n";
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer) {
            cout << "Errore creazione renderer: " << SDL_GetError() << endl;
            SDL_DestroyWindow(window);
            SDL_Quit();
            return 1;
        }

        if(TTF_Init() == -1){
            cout << "Errore Inizializzazione Funzioni TTF: " << SDL_GetError() << endl;
            SDL_Quit(); 
            return 1;
        }
        TextRenderer textRenderer(renderer, "./Sprites/arial.ttf", 36);

        // Creazione mappa & Inizializzazione Mappa 
        Object map = InitializeObject(&map.riuscita,"./Sprites/map.bmp", renderer, "map");
        if(map.riuscita == 1){
            // free_args(2, window, renderer);
            exit(-1);
        }
        
        // Imposta il target di rendering a 30 FPS
        const int targetFPS = 30;
        const int delayTime = 100 / targetFPS;

        // Variabili per il controllo dei fotogrammi
        Uint32 frameStart, frameTime;

        bool keyW = false;
        bool keyA = false;
        bool keyS = false;
        bool keyD = false;

        bool fire = false;
        Uint32 lastShotTime = 0; 
        int bulletSpeed = 100 / targetFPS;

        Uint32 lastShotTimeEnemy = 0;

        // Creazione Player & Inizializzazione Player
        Character player;
        // Posizioni Di Partenza
        SDL_Rect LifeBarPosition;
        LifeBarPosition.w = (width * ANY_LIFEBAR_SIZE_WIDHT)/640;
        LifeBarPosition.h = (height * ANY_LIFEBAR_SIZE_HEIGHT)/480;
        LifeBarPosition.x = (width * 20)/640;
        LifeBarPosition.y = (height * 20)/640;
        
        float widthRatio = static_cast<float>(width) / 640.0f;
        float heightRatio = static_cast<float>(height) / 480.0f;

        SDL_Rect StartPosition;
        StartPosition.w = static_cast<int>((widthRatio * 118));
        StartPosition.h = static_cast<int>((heightRatio * 134));
        StartPosition.x = static_cast<int>((widthRatio * (width / 8)) + (widthRatio * (StartPosition.w / 2)));
        StartPosition.y = static_cast<int>((heightRatio * (height - StartPosition.h)) / 2);

        player = InizializeCharacter(&player.proprieties.riuscita, "./Sprites/PlayerIdle.bmp", renderer, StartPosition, "player");
        //cout << "Spawnato Player a X = " << StartPosition.x << " Y = " << StartPosition.y << endl;
        player.lifebar = InizialazeLifeBar(renderer, "./Sprites/frame.bmp", LifeBarPosition, "./Sprites/backgroundLife.bmp", "./Sprites/life.bmp");

        vector<Enemy> enemies;
        int enemyW = (width * (width + StartPosition.x - 600) /640); 
        int enemyH = (height * StartPosition.h - ((height * 100)/640)) / 640;
        int enemyX = ((width * (600 - enemyW)))/640;
        int enemyY = StartPosition.y - enemyW/3;

        LifeBarPosition.w = (width * ANY_LIFEBAR_SIZE_WIDHT)/640;
        LifeBarPosition.h = (height * ANY_LIFEBAR_SIZE_HEIGHT)/480;
        LifeBarPosition.x = ((width * (600 - LifeBarPosition.w)))/640;
        LifeBarPosition.y = (height * 20)/640;

        cout << "Controls:\n";
        cout << "WASD: Movement ; LShift (hold): Run\n";
        cout << "'q': Quit ; 'p': Shoot";
        string diff = impostaDifficolta(renderer, InitializeObject(NULL, "./Sprites/Welcome.bmp", renderer, "Scena Difficoltà"));
        status = GameStatus::running;
        while (status == GameStatus::running) {
            if(enemies.empty()){
                spawnNewEnemy(enemies, renderer, enemyX, enemyY, bulletSpeed, width, height);
            }else 
                if (enemies.back().lifebar.life <= 0) {
                    enemies.pop_back();
                    spawnNewEnemy(enemies, renderer, enemyX, enemyY, bulletSpeed, width, height);
                    nEnemies++;
                    player.updateLifeBar((width * -10)/640);
                }
            for (int i = 0; i < enemies.size(); i++)
            {
                if(!enemies[i].delayShootEnemyBool && enemies[i].canShoot) enemies[i].delayShootEnemy = impostaDelayProiettili(diff);
            }
            frameStart = SDL_GetTicks();
            Uint32 currentTime = SDL_GetTicks();
            Uint32 currentTimeEnemy = SDL_GetTicks();

            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT){
                    Quit = true;
                    break;
                }
                else if (event.type == SDL_KEYDOWN) {
                    // Imposta le variabili dei tasti premuti
                    switch (event.key.keysym.sym) {
                        case SDLK_w:
                            keyW = true;
                            break;
                        case SDLK_a:
                            keyA = true;
                            break;
                        case SDLK_s:
                            keyS = true;
                            break;
                        case SDLK_d:
                            keyD = true;
                            break;
                        case SDLK_p:
                            fire = true;
                            break;
                        case SDLK_r:
                            player.position = StartPosition;
                            break;
                        case SDLK_q:
                            Quit = true;
                            break;
                        case SDLK_LSHIFT:
                            player.run = true;
                            break;
                        default:
                            break;
                    }
                }
                else if (event.type == SDL_KEYUP) {
                    // Resetta le variabili dei tasti rilasciati
                    switch (event.key.keysym.sym) {
                        case SDLK_w:
                            keyW = false;
                            break;
                        case SDLK_a:
                            keyA = false;
                            break;
                        case SDLK_s:
                            keyS = false;
                            break;
                        case SDLK_d:
                            keyD = false;
                            break;
                        case SDLK_p:
                            fire = false;
                            break;
                        case SDLK_LSHIFT:
                            player.run = false;
                            break;
                        default:
                            break;
                    }
                }
            }
            if(Quit) break;
            // Calcola la direzione del movimento
            int moveX = 0;
            int moveY = 0;
            if(player.lifebar.life > 0){
                if (keyW) moveY = -1;
                if (keyA) moveX = -1;
                if (keyS) moveY = 1;
                if (keyD) moveX = 1;
            }
            if(player.run && player.lifebar.life > 0){
                if (keyW) moveY = -2;
                if (keyA) moveX = -2;
                if (keyS) moveY = 2;
                if (keyD) moveX = 2;
            }

            // Controllo se il nuovo posizionamento è all'interno dei limiti dello schermo
            int newPlayerX = player.position.x + moveX;
            int newPlayerY = player.position.y + moveY;

            if (newPlayerX >= 0 && newPlayerX + player.position.w <= width && newPlayerY >= 0 && newPlayerY + player.position.h <= height) {
                player.position.x = newPlayerX;
                player.position.y = newPlayerY;
            }

            for (int i = 0; i < enemies.size(); i++) {
                for (int j = 0; j < enemies[i].bullets.size(); j++) {
                    if (enemies[i].bullets[j].position.x + enemies[i].bullets[j].speed < - enemies[i].bullets[j].position.w) {
                        enemies[i].bullets.erase(enemies[i].bullets.begin() + j);
                        j--;
                    }
                }
            }

            for (int i = 0; i < enemies.size(); i++)
                if(!player.canShoot){
                    enemies[i].canShoot = false;
                    whoWon = 1;
                }
            
            for (int i = 0; i < enemies.size(); i++)
                if(player.CheckBulletCollision(enemies[i]))
                    for (int j = 0; j < enemies[i].bullets.size(); j++)
                        if(enemies[i].bullets[j].canDamage)
                            if(player.updateLifeBar((width * 20)/640)){
                                enemies[i].bullets[j].canDamage = false;
                            }
            for (int i = 0; i < player.bullets.size(); i++)
                for (int j = 0; j < enemies.size(); j++)
                    if(enemies[j].CheckBulletCollisionEnemy(player) && player.bullets[i].canDamage){
                        enemies[j].updateLifeBar((width * 10)/640);
                        player.bullets[i].canDamage = false;
                    }

            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, map.texture, NULL, NULL);
            SDL_RenderCopy(renderer, player.proprieties.texture, NULL, &player.position);
            for (int i = 0; i < player.bullets.size(); i++)
            {
                player.bullets[i].Render(renderer);
            }
            for (int i = 0; i < enemies.size(); i++)
                for (int j = 0; j < enemies[i].bullets.size(); j++)
                    enemies[i].bullets[j].Render(renderer);
            for (int i = 0; i < enemies.size(); i++)
            {
                enemies[i].Render(renderer);
            }
            
            if(RenderLifeBar(renderer, player.lifebar.background.texture, &player.lifebar.backgroundPosition, player.lifebar.lifeOBJ.texture, &player.lifebar.lifePosition, player.lifebar.frame.texture, &player.lifebar.framePosition) == -1)
            {
                SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Erorre renderizzando la barra vita\n");
            }
            for (int i = 0; i < enemies.size(); i++)
            {
                if(RenderLifeBar(renderer, enemies[i].lifebar.background.texture, &enemies[i].lifebar.backgroundPosition, enemies[i].lifebar.lifeOBJ.texture, &enemies[i].lifebar.lifePosition, enemies[i].lifebar.frame.texture, &enemies[i].lifebar.framePosition) == -1)
                {
                    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Erorre renderizzando la barra vita\n");
                }
                else SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Enemy life bar renderizzata\n");
            }
            textRenderer.renderText(to_string(nEnemies), width/2, 40, {0, 0, 0, 255});
            
            SDL_RenderPresent(renderer);
            // FINE RENDERING

            for (int i = 0; i < enemies.size(); i++) {
                for (int j = 0; j < enemies[i].bullets.size(); j++) {
                    enemies[i].bullets[j].Update(width);
                    if (!enemies[i].bullets[j].isActive) {
                        enemies[i].bullets.erase(enemies[i].bullets.begin() + j);
                        j--;
                    }
                }
            }

            if (fire && currentTime - lastShotTime >= 500 && player.canShoot) {
                int bulletX = (player.position.x + player.position.w); 
                int bulletY = player.position.y + ((width * 40)/640); 
                Bullet newBullet(renderer, bulletX, bulletY, bulletSpeed, width, height, "./Sprites/bullet.bmp");
                player.bullets.push_back(newBullet); 
                lastShotTime = currentTime;
                //cout << "New bullet created at X: " << bulletX << " Y: " << bulletY << endl;
            }

            // Delay proiettili nemico

            for (int i = 0; i < enemies.size(); i++) {
                if (currentTimeEnemy - enemies[i].lastShotTimeEnemy >= enemies[i].delayShootEnemy && enemies[i].lifebar.life > 0) {
                    enemies[i].ShootBullet(renderer, "./Sprites/enemy_bullet.bmp");
                    enemies[i].lastShotTimeEnemy = currentTimeEnemy;
                    enemies[i].delayShootEnemyBool = false;
                }
                else enemies[i].delayShootEnemyBool = true;
            }

            // Aggiornamento dei proiettili attivi
            for (int i = 0; i < player.bullets.size(); i++) {
                player.bullets[i].Update(width);
                if (!player.bullets[i].isActive) {
                    player.bullets.erase(player.bullets.begin() + i); 
                    i--; 
                }
            }

            for (int i = 0; i < enemies.size(); i++)
            {
                if(!enemies[i].canShoot) whoWon = -1;
            }

            // Calcola il tempo trascorso per il fotogramma
            frameTime = SDL_GetTicks() - frameStart;
            // Aggiorna il ritardo solo se il tempo trascorso è inferiore al ritardo desiderato
            if (frameTime < delayTime) {
                SDL_Delay(delayTime - frameTime);
            }
            if(Quit) status = GameStatus::quitted;
            if(player.lifebar.life <= 0) status = GameStatus::died;
        }
        if(!Quit){
            SDL_RenderClear(renderer);
            system("cls");
            Object finalScene;
            TextRenderer finalText(renderer, "./Sprites/arial.ttf", 36);
            if(status == GameStatus::quitted){
                finalScene = InitializeObject(&finalScene.riuscita, ".Sprites/thxForP.bmp", renderer, "finalScene");
            }
            if(status == GameStatus::died){
                finalScene = InitializeObject(&finalScene.riuscita,"./Sprites/youLose.bmp", renderer, "finalScene");
            }
            yPremuto = attendiInput(renderer, finalScene, finalText, nEnemies, width, height, status);
        }

        // Pulizia e uscita
        cout << "Destroying Player\n";
        SDL_DestroyTexture(player.proprieties.texture);
        cout << "Destroying Map\n";
        SDL_DestroyTexture(map.texture);
        SDL_FreeSurface(map.surface);
        cout << "Destroying Renderer\n";
        SDL_DestroyRenderer(renderer);
        cout << "Destroying Window\n";
        SDL_DestroyWindow(window);
        cout << "Killing the console\n";
        FreeConsole();
        cout << "Cleaning Complete\n";
        scanf("%d",NULL);
        cout << "Exiting\n";
    }while(yPremuto);
    cout << "Quitting from TTF and SDL\n";
    SDL_Quit();
    TTF_Quit();
    return 0;
}