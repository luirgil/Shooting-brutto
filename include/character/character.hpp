/**
 * @file character.hpp
 * @brief Contiene la dichiarazione della classe Character.
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
#include "../bullet/bullet.hpp"
#include "../enemy/enemy.hpp"
#include "../lifeBar/lifeBar.hpp"
#include "../object/object.hpp"
#include "../constants/constants.hpp"
#include "../sottoprogrammi/sottoprogrammi.hpp"
#include <SDL.h>
class Enemy;

/**
 * @brief Rappresenta il personaggio del giocatore nel gioco.
 */
class Character {
public: 
    SDL_Rect position; /**< La posizione del personaggio sullo schermo. */
    Object proprieties; /**< Le proprietà grafiche del personaggio. */
    std::vector<Bullet> bullets; /**< Vettore contenente i proiettili sparati dal personaggio. */
    LifeBar lifebar; /**< La barra della vita del personaggio. */
    bool shooted; /**< Flag che indica se il personaggio è stato colpito da un proiettile nemico. */
    bool run; /**< Flag che indica se il personaggio stà correndo. */
    bool canShoot; /**< Determina se il personaggio può sparare. */
    
    /**
     * @brief Aggiorna la barra della vita del personaggio.
     * @param n La quantità da rimuovere dalla barra della vita.
     * @return 1 se la vita del personaggio è ancora positiva, altrimenti 0.
     */
    int updateLifeBar(int n);

    /**
     * @brief Verifica la collisione del personaggio con i proiettili nemici.
     * @param enemy Il nemico con cui verificare la collisione.
     * @return True se c'è una collisione, altrimenti False.
     */
    bool CheckBulletCollision(Enemy& enemy);
};

#endif // CHARACTER_H
