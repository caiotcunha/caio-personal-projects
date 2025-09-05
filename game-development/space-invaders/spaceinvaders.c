#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdlib.h>
//fps
const float FPS = 30;
//tela
const int SCREEN_W = 860;
const int SCREEN_H = 540;
//cenário
const int GRASS_H = 60;
//nave piloto dimensões
const int NAVE_W = 100;
const int NAVE_H = 50;
//alienigena dimensões
const int ALIEN_W = 50;
const int ALIEN_H = 25;
//defines úteis
#define NUM_COLUNAS_ALIENS 5
#define NUM_FILAS_ALIEN 4
#define DIST_X_ALIENS 30
#define DIST_Y_ALIENS 30
#define SPEED_ALIEN 10
#define SPEED_NAVE 12
//inicializa o score
int score = 0;
char my_score[100];
int pontos_por_nave = 1;
int naves_destruidas = 0;
//incializa recorde
int recorde = 0;
char texto[100];
//variavel para setar o final
int finalizacao = 1;

ALLEGRO_FONT *tamanho_l;
//Grava o recorde do jogador em um arquivo txt
int NovoRecorde(int score, int *recorde) {
	FILE *arq = fopen("recorde.txt", "r");
	*recorde = -1;
	if(arq != NULL) {
		fscanf(arq, "%d", recorde);
		fclose(arq);
	}
	if(*recorde <= score ){
		arq = fopen("recorde.txt", "w");
		fprintf(arq, "%d", score);
		fclose(arq);
		return 1;
	}
	return 0;	
}

typedef struct Alien{
	float x,y;
	float x_vel,y_vel;
	int viva;
	ALLEGRO_COLOR cor;
} Alien ;
//inicializa alien
void initAlien(Alien *alien){
	alien->x = 0;
	alien->y = 0;
	alien->x_vel = SPEED_ALIEN;
	alien->y_vel = DIST_Y_ALIENS;
	alien->cor = al_map_rgb(rand()%256,rand()%256,rand()%256);
	alien->viva = 1;
}
//desenha alien
void draw_alien(Alien alien){
	al_draw_filled_rectangle(alien.x,alien.y , alien.x + ALIEN_W, alien.y + ALIEN_H,
    alien.cor);
}
//atualiza posicao do alien
void update_Matriz_alien( Alien matriz_alien[NUM_FILAS_ALIEN][NUM_COLUNAS_ALIENS] ){
	int salto = 0;
	for(int i = 0; i < NUM_FILAS_ALIEN; i++ ){
		for(int j = 0; j < NUM_COLUNAS_ALIENS; j++ ){
			if( matriz_alien[i][j].viva == 1 ){
				if(matriz_alien[i][j].x + ALIEN_W + matriz_alien[i][j].x_vel > SCREEN_W || matriz_alien[i][j].x + matriz_alien[i][j].x_vel < 0){
					salto = 1;
				}
			}
		}
	}
	if( salto == 1 ){
		for(int i = 0; i < NUM_FILAS_ALIEN; i++ ){
			for(int j = 0; j < NUM_COLUNAS_ALIENS; j++ ){
				matriz_alien[i][j].y += matriz_alien[i]->y_vel;
				matriz_alien[i][j].x_vel *= -1;
			}
		}
	}
	for(int i = 0; i < NUM_FILAS_ALIEN; i++ ){
		for(int j = 0; j < NUM_COLUNAS_ALIENS; j++ ){
			matriz_alien[i][j].x += matriz_alien[i][j].x_vel;
		}
	}
}

void init_Matriz_Aliens( Alien matriz_alien[NUM_FILAS_ALIEN][NUM_COLUNAS_ALIENS]){
	for (int i = 0; i < NUM_FILAS_ALIEN; i++){
		for(int j = 0; j < NUM_COLUNAS_ALIENS; j++){
		initAlien(&matriz_alien[i][j]);
		matriz_alien[i][j].x += j*ALIEN_W + j*DIST_X_ALIENS;
		matriz_alien[i][j].y += i*ALIEN_H + i*DIST_Y_ALIENS;
		}
	}
}

void draw_matriz_alien(Alien matriz_alien[NUM_FILAS_ALIEN][NUM_COLUNAS_ALIENS]){
	for(int i = 0; i < NUM_FILAS_ALIEN; i++ ){
		for(int j = 0; j < NUM_COLUNAS_ALIENS; j++ ){
			if(matriz_alien[i][j].viva == 1){
			draw_alien( matriz_alien[i][j] );
			}
		}
	}
}

typedef struct Nave{
	float x;
	float vel;
	int dir, esq;
	ALLEGRO_COLOR cor;
} Nave ;
//desenhar cenário
void draw_scenario(){

	al_clear_to_color(al_map_rgb(0,0,0));
	al_draw_filled_rectangle(0,SCREEN_H - GRASS_H ,SCREEN_W , SCREEN_H,
    al_map_rgb(0,255,0));
}
//inicializar nave
void initNave (Nave *nave){
	nave->x = SCREEN_W/2;
	nave->cor = al_map_rgb(0,0,255);
	nave->vel = SPEED_NAVE;
	nave->dir = 0; 
	nave->esq = 0;
}
//desenhar nave
void draw_nave(Nave nave){
	float y_base = SCREEN_H - GRASS_H/2;
	al_draw_filled_triangle(nave.x, y_base - NAVE_H, nave.x - NAVE_W/2 , y_base,
   	nave.x + NAVE_W/2, y_base, nave.cor);
}
//atualiza a posição da nave
void update_nave(Nave *nave){
	if(nave->dir && nave->x + nave->vel <= SCREEN_W - NAVE_W/2){
		nave->x += nave->vel;
	}
	if(nave->esq && nave->x - nave->vel >= NAVE_W/2){
		nave->x -= nave->vel;
	}

}
//verifica colisao de um alien com o solo
int colisao_alien_solo(Alien alien){
	if(alien.viva == 1){
		if( alien.y + ALIEN_H >= SCREEN_H - GRASS_H ){
			return 1;
		}
	}
	return 0;
}
//verifica colisao de todos os aliens da matrzi com o solo
int colisao_matriz_alien_solo(Alien matriz_alien[NUM_FILAS_ALIEN][NUM_COLUNAS_ALIENS]){
	for(int i = 0; i < NUM_FILAS_ALIEN; i++){
		for(int j = 0; j < NUM_COLUNAS_ALIENS; j++){
			if(colisao_alien_solo(matriz_alien[i][j]) == 1 ){
				return 1;
			}	
		}
	}
	return 0;
}
//verifica colisao de um alien com a nave
int colisao_alien_nave(Alien alien, Nave nave){
	if( alien.viva == 1){
		if( alien.x == nave.x || alien.x + ALIEN_W == nave.x){
			if(alien.y + ALIEN_H >= SCREEN_H - GRASS_H/2 - NAVE_H){
			return 1;
			}
		}
	}	
	return 0;
}
//verifica colisao de todos os aliens na matriz com a nave
int colisao_matriz_alien_nave(Alien matriz_alien[NUM_FILAS_ALIEN][NUM_COLUNAS_ALIENS], Nave nave){
	for( int i = 0; i < NUM_FILAS_ALIEN; i++ ){
		for( int j = 0; j < NUM_COLUNAS_ALIENS; j++ ){
			if( colisao_alien_nave(matriz_alien[i][j],nave) == 1 ){
				return 1;
			}
		}
	}
return 0;
}

typedef struct Bala{
	float cx;
	float cy;
	float y_vel;
	float raio;
	ALLEGRO_COLOR cor;
} Bala;

void initBala(Bala *bala){
	bala->cx = SCREEN_W/2;
	bala->cy = SCREEN_H - GRASS_H/2 - NAVE_H;
	bala->y_vel = 20;	
	bala->raio = 5;
	bala->cor = al_map_rgb(255,0,0);
}

void draw_bala( Bala bala ){
	al_draw_filled_circle(bala.cx, bala.cy, bala.raio, bala.cor);
}

void update_bala(Bala *bala,int *balanojogo){
	bala->cy -= bala -> y_vel;
	if( bala->cy - bala->raio <= 0 ){
		*balanojogo = 0;
	}
}
int colisao_bala_alien( Alien alien, Bala bala){
	if( bala.cx + bala.raio <= alien.x + ALIEN_W && bala.cx - bala.raio >= alien.x ){
		if( bala.cy - bala.raio >= alien.y && bala.cy - bala.raio <= alien.y + ALIEN_H && alien.viva == 1){
		return 1;
		}
	}	
	return 0;
}
int colisao_bala_matriz_alien(Alien matriz_alien[NUM_FILAS_ALIEN][NUM_COLUNAS_ALIENS],Bala bala){
	for(int i = 0; i < NUM_FILAS_ALIEN; i++){
		for(int j = 0; j < NUM_COLUNAS_ALIENS; j++){
			if(colisao_bala_alien(matriz_alien[i][j],bala) == 1){
				matriz_alien[i][j].viva = 0;
				naves_destruidas += 1;			
				score += pontos_por_nave;
				// a cada 3 naves destruidas a pontuação por nave dobra de valor
				if(naves_destruidas == 3){
					pontos_por_nave = 2*pontos_por_nave;
					naves_destruidas = 0;
				}
				return 1;
			}
		}
	}
	return 0;
}
void draw_score(){
	sprintf(my_score, "%d", score);
	al_draw_text(tamanho_l, al_map_rgb(0,0,255), 0 , SCREEN_H - GRASS_H , 0, my_score);
}
int verifica_vitoria(Alien matriz_alien[NUM_FILAS_ALIEN][NUM_COLUNAS_ALIENS]){
	for (int i = 0; i < NUM_FILAS_ALIEN; i++){
		for(int j = 0; j < NUM_COLUNAS_ALIENS; j++){
			if(matriz_alien[i][j].viva == 1){
				return 0;
			}
		}
	}
	return 1;
}

int main(){
	
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
   
	//----------------------- rotinas de inicializacao ---------------------------------------
    
	//inicializa o Allegro
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
	//inicializa o modulo allegro que carrega as fontes
	al_init_font_addon();

	//inicializa o modulo allegro que entende arquivos ttf de fontes
	if(!al_init_ttf_addon()) {
		fprintf(stderr, "failed to load tff font module!\n");
		return -1;
	}
	//carrega o arquivo arial.ttf da fonte Arial e define que sera usado o tamanho 32 (segundo parametro)
    tamanho_l = al_load_font("arial.ttf", 32, 1);   
	if(tamanho_l == NULL) {
		fprintf(stderr, "font file does not exist or cannot be accessed!\n");
	}
    //inicializa o módulo de primitivas do Allegro
    if(!al_init_primitives_addon()){
		fprintf(stderr, "failed to initialize primitives!\n");
        return -1;
    }
	//cria um temporizador que incrementa uma unidade a cada 1.0/FPS segundos
    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}
 
	//cria uma tela com dimensoes de SCREEN_W, SCREEN_H pixels
	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}

	//instala o teclado
	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to install keyboard!\n");
		return -1;
	}

	//cria a fila de eventos
	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
	//registra na fila os eventos de tela (ex: clicar no X na janela)
	al_register_event_source(event_queue, al_get_display_event_source(display));
	//registra na fila os eventos de tempo: quando o tempo altera de t para t+1
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	//registra na fila os eventos de teclado (ex: pressionar uma tecla)
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	//inicializa nave
	Nave nave;
	initNave(&nave);
	//inicializa aliens
	Alien matriz_alien[NUM_FILAS_ALIEN][NUM_COLUNAS_ALIENS];
	init_Matriz_Aliens(matriz_alien);
	//inicializa bala
	Bala bala;
	initBala(&bala);
	int balanojogo = 0;
	//inicia o temporizador
	al_start_timer(timer);

	int playing = 1;

	//----------------------- main loop ---------------------------------------

	while(playing) {
		ALLEGRO_EVENT ev;
		//espera por um evento e o armazena na variavel de evento ev
		al_wait_for_event(event_queue, &ev);

		//se o tipo de evento for um evento do temporizador, ou seja, se o tempo passou de t para t+1
		if(ev.type == ALLEGRO_EVENT_TIMER) {
			//desenha cenario;
			draw_scenario();
			//atualiza posição da nave
			update_nave(&nave);
			//atualizaposição dos aliens
			update_Matriz_alien(matriz_alien);
			//update bala
			update_bala(&bala,&balanojogo);
			//desenha nave piloto;
			draw_nave(nave);
			//desenha bala
			if(balanojogo == 1){
				draw_bala(bala);
				//verifica colisao bala alien
				balanojogo = !colisao_bala_matriz_alien(matriz_alien,bala);
			}
			//desenha score
			draw_score();
			//desenha alien
			draw_matriz_alien(matriz_alien);
			al_flip_display();
			//verifica colisão alien solo
			playing = !colisao_matriz_alien_solo(matriz_alien);
			//verifica colisão alien nave
			if(playing == 1){
				playing = !colisao_matriz_alien_nave(matriz_alien,nave);
			}
			//verifica se o jogo foi ganho
			if(playing == 1){
				playing = !verifica_vitoria(matriz_alien);
			}
		}
		//se o tipo de evento for o fechamento da tela (clique no x da janela)
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			playing = 0;
			finalizacao = 0;
		}
		//evento de teclado
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch(ev.keyboard.keycode){
				case ALLEGRO_KEY_LEFT:
					nave.esq = 1;
					break;
				case ALLEGRO_KEY_RIGHT:
					nave.dir = 1;
					break;
				case ALLEGRO_KEY_SPACE:
					if(balanojogo == 0){
						bala.cx = nave.x;
						bala.cy = SCREEN_H - GRASS_H/2 - NAVE_H;
						balanojogo = 1;
					}
					break;
			}
			
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch(ev.keyboard.keycode){
				case ALLEGRO_KEY_LEFT:
					nave.esq = 0;
					break;
				case ALLEGRO_KEY_RIGHT:
					nave.dir = 0;
					break;
			}		
		}
	}
	
	//------------------------------- finalização -----------------------------------------------------------------------------------
	if(finalizacao == 1){
		//reseta a tela para preto
		al_clear_to_color(al_map_rgb(0,0,0));

		if(verifica_vitoria(matriz_alien) == 1){
			al_draw_text(tamanho_l, al_map_rgb(255,255,255), SCREEN_W/2 , GRASS_H , ALLEGRO_ALIGN_CENTRE , "vc venceu :)");
		
		}else{
			al_draw_text(tamanho_l, al_map_rgb(255,255,255), SCREEN_W/2 , GRASS_H , ALLEGRO_ALIGN_CENTRE , "vc perdeu :(");
		
		}
		//atualiza a tela
		al_flip_display();
		al_rest(2);
		//reinicializa a tela para preto
		al_clear_to_color(al_map_rgb(0,0,0));

		if(NovoRecorde(score, &recorde)) {
			al_draw_text(tamanho_l, al_map_rgb(255, 255,255), SCREEN_W/2, GRASS_H,ALLEGRO_ALIGN_CENTRE, "Novo Recorde!");
		}
		else {
		sprintf(texto, "Quase bateu, o recorde é: %d", recorde);
		al_draw_text(tamanho_l, al_map_rgb(255,255,255), SCREEN_W/2, GRASS_H,ALLEGRO_ALIGN_CENTRE, texto);
		}
		//reinicializa a tela
		al_flip_display();

		al_rest(2);
	}

	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
   
 
	return 0;
}