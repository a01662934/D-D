
//Este código genera un juego de D&D con la ayuda de datos abstractos, archivos externos y listas ligadas para poder generar una experiencia completa y eficiente al usuario 

//De igual forma este código puede generar diferentes interacciones dentro de un grafo con datos proporcionados mediante un archivo, tales como realizar recorridos bfs y dfs asi como dijkstra.

//fecha de última modificación: 29 de Noviembre de 2023

//NOTA IMPORTANTE: PARA PROBAR LOS DIFERENTES ARCHIVOS (100, 0 o todos los datos) vaya a la línea 56 del archivo Game.h y cambie el nombre al deseado, puede elegir entre (dataDND100.csv, dataDND0.csv o dataDND.csv )

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "Game.h"
using namespace std;

int main() {
  
    int option;

    cout << "Elije una Opcion:" << endl;
    cout << "1. Grafo de Ciudades " << endl;
    cout << "2. Juego D&D" << endl;
    cout << "0. Salir" << endl;

    cout << "Elige una opción: ";
    cin >> option;

    switch (option) {
        case 1:
          //  Dungeons&Dragons 3 
            jugargrafo();
          
            break;
    
        case 2:

          //Dungeons&Dragons 2 
           
            srand(time(nullptr));
            jugar();  
    
            break;
    }
}
