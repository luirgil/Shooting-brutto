#ifndef OBJECT_H
#define OBJECT_H

#include "../sdl/include/SDL2/SDL.h"

/**
 * @file object.hpp
 * @brief Contiene la dichiarazione della classe Object.
 */

/**
 * @brief Contiene le variabili essenziali per la creazione di un oggetto SDL <br/> Esclusi SDL_image SDL_ttf SDL_Mixer
*/
class Object {
public:
    SDL_Surface* surface; /**< Surface per l'oggetto. */
    SDL_Texture* texture; /**< Texture per l'oggetto. */
    int riuscita; /**< Flag per indicare il successo dell'inizializzazione dell'oggetto. */
};

#endif
