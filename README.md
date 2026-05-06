# - Ship Battle -

L'applicazione di **Battaglia Navale** sviluppata interamente in C++ e permette a due persone di sfidarsi in locale attraverso il terminale.

---

## Descrizione📜
Il gioco riproduce la classica sfida tattica tra due ammiragli. Ogni giocatore ha a disposizione una griglia **9x9** dove posizionare strategicamente la propria flotta. L'obiettivo è affondare tutte le navi nemiche prima che sia l'avversario a farlo.

## Caratteristiche principali💻
* **Interfaccia colorata:** Codici colore ANSI per distinguere i colpi andati a segno (ROSSO) dai colpi mancati (BLU);
* **Sistema di posizionamento WASD:** Dopo la scelta della prima coordinata, si possono costruire le navi con i tasti WASD;
* **Gestione flotta:** Ogni giocatore dispone di 6 navi di diverse lunghezze (da 5 a 2 caselle);
* **Salvataggio cronologia:** Inserimento risultati in un file chiamato `history.txt`;
* **Multi-Piattaforma:** Distinzione tra macchina Windows/Linux per corretta pulizia del terminale.

## Come avviare il programma▶️
1.  Scarica il file `game.cpp`
2.  Compilalo con un compilatore C++ (es. `g++ game.cpp -o ShipBattle`)
3.  Esegui il file generato
4.  Inserisci i nomi dei due giocatori e divertiti!

## Conoscenze applicate🎒
Per realizzare questo software ho applicato diversi concetti studiati quest'anno:
* **Vettori e indici:** Per la gestione del campo di battaglia;
* **Funzioni:** Per dividere il codice in blocchi logici e riutilizzabili;
* **File I/O:** Uso delle librerie `fstream` per leggere e scrivere la cronologia;
* **Libreria Time:** Per generare ritardi (`wait`) e casualità (`srand`).

---
*Progetto realizzato da Altavilla Mattia come Capolavoro per l'A.S.2025/26*
