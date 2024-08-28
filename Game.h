// Este código genera un juego de D&D con la ayuda de datos abstractos, archivos
// externos y listas ligadas, stacks, queues arboles avl y grafos para poder generar una experiencia completa y
// eficiente al usuario

//NOTA IMPORTANTE: PARA PROBAR LOS DIFERENTES ARCHIVOS (100, 0 o todos los datos) vaya a la línea 56 del archivo Game.h y cambie el nombre al deseado, puede elegir entre (dataDND100.csv, dataDND0.csv o dataDND.csv )

#include "Graph.h"
#include "avlTree.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

//Clase Para las Ciudades de D&D
class City {
private:
  string city1;
  string city2;
  double distance;

public:
  City(string city1, string city2, double distance)
      : city1(city1), city2(city2), distance(distance) {}

  string getCity1() const {
    return city1;
  }

  string getCity2() const {
    return city2;
  }

  double getDistance() const {
    return distance;
  }
};

//Función para leer las ciudades y añadirlas a un grafo con sus respectivas relaciones 

ostream &operator<<(ostream &salida, const City &cd) {
  salida << cd.getCity1() << " - " << cd.getCity2() << " : " << cd.getDistance() << " km" << endl;
  return salida;
}

void cargaCity(Graph<string, string> &distances) {
  string linea, token;
  fstream archivo("dataDND.csv", ios::in);
  if (archivo.is_open()) {
    getline(archivo, linea); // Descartar la primera línea (encabezados)

    while (getline(archivo, linea)) {
      stringstream strdata(linea);
      string city1, city2, distanceStr;
      getline(strdata, city1, ',');
      getline(strdata, city2, ',');
      getline(strdata, distanceStr, ',');
      int distance = stoi(distanceStr);

      // Agregar ciudades al grafo y sus respectivas distancias
      distances.addVertex(city1);
      distances.addVertex(city2);
      distances.addEdge(city1, Vertex<string>(city2, distance));
      distances.addEdge(city2, Vertex<string>(city1, distance));
    }
  } else {
    throw -1;
  }
}


class Agamotto {
private:
  int estadoHP;
  int estadoLP;
  bool utilizado;

public:
  Agamotto() : estadoHP(-1), estadoLP(-1), utilizado(false) {}

  void guardarEstado(int HP, int LP) {
    estadoHP = HP;
    estadoLP = LP;
    utilizado = true;
  }

  void mostrarEstado(int &HP, int &LP) const {
    if (utilizado) {
      HP = estadoHP;
      LP = estadoLP;
      cout << "Estado restaurado usando el Ojo de Agamotto." << endl;
    } else {
      cout << "El Ojo de Agamotto no ha sido utilizado." << endl;
    }
  }
};

// Clase Monstruos
class Monster {
private:
  string name;
  double cr;
  string type;
  string size;
  int ac;
  int hp;
  string align;

public:
  Monster() {}
  Monster(string name, double cr, string type, string size, int ac, int hp,
          string align)
      : name(name), cr(cr), type(type), size(size), ac(ac), hp(hp),
        align(align) {}


    bool operator<(const Monster& other) const {
        return this->getHP() < other.getHP();
    }

    bool operator>(const Monster& other) const {
        return this->getHP() > other.getHP();
    }

  void printMonster() const  { // O(1)
    cout << "Name: " << name << endl;
    cout << "Cr: " << cr << endl;
    cout << "Type: " << type << endl;
    cout << "Size: " << size << endl;
    cout << "Ac: " << ac << endl;
    cout << "Hp: " << hp << endl;
    cout << "Alignment: " << align << "\n" << endl;
  }

  int getHP() const { // O(1)
    return hp;
  }

  int reduceHP(int Pdamage) { // O(1)
    return hp -= Pdamage;
  }

  bool isAlive() const { // O(1)
    return hp > 0;
  }

  string getName() const { // O(1)
    return name;
  }

  double getCR() { // O(1)
    return cr;
  }
  // devuelve el estado del monstruo dependiendo si esta vivo o muerto
  string getEstado() const { // O(1)
    string estado = "Name: " + name + "\n";
    estado +=
        "Estado: " + (isAlive() ? string("Vivo") : string("Derrotado")) + "\n";
    return estado;
  }
};

// Clase calabozos

class Calabozo {
private:   
  string nombreCalabozo;
  Monster monstruo;
  int monstruosRestantes;

public:
  //LinkedList<Monster> monsters;
  Calabozo() {}
  Calabozo(string nombreCalabozo, Monster monstruo)
      : nombreCalabozo(nombreCalabozo), monstruo(monstruo) {}

  int getMonsterHP() const { // O(1)
    return monstruo.getHP();
  }

  void printCalabozo() {
    cout << "Nombre del Calabozo: " << nombreCalabozo << endl;
    monstruo.printMonster();
  }

  string getNombreCalabozo() const { // O(1)
    return nombreCalabozo;
  }

  Monster getMonstruo() const { // O(1)
    return monstruo;
  }

  // Muestra los calabozos que hay
  void printDungeon(const LinkedList<Calabozo> &calabozos) const { // O(n)
    cout << "Lista de calabozos y sus monstruos:" << endl;

    for (int i = 0; i < calabozos.size(); i++) {
      const Calabozo &calabozo = calabozos.get(i);
      const Monster &monstruo = calabozo.getMonstruo();

      cout << calabozo.getNombreCalabozo() << " contiene a "
           << monstruo.getName() << endl;
    }

    cout << "Fin del calabozo." << endl;
  }

  string getMonsterState() const { // O(1)
    return monstruo.getEstado();
  }

};

// Clase Hechizos

class Spell {
private:
  int ID;
  string Name;
  string type;
  int Damage;

public:
  Spell() {}
  Spell(int ID, string Name, string type, int Damage)
      : ID(ID), Name(Name), type(type), Damage(Damage) {}

  void printSpell() { // O(1)
    cout << "ID: " << ID << endl;
    cout << "Nombre: " << Name << endl;
    cout << "Tipo: " << type << endl;
    cout << "Daño: " << Damage << endl;
  }

  int getID() const { // O(1)
    return ID;
  }

  string getName() const { // O(1)
    return Name;
  }

  string getType() const { // O(1)
    return type;
  }

  int getDamage() const { // O(1)
    return Damage;
  }
};

// Clase Objetos
class Object {
private:
  string ID;
  string Tipo;
  int Valor;

public:
  Object() {}
  Object(string ID, string Tipo, int Valor)
      : ID(ID), Tipo(Tipo), Valor(Valor) {}

  int getValor() const { // O(1)
    return Valor;
  }

  string getID() const { // O(1)
    return ID;
  }

  string getTipo() const { // O(1)
    return Tipo;
  }

  void printObject() { // O(1)
    cout << "ID " << ID << endl;
    cout << "Tipo: " << Tipo << endl;
    cout << "Valor " << Valor << "\n" << endl;
  }
};

// Clase Mazmorra

class Mazmorra {
public:
  LinkedList<Monster> monstersSinRoom;
    void sort() {
    for (int i = 0; i < monstersSinRoom.size(); i++) {
      for (int j = 0; j < monstersSinRoom.size() - 1; j++) {
        Monster a = monstersSinRoom.get(j);
        Monster b = monstersSinRoom.get(j + 1);
        // Compara los puntos de vida (HP) de los monstruos
        if (a.getHP() < b.getHP()) {
          Monster temp = monstersSinRoom.get(j + 1);
          monstersSinRoom.set(j + 1, monstersSinRoom.get(j));
          monstersSinRoom.set(j, temp);
        }
      }
    }
  }
};

// Clase Jugador
class Jugador {
private:
  string nombre;
  string raza;
  int hp;
  int lp;
  bool revivable;
  int D20 = rand() % 20 + 1;

  LinkedList<Spell> habilidades;
  AVL<Monster> monstruosDerrotados; 
  LinkedList<Object> objetos;
  Agamotto ojoAgamotto;
  LinkedList<Monster> monstruo;

public:
  // Aqui se establece la vida del jugador y sus hitpoints
  //checar si el hp y lp sigen funcionando si los borras
  Jugador() : hp(50), raza("----"), lp(500), revivable(true) {}  //hacer con set

  Jugador(string nombreJugador, string razaJugador)
      : nombre(nombreJugador), raza(razaJugador) {
    hp = rand() % 13 + 8; // Genera un número entre 8 y 20
    lp = rand() % 13 + 8; // Genera un número entre 8 y 20
    revivable = true;
  }

  // lista de getters que se encarga de devolver los diferentes variables
  // solicitadas para poder ser usadas fuera de la clase

  bool isRevivable() const { return revivable; }

  void inicializarOjoAgamotto() { ojoAgamotto.guardarEstado(getHP(), getLP()); }
//checar
  void mostrarOjoAgamotto() {
    int HP, LP;
    ojoAgamotto.mostrarEstado(HP, LP);
  }

  void revivePlayer() {
      revivable = false;
      cout << "El jugador ha sido revivido usando el Ojo de Agamotto." << endl;

  }

  string getNombre() { // O(1)
    return nombre;
  }
  LinkedList<Object> &getObjetos() { // O(1)
    return objetos;
  }
  string getRaza() { // O(1)
    return raza;
  }

  int getHP() { // O(1)
    return hp;
  }

  int getLP() { // O(1)
    return lp;
  }

  int reduceLP(int Mdamage) { // O(1)
    return lp -= Mdamage;
  }

  LinkedList<Spell> getHabilidades() { // O(1)
    return habilidades;
  }

  // funcion que eleva el hp del jugador
  void aumentarHP(int incremento) { // O(1)
    hp += incremento;
  }

  // funcion que eleva el lp del jugador
  void aumentarLP(int incremento) { // O(1)
    lp += incremento;
  }

  // muestra el estado en todos los calabozos con los monstruos y su estado

    void printEstadoCalabozos(const LinkedList<Calabozo> &calabozos) const { // O(n)
      cout << "Estado de los monstruos en los calabozos:" << endl;
      for (int i = 0; i < calabozos.size(); i++) {
        const Calabozo &calabozo = calabozos.get(i);
        cout << "Calabozo: " << calabozo.getNombreCalabozo() << endl;
        cout << calabozo.getMonsterState() << endl;
      }
  }

  // permite seleccionar un objeto

  void elegirObjetoCuracion(LinkedList<Object> &objetosJugador,
                            LinkedList<Object> &objetosElegidos) { // O(m)
    cout << "Elige un objeto (ingresa el número de ID):"
         << "\n"
         << endl;

    int oeleccion;
    cin >> oeleccion;

    if (oeleccion >= 1 && oeleccion <= objetosJugador.size()) {
      objetosElegidos.addLast(objetosJugador.get(oeleccion - 1));
      objetosElegidos.print();
    } else {
      cout << "Selección inválida. Introduce un ID válido." << endl;
    }

    cout << endl;
  }

  // permite al jugador usar un objeto

  void usarObjeto(LinkedList<Object> &objetosElegidos, Jugador &jugador) {
    if (objetosElegidos.size() >= 1) {
      int totalCura = 0;
      for (int i = 0; i < objetosElegidos.size(); i++) {
        totalCura += objetosElegidos.get(i).getValor();
      }

      jugador.aumentarLP(totalCura);
      cout << " Te has curado un total de " << totalCura << " puntos de vida."
           << endl;

    } else {
      cout << "No tienes suficientes objetos" << endl;
    }
  }

//AVL
  void derrotarMonstruo(const Monster &monstruo) {
    monstruosDerrotados.insert(monstruo);
  }

  void mostrarMonstruosDerrotados() {
    monstruosDerrotados.inOrden();
  }

  // permite crear una lista ligada con los hechizos elegidos
  void elegirHechizo(LinkedList<Spell> &spell,
                     LinkedList<Spell> &habilidadesElegidas) {
    cout << "Elige dos habilidades (ingresa el número de ID):"
         << "\n"
         << endl;

    for (int i = 0; i < 2; i++) {
      cout << "Habilidad " << (i + 1) << ": ";
      int eleccion;
      cin >> eleccion;

      if (eleccion >= 1 && eleccion <= spell.size()) {
        habilidadesElegidas.addLast(spell.get(eleccion - 1)); // O(n)
      } else {
        cout << "Selección inválida. Introduce un ID válido." << endl;
        i--;
      }
    }

    cout << "Habilidades elegidas:" << endl;
    habilidadesElegidas.print();
    cout << endl;
  }

  // permite usar los hechizos elegidos
/*  Función de código anterior
  void usarHechizos(LinkedList<Spell> &habilidadesElegidas, Monster &monstruo,
    Jugador &jugador) { // O(n)
    if (habilidadesElegidas.size() >= 2) {
      int totalDamage = 0;
      for (int i = 0; i < 2; i++) {
        totalDamage += habilidadesElegidas.get(i).getDamage();
      }

      monstruo.reduceHP(totalDamage);
      cout << "Has infligido " << totalDamage << " de daño al monstruo."
           << endl;

    } else {
      cout << "No tienes suficientes habilidades para usar un hechizo." << endl;
    }
  }*/

//función nueva con complejidad reducida a O(n)
void usarHechizos(LinkedList<Spell> &habilidadesElegidas, Monster &monstruo, Jugador &jugador) {
  if (habilidadesElegidas.size() >= 2) {
    int totalDamage = habilidadesElegidas.get(0).getDamage() +
                      habilidadesElegidas.get(1).getDamage();

    monstruo.reduceHP(totalDamage);
    cout << "Has infligido " << totalDamage << " de daño al monstruo." << endl;
  } else {
    cout << "No tienes suficientes habilidades para usar un hechizo." << endl;
  }
}


  // muestra la informacion del jugador

  void printPlayer() {
    cout << "Nombre del Jugador: " << nombre << endl;
    cout << "Raza del Jugador: " << raza << endl;
    cout << "Nivel de HP del Jugador: " << hp << endl;
    cout << "Nivel de LP del Jugador:" << lp << "\n" << endl;

    if (revivable) {
      cout << "El jugador puede ser revivido." << endl;
    } else {
      cout << "El jugador no puede ser revivido." << endl;
    }
    cout << endl;
  }

};


// carga el archivo que contiene a los mosntruos y los pone en una lista ligada
ostream &operator<<(ostream &salida, const Monster &m) {
  salida << m.getName() << " : " << m.getHP() << endl;
  return salida;
}

void cargaMonsters(LinkedList<Monster> &monsters) {
  string linea, token;
  fstream archivo("monsters.csv", ios::in);
  if (archivo.is_open()) {
    getline(archivo, linea);
    while (getline(archivo, linea)) {
      stringstream strdata(linea);
      string name;
      getline(strdata, name, ',');
      string cr;
      getline(strdata, cr, ',');
      string type;
      getline(strdata, type, ',');
      string size;
      getline(strdata, size, ',');
      string ac;
      getline(strdata, ac, ',');
      string hp;
      getline(strdata, hp, ',');
      string align;
      getline(strdata, align, ',');
      Monster m(name, stod(cr), type, size, stoi(ac), stoi(hp), align);
      monsters.addLast(m);
    }
  } else {
    throw -1;
  }
}

// carga el archivo que contiene los hechizos y los pone en una lista ligada
ostream &operator<<(ostream &SalidaS, const Spell &s) {
  SalidaS << s.getID() << ": " << s.getName() << ": " << s.getType() << ": "
          << s.getDamage();
  return SalidaS;
}

void cargaSpell(LinkedList<Spell> &spell) {
  string linea, token;
  fstream archivo("spell.csv", ios::in);
  if (archivo.is_open()) {
    getline(archivo, linea);
    while (getline(archivo, linea)) {
      stringstream strdata(linea);
      string ID;
      getline(strdata, ID, ',');
      string nombre;
      getline(strdata, nombre, ',');
      string tipo;
      getline(strdata, tipo, ',');
      string damage;
      getline(strdata, damage, ',');
      Spell s(stoi(ID), nombre, tipo, stoi(damage));
      spell.addLast(s);
    }
  } else {
    throw -1;
  }
}

// carga el archivo que contiene los objetos y los pone en una lista ligada
ostream &operator<<(ostream &salidaO, const Object &o) {
  salidaO << o.getID() << " : " << o.getTipo() << " : " << o.getValor() << endl;
  return salidaO;
}

void cargaObject(LinkedList<Object> &objetos) {
  string linea, token;
  fstream archivo("objetosd.csv", ios::in);
  if (archivo.is_open()) {
    getline(archivo, linea);
    while (getline(archivo, linea)) {
      stringstream strdata(linea);
      string ID;
      getline(strdata, ID, ',');
      string Tipo;
      getline(strdata, Tipo, ',');
      string Valor;
      getline(strdata, Valor, ',');
      Object o(ID, Tipo, stoi(Valor));
      objetos.addLast(o);
    }
  } else {
    throw -1;
  }
}

void swap(int *xp, int *yp) {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

void crearDungeon(LinkedList<Monster> &monsters, LinkedList<LinkedList<Monster>> &mazmorras) {
  int numMazmorras = rand() % 20 + 1;
  cout << "Número de mazmorras en el calabozo: " << numMazmorras << endl;

  for (int i = 0; i < numMazmorras; i++) {
    int cantidadDeMonstruos = rand() % 6 + 1;

    LinkedList<Monster> currentMazm;

    for (int j = 0; j < cantidadDeMonstruos; j++) {
      int indexMonster = rand() % monsters.size();
      Monster monster = monsters.get(indexMonster);
      currentMazm.addLast(monster);
    }

    mazmorras.addLast(currentMazm);  
  }
}

void jugar() {
  LinkedList<Spell> spell;
  cargaSpell(spell);
  LinkedList<Monster> monsters;
  cargaMonsters(monsters);
  LinkedList<Object> objetos;
  cargaObject(objetos);
  LinkedList<Calabozo> calabozos;
  LinkedList<LinkedList<Monster>> mazmorraas;

  Jugador jugadores[3];
  for (int i = 0; i < 3; ++i) {
    string nombreJugador, razaJugador;
    cout << "Ingrese el nombre del Jugador " << (i + 1) << ": ";
    cin >> nombreJugador;
    cout << "Ingrese la raza del Jugador " << (i + 1) << ": ";
    cin >> razaJugador;

    if (razaJugador == "Human" || razaJugador == "human") {
      cout << "Los humanos son equilibrados en cuanto a su manejo de armas y "
              "hechizos, elige sabiamente tus ataques "
           << endl;
    } else if (razaJugador == "Elf" || razaJugador == "elf") {
      cout << "Los Elfos son muy buenos utilizando magia, elige sabiamente tus "
              "ataques"
           << endl;
    } else if (razaJugador == "Dwarf" || razaJugador == "dwarf") {
      cout << "Los Enanos son especialistas en armas, elige sabiamente tus "
              "ataques "
           << endl;
    } else {
      cout << "Mmmm... esa raza no la conozco, pero apuesto a que tiene sus "
              "ventajas "
           << endl;
    }

    jugadores[i] = Jugador(nombreJugador, razaJugador);
    jugadores[i].inicializarOjoAgamotto(); 

    cout << "Jugador " << (i + 1) << " creado con éxito.\n" << endl;
  }

  for (int i = 0; i < 3; ++i) {
    cout << "Datos del Jugador " << (i + 1) << ":" << endl;
    jugadores[i].printPlayer();
  }
////////////////////////////////////////////////////////////////////////////////////////777
crearDungeon(monsters, mazmorraas);
int numCalabozosTotales = mazmorraas.size();
////////////////////////////////////////////////////////////////////////////////////////777
////////////////////////////////////////////////////////////////////////////////////////777
////////////////////////////////////////////////////////////////////////////////////////777
////////////////////////////////////////////////////////////////////////////////////////777
////////////////////////////////////////////////////////////////////////////////////////777

  // Variable para contar jugadores vivos
  int jugadoresVivos = 3;
  int jugadoresDerrotados = 0;


  // Bucle principal del juego

    for (int i = 0; i < numCalabozosTotales && jugadoresVivos > 0; i++) {

    // Caer en un calabozo aleatorio para empezar a pelear
    int Dado = rand() % numCalabozosTotales + 1;
    int posTotal = Dado;
    posTotal = posTotal % numCalabozosTotales;
    cout << "\nSe lanzó el dado para ver cuantas posiciones avanzan..." << endl;
    cout << "Avanzan un total de " << Dado << " posiciones" << endl;
    cout << "Se encuentran en el calabozo #" << posTotal + 1 << endl;

    // Obtener y mostrar la mazmorra actual
    Mazmorra currentMazmorra;
    currentMazmorra.monstersSinRoom = mazmorraas.get(posTotal);  // Obtener los monstruos de la mazmorra actual
    currentMazmorra.sort();  // Ordenar los monstruos en la mazmorra
    cout << "Monstruos en la mazmorra: " << currentMazmorra.monstersSinRoom.size() << endl;
    currentMazmorra.monstersSinRoom.print();  // Imprimir los monstruos ordenados

    // Iterar sobre los monstruos en la mazmorra actual
    for (int k = 0; k < currentMazmorra.monstersSinRoom.size(); k++) {
       Monster currentMonster = currentMazmorra.monstersSinRoom.get(k);

      Calabozo calabozo; // Aquí deberías obtener el calabozo correspondiente a la mazmorra actual
      Monster monstruo = calabozo.getMonstruo();

      cout << "Enfrentando a un " << currentMonster.getName() << " en el calabozo " << posTotal + 1 << "." << endl;
      currentMonster.printMonster();

      for (int j = 0; j < 3; j++) {
        Jugador &jugador = jugadores[j];

        if (jugador.getLP() > 0 && currentMonster.isAlive()) {
          int opcion;
          cout << "Turno de Jugador " << (j + 1) << ": " << endl;
          cout << "1) Atacar\n2) Usar hechizo\n3) Usar item/poción\nElije una "
                  "opción: ";
          cin >> opcion;
          cout << endl;

          if (opcion == 1) {
              int Pdamage = rand() % 15 + 1;
              currentMonster.reduceHP(Pdamage);
              cout << "El Jugador " << (j + 1) << " ha infligido " << Pdamage << " de daño al monstruo." << endl;
            } else if (opcion == 2) {
              LinkedList<Spell> habilidadesElegidas;

              // Mostrar la lista de hechizos disponibles
              for (int i = 0; i < spell.size(); i++) {
                cout << "ID: " << i + 1 << ", ";
                cout << spell.get(i).getName() << " - " << spell.get(i).getType() << " - " << spell.get(i).getDamage() << " Daño" << endl;
              }

              jugador.elegirHechizo(spell, habilidadesElegidas);
              jugador.usarHechizos(habilidadesElegidas, currentMonster, jugador);
            } else if (opcion == 3) {
              LinkedList<Object> objetosElegidos;

              for (int i = 0; i < objetos.size(); i++) {
                cout << "ID: " << i + 1 << ", ";
                cout << objetos.get(i).getTipo() << " - " << objetos.get(i).getValor() << " Valor " <<  endl;
              }

              jugador.elegirObjetoCuracion(objetos, objetosElegidos);
              jugador.usarObjeto(objetosElegidos, jugador);
            }
            // Ataque por parte del monstruo, si está vivo te regresa el daño
            if (currentMonster.isAlive()) {
              int Mdamage = rand() % 20 + 1;
              jugador.reduceLP(Mdamage);
              cout << "El monstruo ha infligido " << Mdamage << " de daño al Jugador " << (j + 1) << "." << endl;
            } 
            else if (currentMonster.getHP() <= 0 ) {
              cout << "El Jugador " << (j + 1) << " ha derrotado al monstruo." << endl;
              jugador.derrotarMonstruo(currentMonster);

              double crIncremento = monstruo.getCR() * 0.10;
              int hpIncremento = jugador.getHP() + crIncremento;
              int lpIncremento = jugador.getLP() + crIncremento;

              jugador.aumentarHP(hpIncremento);
              jugador.aumentarLP(lpIncremento);
              // Cambiar mensaje
              cout << "El HP del Jugador " << (j + 1) << " Ahora es de: " << hpIncremento << " puntos." << endl;
              cout << "El LP del Jugador " << (j + 1) << " Ahora es de: " << lpIncremento << " puntos." << "\n" << endl;
            }
          }

          // Verificar si el jugador actual ha sido derrotado
          if (jugador.getLP() <= 0) {
            cout << "El Jugador " << (j + 1) << " ha sido derrotado." << "\n" << endl;

            // Verificar si el jugador puede ser revivido
            if (jugador.isRevivable()) {
              string respuesta;
              cout << "¿Deseas revivir al Jugador " << (j + 1) << "? (si/no): ";
              cin >> respuesta;
              // Meter la parte de 
              // Revivir al jugador si la respuesta es 'si'
              if (respuesta == "si") {
                jugador.aumentarLP(20);
                jugador.revivePlayer();
              } else {
                jugadoresDerrotados++;
                jugadoresVivos--;
              }
            }
          }
        }
      }
    }

  // Mostrar estado final
  cout << "Estado final de los jugadores:" << endl;
  for (int i = 0; i < 3; i++) {
    jugadores[i].printPlayer();
    jugadores[i].mostrarOjoAgamotto();
  }

  // Mostrar la lista de monstruos derrotados y un mensaje de fin del juego
  cout << "¡Felicidades, todos los jugadores han completado el calabozo!"
       << endl;

  for (int i = 0; i < 3; ++i) {
    cout << "Monstruos derrotados por " << jugadores[i].getNombre()        << ":" << endl;

    jugadores[i].mostrarMonstruosDerrotados();

    cout << "------------------------------" << endl;
  }

  cout << "¡Fin del juego!" << endl;
};


void jugargrafo(){
  
  Graph<string, string> distances;

  try {
      cargaCity(distances);

      int opcion;
      do {
          // Menú de opciones
          cout << "\n--- Menú ---" << endl;
          cout << "1. Mostrar grafo" << endl;
          cout << "2. Mostrar ciudad con menos y más conexiones" << endl;
          cout << "3. Realizar BFS desde una ciudad" << endl;
          cout << "4. Realizar DFS desde una ciudad" << endl;
          cout << "5. Realizar pruning del grafo" << endl;
          cout << "6. Realizar Dijkstra desde una ciudad" << endl;
          cout << "7. Identificar las ciudades más concurridas" << endl;
          cout << "0. Salir" << endl;

          // Obtener la opción del usuario
          cout << "\nIngrese el número de la opción que desea realizar: ";
          while (!(cin >> opcion) || opcion < 0 || opcion > 7) {
              cout << "Entrada inválida. Ingrese un número válido: ";
              cin.clear();
          }

          // Hacer la opción seleccionada
          switch (opcion) {
              case 1:
                  cout << "Grafo de distancias:" << endl;
                  distances.print();
                  break;
              case 2:
                
                  {
                    string VerticeConMenos = distances.menosConexiones();
                    cout << "La ciudad con menos conexiones es: " << VerticeConMenos << endl;

                    string VerticeConMas = distances.masConexiones();
                    cout << "La ciudad con más conexiones es: " << VerticeConMas << endl;
                    
                  }
                  break;
              case 3:
                  {
                      string startCity;
                      cout << "Ingrese la ciudad de inicio: ";
                      cin >> startCity;
                      
                      vector<string> bfsResult = distances.bfs(startCity);
                      cout << "BFS de " << startCity << endl;
                      for (const auto &city : bfsResult) {
                          cout << city << " ";
                      }
                      cout << endl;
                  }
                  break;
              case 4:
                  {
                      string startCity;
                      cout << "Ingrese la ciudad de inicio: ";
                      cin >> startCity;
                      vector<string> dfsResult = distances.dfs(startCity);
                      cout << "DFS de " << startCity << endl;
                      for (const auto &city : dfsResult) {
                          cout << city << " ";
                      }
                      cout << endl;
                  }
                  break;
              case 5:
                  {
                      int minConnections;
                      cout << "Ingrese el número mínimo de conexiones para realizar el pruning: ";
                      while (!(cin >> minConnections) || minConnections < 0) {
                          cout << "Entrada inválida. Ingrese un número válido: ";
                      }
                      distances.pruneGraph(minConnections);
                      cout << "Grafo después del pruning:" << endl;
                      distances.print();
                  }
                  break;
            
              case 6:
                  {
                      string startCity;
                      cout << "Ingrese la ciudad de inicio: ";
                      cin >> startCity;
        vector<Vertex<string>> dijkstraResult =distances.dijkstra(startCity);
                      cout << "Dijkstra de " << startCity << endl;
                      
                      for (const auto &vertex : dijkstraResult) {
                          cout << vertex << " ";
                      }
                      cout << endl;
                  }
                
                  break;
              case 7:
                  {
                    cout << "El top 10 de ciudades más visitadas es: ";
                    vector<string> mostVisited = distances.topCiudades();
                    for (const auto &vertex : mostVisited) {
                      cout << vertex << endl;
                    }
                    cout << endl;
                  }
                  break;
              case 0:
                  cout << "Saliendo del programa." << endl;
                  break;
          }

      } while (opcion != 0);

  } catch (int error) {
      cout << "Error al abrir el archivo." << endl;
  }
  
};