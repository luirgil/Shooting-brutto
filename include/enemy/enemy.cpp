#include "../enemy/enemy.hpp"
#include <stdio.h>
#include "../constants/constants.hpp"
#include <SDL.h>
#include "../character/character.hpp"
#include <cstdlib>

Enemy::Enemy(SDL_Renderer* renderer, int x, int y, int bulletSpeed, int SCREENWIDTH, int SCREENHEIGHT, const char* imagePath) {
    position.x = x; 
    position.y = y;
    speed = bulletSpeed;
    position.w = (SCREENWIDTH * ENEMYWIDHT) / 640; // Larghezza del nemico
    position.h = (SCREENHEIGHT * ENEMYHEIGHT) / 480; // Altezza del nemico
    Enemy::SCREENWIDTH = SCREENWIDTH;
    Enemy::SCREENHEIGHT = SCREENHEIGHT;
    lastShotTimeEnemy = 0;
    canShoot = true;
    
    // Carica la texture dell'immagine del proiettile
    SDL_Surface* enemySurface = SDL_LoadBMP(imagePath);
    if (!enemySurface) {
        printf("Errore caricamento immagine nemico: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
    texture = SDL_CreateTextureFromSurface(renderer, enemySurface);
}

void Enemy::ShootBullet(SDL_Renderer* renderer, const char* imagePath) {
    // Calcola una posizione casuale all'interno dell'area verticale occupata dall'Enemy
    int bulletX = position.x + (position.w / 2);
    int minBulletY = position.y;
    int maxBulletY = position.y + position.h;
    int bulletY = minBulletY + rand() % (maxBulletY - minBulletY + 1);

    Bullet newBullet(renderer, bulletX, bulletY, -speed, SCREENWIDTH, SCREENHEIGHT, imagePath);
    bullets.push_back(newBullet);
}


void Enemy::UpdateBullet(int screenWidth) {
    position.x += speed;
}

void Enemy::Render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, NULL, &position);
}

bool Enemy::CheckBulletCollisionEnemy(Character& character) {
    for (const auto& bullet : character.bullets) {
        // Ottieni le coordinate e le dimensioni del proiettile nemico
        SDL_Rect bulletRect = bullet.position;

        // Verifica la collisione tra il proiettile nemico e il giocatore
        if (SDL_HasIntersection(&bulletRect, &position)) {
            return true;
        }
    }
    // Nessuna collisione con i proiettili nemici
    return false;
}

int Enemy::updateLifeBar(int n) {
    this->lifebar.life = this->lifebar.lifePosition.w -= n;
    if(this->lifebar.life <= 0) canShoot = false;
    return 1;
}
