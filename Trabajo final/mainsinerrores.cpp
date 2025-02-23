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
#include <string> 
#include <cstdlib>

//----REVISAR MAYUSCULAS Y MINUSCULAS Y LA SINTAXIS QUE ESTO NO ES VISUAL STUDIO

using namespace std;

//crear las clases que intervendrán en el juego

//capaz tengo que hacer el "terreno" primero....

class Primal {
protected:
	int x, y;
	int color;
	char symbol;
	
	// los declaro así para que sean valores protegidos: posición, símbolo y color
	
public:
	Primal (int xInicial, int yInicial, char sym, int col) : x(xInicial), y(yInicial),symbol (sym), color (col) {}
	
	virtual void dibujar () {
		textcolor (color);
		gotoxy (x,y);
		
		cout << symbol;
		
	}
	
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
	
	virtual ~Primal () {}
	
	
};


//Esta es la clase para todos los elementos del videojuego con los atributos progegidos, el constructor y algunos métodos
//Se crea el Destructor para tener certeza que se destruyan las clases derivadas

class Disparo : public Primal {
public:
	Disparo (int xInicial, int yInicial) : Primal (xInicial, yInicial, 'l' , LIGHTCYAN) {}
	
	void move() override {
		clear ();
		y--;
	}
	
};

//Clase simple para los disparos
//se mueve hacia arriba
//usa el simbolo 'l' con color cyan

class NaveJugador : public Primal {
private:
	int vidas;
	int puntaje;
	
public:
	NaveJugador (int xInicial, int yInicial) : Primal (xInicial, yInicial, 'A', GREEN), vidas (5), puntaje (0) {}
	
	void move() override {
		if (kbhit ()) {
			char tecla = getch ();
			clear ();
			
			switch (tecla) {
			case 'a' : if (x>1) x--; break;
			case 'd' : if (x<78) x++; break;
			case 'w' : if (y>1) y--; break;
			case 's' : if (y<23) y++; break;
			//-----------------REVISAR: por ahí los valores no queden bien,
			
			}
			dibujar();
		}
	}
	
	bool disparar (vector <Disparo*> & disparos) {
		if (kbhit()) {
			char tecla = getch();
			if (tecla == ' ') {
				disparos.push_back (new Disparo(x, y-1));
				return true;
			}
		}
		return false;
	}
	
	void perderVidas() { vidas--; }
	void agregarPuntaje (int puntos) { puntaje += puntos; }

	int getVidas() const { return vidas; }
	int getPuntaje() const { return puntaje; }
	
};

//Hereda de Primal, tiene las 5 vidas iniciales y la puntuacion
//con el "move" se usan las teclas WASD
//el metodo disparar crea nuevas balas cuando se preciona la tecla 'espacio'


//--------REVISAR: capaz la clase disparo puede ir despues....
//--------REVISAR: si el color se escribia así



class Enemigo : public Primal {
protected:
	int puntos;
	int velocidad;
public:
	Enemigo(int xInicial, int yInicial, char sym, int col, int pts, int vel)
		: Primal (xInicial, yInicial, sym, col), puntos(pts), velocidad(vel) {}
	
	int getPuntos() const {return puntos; }
	
};

//Clase base para todos los Enemigos
//se agregan puntos al eliminar y velocidad
//los enemigos se moverán diferente

class NaveEnemiga : public Enemigo {
private:
	int direccion;
public:
	NaveEnemiga(int xInicial, int yInicial)
		: Enemigo(xInicial, yInicial, 'V', LIGHTRED, 10, rand() % 2 + 1) {
		direccion = (xInicial <= 40) ? 1 : -1;
	}
	//VER COMO QUEDAN ESTOS VALORES!
	
	void move () override {
		clear();
		x += direccion * velocidad;
		
		if (x <=1 || x >= 78) {
			direccion *= -1;
				y++;
		}
		dibujar();
	}
};

//la nave enemiga se mueve en sentido horizontal
//da 10 puntos al ser eliminada
//se cambia la direccion al llegar al borde bajando una linea
//velocidad aleatora 1-2

class Meteorito : public Enemigo {
public:
	Meteorito(int xInicial)
		: Enemigo(xInicial, 1, '*', BROWN, 0, rand () % 2 + 1) {}
	
	void move () override {
		clear();
		y += velocidad;
		dibujar();
	}
};

//el meteorito se mueve en sentido vertica
//no da puntos si se destruye, pero sí quita vida 
//velocidad aleatoria 1-2

class Madre {
private:
	NaveJugador* jugador;
	vector<Enemigo*> enemigos;
	vector<Disparo*> disparos;
	vector<string> mensajes;
	
	bool gameOver;
	int frameCount;
	
	void dibujarBorde();
	void mostrarStatus();
	void mostrarMensajes();
	void agregarMensaje(const string& msj);
	void spawnEnemigos();
	void colisionesEnemigos();
	void limpiarObjetos();
	
public:
	Madre () : gameOver(false), frameCount(0) {
		srand(time(nullptr));
		jugador = new NaveJugador (40, 20);
		mensajes.push_back ("Defendamos la galaxia! Vamos, Miguel!");
		
	}
	
	~Madre () {
		
		delete jugador;
		for (auto disparo : disparos) delete disparo;
		for (auto enemigo : enemigos) delete enemigo;
		
	}
	
	void run (); 
};

	

// acá armo la clase principal que gestiona
//controla mensajes, cuenta frames, estado de juego, puntero a los objetos
//el metodo run contiene el bucle principal
//el constructor inicializa el juego y el destructor libera memoria

void Madre::dibujarBorde() {
	textcolor (WHITE);
	for (int i=0; i < 70; i++) {
		gotoxy (i, 0);
		cout << "#";
		gotoxy (i, 24);
		cout << "#";
	}
	for (int i=0; i<25; i++){
		gotoxy (0, i);
		cout <<"#";
		gotoxy (79, i);
		cout << "#";
	}
}
//dibujo el borde del mapa con el simbolo #

void Madre::mostrarStatus() {
	textcolor (LIGHTGRAY);
	gotoxy (2, 25);
	cout << "Vidas: " << jugador -> getVidas() <<" Puntaje: " << jugador -> getPuntaje();
	gotoxy(50, 25);
	cout << "CONTROLES : A, D, W, S y BARRA ESPACIADORA ";
}
//se muestra en pantalla las vidas, los puntos y las teclas de controles

void Madre::mostrarMensajes() {
	int y = 26;
	for (size_t i=0; i < mensajes.size() && i <3; i++){
		gotoxy (2, y + i);
		cout << " ";
		gotoxy (2, y + i);
		cout << mensajes[i];
	}
}

void Madre::agregarMensaje (const string& msj) {
	mensajes.insert(mensajes.begin(),msj);
	if (mensajes.size() >3) {
		mensajes.pop_back();
	}
}
//Es para los mensajes que aparecen en pantalla, como "Buen tiro"

void Madre::spawnEnemigos() {
	if (frameCount % 30 == 0) {
		int x = rand() % 75 + 2;
		enemigos.push_back (new NaveEnemiga(x,2));
	}
	if (frameCount % 20 == 0) {
		int x = rand() % 75 + 2;
		enemigos.push_back (new Meteorito(x));
	}
}
//Hace nuevos enemigos cada 30 frames para naves, cada 20 frames para meteoritos

void Madre::colisionesEnemigos() {
	for (auto disparoIt = disparos.begin(); disparoIt != disparos.end();) {
		bool disparoRemoved = false;
		
		for (auto enemigoIt = enemigos.begin(); enemigoIt != enemigos.end();) {
			if ((*disparoIt)-> chocar (**enemigoIt)) {
				NaveEnemiga* nave = dynamic_cast<NaveEnemiga*>(*enemigoIt);
				if (nave) {
					jugador->agregarPuntaje(nave->getPuntos());
			
			//mensaje aleatorio
			string msjs[] = {"¡Buen Tiro!", "Excelenteee", "¡Lo hiciste!", "¡Fabulosoo!"};
			agregarMensaje(msjs[rand() %4] + " +" + to_string(nave->getPuntos()) + " puntos");
				}
				
				(*disparoIt)->clear();
				(*enemigoIt)->clear();
				
				delete *disparoIt;
				delete *enemigoIt;
				
				disparoIt = disparos.erase(disparoIt);
				enemigoIt = enemigos.erase(enemigoIt);
				
				disparoRemoved = true;
				break;
				
				
			}else {
				++enemigoIt;
			}
		}
		
		if (!disparoRemoved) {
			++disparoIt;
		}
	}
	//colisiones entre la nave y los enemigos
	for (auto enemigoIt = enemigos.begin(); enemigoIt != enemigos.end();) {
		Meteorito* meteorito = dynamic_cast<Meteorito*>(*enemigoIt);
		if (meteorito && meteorito->chocar(*jugador)) {
			jugador->perderVidas();
			
			//para la titilacion
			for (int i=0; i<3; i++) {
				jugador->clear();
				Sleep(100);
				jugador->dibujar();
				Sleep(100);
			}
			
			agregarMensaje("Te dieron... Perdés una vida. Te quedan: " + to_string(jugador->getVidas()));
			meteorito->clear();
			delete meteorito;
			enemigoIt = enemigos.erase(enemigoIt);
			
			if (jugador->getVidas() <=0) {
				gameOver = true;
			}
		}else {
			++enemigoIt;
		}
		
	}
	
}

//Entre los disparos y los enemigos: suma puntos y muestra mensaje
//Entre la nave y los meteoritos: se pierde vida y efecto de titilacion

void Madre::limpiarObjetos () {
	for (auto it = disparos.begin(); it != disparos.end();) {
		if ((*it) ->getY() <=0) {
			(*it)->clear();
			delete *it;
			it = disparos.erase(it);
		}else {
			++it;
		}
	}
	for (auto it = enemigos.begin(); it != enemigos.end();) {
		if ((*it) ->getY() >= 24) {
			(*it)->clear();
			delete *it;
			it = enemigos.erase(it);
		}else {
			++it;
		}
	}
}

void Madre::run() {
	clrscr();
	_setcursortype(_NOCURSOR);
	
	dibujarBorde();
	mostrarStatus();
	
	while (!gameOver) {
		frameCount++;
		
		jugador->move();
		jugador->disparar(disparos);
		
		for (auto disparo : disparos) disparo->move();
		for (auto enemigo : enemigos) enemigo->move();
		
		spawnEnemigos();
		
		colisionesEnemigos();
		
		jugador->dibujar();
		for (auto disparo : disparos) disparo->dibujar();
		for (auto enemigo : enemigos) enemigo->dibujar();
		
		mostrarStatus();
		mostrarMensajes();
		
		Sleep(50);
	}
	
	clrscr();
	gotoxy (30, 10);
	cout << "Juego Terminado";
	gotoxy (30, 12);
	cout << "Tu puntuación final es: " << jugador->getPuntaje();
	gotoxy (25, 14);
	cout << "Para salir presiona una tecla cualquiera, como Homero...";
	
	getch();
	
}

//Este es el bucle principal del juego: se limpia la pantalla, se oculta el mouse, se dibuja el borde.
//Se ejecuta el bucle mientras no sea GameOver. Se mueven objetos, se crean enemigos, se detecta colisiones, se dibujan los objetos, se espera 50ms para controlar la velocidad.
//Se muetra la pantalla de fin del juego con la puntuacion obtenida

//---¿NO HACE FALTA UN CIN.FAIL EN EL JUEGO? O NO HACE FALTA?

int main () {
	Madre game;
	game.run ();
	
	return 0;
}
