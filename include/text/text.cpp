#include "text.hpp"
#include <iostream>
using namespace std;

TextRenderer::TextRenderer(SDL_Renderer* renderer, const std::string& fontPath, int fontSize) {
    this->renderer = renderer;
    loadFont(fontPath, fontSize);
}

TextRenderer::~TextRenderer() {
    TTF_CloseFont(font);
}

void TextRenderer::loadFont(const std::string& fontPath, int fontSize) {
    if(fontPath[fontPath.length()-4] == '.'){
        if(fontPath[fontPath.length()-3] == 't'){
            if(fontPath[fontPath.length()-2] == 't'){
                if(fontPath[fontPath.length()-1] == 'f');
                else{
                    cout << "Errore|Font non esistente| Il Font deve stare nella cartella \"Sprites\" nome file: <nome>.ttf. Premere un tasto per chiudere";
                    scanf("%d",NULL);
                    exit(-1);
                }
            }
            else{
                cout << "Errore|Font non esistente| Il Font deve stare nella cartella \"Sprites\" nome file: <nome>.ttf. Premere un tasto per chiudere";
                scanf("%d",NULL);
                exit(-1);
            }
        }
        else{
            
            cout << "Errore|Font non esistente| Il Font deve stare nella cartella \"Sprites\" nome file: <nome>.ttf. Premere un tasto per chiudere";
            scanf("%d",NULL);
            exit(-1);
        }
    }
    else{
        cout << "Errore|Font non esistente| Il Font deve stare nella cartella \"Sprites\" nome file: <nome>.ttf. Premere un tasto per chiudere";
        scanf("%d",NULL);
        exit(-1);
    }
    
    font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (font == nullptr) {
        cout << "Errore creazione font";
    }
}

void TextRenderer::renderText(const std::string& text, int x, int y, SDL_Color color) {
    if (font == nullptr || renderer == nullptr) {
        return;
    }

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (surface == nullptr) {
        
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) {
        
    }

    SDL_Rect dstRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);
}
