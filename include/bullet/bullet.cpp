#include "bullet.hpp"
#include <stdio.h>
#include "../constants/constants.hpp"
#include <SDL.h>

Bullet::Bullet(SDL_Renderer* renderer, int x, int y, int bulletSpeed, int SCREENWIDTH, int SCREENHEIGHT, const char* imagePath) {
    position.x = x;
    position.y = y;
    position.w = (SCREENWIDTH * BULLETWIDHT) / 640; // Larghezza del proiettile
    position.h = (SCREENHEIGHT * BULLETHEIGHT) / 480; // Altezza del proiettile
    speed = bulletSpeed;
    isActive = true;
    // Carica la texture dell'immagine del proiettile
    SDL_Surface* bulletSurface = SDL_LoadBMP(imagePath);
    if (!bulletSurface) {
        printf("Errore caricamento immagine proiettile: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
    texture = SDL_CreateTextureFromSurface(renderer, bulletSurface);
    canDamage = true;
}

void Bullet::Update(int screenWidth) {
    position.x += speed;
        
    // Verifica se il proiettile è fuori dallo schermo
    if (position.x > screenWidth) {
        isActive = false;
    }
}

void Bullet::Render(SDL_Renderer* renderer) {
   SDL_RenderCopy(renderer, texture, NULL, &position);
}
