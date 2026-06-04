#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;
#define maxTabella 81   //9*9
#define navi 6
#define punti 21
//COLORI ANSI
#define ROSSO "\033[31m"
#define VERDE "\033[32m"
#define GIALLO "\033[33m"
#define BLU "\033[34m"
#define DEFAULT "\033[0m"

// ---------------------------------- ELENCO FUNZIONI ----------------------------------
void menu(int&);    //MENU INIZIALE
void istruzioni();
void menuPos1();    //ISTRUZIONI POSIZIONAMENTO COORD.1
void menuPos2();    //ISTRUZIONI POSIZIONAMENTO COORD.2-3-4-5
void matrix(int[], string&, string&, string&, string&, string&, string&);   //CAMPO DI BATTAGLIA
void posiziona (int[], string, string&, string&, string&, string&, string&, string&);   //POSIZIONAMENTO NAVI
bool collision (int[], int[], string&, int); //RILEVA COLLISIONE
int assegnazione(int[], string);    //TRADUZIONE COORDINATA IN INDICE
int turno (int[], int[], string, string&, string&, string&, string&, string&, string&, int&); //TURNO GIOCATORE
void cancella (string&, string&, string&, string&, string&, string&, string);   //RICONOSCIMENTO NAVI DISTRUTTE
void wait(int); //TEMPO DI ATTESA
void start(string&, string&, int&, int&, int[], int[], int[], int[], string&, string&, string&, string&, string&, string&, string&, string&, string&, string&, string&, string&, int&, int&);   //INIZIO PARTITA
int playagain(string, string, int, int);    //GIOCA ANCORA
void clean();   //PULIZIA TERMINALE
void showHistory(); //MOSTRA CRONOLOGIA PARTITE

// ---------------------------------- MAIN ----------------------------------
int main() {
    int scelta1=1;
    int victory1, victory2, total_score1=0, total_score2=0;
    do {
        menu(scelta1);
        switch (scelta1) {
            case 0:
            break;

            case 1: {
            clean();
            int scelta=1, won1=0, won2=0;
            string p1, p2;
            cout << "------ " << GIALLO << "Inserisci i nickname dei giocatori" << DEFAULT << " ------\n" << endl;
            cout << "\tGIOCATORE 1: ";
            cin >> p1;
            cout << "\tGIOCATORE 2: ";
            cin >> p2;
            clean();

            do {
                string boat1_1="", boat2_1="", boat3_1="", boat4_1="", boat5_1="", boat6_1="", boat1_2="", boat2_2="", boat3_2="", boat4_2="", boat5_2="", boat6_2="";
                int n1[maxTabella], n2[maxTabella], v1[maxTabella], v2[maxTabella], score1=0, score2=0;
                for (int i=0; i<maxTabella; i++) {
                    n1[i] = 0;
                    n2[i] = 0;
                    v1[i] = 0;
                    v2[i] = 0;
                }

                //ASSEGNAZIONE POSIZIONE NAVI
                posiziona(n1, p1, boat1_1, boat2_1, boat3_1, boat4_1, boat5_1, boat6_1);
                cout << GIALLO << "\n\nSALVATAGGIO INFORMAZIONI IN ";
                for (int i=5; i>0; i--) {
                    cout << i;
                    wait(250);
                    for (int j=0; j<3; j++) {
                        wait(250);
                        cout << ".";
                    }
                    cout << " ";
                }
                cout << DEFAULT;
                clean();

                posiziona(n2, p2, boat1_2, boat2_2, boat3_2, boat4_2, boat5_2, boat6_2);
                cout << GIALLO << "\n\nSALVATAGGIO INFORMAZIONI IN ";
                for (int i=5; i>0; i--) {
                    cout << i;
                    wait(250);
                    for (int j=0; j<3; j++) {
                        wait(250);
                        cout << ".";
                    }
                    cout << " ";
                }
                cout << DEFAULT;
                clean();

                //INIZIO PARTITA
                cout << "---------- " << GIALLO << "SIMBOLI TABELLONE" << DEFAULT << " ----------" << endl; 
                cout << ">" << ROSSO << " X" << DEFAULT << "\t--->\tNave colpita" << endl;
                cout << ">" << BLU << " O" << DEFAULT << "\t--->\tNave mancata" << endl;
                cout << "---------------------------------------" << endl << endl;

                start(p1, p2, won1, won2, v1, v2, n1, n2, boat1_1, boat2_1, boat3_1, boat4_1, boat5_1, boat6_1, boat1_2, boat2_2, boat3_2, boat4_2, boat5_2, boat6_2, score1, score2);
                scelta = playagain(p1,  p2, won1, won2);
                clean();
                //FINE PARTITA
                total_score1 += score1;
                total_score2 += score2;

            } while (scelta!=0);

            //SALVATAGGIO PARTITA IN CRONOLOGIA
            ofstream file("history.txt", ios::app);
            file << p1 << " " << p2 << endl;;
            file << won1 << " " << won2 << endl;
            file << total_score1 << " " << total_score2 << endl;
            file.close();
            break;
            }

            case 2: {
            clean ();
            showHistory();
            break;
            }

            case 3: {
            clean ();
            ofstream file("history.txt");
            file << "";
            file.close();
            cout << VERDE << "Cronologia cancellata con successo!" << DEFAULT << endl << endl;
            break;
            }

            case 4: {
            clean ();
            istruzioni();
            clean();
            break;
            }
            
            default:
            clean ();
            cout << "Scelta errata! Dai un'occhiata al menu ;)" << endl << endl;
        }
    } while (scelta1!=0);

    return 0;
}



//---------------------------------- FUNZIONI UTILIZZATE ----------------------------------

void menu(int &scelta) {
    cout << "----------- " << BLU << "BATTAGLIA NAVALE" << DEFAULT << " -----------" << endl;
    cout << "1) " << VERDE << "Inizia una nuova partita" << DEFAULT << endl;
    cout << "2) Visualizza cronologia partite" << endl;
    cout << "3) Cancella cronologia partite" << endl;
    cout << "4) " << GIALLO << "Istruzioni gioco" << DEFAULT << endl;
    cout << "0) " << ROSSO << "Esci dal gioco" << DEFAULT << endl;
    cout << "----------------------------------------" << endl;
    cout << "SCELTA: ";
    cin >> scelta;
    cout << endl;
}

void istruzioni() {
    string a;
    cout << "------------------- " << BLU << "ISTRUZIONI GIOCO" << DEFAULT << " -------------------" << endl;
    cout << GIALLO << "OBIETTIVO" << DEFAULT << endl;
    cout << "Affonda tutte le navi nemiche prima che il tuo" << endl;
    cout << "avversario distrugga le tue. Vince chi raggiunge" << endl;
    cout << "21 punti per primo (un punto per ogni segmento colpito)." << endl;
    cout << endl;
    cout << GIALLO << "LE NAVI" << DEFAULT << endl;
    cout << "Ogni giocatore posiziona 6 navi sulla griglia 9x9:" << endl;
    cout << "  - 1 nave da 5 segmenti" << endl;
    cout << "  - 2 navi da 4 segmenti" << endl;
    cout << "  - 2 navi da 3 segmenti" << endl;
    cout << "  - 1 nave da 2 segmenti" << endl;
    cout << endl;
    cout << GIALLO << "POSIZIONAMENTO" << DEFAULT << endl;
    cout << "Inserisci la prima coordinata nel formato" << endl;
    cout << VERDE << "LETTERA + NUMERO" << DEFAULT << " (es. A1, E5, H9)." << endl;
    cout << "Le coordinate successive si scelgono con i tasti" << endl;
    cout << VERDE << "W" << DEFAULT << " (su)  " << VERDE << "S" << DEFAULT << " (giu)  " << VERDE << "A" << DEFAULT << " (sinistra)  " << VERDE << "D" << DEFAULT << " (destra)." << endl;
    cout << "Le navi devono essere posizionate in linea retta." << endl;
    cout << endl;
    cout << GIALLO << "TURNI" << DEFAULT << endl;
    cout << "I giocatori si alternano inserendo una coordinata" << endl;
    cout << "da bombardare. Se colpisci una nave, " << VERDE << "giochi ancora!" << DEFAULT << endl;
    cout << "Se colpisci una casella gia' bombardata, " << ROSSO << "perdi il turno." << DEFAULT << endl;
    cout << endl;
    cout << GIALLO << "SIMBOLI SUL TABELLONE" << DEFAULT << endl;
    cout << ROSSO << "  X" << DEFAULT << "  -->  Nave colpita" << endl;
    cout << BLU << "  O" << DEFAULT << "  -->  Colpo mancato" << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << "\nDIGITA UN CARATTERE QUALSIASI PER TORNARE AL MENU: ";
    cin >> a;
}

void menuPos1() {
    cout << "------ " << BLU << "ISTRUZIONI POSIZIONAMENTO" << DEFAULT << " ------" << endl; 
    cout << "Inserisci la prima coordinata in questo" << endl;
    cout << "formato: " << GIALLO << "LETTERA + NUMERO" << DEFAULT << endl << endl;
    cout << "ESEMPIO: 'A2', 'E8', 'H5'..." << endl;
    cout << "---------------------------------------" << endl << endl;
}

void menuPos2() {
    cout << "------ " << BLU << "ISTRUZIONI POSIZIONAMENTO" << DEFAULT << " ------" << endl; 
    cout << "Inserisci un comando e premi invio:" << endl;
    cout << "\tW ---> Coordinata sopra" << endl;
    cout << "\tS ---> Coordinata sotto" << endl;
    cout << "\tD ---> Coordinata a destra" << endl;
    cout << "\tA ---> Coordinata a sinistra" << endl;
    cout << "---------------------------------------" << endl << endl;
}

void clean() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void posiziona (int n[], string p, string &boat1, string &boat2, string &boat3, string &boat4, string &boat5, string &boat6) {
    int l=5;
    cout << endl << GIALLO << p << DEFAULT << ", scegli le coordinate delle tue navi!\n" << endl;
    cout << endl;
    for (int j=0; j<navi; j++) {
    start_for:
        menuPos1();
        matrix(n, boat1, boat2, boat3, boat4, boat5, boat6);
        cout << endl;
        int indici[5];
        int count=0;
        string coord, successiva, precedente, sopra, sotto, prov;    

        //COORDINATA 1
        cout << "NAVE DA "<<l<<" - Coordinata 1: ";
        cin >> coord;
        while (coord.length()!=2 || coord[0]<65 || coord[0]>73 || coord[1]<49 || coord[1]>57) {
            cout << "Coordinata inesistente!\nNAVE DA "<<l<<" - Coordinata 1: ";
            cin >> coord;
        }
        prov = coord;
        indici[count] = assegnazione(n, coord);

        if (j==0) {
            if (collision (n, indici, boat1, count))
                goto start_for;
            boat1 += coord;
        } else if (j==1) {
            if (collision (n, indici, boat2, count))
                goto start_for;
            boat2 += coord;
        } else if (j==2) {
            if (collision (n, indici, boat3, count))
                goto start_for;
            boat3 += coord;
        } else if (j==3) {
            if (collision (n, indici, boat4, count))
                goto start_for;
            boat4 += coord;
        } else if (j==4) {
            if (collision (n, indici, boat5, count))
                goto start_for;
            boat5 += coord;
        } else {
            if (collision (n, indici, boat6, count))
                goto start_for;
            boat6 += coord;
        }
        
        n[indici[count]] = 1;
        count++;
        clean();
        menuPos2();
        matrix(n, boat1, boat2, boat3, boat4, boat5, boat6);

        //COORDINATA 2
        successiva += coord[0];
        successiva += coord[1] + 1;
        precedente += coord[0];
        precedente += coord[1] - 1;
        sopra += coord[0] - 1;
        sopra += coord[1];
        sotto += coord[0] + 1;
        sotto += coord[1];

        do {
            cout << "\nNAVE DA "<<l<<" - Coordinata 2: ";
            cin >> coord;
            while (coord.length()!=1 || (coord!="W" && coord!="w" && coord!="S" && coord!="s" && coord!="D" && coord!="d" && coord!="A" && coord!="a")) {
                cout << "Coordinata errata! Inserisci uno dei comandi WASD\nNAVE DA "<<l<<" - Coordinata 2: ";
                cin >> coord;
            }
            if (coord=="W" || coord=="w")
                coord = sopra;
            else if (coord=="S" || coord=="s")
                coord = sotto;
            else if (coord=="D" || coord=="d")
                coord = successiva;
            else if (coord=="A" || coord=="a")
                coord = precedente;

            if (coord.length()!=2 || coord[0]<65 || coord[0]>73 || coord[1]<49 || coord[1]>57)
                cout << "FUORI DAI BORDI! Inserisci uno dei comandi WASD" << endl;

        } while (coord.length()!=2 || coord[0]<65 || coord[0]>73 || coord[1]<49 || coord[1]>57);

        indici[count] = assegnazione(n, coord);

        if (j==0) {
            if (collision (n, indici, boat1, count))
                goto start_for;
            boat1 += coord;
        } else if (j==1) {
            if (collision (n, indici, boat2, count))
                goto start_for;
            boat2 += coord;
        } else if (j==2) {
            if (collision (n, indici, boat3, count))
                goto start_for;
            boat3 += coord;
        } else if (j==3) {
            if (collision (n, indici, boat4, count))
                goto start_for;
            boat4 += coord;
        } else if (j==4) {
            if (collision (n, indici, boat5, count))
                goto start_for;
            boat5 += coord;
        } else {
            if (collision (n, indici, boat6, count))
                goto start_for;
            boat6 += coord;
        }
        
        n[indici[count]] = 1;
        count++;
        clean();
        menuPos2();
        matrix(n, boat1, boat2, boat3, boat4, boat5, boat6);
        cout << endl;

        //COORDINATE 3-4-5
        for (int i=3; i<=l; i++) {
            if (coord==successiva || coord==precedente) {
                if (coord==successiva)
                    successiva[1] += 1;
                else
                    precedente[1] -= 1;

                do {
                    cout << "NAVE DA "<<l<<" - Coordinata " << i << ": ";
                    cin >> coord;
                    while (coord.length()!=1 || (coord!="D" && coord!="d" && coord!="A" && coord!="a")) {
                        cout << "Coordinata errata! Inserisci uno dei comandi AD\nNAVE DA "<<l<<" - Coordinata "<<i<<": ";
                        cin >> coord;
                    }
                    if (coord=="D" || coord=="d")
                        coord = successiva;
                    else if (coord=="A" || coord=="a")
                        coord = precedente;
                    
                    if (coord.length()!=2 || coord[0]<65 || coord[0]>73 || coord[1]<49 || coord[1]>57)
                        cout << "FUORI DAI BORDI! Inserisci uno dei comandi AD" << endl;
                } while (coord.length()!=2 || coord[0]<65 || coord[0]>73 || coord[1]<49 || coord[1]>57);

            } else {
                if (coord == sopra)
                    sopra[0] -= 1;
                else
                    sotto[0] += 1;
                
                do {
                    cout << "NAVE DA "<<l<<" - Coordinata " << i << ": ";
                    cin >> coord;
                    while (coord.length()!=1 || (coord!="W" && coord!="w" && coord!="S" && coord!="s")) {
                        cout << "Coordinata errata! Inserisci uno dei comandi WS\nNAVE DA "<<l<<" - Coordinata "<<i<<": ";
                        cin >> coord;
                    }
                    if (coord=="W" || coord=="w")
                        coord = sopra;
                    else if (coord=="S" || coord=="s")
                        coord = sotto;
                    
                    if (coord.length()!=2 || coord[0]<65 || coord[0]>73 || coord[1]<49 || coord[1]>57)
                        cout << "FUORI DAI BORDI! Inserisci uno dei comandi WS" << endl;
                } while (coord.length()!=2 || coord[0]<65 || coord[0]>73 || coord[1]<49 || coord[1]>57);
            }

            indici[count] = assegnazione(n, coord);

            if (j==0) {
                if (collision (n, indici, boat1, count))
                    goto start_for;
                boat1 += coord;
            } else if (j==1) {
                if (collision (n, indici, boat2, count))
                    goto start_for;
                boat2 += coord;
            } else if (j==2) {
                if (collision (n, indici, boat3, count))
                    goto start_for;
                boat3 += coord;
            } else if (j==3) {
                if (collision (n, indici, boat4, count))
                    goto start_for;
                boat4 += coord;
            } else {
                if (collision (n, indici, boat5, count))
                    goto start_for;
                boat5 += coord;
            }
            
            n[indici[count]] = 1;
            count++;
            clean();
            if ((l==5 && i<5) || (l==4 && i<4) || (l==3 && i<3)) {
                menuPos2();
                matrix(n, boat1, boat2, boat3, boat4, boat5, boat6);
                cout << endl;
            }
        }
        if (j==0 || j==2 || j==4)
            l--;
    }
    //cout << endl << "DEBUG: " << boat1 << " " << boat2 << " " << boat3 << " " << boat4 << " " << boat5 << " " << boat6;
}

bool collision (int n[], int indici[], string &boat, int count) {
    clean();
    int indice;
    indice = indici[count];
    if (n[indice] == 1) {
        cout << ROSSO << "\nCOLLISIONE RILEVATA! Riposiziona la tua nave da capo" << DEFAULT << endl << endl;
        boat = "";
        for (int i=0; i<count; i++)
            n[indici[i]] = 0;
        return true;
    } else {
        return false;
    }
}

void start(string &p1, string &p2, int &won1, int &won2, int v1[], int v2[], int n1[], int n2[], string &boat1_1, string &boat2_1, string &boat3_1, string &boat4_1, string &boat5_1, string &boat6_1, string &boat1_2, string &boat2_2, string &boat3_2, string &boat4_2, string &boat5_2, string &boat6_2, int &score1, int &score2) {
    srand(time(NULL));
    int n = (rand()%2 + 1), ris=0;
    if (n==1) {  //gioca prima il giocatore 1
        while (ris!=1) {
            turno1_1:
                ris = turno(v1, n2, p1, boat1_2, boat2_2, boat3_2, boat4_2, boat5_2, boat6_2, score1);
                if (ris==1) {
                    cout << "\nL'ammiraglio " << GIALLO << p1 << DEFAULT << " ha vinto!";
                    won1++;
                    break;
                } else if (ris==2) {
                    goto turno1_1;
                }
            turno2_1:
                ris = turno(v2, n1, p2, boat1_1, boat2_1, boat3_1, boat4_1, boat5_1, boat6_1, score2);
                if (ris==1) {
                    cout << "\nL'ammiraglio " << GIALLO << p2 << DEFAULT << " ha vinto!";
                    won2++;
                } else if (ris==2) {
                    goto turno2_1;
                }
        }
    } else {    //gioca prima il giocatore 2
        while (ris!=1) {
            turno1_2:
                ris = turno(v2, n1, p2, boat1_1, boat2_1, boat3_1, boat4_1, boat5_1, boat6_1, score2);
                if (ris==1) {
                    cout << "\nL'ammiraglio " << GIALLO << p2 << DEFAULT << " ha vinto!"<< endl << endl;
                    won2++;
                    break;
                } else if (ris==2) {
                    goto turno1_2;
                }
            turno2_2:
                ris = turno(v1, n2, p1, boat1_2, boat2_2, boat3_2, boat4_2, boat5_2, boat6_2, score1);
                if (ris==1) {
                    cout << "\nL'ammiraglio " << GIALLO << p1 << DEFAULT << " ha vinto!"<< endl << endl;
                    won1++;
                } else if (ris==2) {
                    goto turno2_2;
                }
        }
    }
}

int playagain(string p1, string p2, int won1, int won2) {
    int scelta;
    cout << endl << endl << p1 << " - " << VERDE << won1 << DEFAULT << "\t" << p2 << " - " << VERDE << won2 << DEFAULT << endl;
    cout << "\nVuoi giocare ancora?\n" << BLU << "1" << DEFAULT << " --> SI\n" << ROSSO << "0" << DEFAULT << " --> NO" << endl;
    cout << "\nSCELTA: ";
    cin >> scelta;
    while (scelta!=0 && scelta!=1) {
        cout << "Valore errato!\nSCELTA: ";
        cin >> scelta;
    }

    return scelta;
}

void matrix(int n[], string &b1, string &b2, string &b3, string &b4, string &b5, string &b6) {
    cout << "\t   1 2 3 4 5 6 7 8 9" << endl;
    
    char riga = 'A';
    for (int i = 0; i < 9; i++) {       //RIGHE
        cout << "\t" << riga << " |";
        for (int j = 0; j < 9; j++) {   //COLONNE
            int index = i * 9 + j;
            if (n[index]==0)
                cout << " " << "|";
            else if (n[index]==1)
                cout << ROSSO << "X" << DEFAULT << "|";
            else   
                cout << BLU << "O" << DEFAULT << "|";

            if (j==8 && i==2)
                cout << "\t\t------------- " << GIALLO << "RADAR" << DEFAULT << " -------------";
            if (j==8 && i==3) {
                if (b1.empty())
                    cout << ROSSO << "\t\tNAVE DA 5" << DEFAULT << " - ";
                else
                    cout << VERDE << "\t\tNAVE DA 5" << DEFAULT << " - ";
                if (b2.empty())
                    cout << ROSSO << "NAVE DA 4" << DEFAULT << " - ";
                else
                    cout << VERDE << "NAVE DA 4" << DEFAULT << " - ";
                if (b3.empty())
                    cout << ROSSO << "NAVE DA 4" << DEFAULT;
                else
                    cout << VERDE << "NAVE DA 4" << DEFAULT;  
            }                  
            if (j==8 && i==5) {
                if (b4.empty())
                    cout << ROSSO << "\t\tNAVE DA 3" << DEFAULT << " - ";
                else
                    cout << VERDE << "\t\tNAVE DA 3" << DEFAULT << " - ";
                if (b5.empty())
                    cout << ROSSO << "NAVE DA 3" << DEFAULT << " - ";
                else
                    cout << VERDE << "NAVE DA 3" << DEFAULT << " - ";
                if (b6.empty())
                    cout << ROSSO << "NAVE DA 2" << DEFAULT;
                else
                    cout << VERDE << "NAVE DA 2" << DEFAULT;
            }
            if (j==8 && i==6)
                cout << "\t\t---------------------------------";
        }
        cout << endl;
        riga++;
    }
}

int assegnazione(int n[], string coord) {
    int N1, N2, indice;
    N1 = coord[0] - 65;
    N2 = coord[1] - 48;
    indice = (9*N1 + N2) - 1;

    return indice;
}

void cancella (string &boat1, string &boat2, string &boat3, string &boat4, string &boat5, string &boat6, string coord) {
    for (int i=0; i<boat1.length(); i=i+2) {
        if (coord == boat1.substr(i, 2)) {
            boat1.erase(i, 2);
            i = i-2;
            if (boat1.empty()) {
                cout << ROSSO << "\n\tNAVE DA 5 DISTRUTTA!" << DEFAULT << endl;
            }
            return;
        }
    }
    for (int i=0; i<boat2.length(); i=i+2) {
        if (coord == boat2.substr(i, 2)) {
            boat2.erase(i, 2);
            i = i-2;
            if (boat2.empty()) {
                cout << ROSSO << "\n\tNAVE DA 4 DISTRUTTA!" << DEFAULT << endl;
            }
            return;
        }
    }
    for (int i=0; i<boat3.length(); i=i+2) {
        if (coord == boat3.substr(i, 2)) {
            boat3.erase(i, 2);
            i = i-2;
            if (boat3.empty()) {
                cout << ROSSO << "\n\tNAVE DA 4 DISTRUTTA!" << DEFAULT << endl;
            }
            return;
        }
    }
    for (int i=0; i<boat4.length(); i=i+2) {
        if (coord == boat4.substr(i, 2)) {
            boat4.erase(i, 2);
            i = i-2;
            if (boat4.empty()) {
                cout << ROSSO << "\n\tNAVE DA 3 DISTRUTTA!" << DEFAULT << endl;
            }
            return;
        }
    }
    for (int i=0; i<boat5.length(); i=i+2) {
        if (coord == boat5.substr(i, 2)) {
            boat5.erase(i, 2);
            i = i-2;
            if (boat5.empty()) {
                cout << ROSSO << "\n\tNAVE DA 3 DISTRUTTA!" << DEFAULT << endl;
            }
            return;
        }
    }
    for (int i=0; i<boat6.length(); i=i+2) {
        if (coord == boat6.substr(i, 2)) {
            boat6.erase(i, 2);
            i = i-2;
            if (boat6.empty()) {
                cout << ROSSO << "\n\tNAVE DA 2 DISTRUTTA!" << DEFAULT << endl;
            }
            return;
        }
    }
}

int turno (int v[], int n[], string p, string &boat1, string &boat2, string &boat3, string &boat4, string &boat5, string &boat6, int &score) {
    int N1, N2, indice;
    string coord;
    int repeat = 0;
    cout << "---------------------------------------" << endl;
    matrix(v, boat1, boat2, boat3, boat4, boat5, boat6);
    cout << "\nAmmiraglio " << GIALLO << p << DEFAULT << ", tocca a te!" << endl;
    cout << "COORDINATA DA BOMBARDARE: ";
    cin >> coord;
    while (coord.length()!=2 || coord[0]<65 || coord[0]>73 || coord[1]<49 || coord[1]>57) {
        cout << "Coordinata inesistente!\nCOORDINATA DA BOMBARDARE: ";
        cin >> coord;
    }
    N1 = coord[0] - 65;
    N2 = coord[1] - 48;
    indice = (9*N1 + N2) - 1;
    
    if (v[indice]==0) {
        if (n[indice] == 1) {
            v[indice] = 1;
            repeat = 1;
            score++;
        } else {
            v[indice] = 2;
        }
    } else {
        cout << "\nComplimenti ammiraglio, hai colpito una coordinata bombardata in precedenza!\nPurtroppo perdi questo turno :(\n" << endl;
    }
    cout << endl;
    matrix(v, boat1, boat2, boat3, boat4, boat5, boat6);
    cancella (boat1, boat2, boat3, boat4, boat5, boat6, coord);
    cout << VERDE << "\nIL TUO PUNTEGGIO" << DEFAULT << ": " << score << endl;
    cout << "---------------------------------------" << endl;
    wait(2500);
    clean();

    if (score>=punti) {
        return 1;
    } else {
        if (repeat == 1)
            return 2;
        else
            return 0;
    }
}

void wait(int n) {
    clock_t start = clock();
    clock_t stop = start;
    while ((stop-start)<n)
        stop = clock();
    
    //cout << (stop-start)/1000 << "s" << endl;
}

void showHistory() {
    int s1, s2;
    string p1, p2;
    int victory1, victory2;
    cout << "------------------ " << GIALLO << "ELENCO PARTITE" << DEFAULT << " ------------------" << endl;
    ifstream file("history.txt");
    if (!(file >> p1)) {
        cout << "Nessuna partita salvata" << endl;
        file.close();
    } else {
    ifstream file("history.txt");
    while (file >> p1) {
        file >> p2 >> victory1 >> victory2 >> s1 >> s2;
        cout << p1 << " - " << VERDE << victory1 << DEFAULT << " (" << s1 << "pt) \tVS\t " << p2 << " - " << VERDE << victory2 << DEFAULT << " (" << s2 << "pt) " << endl;
    }
    file.close();
    }
    cout << "----------------------------------------------------" << endl << endl;
}