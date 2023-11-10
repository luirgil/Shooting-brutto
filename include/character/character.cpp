#include "character.hpp"
#include "../enemy/enemy.hpp"
using namespace std;


int Character::updateLifeBar(int n) {
    this->lifebar.life = this->lifebar.lifePosition.w -= n;
    if(this->lifebar.life <= 0) canShoot = false;
    return 1;
}

bool Character::CheckBulletCollision(Enemy& enemy) {
    for (const auto& bullet : enemy.bullets) {
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

