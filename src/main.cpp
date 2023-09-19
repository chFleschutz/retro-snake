#include <iostream>
#include <fstream>
#include <conio.h>
#include <thread>
#include <string>

#include "Screen.h"
#include "Head.h"
#include "Food.h"

using namespace std;

int main()
{
    //****************************************
    //Vorbereitung aller Objekte und Variablen

    //Variablen
    const int width = 60;             //Breite des Spielfeldes
    const int height = 28;            //Höhe des Spielfeldes
    const int maxFood = 3;            //Maximal gleichzeitiges Essen auf dem Spielfeld
    const int maxBodys = width * height;        //Maximale Körperteile der Schlange

    char field[width][height];        //2-Dimensionales Spielfeld

    char key;                         //Eingabespeicher
    const char filler = ' ';          //Lückenfüllersymbol des Spielfeldes
    const char charFood = 'o';        //Symbol des Essens
    const char charSnake = '#';       //Symbol der Schlange
            
    int score;                        //Punktestand des Spielers

    bool isPlaying;                   //Schleifenvariable für Gameloop
    bool isRunning = true;            //Schleifenvariable für Programmschleife

    fstream scoreboard;               //zugriff auf scorebored.txt
    string highscore = "0";           //speichert den highscore aus scoreboard.txt

    //Random-Generator initialisieren
    srand(time(NULL));

    //****************
    //Programmschleife
    //****************
    do
    {
        //Spielfeld erstellen
        Screen Screen(*field, width, height);

        //Snake erstellen
        Head head(width, height, maxBodys);

        //Essen erstellen und Speicher dafür reservieren
        Food** food = nullptr;
        food = new Food * [maxFood];
        for (size_t i = 0; i < maxFood; i++)
        {
            food[i] = nullptr;
        }
        food[0] = new Food(width, height);

        //Variablen zurücksetzen
        key = 'd';                      //Snake bewegt sich anfangs nach rechts
        score = 0;
        isPlaying = true;

        //************
        //Menue-screen
        Screen.setCursor(0, 0, 10);
        cout << R"(


                                  MP""""""`MM                   dP                
                                  M  mmmmm..M                   88                
                                  M.      `YM 88d888b. .d8888b. 88  .dP  .d8888b. 
                                  MMMMMMM.  M 88'  `88 88'  `88 88888"   88ooood8 
                                  M. .MMM'  M 88    88 88.  .88 88  `8b. 88.  ... 
                                  Mb.     .dM dP    dP `88888P8 dP   `YP `88888P' 
                                  MMMMMMMMMMM)";
        
        //Highscore laden und ausgeben
        scoreboard.open("scoreboard.txt", fstream::in);
        if (scoreboard.is_open())
        {
            //Highscore einlesen
            getline(scoreboard, highscore);
            Screen.setCursor(26, 11);
            cout << "Highscore: " << highscore;
            scoreboard.close();
        }
        else
        {
            //Highscore konnte nicht geladen werden
            Screen.setCursor(24, 11);
            cout << "Could not load any Highscores" << endl;
            //Erstellen einer neuen scoreboard.txt datei
            scoreboard.open("scoreboard.txt", fstream::out);
            scoreboard << "0";
            scoreboard.close();
        }

        //Menue-screen vervollständigen
        Screen.setCursor(26, 13);
        cout << "PRESS ANY KEY" ;

        //Auf eingabe warten
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));  //Inputbuffer leeren
        switch (_getch())
        {
        case 'x': 
            //Spiel beenden bzw. wenn im Hauptmenu schliesen
            isRunning = false;
            isPlaying = false;
            system("cls");
        default:
            break;
        }

        //Spielfeld initialisieren
        if (isPlaying)
        {
            Screen.initializeScreen();
        }
        
        //********
        //Gameloop
        while(isPlaying)
        {
            //User Input
            if (_kbhit())
            { 
                //Speichern des letzten und der neuen Eingabe
                char lastKey = key;
                key = _getch();
                //Prüfen auf falsche Eingabe
                if (key != 'w' && key != 'a' && key != 's' && key != 'd' && key != 'x')
                {
                    key = lastKey;
                }
                //Prüfen auf Eingabe um Rückwärts zu gehen (-> sofortiger tot)
                if ((key == 'w' && lastKey == 's') || (key == 's' && lastKey == 'w') || (key == 'a' && lastKey == 'd') || (key == 'd' && lastKey == 'a'))
                {
                    key = lastKey;
                }
            }
            //Alte Position vom Schlangekopf und vom letzen Körperteil durch den Lückenfüller ersetzen (leer)
            Screen.set(filler, head.getPosX(), head.getPosY());
            Screen.set(filler, head.getLastBodyPosX(), head.getLastBodyPosY());

            //Snake nach Eingabe verschieben
            switch (key)
            {
            case 'w':
                head.setPosY(head.getPosY() - 1);
                break;
            case 'a':
                head.setPosX(head.getPosX() - 1);
                break;
            case 's':
                head.setPosY(head.getPosY() + 1);
                break;
            case 'd':
                head.setPosX(head.getPosX() + 1);
                break;
            case 'x':
                //Spiel wird mit x beendet
                isPlaying = false;
                break;
            default:
                break;
            }
            //Körpteile mitbewegen
            head.moveBody();

            //Kollision
            if (head.isCrashed())
            {
                isPlaying = false;
                cout << "\a";
            }

            //Neues Essen erstellen und Essen aufsammeln
            for (size_t i = 0; i < maxFood; i++)
            {
                //Essen sammeln
                if (food[i] != nullptr)
                {
                    //Prüfen auf gleiche Position vom Schlangenkopf und essen
                    if (food[i]->getPosX() == head.getPosX() && food[i]->getPosY() == head.getPosY())
                    {
                        //das essen löschen
                        delete food[i];
                        food[i] = nullptr;
                        //snake um ein glied erweitern
                        head.addBody();
                        //Score um eins erhöhen
                        score++;
                    }
                }
                //Neues Essen erstellen
                if (food[i] == nullptr)
                {
                    food[i] = new Food(width, height);
                }
            
            }

            //**************
            //Graphic output

            //Neue Positionen der Objekte in Screen speichern und ausgeben
            //Essen 
            for (size_t i = 0; i < maxFood; i++)
            {
                if (food[i] != nullptr)
                {
                    Screen.set(charFood, food[i]->getPosX(), food[i]->getPosY());
                }
            }
            //Kopf
            Screen.set(charSnake, head.getPosX(), head.getPosY());
            //Körper 
            for (size_t i = 0; i < maxBodys; i++)
            {
                //Prüfen ob ein Körperteil and stelle i existiert
                if (head.hasBody(i))
                {
                    //Position speichern
                    Screen.set(charSnake, head.getBodyPosX(i), head.getBodyPosY(i));
                }
                else break; //Schleife beenden, da danach kein weiters Körperteil folgt
            }
            //Score ausgeben
            Screen.setCursor(0, height + 1);
            cout << "Score: " << score;

            //Pause 
            this_thread::sleep_for(100ms);
        }

        //Game Over Nachricht ausgeben und 2s anzeigen
        Screen.gameOver();
        this_thread::sleep_for(2s);
        system("cls");

        //Score in Scoreboard.txt speichern
        scoreboard.open("scoreboard.txt");
        if (scoreboard.is_open())
        {
            if (score > stoi(highscore))
            {
                scoreboard << score;
            }
            scoreboard.close();
        }
        else
        {
            cout << "Could not save Score" << endl; //Konnte Highscore nicht speichern
            this_thread::sleep_for(1s);
        }
        system("cls");
    } while (isRunning);

    return 0;
}