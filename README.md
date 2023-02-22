# Optimización de codigo

## Índice
1. [Optimizaciones estéticas](#1-optimizaciones-estéticas)
2. [Eliminacion de codigo](#2-eliminacion-de-codigo)
3. [Funcion extra](#3-funcion-extra)


## Ejercicio

# 1. Optimizaciones estéticas

en este codigo existian algunas mejoras posibles para la **legibilidad** del mismo, como la substitucion de la forma en la que se suma en el codigo.

Tenemos el siguiente ejemplo:

```c++
if( mano[contadorMano].numero == 1){
    cout <<  "\033[1;33m A de " << mano[contadorMano].palo << "\033[0m" << endl;
    contadorAs++;
    if (contadorAs >= 1 && puntos+11 > 21){
    puntos = puntos + 1;
    } else {
    puntos = puntos + 11;
    }
    num_cartas_mano++;
} else if (mano[contadorMano].numero == 11){
    cout <<  "\033[1;33m Sota de " << mano[contadorMano].palo << "\033[0m" << endl;
    puntos = puntos + 10;
    num_cartas_mano++;
} else if (mano[contadorMano].numero == 12){
    cout <<  "\033[1;33m Caballo de " << mano[contadorMano].palo << "\033[0m" << endl;
    puntos = puntos + 10;
    num_cartas_mano++;
} else if (mano[contadorMano].numero == 13){
    cout <<  "\033[1;33m Rey de " << mano[contadorMano].palo << "\033[0m" << endl;
    puntos = puntos + 10;
    num_cartas_mano++;
} else {
    cout << "\033[1;33m " << mano[contadorMano].numero << " de " << mano[contadorMano].palo << "\033[0m" << endl;
    puntos = puntos + mano[contadorMano].numero;
    num_cartas_mano++;
}
```
Aqui vemos que para sumar puntos lo que hace es puntos = puntos + 10. Lo cual se puede abreviar en puntos += 10.

Otra cosa que he cambiado son el orden de los for para rellenar la baraja, simplemente porque prefiero ordenar por palo que por numero.

### Ahora, un gusto personal

Yo personalmente prefiero utilitzar el carácter de salto de linea antes que la variable endl del namespace std. Asi que he sustituido todos los endl por '\n'

Antes:

```c++
cout <<  "\033[1;33m A de " << mano[contadorMano].palo << "\033[0m" << endl;
```

Después:

```c++
cout <<  "\033[1;33m A de " << mano[contadorMano].palo << "\033[0m" << '\n';
```

Una ultima cosa es que a la hora de repartir por primera vez se hace fuera del bucle, cuando contamos con un if que mira si es el primer turno, simplemente he movido el for de repartir dentro del if

```c++
// Antes
for (int contadorBaraja = 0; contadorBaraja < 2; contadorBaraja++){
    mano[contadorBaraja] = baraja[rand()%52];
}
// después (el if funciona para mas cosas, pero el cambio esta aqui)
if (turno == 0){
    // repartimos las 2 primeras cartas para el jugador
    for (int contadorBaraja = 0; contadorBaraja < 2; contadorBaraja++){
    mano[contadorBaraja] = baraja[rand() % 52];
    num_cartas_mano++;
}
```

# 2. Eliminacion de codigo

Hay bastantes variables, arrays que son facilmente suprimibles. Tal es el caso del array de numeros que se usa para rellenar la baraja. No es necesario en ese caso ya que con i + 1 obtenemos el mismo resultado. 

Tambien, para este bucle se crea una variable que no volveremos a usar en todo el código, por ello podemos crear un puntero que apunte a un int nuevo en 0 para luego de usarlo, borrarlo inmediatamente.


Por lo tanto esto:
```c++
// bucle que rellena la baraja
for ( int i = 0; i < 13; i++){
		for ( int j = 0; j < 4; j++){
			baraja[contador].numero = numeros[i];
			baraja[contador].palo = palos[j];
			contador++;
		}
	}
```

pasaria a:

```c++
int *contador = new int(0);
  for (int j = 0; j < 4; j++){
    for (int i = 0; i < 13; i++){
      baraja[*contador].numero = i + 1;
      baraja[*contador].palo = palos[j];
      *contador += 1;
    }
  }
  delete contador;
```

### Pasar de tener manos de 52 posiciones a solo 12

**esto no cuenta como eliminacion** Pero si que conseguimos ahorrar un poco de memoria y no hacer tantas iteraciones en los bucles.
```c++
// mano antes
carta mano[52];
// mano después
carta mano[12];
```

### Pasamos de hacer 52 iteraciones en los bucles a el numero de cartas

de esta forma pasan dos cosas:

1. Le damos utilidad a la variable num_cartas_mano (no se usaba para nada)
2. Ahorramos las iteraciones sobrantes y eliminamos el if que evaluaba cuando dejaba de haber cartas

### ya no contamos en la opcion de mostrar mano

Al mostrar las cartas, no estamos cambiando el valor de los puntos del jugador, por lo que no tenemos que poner ese contador a 0 ni aumentarlo por cada carta, simplemente tenemos que mostrarlas
```c++
// antes
puntos = 0;
contadorAs = 0;
for (int contadorMano = 0; contadorMano < 52; contadorMano++){
    if (mano[contadorMano].palo != ""){
    if( mano[contadorMano].numero == 1){
        cout <<  "\033[1;33m A de " << mano[contadorMano].palo << "\033[0m" << endl;
        contadorAs++;
        if (contadorAs >= 1 && puntos+11 > 21){
        puntos = puntos + 1;
        } else {
        puntos = puntos + 11;
        }
        num_cartas_mano++;
    } else if (mano[contadorMano].numero == 11){
        cout <<  "\033[1;33m Sota de " << mano[contadorMano].palo << "\033[0m" << endl;
        puntos = puntos + 10;
        num_cartas_mano++;
    } else if (mano[contadorMano].numero == 12){
        cout <<  "\033[1;33m Caballo de " << mano[contadorMano].palo << "\033[0m" << endl;
        puntos = puntos + 10;
        num_cartas_mano++;
    } else if (mano[contadorMano].numero == 13){
        cout <<  "\033[1;33m Rey de " << mano[contadorMano].palo << "\033[0m" << endl;
        puntos = puntos + 10;
        num_cartas_mano++;
    } else {
        cout << "\033[1;33m " << mano[contadorMano].numero << " de " << mano[contadorMano].palo << "\033[0m" << endl;
        puntos = puntos + mano[contadorMano].numero;
        num_cartas_mano++;
    }
    }
}
// después

for (int contadorMano = 0; contadorMano < num_cartas_mano; contadorMano++){
    mostrarCarta(mano[contadorMano]);
}
```
En el ejemplo anterior podemos ver un pequeño spoiler de la funcion nueva que se usa todo el codigo. La explico en el siguiente apartado.


### Variable inutil

Existe una variable en el codigo que no se utilitza para absolutamente nada, es el contadorAs, esta guarda el numero de ases que tiene el jugador, pero en el contexto en el que se usa no afecta en lo absoluto, podemos borrar esta variable tranquilamente y de donde se use.

### Librerias no usadas

Este codigo incluye muchisimas librerias que no son usadas. En realidad de todas las que hay, solo necesitamos 2.

Antes:
```c++
#include <iostream>
#include <cstdlib> //for rand and srand
#include <cstdio>
#include <string>
#include <ctime> // time function for seed value´
#include <chrono>
#include <thread>
```

Después:

```c++
#include <iostream>
#include <thread>
```

El codigo solo usa la libreria iostream para mostrar por consola los output y thread para crear un delay en el turno de la máquina.

# 3. Funcion extra

Como ultimo cambio significativo he creado una funcion que se usa para mostrar las cartas por pantalla que devuelve el valor respectivamente. Adicionalmente esta funcion puede mostrar o no el texto a color con un parametro extra que le podemos enviar.

La funcion es la siguiente:

```c++
int mostrarCarta(carta card, bool all){

  int returnValue;

  cout << (!all ? "\033[1;33m " : " ");
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

  cout << (!all ? "\033[0m" : " ") << '\n';
  return returnValue;
}
```

Ahora cuando cogemos una carta, las mostramos o es el turno de la máquina, podemos utilizar esta funcion para ahorrar mucho codigo.

Podemos ver que cuando tenemos un as, esta funcion devuelve 0. Por lo que cuando vamos a evaluar el valor del as podemos hacer algo como lo siguiente:
```c++
valor = mostrarCarta(carta);

if(valor == 0){
    valor = (puntos + 11 > 21) ? 1 : 11;
}
// de esta forma sumamos el valor que mas convenga al usuari en el momento
```
antes se hacia de esta forma:
```c++
if( mano[contadorMano].numero == 1){
    cout <<  "\033[1;33m A de " << mano[contadorMano].palo << "\033[0m" << endl;
    contadorAs++;
    if (contadorAs >= 1 && puntos+11 > 21){
        puntos = puntos + 1;
    } else {
        puntos = puntos + 11;
}
```
