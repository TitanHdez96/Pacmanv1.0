#include <iostream>
#include<Windows.h>
#include<allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include<cstdlib>

#define maxfilas 32//rows
#define maxcolum 29//cols
using namespace std;

int dir = 0;//Controla Direccion de PacMan
int fdir = 0, fx = 1 * 20, fy = 1 * 20;//Direccion y movimientio
int px = 23*20, py = 14*20;//

char mapa[maxfilas][maxcolum] = {//Mapa de caracteres
		("XXXXXXXXXXXXXXXXXXXXXXXXXXXX"),
		("X************XX************X"),
		("X*XXXX*XXXXX*XX*XXXXX*XXXX*X"),
		("XoXXXX*XXXXX*XX*XXXXX*XXXXoX"),
		("X*XXXX*XXXXX*XX*XXXXX*XXXX*X"),
		("X**************************X"),
		("X*XXXX*XX*XXXXXXXX*XX*XXXX*X"),
		("X*XXXX*XX*XXXXXXXX*XX*XXXX*X"),
		("X******XX****XX****XX******X"),
		("XXXXXX*XXXXX*XX*XXXXX*XXXXXX"),
		("XXXXXX*XXXXX*XX*XXXXX*XXXXXX"),
		("XXXXXX*XX**********XX*XXXXXX"),
		("XXXXXX*XX*XXX__XXX*XX*XXXXXX"),
		("XXXXXX*XX*X      X*XX*XXXXXX"),
		("**********X      X**********"),
		("XXXXXX*XX*X      X*XX*XXXXXX"),
		("XXXXXX*XX*XXXXXXXX*XX*XXXXXX"),
		("XXXXXX*XX**********XX*XXXXXX"),
		("XXXXXX*XX*XXXXXXXX*XX*XXXXXX"),
		("XXXXXX*XX*XXXXXXXX*XX*XXXXXX"),
		("X************XX************X"),
		("X*XXXX*XXXXX*XX*XXXXX*XXXX*X"),
		("X*XXXX*XXXXX*XX*XXXXX*XXXX*X"),
		("Xo**XX******** *******XX**oX"),
		("XXX*XX*XX*XXXXXXXX*XX*XX*XXX"),
		("XXX*XX*XX*XXXXXXXX*XX*XX*XXX"),
		("X******XX****XX****XX******X"),
		("X*XXXXXXXXXX*XX*XXXXXXXXXX*X"),
		("X*XXXXXXXXXX*XX*XXXXXXXXXX*X"),
		("X**************************X"),
		("XXXXXXXXXXXXXXXXXXXXXXXXXXXX")
};

void dibujar_mapa() {//Dibuja el mapa en base al mapa de caracteres
	int rows, cols;
	ALLEGRO_BITMAP* cuadro = al_load_bitmap("Cuadro1.png");
	ALLEGRO_BITMAP* pastilla = al_load_bitmap("Pastilla.png");
	ALLEGRO_BITMAP* spastilla = al_load_bitmap("Super Pastilla.png");
	for (rows = 0; rows < 32; rows++){
		for ( cols = 0; cols < 29; cols++){
			if (mapa[rows][cols] == 'X') {
				al_draw_bitmap(cuadro, cols * 20, rows * 20, NULL);
			}else if (mapa[rows][cols] == '*') {
				al_draw_bitmap(pastilla, cols * 20, rows * 20, NULL);
			}else if (mapa[rows][cols] == 'o') {
				al_draw_bitmap(spastilla, cols * 20, rows * 20, NULL);
			}
			

			if ( px / 20 == rows && py / 20 == cols) {
				mapa[rows][cols] = ' ';
			}
		}
	}
	

}

void dibujar_pacman() {//Dibuja a Pacman dentro del mapa
	
	ALLEGRO_BITMAP* pacman = al_load_bitmap("Pacman.png");
	al_draw_bitmap(pacman,py, px, NULL);
	
}

void dibujar_fantasma() {//Dibuja a un fantasma dentro del mapa
	
	ALLEGRO_BITMAP* ghost = al_load_bitmap("BlinkyDown.png");
	al_draw_bitmap(ghost, fx, fy,NULL);
}

void fantasma() {//Dibuja al fantasma en el mapa
	
	dibujar_fantasma();
	/*if (fdir == 0) {
		if (mapa[fx / 20][(fy - 20) / 20] != 'X') { fx -= 20; }
		else fdir = rand() % 4;
	}
	if (fdir == 1) {
		if (mapa[fx / 20][(fy + 20) / 20] != 'X') { fx += 20; }
		else fdir = rand() % 4;
	}
	if (fdir == 2) {
		if (mapa[(fx - 20 / 20)][fy / 20] != 'X') { fy -= 20; }
		else fdir = rand() % 4;
	}
	if (fdir == 3) {
		if (mapa[(fx + 20 / 20)][fy / 20] != 'X') { fy += 20; }
		else fdir = rand() % 4;
	}
	if (fx >= px && fy >= py) {
		if(mapa[(fx/20)+1][fy/20]!='X')
		fx += 20;
		
	}*/
}

int main() {
	int ancho = 0, alto = 0;
	int x = -1, y = -1;
	
	
	
	al_init();
	al_init_image_addon();
	al_install_mouse();
	al_install_keyboard();

	ancho = GetSystemMetrics(SM_CXSCREEN);
	alto = GetSystemMetrics(SM_CYSCREEN);
	ALLEGRO_DISPLAY* ventana = al_create_display(560, 620);//Crea la ventana
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();//Permite detectar eventos en la ventana creada
	al_register_event_source(event_queue, al_get_mouse_event_source());//Detecta eventos del mouse
	al_register_event_source(event_queue, al_get_keyboard_event_source());//Detecta eventos del teclado 
	ALLEGRO_EVENT Evento;
	al_wait_for_event(event_queue, &Evento);
	al_set_window_position(ventana, ancho / 2 - 560 / 2, alto / 2 - 620 / 2);//Posiciona la ventana en el centro de la pantalla 
	
	

	ALLEGRO_EVENT event;//Comando para detectar un evento 
	unsigned char key[ALLEGRO_KEY_MAX];//Permite utilizar todas las teclas de nuestro teclado(cada tecla se tiene que configurar)
	memset(key, 0, sizeof(key));
	
	dibujar_pacman();
	dibujar_mapa();
	
	
	while (1) {
		dibujar_mapa();
		
		/*ALLEGRO_EVENT Evento;
		al_wait_for_event(event_queue, &Evento);
		if (Evento.type == ALLEGRO_EVENT_MOUSE_AXES || Evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			x = Evento.mouse.x;
			y = Evento.mouse.y;
			if (Evento.mouse.button & 1) {

			}
		}*/
		ALLEGRO_EVENT Evento;
		al_wait_for_event(event_queue, &Evento);
		if (Evento.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (Evento.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				dir = 0;
				break;
			case ALLEGRO_KEY_DOWN:
				dir = 1;
				break;
			case ALLEGRO_KEY_LEFT:
				dir = 2;
				break;
			case ALLEGRO_KEY_RIGHT:
				dir = 3;
				break;
			}
			if (dir == 0){
				if(mapa[(px-20)/20][py/20] !='X' )
				px -= 20; 
			}
			if (dir == 1){
				if (mapa[(px + 20) / 20][py / 20] != 'X')
				px += 20; 
			}
			if (dir == 2){
				if (mapa[px / 20][(py-20) / 20] != 'X')
				py -= 20; 
			}
			if (dir == 3){
				if (mapa[px / 20][(py + 20) / 20] != 'X')
				py += 20;
			}
		}
		
		if (py <= -20) { py = 540; }
		if (py > 540) { py = 0; }
		
		dibujar_pacman();
		fantasma();
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}
	
	

		return 0;
}