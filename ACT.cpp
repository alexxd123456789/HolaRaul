/*
=======================================================
Nom:            Alejandro Vidal Casado
=======================================================
S'ha d'optimitzar aquest codi tot el que pugueu.
Fer un document PDF on s'explica detalladament com estava el codi i quina millora heu fet.
Podeu modificar el codi tot el que vulgueu, però ha de mantenir les mateixes funcionalitats, no pot tenir noves ni tenir menys, el programa ha de fer el mateix.
*/

#include <iostream>
#include <thread>

using namespace std;

struct carta{
  int numero;
  string palo;
};

int mostrarCarta(carta card, bool notColor = false);
// buenas tardes
int main(){
  // creamos la baraja y generamos la semilla de los numeros aleatorios
  struct carta baraja[52];
  time_t t;
  srand((unsigned)time(&t));

  const string palos[4] = {"Corazones", "Diamantes", "Picas", "Treboles"};
  // rellenamos la baraja
  int *contador = new int(0);
  for (int j = 0; j < 4; j++){
    for (int i = 0; i < 13; i++){
      baraja[*contador].numero = i + 1;
      baraja[*contador].palo = palos[j];
      *contador += 1;
    }
  }
  delete contador;
  // varialbes necesarias para manejar las cartas
  int opcion;
  bool repetir = true;
  struct carta mano[12], manoMaquina[12];
  int valor, num_cartas_mano = 0, carta_mano_maquina = 0, puntos = 0, puntosMaquina = 0, turno = 0;

  do{
    cout << "\033[1;31m \n\nMenu de Opciones \033[0m" << '\n';
    cout << "\033[1;32m 1. Robar carta \033[0m" << '\n';
    cout << "\033[1;32m 2. Mostrar mano \033[0m" << '\n';
    cout << "\033[1;32m 3. Plantarse \033[0m" << '\n';
    cout << "\033[1;32m 4. Ver baraja \033[0m" << '\n';
    cout << "\033[1;32m 0. SALIR \033[0m" << '\n';

    if (turno == 0){
      // repartimos las 2 primeras cartas para el jugador
      for (int contadorBaraja = 0; contadorBaraja < 2; contadorBaraja++){
        mano[contadorBaraja] = baraja[rand() % 52];
          num_cartas_mano++;
      }

      cout << "\033[1;31m \nTus cartas son: \033[0m" << '\n';
      puntos = 0;
      // mostramos las cartas y sumamos el valor
      for (int contadorMano = 0; contadorMano < num_cartas_mano; contadorMano++){
          valor = mostrarCarta(mano[contadorMano]);

          if(valor == 0){
            valor = (puntos + 11 > 21) ? 1 : 11; 
          }
          
          puntos += valor;
      }
      // mostramos si hemos ganado o continuamos jugando
      if (puntos == 21){
        cout << "\033[1;33mFELICIDADES tienes " << puntos << " puntos!(Blackjack)\033[0m" << '\n';
        repetir = false;
        break;
      }
      else{
        cout << "\033[1;32mTienes " << puntos << " puntos \033[0m" << '\n';
      }
    }
    // pedimos la opcion y sumamos 1 a turno
    cout << "\nIngrese una opcion: ";
    cin >> opcion;
    turno++;

    switch (opcion)
    {
    case 1:
      system("clear");
      // cojecmos una carta y mostramos
      mano[num_cartas_mano + 1] = baraja[rand() % 52];
      cout << "\033[1;32mTu carta es: \033[0m" << '\n';
      // analizamos el valor de la carta
      valor = mostrarCarta(mano[num_cartas_mano + 1]);

      if (valor == 0){
        valor = (puntos + 11 > 21) ? 1 : 11;
      }
      // sumamos el resultado de la funcion (si es un as es 0)
      puntos += valor;
      num_cartas_mano++;
      // analizamos la puntuacion del jugador
      if (puntos > 21){
        cout << "\033[1;31mTe has pasado... puntos: " << puntos << "\033[0m" << '\n';
        cout << "\033[1;31mHas perdido\033[0m" << '\n';
        repetir = false;
        break;
      }
      else if (puntos == 21){
        cout << "\033[1;33mFELICIDADES tienes " << puntos << " puntos!(Blackjack)\033[0m" << '\n';
        repetir = false;
        break;
      }
      else{
        cout << "\033[1;32mTienes " << puntos << " puntos \033[0m" << '\n';
      }
      break;

    case 2:
      // mostramos las cartas del jugador con sus puntos
      system("clear");
      cout << "\033[1;31m \nTus cartas son: \033[0m" << '\n';
      for (int contadorMano = 0; contadorMano < num_cartas_mano; contadorMano++){
        mostrarCarta(mano[contadorMano]);
      }
      cout << "\033[1;32mTienes " << puntos << " puntos \033[0m" << '\n';
      break;

    case 3:
      // mostramos al jugador los puntos que ha conseguido
      system("clear");
      cout << "\033[1;32mHas conseguido " << puntos << " puntos \033[0m" << '\n';
      cout << "\033[1;36mAhora juega la máquina\033[0m" << '\n';
      // iremos cogiendo cartas mentras tengamos menos puntos que el jugador
      while (puntosMaquina < puntos){
        cout << "\033[1;36mLa maquina roba carta\033[0m" << '\n';
        // hacmemos que el usuario espere
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        manoMaquina[carta_mano_maquina] = baraja[rand() % 52];
        // mostramos la carta
        valor = mostrarCarta(manoMaquina[carta_mano_maquina]);

        if (valor == 0){
          valor = (puntosMaquina + 11 > 21) ? 1 : 11;
        }

        puntosMaquina += valor;
        cout << "\033[1;37m Puntos maquina: " << puntosMaquina << '\n';
        carta_mano_maquina++;
      }
      // comprobamos el resultado de la partida
      if (puntosMaquina > 21){
        cout << "\033[1;31mLa máquina se ha pasado\033[0m" << '\n';
        cout << "\033[1;33mFELICIDADES, HAS GANADO!\033[0m" << '\n';
      }
      else if (puntosMaquina == puntos){
        cout << "\033[1;33mLa máquina se planta\033[0m" << '\n';
        cout << "\033[1;33mEmpate\033[0m" << '\n';
      }
      else{
        cout << "\033[1;33mLa máquina se planta\033[0m" << '\n';
        cout << "\033[1;31mHas perdido...\033[0m" << '\n';
      }
      // mostramos la puntucacion de ambos y paramos la ejecucion del codigo
      cout << "\033[1;35mTu has conseguido " << puntos << " puntos y la máquina " << puntosMaquina << " puntos\033[0m" << '\n';
      repetir = false;
      break;
    case 4:
      // ejecutamos la funcion mostrar carta por cada carta de la baraja
      for (int contadorBaraja = 0; contadorBaraja < 52; contadorBaraja++){
        mostrarCarta(baraja[contadorBaraja], true);
      }
      break;

    case 0:
      repetir = false;
      break;
    }
  } while (repetir);

  return 0;
}
// funcion que muestra una carta y segun si mostramos todas o no, aplicara un estilo
int mostrarCarta(carta card, bool notColor){
  int returnValue;

  cout << (!notColor ? "\033[1;33m " : " ");
  switch (card.numero){
  case 1:
    cout << "A de " << card.palo;
    returnValue = 0;
    break;

  case 11:
    cout << "Sota de " << card.palo;
    returnValue = 10;
    break;

  case 12:
    cout << "Caballo de " << card.palo;
    returnValue = 10;
    break;

  case 13:
    cout << "Rey de " << card.palo;
    returnValue = 10;
    break;

  default:
    cout << card.numero << " de " << card.palo;
    returnValue = card.numero;
    break;
  }

  cout << (!notColor ? "\033[0m" : " ") << '\n';
  return returnValue;
}