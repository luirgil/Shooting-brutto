#ifndef TEXT_HPP
#define TEXT_HPP

#include "../sdl/include/SDL2/SDL.h"
#include "../sdl/include/SDL2/SDL_ttf.h"
#include <string>

/**
 * @file text.hpp
 * @brief Contiene la dichiarazione della classe TextRenderer.
 */

/**
 * @brief Classe utile per la gestione di un testo SDL_ttf
*/
class TextRenderer {
public:
    /**
     * @brief Costruttore della classe TextRenderer.
     *
     * Questo costruttore crea un oggetto TextRenderer con il renderer SDL specificato,
     * caricando il font dal percorso specificato e impostando la dimensione del font.
     *
     * @param renderer Puntatore all'oggetto SDL_Renderer dove disegnare il testo.
     * @param fontPath Il percorso del file del font TrueType (TTF) da caricare.
     * @param fontSize La dimensione del font da utilizzare per il testo.
     */
    TextRenderer(SDL_Renderer* renderer, const std::string& fontPath, int fontSize);

    /**
     * @brief Distruttore della classe TextRenderer.
     *
     * Questo distruttore libera le risorse allocate per il font.
     */
    ~TextRenderer();

    /**
     * @brief Carica un font TrueType (TTF) dal percorso specificato e imposta la dimensione del font.
     *
     * Questo metodo carica il font dal file TTF specificato nel percorso e imposta la dimensione del font
     * per il rendering del testo.
     *
     * @param fontPath Il percorso del file del font TrueType (TTF) da caricare.
     * @param fontSize La dimensione del font da utilizzare per il testo.
     */
    void loadFont(const std::string& fontPath, int fontSize);

    /**
     * @brief Renderizza il testo specificato sulla finestra associata al renderer nelle coordinate specificate.
     *
     * Questo metodo renderizza il testo specificato sulla finestra associata al renderer
     * nelle coordinate (x, y) specificate con il colore specificato.
     *
     * @param text La stringa di testo da renderizzare.
     * @param x La coordinata x in cui posizionare il testo sulla finestra.
     * @param y La coordinata y in cui posizionare il testo sulla finestra.
     * @param color Il colore del testo, specificato come un oggetto SDL_Color.
     */
    void renderText(const std::string& text, int x, int y, SDL_Color color);

private:
    TTF_Font* font;
    SDL_Renderer* renderer;
};

#endif // TEXT_HPP
