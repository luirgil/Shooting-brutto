#ifndef CONSTANTS_H
#define CONSTANTS_H

/**
 * @file constants.hpp
 * @brief Contiene le costanti utilizzate nel gioco.
 */

#define BULLETWIDHT 70 /**< Larghezza del proiettile. */
#define BULLETHEIGHT 22 /**< Altezza del proiettile. */

#define ENEMYWIDHT 114 /**< Larghezza del nemico. */
#define ENEMYHEIGHT 219 /**< Altezza del nemico. */

#define ANY_LIFEBAR_SIZE_WIDHT 200 /**< Larghezza predefinita della barra della vita. */
#define ANY_LIFEBAR_SIZE_HEIGHT 22 /**< Altezza predefinita della barra della vita. */

#define DEFAULT_WIDTH 640 /**< Larghezza predefinita della finestra del gioco. */
#define DEFAULT_HEIGHT 480 /**< Altezza predefinita della finestra del gioco. */

typedef enum {
    running, /**< Il Gioco è in esecuzione. */
    quitted, /**< Il Gioco è stato chiuso attraverso l'apposito tasto di chiusura. */
    died /**< Il personaggio è morto. */
} GameStatus; /**< Definisce lo stato del gioco. */


#endif
