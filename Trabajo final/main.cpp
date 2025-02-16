/*Objetivo: El objetivo es disparar a los enemigos que cruzan la pantalla a distintas velocidades y evitar los meteoritos que caen verticalmente. La nave del jugador tiene 5 vidas. Cada vez que un meteorito golpea la nave, se pierde una vida.
*Jugabilidad:
Nave: Controlada por el jugador, puede moverse en cualquier dirección (izquierda, derecha, arriba, abajo) y disparar.
Enemigos: Se mueven horizontalmente a diferentes velocidades y aparecen desde los bordes de la pantalla.
Meteoritos: Caen verticalmente desde la parte superior de la pantalla y pueden golpear la nave.
*Puntuación:
Eliminar enemigos: Al disparar y eliminar enemigos, se suma una cantidad de puntos (esto se puede ajustar según el enemigo).
Mensajes de Puntaje: Mostrar mensajes de puntuación como "Nice shoot", "Good one", etc., cuando un enemigo es eliminado.
*Vidas:
Iniciales: Comienza con 5 vidas.
Perder vidas: Se pierde una vida si un meteorito golpea la nave. Cuando se pierden todas las vidas, el juego termina y muestra el puntaje final.
*OPCIONES:
Mensajes: Mostrar mensajes de estado o puntaje en la pantalla.
Titilación de Pantalla: Opcional, puede incluirse para efectos visuales, como para destacar eventos importantes.
*Deberá: Tener una estructura de clases (o sea, Orientado a Objetos, con más de 1 clase)
En lo posible, utilizar polimorfismo. Sino, al menos herencia.
Que los modificadores de acceso estén bien usados (public, private, protected)
Los objetos y métodos deben estar bien definidos, no hacer métodos que hagan múltiples tareas.	
Crear una clase gerencial, es decir una clase que maneje la lógica del juego y llame a los demás objetos. Dejar el main limpio. Sólo un objeto que invoque a un método de iniciar juego.
No utilizar estructuras ni conceptos que no vimos en clase (también es un desafío hacer las cosas con las herramientas que tenemos)
*Detalles gráficos:
Pantalla de juego
Puntaje
Indicador de teclas para jugar
El borde*/

#include <iostream>
#include <conio2.h>
#include <vector>
#include <ctime>
#include <windows.h>
#include <string> //NO SE SI LA TERMINO USANDO...
#include <cstdlib>

//----REVISAR MAYUSCULAS Y MINUSCULAS Y LA SINTAXIS QUE ESTO NO ES VISUAL STUDIO
	
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
//-----------------REVISAR: por ahí los valores no queden bien,
			 
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
		vidas --;
	}
	
	void agregarPuntaje (int puntos) {
		puntaje += puntos
	}
	
	Int getVidas () const { return vidas; }
	int getPuntaje () const { return puntaje; }
		
};

//Hereda de Primal, tiene las 5 vidas iniciales y la puntuacion
//con el "move" se usan las teclas WASD
//el metodo disparar crea nuevas balas cuando se preciona la tecla 'espacio'


//--------REVISAR: capaz la clase disparo puede ir despues....
//--------REVISAR: si el color se escribia así

Class Disparo : public Primal {
public:
	disparo (int xInicial, int yInicial) : Primal (xInicial, yIncial, 'l' , LIGHTCYAN) {}
	
	void move() override {
		clear ();
		y--;
	}
	
};

//Clase simple para los disparos
//se mueve hacia arriba
//usa el simbolo 'l' con color cyan

Class Enemigos : public Primal {
protected:
	int puntos;
	int velocidad;
public:
	Enemigos(int xInicial, int yInicial, char simbolo, int colour, int pts, int vel)
		: Primal (int xInicial, int yInicial, simbolo, colour), puntos(pts), velocidad(vel) {}
	
	int getPuntos() const {return puntos; }
	
};

//Clase base para todos los Enemigos
//se agregan puntos al eliminar y velocidad
//los enemigos se moverán diferente

Class Nave : public Enemigos {
private:
	int direccion;
public:
	Nave(int xInicial, int yInicial, 'V', LIGHTRED, 10, rand() % 2 + 1) {
		direccion = (xInicial <= 40) ? 1 : -1;
	}
	//VER COMO QUEDAN ESTOS VALORES!
	
	void move () override {
		clear();
		x += direccion * velocidad;
		
		if (x <=1 || x >= 78) {
			direccion *= -1:
				y++;
		}
	}
};

//la nave enemiga se mueve en sentido horizontal
//da 10 puntos al ser eliminada
//se cambia la direccion al llegar al borde bajando una linea
//velocidad aleatora 1-2

Class Meteorito : public Enemigos
public:
	Meteorito(int xInicial)
		: Enemigos(xInicial, 1, '*', BROWN, 0, rand () % 2 + 1) {}
	
	void move () override {
		clear();
		y += velocidad;
	}
};

//el meteorito se mueve en sentido vertica
//no da puntos si se destruye, pero sí quita vida 
//velocidad aleatoria 1-2
	
	
	
	
	
	
//---¿NO HACE FALTA UN CIN.FAIL EN EL JUEGO? O NO HACE FALTA?

int main {
	
	return 0;
}

