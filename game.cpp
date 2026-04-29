#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;
#define maxTabella 81   //9*9
#define navi 6
#define punti 21

// ---------------------------------- ELENCO FUNZIONI ----------------------------------
void menu(int &scelta);
void matrix(int n[]);
void posiziona (int n[], string p);
void assegnazione(int n[], string coord);
int turno (int v[], int n[], string p);
void wait(int n);
void start(string &p1, string &p2, int &won1, int &won2, int v1[], int v2[], int n1[], int n2[]);
int playagain(string p1, string p2, int won1, int won2);
void clean();
void showHistory();

// ---------------------------------- MAIN ----------------------------------
int main() {
    int scelta1=1;
    int victory1, victory2;
    do {
        menu(scelta1);
        switch (scelta1) {
            case 0:
            break;

            case 1: {
            clean();
            int scelta=1, won1=0, won2=0;
            string p1, p2;
            cout << "\tGIOCATORE 1: ";
            cin >> p1;
            cout << "\tGIOCATORE 2: ";
            cin >> p2;

            do {
                int n1[maxTabella], n2[maxTabella], v1[maxTabella], v2[maxTabella];
                for (int i=0; i<maxTabella; i++) {
                    n1[i] = 0;
                    n2[i] = 0;
                    v1[i] = 0;
                    v2[i] = 0;
                }

                //ASSEGNAZIONE POSIZIONE NAVI
                posiziona(n1, p1);
                posiziona(n2, p2);

                //INIZIO PARTITA
                cout << "---------- SIMBOLI TABELLONE ----------" << endl; 
                cout << "'X' ---> Nave colpita" << endl;
                cout << "'O' ---> Nave mancata" << endl;
                cout << "---------------------------------------" << endl << endl;

                start(p1, p2, won1, won2, v1, v2, n1, n2);
                scelta = playagain(p1,  p2, won1, won2);
                clean();
                //FINE PARTITA

            } while (scelta!=0);

            //SALVATAGGIO PARTITA IN CRONOLOGIA
            ofstream file("history.txt", ios::app);
            file << p1 << " " << p2 << endl;;
            file << won1 << " " << won2 << endl;
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
            cout << "Cronologia cancellata con successo!" << endl << endl;
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
    cout << "----------- BATTAGLIA NAVALE -----------" << endl;
    cout << "1) Inizia una nuova partita" << endl;
    cout << "2) Visualizza cronologia partite" << endl;
    cout << "3) Cancella cronologia partite" << endl;
    cout << "0) Esci dal gioco" << endl;
    cout << "----------------------------------------" << endl;
    cout << "SCELTA: ";
    cin >> scelta;
    cout << endl;
}

void clean() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void posiziona (int n[], string p) {
    string c;
    int l=5;
    cout << endl << p << ", scegli le coordinate delle tue navi!\n";
    for (int j=0; j<navi; j++) {                            //GIOCATORE 2
        string coord, successiva, precedente, sopra, sotto, prov;    
        cout << endl;
        matrix(n);

        //COORDINATA 1
        cout << "\nNAVE DA "<<l<<" - Coordinata 1: ";
        cin >> coord;
        while (coord.length()!=2 || coord[0]<65 || coord[0]>73 || coord[1]<49 || coord[1]>57) {
            cout << "Coordinata inesistente!\nNAVE DA "<<l<<" - Coordinata 1: ";
            cin >> coord;
        }
        prov = coord;
        assegnazione(n, coord);

        //COORDINATA 2
        successiva += coord[0];
        successiva += coord[1] + 1;
        precedente += coord[0];
        precedente += coord[1] - 1;
        sopra += coord[0] - 1;
        sopra += coord[1];
        sotto += coord[0] + 1;
        sotto += coord[1];

        cout << "NAVE DA "<<l<<" - Coordinata 2: ";
        cin >> coord;
        while ((coord.length()!=2 || coord[0]<65 || coord[0]>73 || coord[1]<49 || coord[1]>57) || (coord!=successiva && coord!=precedente && coord!=sopra && coord!=sotto)) {
            cout << "Coordinata errata! Inserisci una coordinata adiacente!\nNAVE DA "<<l<<" - Coordinata 2: ";
            cin >> coord;
        }
        assegnazione(n, coord);

        //COORDINATE 3-4-5
        for (int i=3; i<=l; i++) {
            if (coord==successiva) {
                successiva[1] += 1;
                cout << "NAVE DA "<<l<<" - Coordinata " << i << ": ";
                cin >> coord;
                while ((coord.length()!=2 || coord[0]<65 || coord[0]>73 || coord[1]<49 || coord[1]>57) || (coord!=successiva && coord!=precedente)) {
                    cout << "Coordinata errata! Inserisci una coordinata adiacente nella riga "<<prov[0]<<"!\nNAVE DA "<<l<<" - Coordinata " << i << ": ";
                    cin >> coord;
                }
                assegnazione(n, coord);
            } else if (coord==precedente) {
                precedente[1] -= 1;
                cout << "NAVE DA "<<l<<" - Coordinata " << i << ": ";
                cin >> coord;
                while ((coord.length()!=2 || coord[0]<65 || coord[0]>73 || coord[1]<49 || coord[1]>57) || (coord!=successiva && coord!=precedente)) {
                    cout << "Coordinata errata! Inserisci una coordinata adiacente nella riga "<<prov[0]<<"!\nNAVE DA "<<l<<" - Coordinata " << i << ": ";
                    cin >> coord;
                }
                assegnazione(n, coord);
            } else if (coord==sopra) {
                sopra[0] -= 1;
                cout << "NAVE DA "<<l<<" - Coordinata " << i << ": ";
                cin >> coord;
                while ((coord.length()!=2 || coord[0]<65 || coord[0]>73 || coord[1]<49 || coord[1]>57) || (coord!=sopra && coord!=sotto)) {
                    cout << "Coordinata errata! Inserisci una coordinata adiacente nella colonna "<<prov[1]<<"!\nNAVE DA "<<l<<" - Coordinata " << i << ": ";
                    cin >> coord;
                }
                assegnazione(n, coord);
            } else {
                sotto[0] += 1;
                cout << "NAVE DA "<<l<<" - Coordinata " << i << ": ";
                cin >> coord;
                while ((coord.length()!=2 || coord[0]<65 || coord[0]>73 || coord[1]<49 || coord[1]>57) || (coord!=sopra && coord!=sotto)) {
                    cout << "Coordinata errata! Inserisci una coordinata adiacente nella colonna "<<prov[1]<<"!\nNAVE DA "<<l<<" - Coordinata " << i << ": ";
                    cin >> coord;
                }
                assegnazione(n, coord);
            }
        }
        if (j==0 || j==2 || j==4)
        l--;
    }
    cout << endl;
    matrix(n);
    cout << "\nDigita un tasto e premi invio per nascondere le tue posizioni: ";
    cin >> c;
    clean();
}

void start(string &p1, string &p2, int &won1, int &won2, int v1[], int v2[], int n1[], int n2[]) {
    srand(time(NULL));
    int n = (rand()%2 + 1), ris=0;
    if (n==1) {  //gioca prima il giocatore 1
        while (ris!=1) {
            ris = turno(v1, n2, p1);
            if (ris==1) {
                cout << "\nL'ammiraglio " << p1 << " ha vinto!";
                won1++;
                break;
            }
            ris = turno(v2, n1, p2);
            if (ris==1) {
                cout << "\nL'ammiraglio " << p2 << " ha vinto!";
                won2++;
            }
        }
    } else {    //gioca prima il giocatore 2
        while (ris!=1) {
            ris = turno(v2, n1, p2);
            if (ris==1) {
                cout << "\nL'ammiraglio " << p2 << " ha vinto!"<< endl << endl;
                won2++;
                break;
            }
            ris = turno(v1, n2, p1);
            if (ris==1) {
                cout << "\nL'ammiraglio " << p1 << " ha vinto!"<< endl << endl;
                won1++;
            }
        }
    }
}

int playagain(string p1, string p2, int won1, int won2) {
    int scelta;
    cout << endl << endl << p1 << " - " << won1 << "\t" << p2 << " - " << won2 << endl;
    cout << "\nVuoi giocare ancora?\n1 --> SI\n0 --> NO" << endl;
    cout << "SCELTA: ";
    cin >> scelta;
    while (scelta!=0 && scelta!=1) {
        cout << "Valore errato!\nSCELTA: ";
        cin >> scelta;
    }

    return scelta;
}

void matrix(int n[]) {
    string s;
    for (int i=0; i<maxTabella; i++) {
        if (n[i]==0)
            s+=" ";
        else if (n[i]==1)
            s+="X";
        else   
            s+="O";
    }
    cout << "\t   1 2 3 4 5 6 7 8 9" << endl;
    cout << "\tA |"<<s[0]<<"|"<<s[1]<<"|"<<s[2]<<"|"<<s[3]<<"|"<<s[4]<<"|"<<s[5]<<"|"<<s[6]<<"|"<<s[7]<<"|"<<s[8]<<"|" << endl;
    cout << "\tB |"<<s[9]<<"|"<<s[10]<<"|"<<s[11]<<"|"<<s[12]<<"|"<<s[13]<<"|"<<s[14]<<"|"<<s[15]<<"|"<<s[16]<<"|"<<s[17]<<"|" << endl;
    cout << "\tC |"<<s[18]<<"|"<<s[19]<<"|"<<s[20]<<"|"<<s[21]<<"|"<<s[22]<<"|"<<s[23]<<"|"<<s[24]<<"|"<<s[25]<<"|"<<s[26]<<"|" << endl;
    cout << "\tD |"<<s[27]<<"|"<<s[28]<<"|"<<s[29]<<"|"<<s[30]<<"|"<<s[31]<<"|"<<s[32]<<"|"<<s[33]<<"|"<<s[34]<<"|"<<s[35]<<"|" << endl;
    cout << "\tE |"<<s[36]<<"|"<<s[37]<<"|"<<s[38]<<"|"<<s[39]<<"|"<<s[40]<<"|"<<s[41]<<"|"<<s[42]<<"|"<<s[43]<<"|"<<s[44]<<"|" << endl;
    cout << "\tF |"<<s[45]<<"|"<<s[46]<<"|"<<s[47]<<"|"<<s[48]<<"|"<<s[49]<<"|"<<s[50]<<"|"<<s[51]<<"|"<<s[52]<<"|"<<s[53]<<"|" << endl;
    cout << "\tG |"<<s[54]<<"|"<<s[55]<<"|"<<s[56]<<"|"<<s[57]<<"|"<<s[58]<<"|"<<s[59]<<"|"<<s[60]<<"|"<<s[61]<<"|"<<s[62]<<"|" << endl;
    cout << "\tH |"<<s[63]<<"|"<<s[64]<<"|"<<s[65]<<"|"<<s[66]<<"|"<<s[67]<<"|"<<s[68]<<"|"<<s[69]<<"|"<<s[70]<<"|"<<s[71]<<"|" << endl;
    cout << "\tI |"<<s[72]<<"|"<<s[73]<<"|"<<s[74]<<"|"<<s[75]<<"|"<<s[76]<<"|"<<s[77]<<"|"<<s[78]<<"|"<<s[79]<<"|"<<s[80]<<"|" << endl;
}

void assegnazione(int n[], string coord) {
    int N1, N2, indice;
    N1 = coord[0] - 65;
    N2 = coord[1] - 48;
    indice = (9*N1 + N2) - 1;

    n[indice] = 1;
}

int turno (int v[], int n[], string p) {
    int N1, N2, indice, cnt=0;
    string coord;
    cout << "------------------------------------" << endl;
    matrix(v);
    cout << "\nAmmiraglio " << p << ", tocca a te!" << endl;
    cout << "COORDINATA DA BOMBARDARE: ";
    cin >> coord;
    while (coord.length()!=2 || coord[0]<65 || coord[0]>73 || coord[1]<49 || coord[1]>57) {
        cout << "Coordinata inesistente!\nCOORDINATA DA BOMBARDARE: ";
        cin >> coord;
    }
    N1 = coord[0] - 65;
    N2 = coord[1] - 48;
    indice = (9*N1 + N2) - 1;
    
    if (n[indice] == 1)
        v[indice] = 1;
    else
        v[indice] = 2;
    cout << endl;
    matrix(v);
    cout << "------------------------------------" << endl;
    //wait(3000);
    clean();
    for (int i=0; i<maxTabella; i++) {
        if (v[i]==1)
            cnt++;
    }

    if (cnt>=punti)
        return 1;
    else
        return 0;
}

void wait(int n) {
    clock_t start = clock();
    clock_t stop = start;
    while ((stop-start)<n)
        stop = clock();
    
    //cout << (stop-start)/1000 << "s" << endl;
}

void showHistory() {
    string p1, p2;
    int victory1, victory2;
    cout << "------------ ELENCO PARTITE ------------" << endl;
    ifstream file("history.txt");
    if (!(file >> p1)) {
        cout << "Nessuna partita salvata" << endl;
        file.close();
    } else {
    ifstream file("history.txt");
    while (file >> p1) {
        file >> p2 >> victory1 >> victory2;
        cout << p1 << " - " << victory1 << " \tVS\t " << p2 << " - " << victory2 << endl;
    }
    file.close();
    }
    cout << "----------------------------------------" << endl << endl;
}