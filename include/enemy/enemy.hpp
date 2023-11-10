/**
 * @file enemy.hpp
 * @brief Contiene la dichiarazione della classe Enemy.
 */

#ifndef ENEMY_H
#define ENEMY_H

#include "../sdl/include/SDL2/SDL.h"
#include <vector>
#include "../bullet/bullet.hpp"
#include "../constants/constants.hpp"
#include "../lifeBar/lifeBar.hpp"
#include "../character/character.hpp"

class Character;

/**
 * @brief Rappresenta un nemico nel gioco.
 */
class Enemy {
public:
    /**
     * @brief Costruttore della classe Enemy.
     * @param renderer Il renderer SDL.
     * @param x La coordinata X iniziale del nemico.
     * @param y La coordinata Y iniziale del nemico.
     * @param bulletSpeed La velocità dei proiettili sparati dal nemico.
     * @param SCREENWIDTH La larghezza della finestra di gioco.
     * @param SCREENHEIGHT L'altezza della finestra di gioco.
     * @param imagePath Il percorso del file BMP contenente l'immagine del nemico.
     */
    Enemy(SDL_Renderer* renderer, int x, int y, int bulletSpeed, int SCREENWIDTH, int SCREENHEIGHT, const char* imagePath);

    /**
     * @brief Fa sparare un proiettile al nemico.
     * @param renderer Il renderer SDL.
     * @param imagePath Il percorso del file BMP contenente l'immagine del proiettile.
     */
    void ShootBullet(SDL_Renderer* renderer, const char* imagePath);

    /**
     * @brief Aggiorna la posizione dei proiettili sparati dal nemico.
     * @param screenWidth La larghezza della finestra di gioco.
     */
    void UpdateBullet(int screenWidth);

    /**
     * @brief Disegna il nemico sul renderer.
     * @param renderer Il renderer SDL.
     */
    void Render(SDL_Renderer* renderer);

    /**
     * @brief Verifica la collisione tra i proiettili del personaggio e il nemico.
     * @param character Il personaggio con cui verificare la collisione.
     * @return True se c'è una collisione, altrimenti False.
     */
    bool CheckBulletCollisionEnemy(Character& character);

    /**
     * @brief Aggiorna la barra della vita del nemico.
     * @param n La quantità da rimuovere dalla barra della vita.
     * @return 1 se la vita del nemico è ancora positiva, altrimenti 0.
     */
    int updateLifeBar(int n);

    int lastShotTimeEnemy; /**< Il momento in cui il nemico ha sparato l'ultimo proiettile. */
    SDL_Rect position; /**< La posizione del nemico sullo schermo. */
    SDL_Texture* texture; /**< La texture del nemico. */
    std::vector<Bullet> bullets; /**< Vettore contenente i proiettili sparati dal nemico. */
    bool canShoot; /**< Determina se il nemico può sparare. */
    int speed; /**< La velocità del nemico. */
    int SCREENWIDTH; /**< La larghezza della finestra di gioco. */ 
    int SCREENHEIGHT; /**< L'altezza della finestra di gioco. */
    LifeBar lifebar; /**< La barra della vita del nemico. */
    bool delayShootEnemyBool; /**< Flag per gestire il ritardo tra i colpi del nemico. */
    int delayShootEnemy; /**< Il ritardo tra i colpi del nemico. */
};

#endif // ENEMY_H
