/**
 * @file sottoprogrammi.hpp
 * @brief Contiene le dichiarazioni delle funzioni ausiliarie.
 */

#ifndef SOTTOPROGRAMMI_H
#define SOTTOPROGRAMMI_H

#include <SDL.h>
#include <iostream>
#include "../object/object.hpp"
#include "../character/character.hpp"
#include "../enemy/enemy.hpp"
#include <SDL_ttf.h>
using namespace std;
class Character;
class Enemy;
class TextRenderer;

/**
 * @brief Libera la memoria allocata per gli argomenti passati alle funzioni.
 * @param num_args Il numero di argomenti passati alla funzione.
 * @param ... Gli argomenti da liberare.
 */
void free_args(int num_args, ...);

/**
 * @brief Inizializza la posizione SDL_Rect.
 * @param position La SDL_Rect da inizializzare.
 * @return La SDL_Rect inizializzata.
 */
SDL_Rect InizializePosition(SDL_Rect position);

/**
 * @brief Inizializza una surface SDL.
 * @param r Puntatore a una variabile per memorizzare l'esito dell'inizializzazione.
 * @param surface Il percorso del file BMP contenente l'immagine.
 * @return La surface SDL inizializzata.
 */
SDL_Surface* InizializeSurface(int *r, const char* surface);

/**
 * @brief Inizializza una texture SDL.
 * @param r Puntatore a una variabile per memorizzare l'esito dell'inizializzazione.
 * @param renderer Il renderer SDL.
 * @param surface La surface SDL da cui creare la texture.
 * @return La texture SDL inizializzata.
 */
SDL_Texture* InizializeTexture(int *r, SDL_Renderer* renderer, SDL_Surface* surface);

/**
 * @brief Inizializza un oggetto grafico.
 * @param r Puntatore a una variabile per memorizzare l'esito dell'inizializzazione.
 * @param surface Il percorso del file BMP contenente l'immagine.
 * @param renderer Il renderer SDL.
 * @param stampa Una stringa identificativa per scopi di debug.
 * @return L'oggetto grafico inizializzato.
 */
Object InitializeObject(int *r, const char* surface, SDL_Renderer* renderer, const char* stampa);

/**
 * @brief Inizializza un personaggio.
 * @param riuscita Puntatore a una variabile per memorizzare l'esito dell'inizializzazione.
 * @param surface Il percorso del file BMP contenente l'immagine del personaggio.
 * @param renderer Il renderer SDL.
 * @param position La posizione iniziale del personaggio.
 * @param stampa Una stringa identificativa per scopi di debug.
 * @return Il personaggio inizializzato.
 */
Character InizializeCharacter(int* riuscita, const char* surface, SDL_Renderer* renderer, SDL_Rect position, const char* stampa);

/**
 * @brief Inizializza la barra della vita.
 * @param renderer Il renderer SDL.
 * @param frameImgPath Il percorso del file BMP contenente l'
 * @param position La posizione della barra sulla finestra di gioco.
 * @param backgroundImgPath Il percorso del file BMP contenente l'immagine di sfondo della barra.
 * @param lifeImgPath Il percorso del file BMP contenente l'immagine della vita nella barra.
 * @return La struttura LifeBar inizializzata.
 */
LifeBar InizialazeLifeBar(SDL_Renderer* renderer, const char* frameImgPath, SDL_Rect position, const char* backgroundImgPath, const char* lifeImgPath);

/**
 * @brief Renderizza la barra della vita sullo schermo.
 * @param renderer Il renderer SDL.
 * @param backgroundT La texture dell'immagine di sfondo della barra.
 * @param backgroundP La posizione dell'immagine di sfondo sulla finestra di gioco.
 * @param lifeOBJT La texture dell'immagine della vita nella barra.
 * @param lifeOBJP La posizione dell'immagine della vita sulla finestra di gioco.
 * @param frameT La texture dell'immagine del frame della barra.
 * @param frameP La posizione dell'immagine del frame sulla finestra di gioco.
 * @return 0 se il rendering è avvenuto con successo, -1 altrimenti.
 */
int RenderLifeBar(SDL_Renderer* renderer, SDL_Texture* backgroundT, SDL_Rect* backgroundP, SDL_Texture* lifeOBJT, SDL_Rect* lifeOBJP, SDL_Texture* frameT, SDL_Rect* frameP);

/**
 * @brief Imposta un ritardo casuale per la sparizione dei proiettili nemici.
 * @return Il ritardo casuale in millisecondi.
 * @param difficulty Indica la difficoltà scelta dal giocatore
 */
int impostaDelayProiettili(std::string difficulty);

/**
 * @brief Imposta la difficoltà del gioco
 * @return La difficoltà del gioco (easy, medium, hard)
 * @param renderer Il renderer SDL
 * @param scene Indica la scena da mostrare
*/
string impostaDifficolta(SDL_Renderer *renderer, Object scene);

/**
 * @brief Attende l'input tra 2 tasti (Y o Q).
 * @param renderer Il renderer SDL.
 * @param finalScene Indica la scena da renderizzare.
 * @param finalText Indica il testo da stampare
 * @param nEnemies Indica i nemici uccisi (usato da finalText)
 * @param width Indica la larghezza della finestra creata (usato da finalText)
 * @param height Indica l'altezza della finestra creata (usato da finalText)
 * @param gameStatus Flag per indicare se renderizzare finalText
*/
bool attendiInput(SDL_Renderer* renderer, const Object& finalScene, TextRenderer& finalText, int nEnemies, int width, int height, GameStatus gameStatus);

/**
 * @brief Crea un nuovo nemico e lo aggiunge al vettore dei nemici.
 *
 * Questo metodo crea un nuovo nemico con i parametri specificati e lo aggiunge al vettore dei nemici passato come argomento. Inoltre, incrementa il valore di nEnemies passato come puntatore per tener traccia del numero totale di nemici.
 *
 * @param[in,out] enemies Il vettore dei nemici a cui aggiungere il nuovo nemico.
 * @param[in] renderer Il puntatore al renderer SDL utilizzato per il rendering del gioco.
 * @param[in] enemyX La coordinata x iniziale del nuovo nemico.
 * @param[in] enemyY La coordinata y iniziale del nuovo nemico.
 * @param[in] bulletSpeed La velocità dei proiettili sparati dal nemico.
 * @param[in] width La larghezza del nemico.
 * @param[in] height L'altezza del nemico.
 */
void spawnNewEnemy(std::vector<Enemy>& enemies, SDL_Renderer* renderer, int enemyX, int enemyY, int bulletSpeed, int width, int height);


#endif // SOTTOPROGRAMMI_H
