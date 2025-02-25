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
#include <conio2.h> //esta biblioteca es para la pantalla y colores
#include <vector> //esta biblioteca es para las listas dinamicas
#include <ctime> //esta biblioteca es para el tiempo y generar numeros
#include <windows.h> //esta biblioteca es para funciones del Windows como Sleep, por ejemplo
#include <string> //esto es para usar la clase string
#include <cstdlib> //esto es para usar funciones como rand



using namespace std;

//creo la clase base para todos los objetos del juego

class Primal {
protected:
	int x, y;
	int color;
	char symbol;
	
	// los declaro así para que sean valores protegidos: posición en el mapa, símbolo y color
	
public:
	Primal (int xInicial, int yInicial, char sym, int col) : x(xInicial), y(yInicial),symbol (sym), color (col) {}
	
	virtual void dibujar () {
		textcolor (color);
		gotoxy (x,y);
		
		putch(symbol);
		
	}
	//dibuja el objeto en su posicion
	
	virtual void clear () {
		textbackground(BLACK);
		gotoxy (x, y);
		
		putch(' ');
		
		
	}
	//el clear borra el objeto
	
	int getX () const { return x; }
	int getY () const { return y; }
	
	//metodo de movimiento que usaran las clases derivadas
	
	virtual void move () = 0;
	
	//verifica si el objeto choca con algo 
	
	bool chocar (const Primal& otra) const {
		return x == otra.x && y == otra.y;
		
	}
	
	virtual ~Primal () {}
	////Se crea el Destructor para tener certeza que se destruyan las clases derivadas
	
};





class Disparo : public Primal {
private:
	int velocidad;
	//velocidad de los disparos
	
public:
	Disparo (int xInicial, int yInicial) : Primal (xInicial, yInicial, 'l' , LIGHTCYAN), velocidad(2) {}
	
	
	void move() override {
		clear ();
		y--;
		if (y>0) {
			dibujar();
		}
	}
	
};

//Clase simple para los disparos
//se mueve hacia arriba
//usa el simbolo 'l' con color cyan

class NaveJugador : public Primal {
private:
	int vidas;
	int puntaje;
	int cooldownDisparo;
	

	
public:
	NaveJugador (int xInicial, int yInicial) : Primal (xInicial, yInicial, 'A', GREEN), vidas (5), puntaje (0), cooldownDisparo(0) {}
	
	void move() override {
		if (kbhit ()) {
			char tecla = getch ();
			clear ();
			
			switch (tecla) {
			case 'a' : if (x>1) x--; break;
			case 'd' : if (x<78) x++; break;
			case 'w' : if (y>1) y--; break;
			case 's' : if (y<23) y++; break;
			case ' ' : 
				if (cooldownDisparo == 0) {
					cooldownDisparo = 5;
				}
				break;
			
			}
			
		}
		if (cooldownDisparo>0) {
			cooldownDisparo--;
			
		}
		dibujar();
		
	}
	
	bool disparar (vector <Disparo*> & disparos) {
		if (cooldownDisparo == 4) {
			disparos.push_back(new Disparo(x, y-1));
			
			return true;
		}
		//hace que dispare desde la nave
		return false;
	}
	//hace un nuevo disparo si está listo
	
	void perderVidas() { vidas--; }
	void agregarPuntaje (int puntos) { puntaje += puntos; }

	int getVidas() const { return vidas; }
	int getPuntaje() const { return puntaje; }
	
};
/*Hereda de Primal, tiene las 5 vidas iniciales y la puntuacion
con el "move" se usan las teclas WASD
el metodo disparar crea nuevas balas cuando se preciona la tecla 'espacio'*/





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

//el meteorito se mueve en sentido vertical
//no da puntos si se destruye, pero sí quita vida 


class Madre {
private:
	NaveJugador* jugador;
	vector<Enemigo*> enemigos;
	vector<Disparo*> disparos;
	vector<string> mensajes;
	
	bool gameOver;
	int frameCount;
//clase Madre para gestionar el juego
//string para los mensajes en pantalla
//el bool es para el estado del juego
//frameCount cuenta los frames para controlar el tiempo
	
	void spawnEnemigos() {
		if (frameCount % 30 == 0) {
			int x = rand() % 75 + 2;
			enemigos.push_back(new NaveEnemiga(x, 2));
		}
		if (frameCount % 20 == 0 && enemigos.size() <15) {
			int x = rand() % 75 + 2;
			enemigos.push_back(new Meteorito(x));
		}
	}
//esto fabrica enemigos periodicamente tanto naves enemigas como meteoritos
	
	void colisionesEnemigos() {
		for (auto disparoIt = disparos.begin(); disparoIt != disparos.end();) {
			bool disparoRemoved = false;
			
			for (auto enemigoIt = enemigos.begin(); enemigoIt != enemigos.end();) {
				if ((*disparoIt)->chocar(**enemigoIt)) {
					NaveEnemiga* nave = dynamic_cast<NaveEnemiga*>(*enemigoIt);
					if (nave) {
						jugador->agregarPuntaje(nave->getPuntos());
						
						string msjs[] = {"¡Buen Tiro!", "Excelenteee", "¡Lo hiciste!", "¡Fabulosoo!"};
						agregarMensaje(msjs[rand() % 4] + " +" + to_string(nave->getPuntos()) + " puntos");
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
	//esto detecta los choques entre los disparos que hacemos y los enemigos
		
		for (auto enemigoIt = enemigos.begin(); enemigoIt != enemigos.end();) {
			if ((*enemigoIt)->chocar(*jugador)) {
				jugador->perderVidas();
				
				for (int i=0; i<3; i++) {
					jugador->clear();
					Sleep(50);
					jugador->dibujar();
					Sleep(50);
				}
				
				if (dynamic_cast<Meteorito*>(*enemigoIt)) {
					agregarMensaje("¡Te golpeó un meteorito! Perdés una vida. Te quedan: " + to_string(jugador->getVidas()));
				
				} else {
					agregarMensaje("¡Colisión con nave enemiga! Perdés una vida. Te queda: " + to_string(jugador->getVidas()));
				}
				
				(*enemigoIt)->clear();
				delete *enemigoIt;
				enemigoIt = enemigos.erase(enemigoIt);
				
				if (jugador->getVidas() <=0) {
					gameOver = true;
					
				}
			}else {
				++enemigoIt;
			}
		}
	}
	//esto detecta los choques entre nuestra nave y las naves enemigas
	
	void limpiarObjetos() {
		
		for (auto it = disparos.begin(); it != disparos.end();) {
			if ((*it)->getY() <=0) {
				(*it)->clear();
				delete *it;
				it = disparos.erase(it);
			}else {
				++it;
			}
		}
		
		for (auto it = enemigos.begin(); it != enemigos.end();) {
			if ((*it)->getY() >=24) {
				(*it)->clear();
				delete *it;
				it = enemigos.erase(it);
			}else {
				++it;
			}
		}
	}	
	//esto va borrando los disparos fuera de la pantalla
	
	void  dibujarBorde() {
		textbackground(BLACK);
		textcolor(WHITE);
		
		for (int i=0; i<=79; i++) {
			gotoxy (i, 0);
			putch ('#');
			gotoxy (i, 24);
			putch ('#');
		}
		
		for (int i=1; i<=23; i++) {
			gotoxy (0, i);
			putch ('#');
			gotoxy (79, i);
			putch ('#');
		}
		
		for (int i=25; i<=28; i++) {
			gotoxy (1, i);
			clreol();
		}
	}
	//esto es para dibujar los bordes de la pantalla
	//el ultimo for es para borrar los mensajes de la parte inferior para que no se apilen
	
	void mostrarStatus() {
		textbackground(BLACK);
		textcolor(LIGHTGRAY);
		
		gotoxy (1, 25);
		cout << "Vidas: " << jugador->getVidas() << " | Puntaje: " << jugador->getPuntaje();
		gotoxy (45, 25);
		cout << "CONTROLES : A, D, W, S y BARRA ESPACIADORA ";
	}
//esto es para mostrar las vidas y el puntaje que llevamos
	
	void mostrarMensajes() {
		textbackground(BLACK);
		textcolor(YELLOW);
		int y = 26;
		
		for (size_t i=0; i <mensajes.size() && i<3; i++) {
			gotoxy (2, y+i);
			clreol();
			cout << mensajes[i];
		}
	}
//con esto se muestras los ultimos 3 mensajes 
	
	void agregarMensaje(const string & msj) {
		mensajes.insert(mensajes.begin(), msj);
		if (mensajes.size() >3) {
			mensajes.pop_back();
		}
	}
//agrega un mensaje pero mantiene lo de los 3 ultimos
	
	
public:
	Madre () : gameOver(false), frameCount(0) {
		srand(time(nullptr));
		jugador = new NaveJugador (40, 20);
		mensajes.push_back ("Defendamos la galaxia! Vamos, Miguel!");
		
		clrscr();
		textbackground(BLACK);
		_setcursortype(_NOCURSOR);
	}
	
	void run() {
		dibujarBorde();
		mostrarStatus();
		jugador->dibujar();
		
		while (!gameOver) {
			frameCount++;
			
			for (auto disparo : disparos) disparo->move();
			for (auto enemigo : enemigos) enemigo->move();
			
			jugador->move();
			jugador->disparar(disparos);
			
			spawnEnemigos();
			colisionesEnemigos();
			limpiarObjetos();
			
			mostrarStatus();
			mostrarMensajes();
			
			Sleep(30);
			
		}
		
		clrscr();
		textbackground(BLACK);
		gotoxy (30, 10);
		cout << "Juego Terminado";
		gotoxy (30, 12);
		cout << "Tu puntuación final es: " << jugador->getPuntaje();
		gotoxy (25, 14);
		cout << "Para salir presiona una tecla cualquiera, como Homero...";
		
		getch();
		
				
	}
	
	~Madre () {
		
		delete jugador;
		for (auto disparo : disparos) delete disparo;
		for (auto enemigo : enemigos) delete enemigo;
		
	}
	
	
};

	

// acá armo la clase principal que gestiona
//controla mensajes, cuenta frames, estado de juego, puntero a los objetos
//el metodo run contiene el bucle principal
//el constructor inicializa el juego y el destructor libera memoria
//Este es el bucle principal del juego: se limpia la pantalla, se oculta el mouse, se dibuja el borde.
//Se ejecuta el bucle mientras no sea GameOver. Se mueven objetos, se crean enemigos, se detecta colisiones, se dibujan los objetos, se espera 50ms para controlar la velocidad.
//Se muetra la pantalla de fin del juego con la puntuacion obtenida
//el destructor libera la memoria de los objetos como jugador, disparos, enemigos


int main () {
	Madre game;
	game.run ();
	
	return 0;
}
//en el main se crea la instancia del juego y lo ejecuta
