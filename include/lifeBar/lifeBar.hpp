#ifndef LIFEBAR_H
#define LIFEBAR_H

#include "../object/object.hpp"

/**
 * @file lifeBar.hpp
 * @brief Contiene la dichiarazione della classe LifeBar.
 */

/**
 * @brief Rappresenta una barra della vita
*/
class LifeBar {
public: 
    Object frame; /**< Oggetto per il frame della barra della vita. */
    SDL_Rect framePosition; /**< Posizione del frame della barra della vita. */
    Object background; /**< Oggetto per lo sfondo della barra della vita. */
    SDL_Rect backgroundPosition; /**< Posizione dello sfondo della barra della vita. */
    Object lifeOBJ; /**< Oggetto per la rappresentazione grafica della vita. */
    SDL_Rect lifePosition; /**< Posizione della vita nella barra della vita. */
    int life; /**< Valore corrente della vita del giocatore. */
};

#endif // LIFEBAR_H
