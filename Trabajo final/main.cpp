//*Objetivo: El objetivo es disparar a los enemigos que cruzan la pantalla a distintas velocidades y evitar los meteoritos que caen verticalmente. La nave del jugador tiene 5 vidas. Cada vez que un meteorito golpea la nave, se pierde una vida.
//*Jugabilidad:
//Nave: Controlada por el jugador, puede moverse en cualquier dirección (izquierda, derecha, arriba, abajo) y disparar.
//Enemigos: Se mueven horizontalmente a diferentes velocidades y aparecen desde los bordes de la pantalla.
//Meteoritos: Caen verticalmente desde la parte superior de la pantalla y pueden golpear la nave.
//*Puntuación:
//Eliminar enemigos: Al disparar y eliminar enemigos, se suma una cantidad de puntos (esto se puede ajustar según el enemigo).
//Mensajes de Puntaje: Mostrar mensajes de puntuación como "Nice shoot", "Good one", etc., cuando un enemigo es eliminado.
//*Vidas:
//Iniciales: Comienza con 5 vidas.
//Perder vidas: Se pierde una vida si un meteorito golpea la nave. Cuando se pierden todas las vidas, el juego termina y muestra el puntaje final.
//*OPCIONES:
//Mensajes: Mostrar mensajes de estado o puntaje en la pantalla.
//Titilación de Pantalla: Opcional, puede incluirse para efectos visuales, como para destacar eventos importantes.
//*Deberá: Tener una estructura de clases (o sea, Orientado a Objetos, con más de 1 clase)
//En lo posible, utilizar polimorfismo. Sino, al menos herencia.
//Que los modificadores de acceso estén bien usados (public, private, protected)
//Los objetos y métodos deben estar bien definidos, no hacer métodos que hagan múltiples tareas.	
//Crear una clase gerencial, es decir una clase que maneje la lógica del juego y llame a los demás objetos. Dejar el main limpio. Sólo un objeto que invoque a un método de iniciar juego.
//No utilizar estructuras ni conceptos que no vimos en clase (también es un desafío hacer las cosas con las herramientas que tenemos)
//*Detalles gráficos:
//Pantalla de juego
//Puntaje
//Indicador de teclas para jugar
//El borde

#include <iostream>
#include <conio2.h>
#include <vector>
#include <ctime>
#include <windows.h>
#include <string>
#include <cstdlib>


using namespace std;

//crear las clases que intervendrán en el juego


Class Primal {
protected:
	int x, y;
	int color;
	char symbol;
	
	// los declaro así para que sean valores protegidos: posición, símbolo y color
	
public:
	Primal (int xInicial, int yIncial) : x(xInicial), y(yIncial), symbol (simbolo), color (colour) {}
	
	virtual void dibujar {
	textcolor (color);
	gotoxy (x,y);
	
	cout << symbol;
	
	};
	
	virtual void clear () {
		gotoxy (x, y);
		
		cout << " ";
		
		
	}
	
	int getX () const { return x; }
	int getY () const { return y; }
	
	virtual void move () = 0;
	
	bool chocar (const Primal& otra) const {
		return x == otra.x && y == otra.y;
		
	}
	
	virtual -Primal () {}
	
		
};
//Esta es la clase para todos los elementos del videojuego con los atributos progegidos, el constructor y algunos métodos
//Se crea el Destructor para tener certeza que se destruyan las clases derivadas

Class Jugador {
private:
	int vidas;
	int puntaje;
	
public:
	 Jugador (int xInicial, int yInicial) : Primal (xInicial, yInicial, 'A' GREEN), vidas (5), puntaje (0) {}
	 
	void move () override {
		 if (kbhit (() {
			 char tecla = getch ();
			 clear ();
			 
			 switch (tecla) {
			 case 'a' : if (x>1) x--; break;
			 case 'd' : if (x<78) x++; break;
			 case 'w' : if (y>1) y--; break;
			 case 's' : if (y<23) y++; break;
			 
			 
			 }
		 }
	 }
	bool disparar (vector<Disparo*> & disparos) {
		 if (kbhit()) {
			 char tecla = getch();
			 if (tecla == ' ') {
				 disparos.push_back (new Disparo(x, y-1));
				 return true;
			 }
		 }
		 return false;
	 }
	
	void perderVidas() {
	
	
	
};

int main {
	
	return 0;
}

