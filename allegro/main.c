#include <stdio.h>
#include<time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

const int SPRITE_SIZE = 32;
int shift = 0;
const float FPS = 30;
const int SCREEN_W = 1415;
const int SCREEN_H = 734;
const int SELETOR_SIZE = 97;
const int margem_x = 15;
const int margem_y = 15;
enum MYKEYS {
   KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};
const int VERMELHO = 2;
const int AZUL = 1;
const int VERDE = 3;
const int AMARELO = 4;

const int CIMA = 0;
const int DIREITA = 1;
const int BAIXO = 2;
const int ESQUERDA = 3;

ALLEGRO_BITMAP *parede;
ALLEGRO_BITMAP *caminho;
ALLEGRO_BITMAP *p_azul;
ALLEGRO_BITMAP *p_verde;
ALLEGRO_BITMAP *p_amarelo;
ALLEGRO_BITMAP *p_vermelho;
ALLEGRO_BITMAP *pa_azul;
ALLEGRO_BITMAP *pa_verde;
ALLEGRO_BITMAP *pa_amarelo;
ALLEGRO_BITMAP *pa_vermelho;
ALLEGRO_BITMAP *background;
ALLEGRO_BITMAP *c_azul;
ALLEGRO_BITMAP *c_verde;
ALLEGRO_BITMAP *c_amarelo;
ALLEGRO_BITMAP *c_vermelho;
ALLEGRO_BITMAP *perguntas;

//ALLEGRO_BITMAP *cachorro;
ALLEGRO_BITMAP *cachorro_lado;
ALLEGRO_BITMAP *cachorro_cima;
ALLEGRO_BITMAP *cachorro_baixo;
ALLEGRO_BITMAP *sprite;
/* 0 - Cima | 1 - Direita | 2 - Baixo | 3 - Esquerda */
int direcao_atual = 3;
int pos_x_cachorro = 0;
int pos_y_cachorro = 0;
int frame_cachorro = 0;

clock_t init_time; //Valor inicial
clock_t last_time; //Valor atual
int wait_time = 8000 * 1000; //Valor de espera
int janela_aberta = 0;

ALLEGRO_FONT *font;
char *texto = "Uma string qualquer";

//Inicia a contagem
int initClock(void) {
    init_time = clock();
    last_time = init_time;
    return (int)init_time;
}

//Atualiza o time
bool checkClock(void) {
    last_time = clock();
    //printf("last: %d, init: %d\n", (int)last_time, (int)init_time);
    //printf("sub: %d\n", (int)last_time-init_time);
    //printf("wait: %d\n", wait_time);
    if ( last_time-init_time >= wait_time ) {
        printf("1");
        return true;//O relogio atingiu o tempo de espera; }
    }else{
        printf("0");
        return false; // o tempo de espera ainda não foi atingido;
    }
}

void lerConf(int mapa[770][3]){
    char linha;

    FILE *fp;

    int pos_x, pos_y, tipo;
    char aux_p[4];
    char aux_t[3];
    int contador = 0;

    int contador_item = 0;

    fp = fopen("map/map1.txt","r");

    if( fp == NULL ){
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }


    while((linha = fgetc(fp)) != EOF ){
        if(contador_item == 770){
            break;
        }

        if(contador < 4)
            aux_p[contador] = linha;
        else if(contador < 8)
            aux_p[contador - 4] = linha;
        else
            aux_t[contador - 8] = linha;

        contador++;

        if(contador == 4){
            sscanf(aux_p, "%d", &pos_x);
            mapa[contador_item][0] = pos_x;
        }
        else if(contador == 8){
            sscanf(aux_p, "%d", &pos_y);
            mapa[contador_item][1] = pos_y;
        }
        else if(contador == 10){
            contador = 0;
            sscanf(aux_t, "%d", &tipo);
//            printf("pos_x: %d\npos_y: %d\ntipo: %d\n", pos_x, pos_y, tipo);
//            printf("contador: %d\n", contador_item);
            mapa[contador_item][2] = tipo;
            contador_item = contador_item + 1;
        }
    }

   fclose(fp);
}

void inicializaBitmaps(){
    parede = al_load_bitmap("img/parede.png");
    caminho = al_load_bitmap("img/caminho.png");
    p_azul = al_load_bitmap("img/p_azul.png");
    p_verde = al_load_bitmap("img/p_verde.png");
    p_amarelo = al_load_bitmap("img/p_amarelo.png");
    p_vermelho = al_load_bitmap("img/p_vermelho.png");
    pa_azul = al_load_bitmap("img/pa_azul.png");
    pa_verde = al_load_bitmap("img/pa_verde.png");
    pa_amarelo = al_load_bitmap("img/pa_amarelo.png");
    pa_vermelho = al_load_bitmap("img/pa_vermelho.png");
    c_azul = al_load_bitmap("img/c_azul.png");
    c_verde = al_load_bitmap("img/c_verde.png");
    c_amarelo = al_load_bitmap("img/c_amarelo.png");
    c_vermelho = al_load_bitmap("img/c_vermelho.png");
    perguntas = al_load_bitmap("img/perguntas.png");

    font = al_load_font("font/roboto.ttf", 22, 0);

    //cachorro = al_load_bitmap("img/cachorro/sprites/cachorro_lado.png");
    cachorro_lado = al_load_bitmap("img/cachorro/sprites/cachorro_lado.png");
    cachorro_cima = al_load_bitmap("img/cachorro/sprites/cachorro_fundo.png");
    cachorro_baixo = al_load_bitmap("img/cachorro/sprites/cachorro_frente.png");
}

bool validaProximo(int mapa[770][3], int posicao){
    if(mapa[posicao][2] == 0)
        return true;
    else if(mapa[posicao][2] == 6)
        return true;
    else if(mapa[posicao][2] == 7)
        return true;
    else if(mapa[posicao][2] == 8)
        return true;
    else if(mapa[posicao][2] == 9)
        return true;
    else if(mapa[posicao][2] == 10)
        return true;
    else if(mapa[posicao][2] == 11)
        return true;
    else if(mapa[posicao][2] == 12)
        return true;
    else if(mapa[posicao][2] == 13)
        return true;
    else if(mapa[posicao][2] == 14)
        return true;
    return false;
}

int atualizaCachorro(){
    int flags = 0;
    if(direcao_atual == 0){
        flags = 0;
        pos_y_cachorro = pos_y_cachorro - 8;
        sprite = al_create_sub_bitmap(cachorro_cima, frame_cachorro * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE);
        al_draw_bitmap(sprite, pos_x_cachorro + margem_x, pos_y_cachorro + margem_y, flags);

    }
    else if(direcao_atual == 1){
        flags = ALLEGRO_FLIP_HORIZONTAL;
        pos_x_cachorro = pos_x_cachorro + 8;
        sprite = al_create_sub_bitmap(cachorro_lado, frame_cachorro * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE);
        al_draw_bitmap(sprite, pos_x_cachorro + margem_x, pos_y_cachorro + margem_y, flags);

    }
    else if(direcao_atual == 2){
        flags = 0;
        pos_y_cachorro = pos_y_cachorro + 8;
        sprite = al_create_sub_bitmap(cachorro_baixo, frame_cachorro * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE);
        al_draw_bitmap(sprite, pos_x_cachorro + margem_x, pos_y_cachorro + margem_y, flags);

    }
    else if(direcao_atual == 3){
        flags = 0;
        pos_x_cachorro = pos_x_cachorro - 8;
        sprite = al_create_sub_bitmap(cachorro_lado, frame_cachorro * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE);
        al_draw_bitmap(sprite, pos_x_cachorro + margem_x, pos_y_cachorro + margem_y, flags);

    }
}

void movimento(int mapa[770][3]){
    int aux_x = pos_x_cachorro/32;
    int aux_y = pos_y_cachorro/32;
    int aux = 0;

    bool v_cima=false, v_direita=false, v_baixo=false, v_esquerda=false;

    v_cima = validaProximo(mapa, ((aux_y-1)*35)+aux_x);
    v_direita = validaProximo(mapa, (aux_y*35)+aux_x+1);
    v_baixo = validaProximo(mapa, ((aux_y+1)*35)+aux_x);
    v_esquerda = validaProximo(mapa, (aux_y*35)+aux_x-1);

    if (frame_cachorro == 3){
        if(direcao_atual == CIMA){
            /* Sem saída */
            if(!v_cima && !v_direita && !v_esquerda) direcao_atual = BAIXO;
            /* Uma opção */
            else if(!v_cima && v_direita && !v_esquerda) direcao_atual = DIREITA;
            else if(!v_cima && !v_direita && v_esquerda) direcao_atual = ESQUERDA;
            /* Duas opções */
            else if(v_cima && v_direita && !v_esquerda){
                aux = rand() % 2;
                if(aux == 0) direcao_atual = CIMA;
                else direcao_atual = DIREITA;
            }
            else if(v_cima && !v_direita && v_esquerda){
                aux = rand() % 2;
                if(aux == 0) direcao_atual = CIMA;
                else direcao_atual = ESQUERDA;
            }
            else if(!v_cima && v_direita && v_esquerda){
                aux = rand() % 2;
                if(aux == 0) direcao_atual = DIREITA;
                else direcao_atual = ESQUERDA;
            }
            else if(v_cima && v_direita && v_esquerda){
                aux = rand() % 3;
                if(aux == 0) direcao_atual = CIMA;
                else if(aux == 1) direcao_atual = DIREITA;
                else direcao_atual = ESQUERDA;
            }
        }
        else if(direcao_atual == DIREITA){
            /* Sem saída */
            if(!v_cima && !v_baixo && !v_direita) direcao_atual = ESQUERDA;
            /* Uma opção */
            else if(!v_cima && v_baixo && !v_direita) direcao_atual = BAIXO;
            else if(v_cima && !v_baixo && !v_direita) direcao_atual = CIMA;
            /* Duas opções */
            else if(v_cima && v_baixo && !v_direita){
                aux = rand() % 2;
                if(aux == 0) direcao_atual = CIMA;
                else direcao_atual = BAIXO;
            }
            else if(v_cima && !v_baixo && v_direita){
                aux = rand() % 2;
                if(aux == 0) direcao_atual = CIMA;
                else direcao_atual = DIREITA;
            }
            else if(!v_cima && v_baixo && v_direita){
                aux = rand() % 2;
                if(aux == 0) direcao_atual = BAIXO;
                else direcao_atual = DIREITA;
            }
            else if(v_cima && v_baixo && v_direita){
                aux = rand() % 3;
                if(aux == 0) direcao_atual = CIMA;
                else if(aux == 1) direcao_atual = DIREITA;
                else direcao_atual = BAIXO;
            }
        }
        else if(direcao_atual == BAIXO){
            /* Sem saída */
            if(!v_esquerda && !v_baixo && !v_direita) direcao_atual = CIMA;
            /* Uma opção */
            else if(!v_baixo && v_direita && !v_esquerda) direcao_atual = DIREITA;
            else if(!v_baixo && !v_direita && v_esquerda) direcao_atual = ESQUERDA;
            /* Duas opções */
            else if(v_baixo && v_direita && !v_esquerda){
                aux = rand() % 2;
                if(aux == 0) direcao_atual = BAIXO;
                else direcao_atual = DIREITA;
            }
            else if(v_baixo && !v_direita && v_esquerda){
                aux = rand() % 2;
                if(aux == 0) direcao_atual = BAIXO;
                else direcao_atual = ESQUERDA;
            }
            else if(!v_baixo && v_direita && v_esquerda){
                aux = rand() % 2;
                if(aux == 0) direcao_atual = DIREITA;
                else direcao_atual = ESQUERDA;
            }
            else if(v_baixo && v_direita && v_esquerda){
                aux = rand() % 3;
                if(aux == 0) direcao_atual = BAIXO;
                else if(aux == 1) direcao_atual = DIREITA;
                else direcao_atual = ESQUERDA;
            }
        }
        else if(direcao_atual == ESQUERDA){
            /* Sem saída */
            if(!v_esquerda && !v_baixo && !v_cima) direcao_atual = DIREITA;
            /* Uma opção */
            else if(!v_cima && v_baixo && !v_esquerda) direcao_atual = BAIXO;
            else if(v_cima && !v_baixo && !v_esquerda) direcao_atual = CIMA;
            /* Duas opções */
            else if(v_cima && v_baixo && !v_esquerda){
                aux = rand() % 2;
                if(aux == 0) direcao_atual = CIMA;
                else direcao_atual = BAIXO;
            }
            else if(v_cima && !v_baixo && v_esquerda){
                aux = rand() % 2;
                if(aux == 0) direcao_atual = CIMA;
                else direcao_atual = ESQUERDA;
            }
            else if(!v_cima && v_baixo && v_esquerda){
                aux = rand() % 2;
                if(aux == 0) direcao_atual = BAIXO;
                else direcao_atual = ESQUERDA;
            }
            else if(v_cima && v_baixo && v_esquerda){
                aux = rand() % 3;
                if(aux == 0) direcao_atual = CIMA;
                else if(aux == 1) direcao_atual = BAIXO;
                else direcao_atual = ESQUERDA;
            }
        }
    }
    atualizaCachorro();
    frame_cachorro = (frame_cachorro + 1) % 4;
}

int desenhaMapa(int mapa[770][3], bool envio[4]){
    int x, y, tipo;

    for(int i = 0; i < 770; i++){
        x = mapa[i][0];
        y = mapa[i][1];
        tipo = mapa[i][2];

        if(tipo == 0)
            al_draw_bitmap(caminho, x + margem_x, y + margem_y, 0);
        else if(tipo == 1)
            al_draw_bitmap(parede, x + margem_x, y + margem_y, 0);
        else if(tipo == 2){
            if(envio[VERMELHO] == false){
                al_draw_bitmap(p_vermelho, x + margem_x, y + margem_y, 0);
            }else{
                mapa[i][2] = 6;
                al_draw_bitmap(pa_vermelho, x + margem_x, y + margem_y, 0);
            }
        }
        else if(tipo == 3){
            if(envio[AZUL] == false){
                al_draw_bitmap(p_azul, x + margem_x, y + margem_y, 0);
            }else{
                mapa[i][2] = 7;
                al_draw_bitmap(pa_azul, x + margem_x, y + margem_y, 0);
            }
        }
        else if(tipo == 4){
            if(envio[VERDE] == false){
                al_draw_bitmap(p_verde, x + margem_x, y + margem_y, 0);
            }else{
                mapa[i][2] = 8;
                al_draw_bitmap(pa_verde, x + margem_x, y + margem_y, 0);
            }
        }
        else if(tipo == 5){
            if(envio[AMARELO] == false){
                al_draw_bitmap(p_amarelo, x + margem_x, y + margem_y, 0);
            }else{
                mapa[i][2] = 9;
                al_draw_bitmap(pa_amarelo, x + margem_x, y + margem_y, 0);
            }
        }
        else if(tipo == 6){
            if(envio[VERMELHO] == false){
                al_draw_bitmap(pa_vermelho, x + margem_x, y + margem_y, 0);
            }else{
                mapa[i][2] = 2;
                al_draw_bitmap(p_vermelho, x + margem_x, y + margem_y, 0);
            }
        }
        else if(tipo == 7){
            if(envio[AZUL] == false){
                al_draw_bitmap(pa_azul, x + margem_x, y + margem_y, 0);
            }else{
                mapa[i][2] = 3;
                al_draw_bitmap(p_azul, x + margem_x, y + margem_y, 0);
            }
        }
        else if(tipo == 8){
            if(envio[VERDE] == false){
                al_draw_bitmap(pa_verde, x + margem_x, y + margem_y, 0);
            }else{
                mapa[i][2] = 4;
                al_draw_bitmap(p_verde, x + margem_x, y + margem_y, 0);
            }
        }
        else if(tipo == 9){
            if(envio[AMARELO] == false){
                al_draw_bitmap(pa_amarelo, x + margem_x, y + margem_y, 0);
            }else{
                mapa[i][2] = 5;
                al_draw_bitmap(p_amarelo, x + margem_x, y + margem_y, 0);
            }
        }
        else if(tipo == 10 && pos_x_cachorro == 0 && pos_y_cachorro == 0){
            printf("i: %d - x: %d - y: %d\n", i, x, y);
            pos_x_cachorro = x;
            pos_y_cachorro = y;
            //al_draw_bitmap(cachorro_lado, x + margem_x, y + margem_y, 0);
            atualizaCachorro();
        }
        else if(tipo == 11){
            mapa[i][2] = 11;
            al_draw_bitmap(c_vermelho, x + margem_x, y + margem_y, 0);
        }
        else if(tipo == 12){
            mapa[i][2] = 12;
            al_draw_bitmap(c_azul, x + margem_x, y + margem_y, 0);
        }
        else if(tipo == 13){
            mapa[i][2] = 13;
            al_draw_bitmap(c_verde, x + margem_x, y + margem_y, 0);
        }
        else if(tipo == 14){
            mapa[i][2] = 14;
            al_draw_bitmap(c_amarelo, x + margem_x, y + margem_y, 0);
        }
    }

    if(envio[VERMELHO] == true)
        envio[VERMELHO] = false;
    if(envio[AZUL] == true)
        envio[AZUL] = false;
    if(envio[VERDE] == true)
        envio[VERDE] = false;
    if(envio[AMARELO] == true)
        envio[AMARELO] = false;

    al_draw_text(font, al_map_rgb(255, 0, 0), (SCREEN_W / 2) + 530, 325, ALLEGRO_ALIGN_CENTRE, "Jogador 1");
    al_draw_text(font, al_map_rgb(0, 255, 0), (SCREEN_W / 2) + 530, 366, ALLEGRO_ALIGN_CENTRE, "Jogador 2");
    al_draw_text(font, al_map_rgb(0, 0, 255), (SCREEN_W / 2) + 530, 407, ALLEGRO_ALIGN_CENTRE, "Jogador 3");
    al_draw_text(font, al_map_rgb(255, 255, 0), (SCREEN_W / 2) + 530, 448, ALLEGRO_ALIGN_CENTRE, "Jogador 4");
}

int main(int argc, char **argv){
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *seletor = NULL;

    float tamanho = 25;
    float espacamento = SELETOR_SIZE + 19;
    float seletor_x = 1174;
    float seletor_y = 40;
    bool key[4] = { false, false, false, false };
    bool redraw = true;
    bool doexit = false;
    float posicao = 0;
    int mapa[770][3];
    bool envio[4] = { false, false, false, false };


    //Inicia o allegro
    al_init();
    al_init_image_addon();
    al_install_keyboard();

     // Inicialização do add-on para uso de fontes
    al_init_font_addon();
    al_init_ttf_addon();

    inicializaBitmaps();
    lerConf(mapa);

    //Cria a lista de eventos
    event_queue = al_create_event_queue();

    //Cria o timer
    timer = al_create_timer(1.0 / FPS);

    //Cria a janela
    display = al_create_display(SCREEN_W, SCREEN_H);

    //Limpa a janela com a cor preta
    al_clear_to_color(al_map_rgb(0, 0, 0));

    //Carrega a imagem de fundo na variável
    background = al_load_bitmap("img/fundo.png");
    //Desenha a imagem de fundo na posição (0,0)
    al_draw_bitmap(background, 0, 0, 0);

    //Carrega a imagem do seletor na variável
    seletor = al_load_bitmap("img/selecao.png");
    //Desenha o seletor na posição (1174,40)
    al_draw_bitmap(seletor, 1174, 40, 0);

    desenhaMapa(mapa, envio);

    //Registra os eventos
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_flip_display();

    //Inicia o timer
    al_start_timer(timer);

    //Inicia contagem de tempo para a pergunta aparecer
    initClock();

    //While do jogo
    while(!doexit){
        //Aguarda o evento
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        //Se der o tempo do timer, verifica qual tecla foi pressionada e se é possível se mover para a posição de destino
        if(ev.type == ALLEGRO_EVENT_TIMER){
            if(key[KEY_LEFT] && (posicao == 1 || posicao == 3) && (janela_aberta == 0)) {
                seletor_x -= espacamento;
                if(posicao == 1)
                    posicao = 0;
                else
                    posicao = 2;
            }
            if(key[KEY_RIGHT] && (posicao == 0 || posicao == 2) && (janela_aberta == 0)) {
                seletor_x += espacamento;
                if(posicao == 0)
                    posicao = 1;
                else
                    posicao = 3;
            }
            if(key[KEY_UP] && (posicao == 2 || posicao == 3) && (janela_aberta == 0)) {
                seletor_y -= espacamento;
                if(posicao == 2)
                    posicao = 0;
                else
                    posicao = 1;
            }
            if(key[KEY_DOWN] && (posicao == 0 || posicao == 1) && (janela_aberta == 0)) {
                seletor_y += espacamento;
                if(posicao == 0)
                    posicao = 2;
                else
                    posicao = 3;
            }

            redraw = true;
        }
        //Se a janela for fechada, termina o jogo
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        //Se o evento for um tecla pressionada, seta a variável dessa tecla para "true" (pressionada)
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_LEFT:
                    key[KEY_LEFT] = true;
                    break;

                case ALLEGRO_KEY_RIGHT:
                    key[KEY_RIGHT] = true;
                    break;

                case ALLEGRO_KEY_UP:
                    key[KEY_UP] = true;
                    break;

                case ALLEGRO_KEY_DOWN:
                    key[KEY_DOWN] = true;
                    break;
            }
        }
        //Se o evento for um tecla solta, seta a variável dessa tecla para "false" (caso seja Esc, encerra o programa)
        else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_LEFT:
                    key[KEY_LEFT] = false;
                    break;

                case ALLEGRO_KEY_RIGHT:
                    key[KEY_RIGHT] = false;
                    break;

                case ALLEGRO_KEY_ESCAPE:
                    doexit = true;
                    break;

                case ALLEGRO_KEY_UP:
                    key[KEY_UP] = false;
                    break;

                case ALLEGRO_KEY_DOWN:
                    key[KEY_DOWN] = false;
                    break;
                case ALLEGRO_KEY_ENTER:
                    if (janela_aberta == 0){
                        if(posicao == 0)
                            envio[VERMELHO] = true;
                        else if(posicao == 1)
                            envio[AZUL] = true;
                        else if(posicao == 2)
                            envio[VERDE] = true;
                        else if(posicao == 3)
                            envio[AMARELO] = true;
                    }

            }
        }

        //Redesenha o jogo
        if(redraw && al_is_event_queue_empty(event_queue)){
            redraw = false;
            al_draw_bitmap(background, 0, 0, 0);
            desenhaMapa(mapa, envio);
            movimento(mapa);
            if (janela_aberta == 0){
                if (checkClock()){
                    janela_aberta = 1;
                }
            }else{
                al_draw_bitmap(perguntas, 0, 0, 0);
                al_draw_textf(font, al_map_rgb(255, 255, 255), SCREEN_W / 2, 250, ALLEGRO_ALIGN_CENTRE, "%s", texto);

                printf("check\n");
                initClock();
            }
            al_draw_bitmap(seletor, seletor_x, seletor_y, 0);
            al_flip_display();
        }
    }

    //Destrói os objetos
    al_destroy_bitmap(background);
    al_destroy_bitmap(seletor);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
