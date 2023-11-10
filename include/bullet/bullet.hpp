/**
 * @file bullet.hpp
 * @brief Contiene la dichiarazione della classe Bullet.
 */

#ifndef BULLET_H
#define BULLET_H

#include "../sdl/include/SDL2/SDL.h"
#include "../sdl/include/SDL2/SDL_ttf.h"
#include "../sdl/include/SDL2/SDL_mixer.h"
#include "../sdl/include/SDL2/SDL_image.h"

/**
 * @brief Rappresenta un proiettile nel gioco.
 */
class Bullet {
public:
    SDL_Rect position; /**< La posizione del proiettile sullo schermo. */
    int speed; /**< La velocità del proiettile. */
    SDL_Texture* texture; /**< La texture del proiettile. */
    bool isActive; /**< Flag che indica se il proiettile è attivo o meno. */
    bool canDamage; /**< Flag che indica se il proiettile può infliggere danni. */

    /**
     * @brief Costruttore della classe Bullet.
     * @param renderer Il renderer SDL.
     * @param x La coordinata X iniziale del proiettile.
     * @param y La coordinata Y iniziale del proiettile.
     * @param bulletSpeed La velocità del proiettile.
     * @param SCREENWIDTH La larghezza della finestra di gioco.
     * @param SCREENHEIGHT L'altezza della finestra di gioco.
     * @param imagePath Il percorso del file BMP contenente l'immagine del proiettile.
     */
    Bullet(SDL_Renderer* renderer, int x, int y, int bulletSpeed, int SCREENWIDTH, int SCREENHEIGHT, const char* imagePath);

    /**
     * @brief Aggiorna la posizione del proiettile.
     * @param screenWidth La larghezza della finestra di gioco.
     */
    void Update(int screenWidth);

    /**
     * @brief Disegna il proiettile sul renderer.
     * @param renderer Il renderer SDL.
     */
    void Render(SDL_Renderer* renderer);
};

#endif // BULLET_H
