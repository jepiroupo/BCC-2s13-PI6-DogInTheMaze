#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <unistd.h>

struct argumento {
	unsigned int socket;
	unsigned int numero;
};

const int porta = 7880;

int contador = 1;
int iniciado = 0;
int jogador1_informado = 0;
int jogador2_informado = 0;
int jogador3_informado = 0;
int jogador4_informado = 0;

char mapa_transferencia[7700] = "";
char mapa[770][3];



int direcao_atual = 0;
int pos_x_cachorro = 0;
int pos_y_cachorro = 0;
int shift = 0;
int sprite = 0;

int porta_azul = 0;
int porta_amarela = 0;
int porta_vermelha = 0;
int porta_verde = 0;

int fim = 0;

int jogador1_conectado = 0;
int jogador2_conectado = 0;
int jogador3_conectado = 0;
int jogador4_conectado = 0;
int jogadores_conectados = 0;

int jogador1_enviado_id = 0;
int jogador2_enviado_id = 0;
int jogador3_enviado_id = 0;
int jogador4_enviado_id = 0;
int jogadores_enviado_id = 0;

int jogador1_recebido_id = 0;
int jogador2_recebido_id = 0;
int jogador3_recebido_id = 0;
int jogador4_recebido_id = 0;
int jogadores_recebido_id = 0;

int jogador1_enviado_mapa = 0;
int jogador2_enviado_mapa = 0;
int jogador3_enviado_mapa = 0;
int jogador4_enviado_mapa = 0;
int jogadores_enviado_mapa = 0;

int jogador1_recebido_mapa = 0;
int jogador2_recebido_mapa = 0;
int jogador3_recebido_mapa = 0;
int jogador4_recebido_mapa = 0;
int jogadores_recebido_mapa = 0;

int jogador1_enviado_dados = 0;
int jogador2_enviado_dados = 0;
int jogador3_enviado_dados = 0;
int jogador4_enviado_dados = 0;
int jogadores_enviado_dados = 0;

int jogador_recebido[4];
int jogadores_recebido_dados = 0;

int jogador_pontuacao[4];

int jogador_disponivel[4];

/* DADOS PASSADOS CONTINUAMENTE */
char ev_pos_x_cachorro[4];
char ev_pos_y_cachorro[4];
char ev_porta_azul[1];
char ev_porta_vermelha[1];
char ev_porta_amarela[1];
char ev_porta_verde[1];
char ev_pontuacao_player1[2];
char ev_pontuacao_player2[2];
char ev_pontuacao_player3[2];
char ev_pontuacao_player4[2];
char ev_jogadas_player1[2];
char ev_jogadas_player2[2];
char ev_jogadas_player3[2];
char ev_jogadas_player4[2];
char ev_direcao_cachorro[1];
char ev_pos_imagem_cachorro[1];
char ev_flip_cachorro[1];
/* FIM DADOS PASSADOS CONTINUAMENTE */

const int CIMA = 0;
const int DIREITA = 1;
const int BAIXO = 2;
const int ESQUERDA = 3;

int liberado_envio = 0;
int liberado_recebimento = 1;
int inicio = 0;
int libera_envio_dados = 0;
int libera_atualizacao = 1;

char ret_numero(int dados, int posicao)
{
	int a, b, c, d;
	if(dados < 10)
	{
		d = 0;
		c = 0;
		b = 0;
		a = dados;
	}
	else if(dados < 100)
	{
		a = dados % 10;
		b = (dados - a) / 10;
		c = 0;
		d = 0;
	}
	else if(dados < 1000)
	{
		a = dados % 10;
		b = ((dados - a) % 100) / 10;
		c = (dados - (b * 10) - a) / 100;
		d = 0;
	}
	else
	{
		a = dados % 10;
		b = (dados - a) % 1000 % 100 / 10;
		c = (dados - (b * 10) - a) % 1000 / 100;
		d = (dados - (c * 100) - (b * 10) - a);
	}

	if(posicao == 4)
		return a;
	else if(posicao == 3)
		return b;
	else if(posicao == 2)
		return c;
	else
		return d;
}

void lerConf()
{
    int contador_item = 0, contador_aux = 0;
	char linha;

	int pos_x, pos_y, tipo;
    char aux_p[4];
    char aux_t[3];
    int contador = 0;

    FILE *fp;
    fp = fopen("map/map1.txt","r");

    if( fp == NULL )
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }


    while((linha = fgetc(fp)) != EOF )
    {
        mapa_transferencia[contador_aux] = linha;
		contador_aux = contador_aux + 1;
		
		if(contador < 4)
            aux_p[contador] = linha;
        else if(contador < 8)
            aux_p[contador - 4] = linha;
        else
            aux_t[contador - 8] = linha;

        contador++;

        if(contador == 4)
        {
            sscanf(aux_p, "%d", &pos_x);
            mapa[contador_item][0] = pos_x;
        }
        else if(contador == 8)
        {
            sscanf(aux_p, "%d", &pos_y);
            mapa[contador_item][1] = pos_y;
        }
        else if(contador == 10)
        {
            contador = 0;
            sscanf(aux_t, "%d", &tipo);
            mapa[contador_item][2] = tipo;
            contador_item = contador_item + 1;

			if(tipo == 10)
			{
				pos_x_cachorro = pos_x;
				pos_y_cachorro = pos_y;
			}
        }
    }

   fclose(fp);
}

int validaProximo(int posicao)
{
    if(mapa[posicao][2] == 0)
        return 1;
    else if(mapa[posicao][2] == 6)
        return 1;
    else if(mapa[posicao][2] == 7)
        return 1;
    else if(mapa[posicao][2] == 8)
        return 1;
    else if(mapa[posicao][2] == 9)
        return 1;
    else if(mapa[posicao][2] == 10)
        return 1;
    else if(mapa[posicao][2] == 11)
        return 1;
    else if(mapa[posicao][2] == 12)
        return 1;
    else if(mapa[posicao][2] == 13)
        return 1;
    else if(mapa[posicao][2] == 14)
        return 1;
    return 0;
}

void limparDados()
{
	strcpy(ev_pos_x_cachorro, "");
	strcpy(ev_pos_y_cachorro, "");
	strcpy(ev_porta_azul, "");
	strcpy(ev_porta_vermelha, "");
	strcpy(ev_porta_amarela, "");
	strcpy(ev_porta_verde, "");
	strcpy(ev_pontuacao_player1, "");
	strcpy(ev_pontuacao_player2, "");
	strcpy(ev_pontuacao_player3, "");
	strcpy(ev_pontuacao_player4, "");
	strcpy(ev_jogadas_player1, "");
	strcpy(ev_jogadas_player2, "");
	strcpy(ev_jogadas_player3, "");
	strcpy(ev_jogadas_player4, "");
	strcpy(ev_direcao_cachorro, "");
	strcpy(ev_pos_imagem_cachorro, "");
	strcpy(ev_flip_cachorro, "");
}

int atualizaCachorro()
{
	int flags = 0;
    if (shift >= 9){
        shift = 0;
    }else{
        shift += 1;
    }

    if(direcao_atual == 0){
        flags = 0;
        pos_y_cachorro = pos_y_cachorro - 32;
        sprite = 1;
    }
    else if(direcao_atual == 1){
        flags = 1;
        pos_x_cachorro = pos_x_cachorro + 32;
        sprite = 2;
    }
    else if(direcao_atual == 2){
        flags = 0;
        pos_y_cachorro = pos_y_cachorro + 32;
        sprite = 3;
    }
    else if(direcao_atual == 3){
        flags = 0;
        pos_x_cachorro = pos_x_cachorro - 32;
        sprite = 2;
    }

	ev_pos_x_cachorro[0] = (char)(((int)'0')+ret_numero(pos_x_cachorro, 1));
	ev_pos_x_cachorro[1] = (char)(((int)'0')+ret_numero(pos_x_cachorro, 2));
	ev_pos_x_cachorro[2] = (char)(((int)'0')+ret_numero(pos_x_cachorro, 3));
	ev_pos_x_cachorro[3] = (char)(((int)'0')+ret_numero(pos_x_cachorro, 4));

	ev_pos_y_cachorro[0] = (char)(((int)'0')+ret_numero(pos_y_cachorro, 1));
	ev_pos_y_cachorro[1] = (char)(((int)'0')+ret_numero(pos_y_cachorro, 2));
	ev_pos_y_cachorro[2] = (char)(((int)'0')+ret_numero(pos_y_cachorro, 3));
	ev_pos_y_cachorro[3] = (char)(((int)'0')+ret_numero(pos_y_cachorro, 4));

	ev_porta_azul[0] = (char)(((int)'0')+ret_numero(porta_azul, 1));

	ev_porta_vermelha[0] = (char)(((int)'0')+ret_numero(porta_vermelha, 1));

	ev_porta_amarela[0] = (char)(((int)'0')+ret_numero(porta_amarela, 1));

	ev_porta_verde[0] = (char)(((int)'0')+ret_numero(porta_verde, 1));

	ev_pontuacao_player1[0] = (char)(((int)'0')+ret_numero(jogador_pontuacao[0], 4));
	ev_pontuacao_player1[1] = (char)(((int)'0')+ret_numero(jogador_pontuacao[0], 3));

	ev_pontuacao_player2[0] = (char)(((int)'0')+ret_numero(jogador_pontuacao[1], 4));
	ev_pontuacao_player2[1] = (char)(((int)'0')+ret_numero(jogador_pontuacao[1], 3));

	ev_pontuacao_player3[0] = (char)(((int)'0')+ret_numero(jogador_pontuacao[2], 4));
	ev_pontuacao_player3[1] = (char)(((int)'0')+ret_numero(jogador_pontuacao[2], 3));

	ev_pontuacao_player4[0] = (char)(((int)'0')+ret_numero(jogador_pontuacao[3], 4));
	ev_pontuacao_player4[1] = (char)(((int)'0')+ret_numero(jogador_pontuacao[3], 3));

	ev_jogadas_player1[0] = (char)(((int)'0')+ret_numero(jogador_disponivel[0], 4));
	ev_jogadas_player1[1] = (char)(((int)'0')+ret_numero(jogador_disponivel[0], 3));

	ev_jogadas_player2[0] = (char)(((int)'0')+ret_numero(jogador_disponivel[1], 4));
	ev_jogadas_player2[1] = (char)(((int)'0')+ret_numero(jogador_disponivel[1], 3));

	ev_jogadas_player3[0] = (char)(((int)'0')+ret_numero(jogador_disponivel[2], 4));
	ev_jogadas_player3[1] = (char)(((int)'0')+ret_numero(jogador_disponivel[2], 3));

	ev_jogadas_player4[0] = (char)(((int)'0')+ret_numero(jogador_disponivel[3], 4));
	ev_jogadas_player4[1] = (char)(((int)'0')+ret_numero(jogador_disponivel[3], 3));

	ev_direcao_cachorro[0] = (char)(((int)'0')+ret_numero(sprite, 4));

	ev_pos_imagem_cachorro[0] = (char)(((int)'0')+ret_numero(shift, 4));

	ev_flip_cachorro[0] = (char)(((int)'0')+ret_numero(flags, 4));

	libera_envio_dados = 1;
	libera_atualizacao = 0;
}

void movimento()
{
	int aux_x = pos_x_cachorro/32;
    int aux_y = pos_y_cachorro/32;
    int aux = 0;

    int v_cima=0, v_direita=0, v_baixo=0, v_esquerda=0;

    v_cima = validaProximo(((aux_y-1)*35)+aux_x);
    v_direita = validaProximo((aux_y*35)+aux_x+1);
    v_baixo = validaProximo(((aux_y+1)*35)+aux_x);
    v_esquerda = validaProximo((aux_y*35)+aux_x-1);

    if(direcao_atual == CIMA)
    {
        /* Sem saída */
        if(v_cima == 0 && v_direita == 0 && v_esquerda == 0) direcao_atual = BAIXO;
        /* Uma opcao */
        else if(v_cima == 0 && v_direita == 1 && v_esquerda == 0) direcao_atual = DIREITA;
        else if(v_cima == 0 && v_direita == 0 && v_esquerda == 1) direcao_atual = ESQUERDA;
        /* Duas opções */
        else if(v_cima == 1 && v_direita == 1 && v_esquerda == 0)
        {
            aux = rand() % 2;
            if(aux == 0) direcao_atual = CIMA;
            else direcao_atual = DIREITA;
        }
        else if(v_cima == 1 && v_direita == 0 && v_esquerda == 1)
        {
            aux = rand() % 2;
            if(aux == 0) direcao_atual = CIMA;
            else direcao_atual = ESQUERDA;
        }
        else if(v_cima == 0 && v_direita == 1 && v_esquerda == 1)
        {
            aux = rand() % 2;
            if(aux == 0) direcao_atual = DIREITA;
            else direcao_atual = ESQUERDA;
        }
        else if(v_cima == 1 && v_direita == 1 && v_esquerda == 1)
        {
            aux = rand() % 3;
            if(aux == 0) direcao_atual = CIMA;
            else if(aux == 1) direcao_atual = DIREITA;
            else direcao_atual = ESQUERDA;
        }
    }
    else if(direcao_atual == DIREITA)
    {
        /* Sem saída */
        if(v_cima == 0 && v_baixo == 0 && v_direita == 0) direcao_atual = ESQUERDA;
        /* Uma opcao */
        else if(v_cima == 0 && v_baixo == 1 && v_direita == 0) direcao_atual = BAIXO;
        else if(v_cima == 1 && v_baixo == 0 && v_direita == 0) direcao_atual = CIMA;
        /* Duas opções */
        else if(v_cima == 1 && v_baixo == 1 && v_direita == 0)
        {
            aux = rand() % 2;
            if(aux == 0) direcao_atual = CIMA;
            else direcao_atual = BAIXO;
        }
        else if(v_cima == 1 && v_baixo == 0 && v_direita == 1)
        {
            aux = rand() % 2;
            if(aux == 0) direcao_atual = CIMA;
            else direcao_atual = DIREITA;
        }
        else if(v_cima == 0 && v_baixo == 1 && v_direita == 1)
        {
            aux = rand() % 2;
            if(aux == 0) direcao_atual = BAIXO;
            else direcao_atual = DIREITA;
        }
        else if(v_cima == 1 && v_baixo == 1 && v_direita == 1)
        {
            aux = rand() % 3;
            if(aux == 0) direcao_atual = CIMA;
            else if(aux == 1) direcao_atual = DIREITA;
            else direcao_atual = BAIXO;
        }
    }
    else if(direcao_atual == BAIXO)
    {
        /* Sem saída */
        if(v_esquerda == 0 && v_baixo == 0 && v_direita == 0) direcao_atual = CIMA;
        /* Uma opcao */
        else if(v_baixo == 0 && v_direita == 1 && v_esquerda == 0) direcao_atual = DIREITA;
        else if(v_baixo == 0 && v_direita == 0 && v_esquerda == 1) direcao_atual = ESQUERDA;
        /* Duas opções */
        else if(v_baixo == 1 && v_direita == 1 && v_esquerda == 0)
        {
            aux = rand() % 2;
            if(aux == 0) direcao_atual = BAIXO;
            else direcao_atual = DIREITA;
        }
        else if(v_baixo == 1 && v_direita == 0 && v_esquerda == 1)
        {
            aux = rand() % 2;
            if(aux == 0) direcao_atual = BAIXO;
            else direcao_atual = ESQUERDA;
        }
        else if(v_baixo == 0 && v_direita == 1 && v_esquerda == 1)
        {
            aux = rand() % 2;
            if(aux == 0) direcao_atual = DIREITA;
            else direcao_atual = ESQUERDA;
        }
        else if(v_baixo == 1 && v_direita == 1 && v_esquerda == 1)
        {
            aux = rand() % 3;
            if(aux == 0) direcao_atual = BAIXO;
            else if(aux == 1) direcao_atual = DIREITA;
            else direcao_atual = ESQUERDA;
        }
    }
    else if(direcao_atual == ESQUERDA)
    {
        /* Sem saída */
        if(v_esquerda == 0 && v_baixo == 0 && v_cima == 0) direcao_atual = DIREITA;
        /* Uma opcao */
        else if(v_cima == 0 && v_baixo == 1 && v_esquerda == 0) direcao_atual = BAIXO;
        else if(v_cima == 1 && v_baixo == 0 && v_esquerda == 0) direcao_atual = CIMA;
        /* Duas opções */
        else if(v_cima == 1 && v_baixo == 1 && v_esquerda == 0)
        {
            aux = rand() % 2;
            if(aux == 0) direcao_atual = CIMA;
            else direcao_atual = BAIXO;
        }
        else if(v_cima == 1 && v_baixo == 0 && v_esquerda == 1)
        {
            aux = rand() % 2;
            if(aux == 0) direcao_atual = CIMA;
            else direcao_atual = ESQUERDA;
        }
        else if(v_cima == 0 && v_baixo == 1 && v_esquerda == 1)
        {
            aux = rand() % 2;
            if(aux == 0) direcao_atual = BAIXO;
            else direcao_atual = ESQUERDA;
        }
        else if(v_cima == 1 && v_baixo == 1 && v_esquerda == 1)
        {
            aux = rand() % 3;
            if(aux == 0) direcao_atual = CIMA;
            else if(aux == 1) direcao_atual = BAIXO;
            else direcao_atual = ESQUERDA;
        }
    }


    atualizaCachorro();
}

void* atualizaMapa(void *args)
{
	while(inicio == 0){	}
	limparDados();
	while(fim == 0)
	{
		if(libera_atualizacao == 1)
		{
			movimento();
		}
	}
}

void* enviar(void* argumento)
{
    /*Buffer de entrada (armazena buffer do cliente)*/
    char buffer[7700] = "";
	char dados[31] = "";
	char id_player[1] = "";

    /*Cast do ponteiro*/
    struct argumento* arg = (struct argumento*) argumento;
    int sockEntrada = arg->socket;
	int num_jogador = arg->numero;

	while(1)
    {
	    if(liberado_envio == 1)
		{
		    if(jogadores_enviado_id == 0)
			{
				while(jogador1_enviado_id == 0 || jogador2_enviado_id == 0 && jogador3_enviado_id == 0 && jogador4_enviado_id == 0)
				{
					if(num_jogador == 1 && jogador1_enviado_id == 0)
					{
						memset(id_player, 0, sizeof(id_player));
						strcpy(id_player, "1");
						jogador1_enviado_id = 1;
					}
					else if(num_jogador == 2 && jogador2_enviado_id == 0)
					{
						memset(id_player, 0, sizeof(id_player));
						strcpy(id_player, "2");
						jogador2_enviado_id = 1;
					}
					else if(num_jogador == 3 && jogador3_enviado_id == 0)
					{
						memset(id_player, 0, sizeof(id_player));
						strcpy(id_player, "3");
						jogador3_enviado_id = 1;
					}
					else if(num_jogador == 4 && jogador4_enviado_id == 0)
					{
						memset(id_player, 0, sizeof(id_player));
						strcpy(id_player, "4");
						jogador4_enviado_id = 1;
					}
				}
				jogadores_enviado_id = 1;
				liberado_recebimento = 1;
				liberado_envio = 0;
				
				if(send(sockEntrada, id_player, 1, 0) < 0){
					perror("Thread 'envia' encerrada!");
					return 0;
				}
			}
			else if(jogadores_enviado_mapa == 0)
			{
				while(jogador1_enviado_mapa == 0 || jogador2_enviado_mapa == 0 || jogador3_enviado_mapa == 0 || jogador4_enviado_mapa == 0)
				{
					strcpy(buffer, mapa_transferencia);
					if(num_jogador == 1 && jogador1_enviado_mapa == 0)
					{
						jogador1_enviado_mapa = 1;
					}
					else if(num_jogador == 2 && jogador2_enviado_mapa == 0)
					{
						jogador2_enviado_mapa = 1;
					}
					else if(num_jogador == 3 && jogador3_enviado_mapa == 0)
					{
						jogador3_enviado_mapa = 1; 
					}
					else if(num_jogador == 4 && jogador4_enviado_mapa == 0)
					{
						jogador4_enviado_mapa = 1;
					}
				}
				jogadores_enviado_mapa = 1;
				liberado_recebimento = 1;
				liberado_envio = 0;

				if(send(sockEntrada, buffer, 7700, 0) < 0){
					perror("Thread 'envia' encerrada!");
					return 0;
				}
			}
			else if(jogadores_recebido_mapa == 0)
			{
				while(jogador1_recebido_mapa == 0 || jogador2_recebido_mapa == 0 || jogador3_recebido_mapa == 0 || jogador4_recebido_mapa == 0)
				{
					strcpy(buffer, mapa_transferencia);
					if(num_jogador == 1 && jogador1_recebido_mapa == 0)
					{
						jogador1_recebido_mapa = 1;
					}
					else if(num_jogador == 2 && jogador2_recebido_mapa == 0)
					{
						jogador2_recebido_mapa = 1;
					}
					else if(num_jogador == 3 && jogador3_recebido_mapa == 0)
					{
						jogador3_recebido_mapa = 1; 
					}
					else if(num_jogador == 4 && jogador4_recebido_mapa == 0)
					{
						jogador4_recebido_mapa = 1;
					}
				}
				jogadores_recebido_mapa = 1;
				liberado_recebimento = 1;
				liberado_envio = 0;

				if(send(sockEntrada, buffer, 7700, 0) < 0){
					perror("Thread 'envia' encerrada!");
					return 0;
				}

				inicio = 1;
			}
			else if(inicio == 1 && libera_envio_dados == 1)
			{
				while(jogador1_enviado_dados == 0 || jogador2_enviado_dados == 0 || jogador3_enviado_dados == 0 || jogador4_enviado_dados == 0)
				{
					strcpy(dados, ev_pos_x_cachorro);
					strcat(dados, ev_pos_y_cachorro);
					strcat(dados, ev_porta_azul);
					strcat(dados, ev_porta_vermelha);
					strcat(dados, ev_porta_amarela);
					strcat(dados, ev_porta_verde);
					strcat(dados, ev_pontuacao_player1);
					strcat(dados, ev_pontuacao_player2);
					strcat(dados, ev_pontuacao_player3);
					strcat(dados, ev_pontuacao_player4);
					strcat(dados, ev_jogadas_player1);
					strcat(dados, ev_jogadas_player2);
					strcat(dados, ev_jogadas_player3);
					strcat(dados, ev_jogadas_player4);
					strcat(dados, ev_direcao_cachorro);
					strcat(dados, ev_pos_imagem_cachorro);
					strcat(dados, ev_flip_cachorro);
					
					/*printf("ev_pos_x_cachorro: |%s|\n", ev_pos_x_cachorro);
					printf("ev_pos_y_cachorro: |%s|\n", ev_pos_y_cachorro);					
					printf("ev_porta_azul: |%s|\n", ev_porta_azul);					
					printf("ev_porta_vermelha: |%s|\n", ev_porta_vermelha);					
					printf("ev_porta_amarela: |%s|\n", ev_porta_amarela);					
					printf("ev_porta_verde: |%s|\n", ev_porta_verde);					
					printf("Dados envio: |%s|\n", dados);*/

					if(num_jogador == 1 && jogador1_enviado_dados == 0)
					{
						jogador1_enviado_dados = 1;
					}
					else if(num_jogador == 2 && jogador2_enviado_dados == 0)
					{
						jogador2_enviado_dados = 1;
					}
					else if(num_jogador == 3 && jogador3_enviado_dados == 0)
					{
						jogador3_enviado_dados = 1; 
					}
					else if(num_jogador == 4 && jogador4_enviado_dados == 0)
					{
						jogador4_enviado_dados = 1;
					}
				}

				liberado_recebimento = 1;
				liberado_envio = 0;
				
				libera_envio_dados = 0;
				libera_atualizacao = 1;

				jogador_recebido[0] = 0;
				jogador_recebido[1] = 0;
				jogador_recebido[2] = 0;
				jogador_recebido[3] = 0;
				
				jogador1_enviado_dados = 0;
				jogador2_enviado_dados = 0;
				jogador3_enviado_dados = 0;
				jogador4_enviado_dados = 0;

				if(send(sockEntrada, dados, 31, 0) < 0){
					perror("Thread 'envia' encerrada!");
					return 0;
				}
			}
		}
	}
}

void* receber(void* argumento)
{
    /*Buffer de entrada (armazena buffer do cliente)*/
	char dados[10];
    /*Cast do ponteiro*/
	struct argumento* arg = (struct argumento*) argumento;
    int sockEntrada = arg->socket;
	int num_jogador = arg->numero;

    /*Loop "infinito"*/
    printf("Jogador %d conectado...\n", num_jogador);

    while(1)
    {
	    if(liberado_recebimento == 1)
		{
		    if(jogadores_conectados == 0)
			{
				while(jogador1_conectado == 0 || jogador2_conectado == 0 || jogador3_conectado == 0 || jogador4_conectado == 0)
				{
					memset(dados, '\0', sizeof(dados));
					if((recv(sockEntrada, dados, 3, 0)) != -1)
					{
						if(strcmp(dados, "ola") == 0)
						{
							if(num_jogador == 1)
							{
								jogador1_conectado = 1;
							}
							else if(num_jogador == 2)
							{
								jogador2_conectado = 1;
							}
							else if(num_jogador == 3)
							{
								jogador3_conectado = 1;
							}
							else if(num_jogador == 4)
							{
								jogador4_conectado = 1;
							}
						}
					}
				}
				jogadores_conectados = 1;
				liberado_envio = 1;
				liberado_recebimento = 0;
				printf("> Jogadores conectados!\n");
			}
			else if(jogadores_recebido_id == 0)
			{
				while(jogador1_recebido_id == 0 || jogador2_recebido_id == 0 || jogador3_recebido_id == 0 || jogador4_recebido_id == 0)
				{
					memset(dados, '\0', sizeof(dados));
					if((recv(sockEntrada, dados, 2, 0)) != -1)
					{
						//printf("> Recebi: %s\n", dados);
						if(strcmp(dados, "ok") == 0)
						{
							if(num_jogador == 1)
							{
								jogador1_recebido_id = 1;
							}
							else if(num_jogador == 2)
							{
								jogador2_recebido_id = 1;
							}
							else if(num_jogador == 3)
							{
								jogador3_recebido_id = 1;
							}
							else if(num_jogador == 4)
							{
								jogador4_recebido_id = 1;
							}
						}
					}
				}
				jogadores_recebido_id = 1;
				liberado_envio = 1;
				liberado_recebimento = 0;
				printf("> Jogadores receberam id!\n");
			}
			else
			{
				while(jogador_recebido[0] == 0 || jogador_recebido[1] == 0 || jogador_recebido[2] == 0 || jogador_recebido[3] == 0)
				{
					memset(dados, '\0', sizeof(dados));
					if((recv(sockEntrada, dados, sizeof(dados), 0)) != -1)
					{
						/* Não fez nada */
						if(strcmp(dados, "ok") == 0)
						{
							jogador_recebido[num_jogador - 1] = 1;
							printf("> Recebido ok!\n");
						}
						/* Mudou porta */
						else if(strcmp(dados, "1") == 0 || strcmp(dados, "2") == 0 || strcmp(dados, "3") == 0 || strcmp(dados, "4") == 0)
						{
							printf("Jogador %d mudou uma porta (%s)!\n", num_jogador - 1, dados);							
							if(jogador_disponivel[num_jogador - 1] > 0)
							{
								if(strcmp(dados, "1") == 0)
								{
									if(porta_azul == 1)
										porta_azul = 0;
									else
										porta_azul = 1;
								}
								else if(strcmp(dados, "2") == 0)
								{
									if(porta_vermelha == 1)
										porta_vermelha = 0;
									else
										porta_vermelha = 1;
								}
								else if(strcmp(dados, "3") == 0)
								{
									if(porta_verde == 1)
										porta_verde = 0;
									else
										porta_verde = 1;
								}
								else if(strcmp(dados, "4") == 0)
								{
									if(porta_amarela == 1)
										porta_amarela = 0;
									else
										porta_amarela = 1;
								}
								jogador_disponivel[num_jogador - 1] = jogador_disponivel[num_jogador - 1] - 1;
							}
							jogador_recebido[num_jogador - 1] = 1;
						}
						/* Respondeu uma pergunta */
						else if(dados[2] == '|')
						{
							printf("Jogador %d repondeu uma pergunta: %s\n", num_jogador - 1, dados);
							jogador_recebido[num_jogador - 1] = 1;
						}
					}
				}
				liberado_envio = 1;
				liberado_recebimento = 0;
			}
		}
    }
}
 
int configuracaoServidor()
{
    /*Cria o descritor*/
    int sockfd;
    /*Declaracao da estrutura*/
    struct sockaddr_in serverAddr;
    /*Cria o socket*/
    if ((sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
      printf("Erro no Socket\n");
      exit(1);
    }
    /*Zera a estrutura*/
    memset(&serverAddr, 0, sizeof (serverAddr));
    /*Seta a familia*/
    serverAddr.sin_family = AF_INET;
    /*Seta os IPS (A constante INADDR_ANY e todos os ips ou qualquer ip) htonl -> conversao*/
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    /*Define a porta*/
    serverAddr.sin_port = htons(porta);
    /*Faz a bindagem (cola, gruda, conecta seja o que for)*/
	int on = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if (bind(sockfd, (struct sockaddr *) & serverAddr, sizeof (serverAddr)) < 0)
    {
		printf("Erro no Socket\n");
		exit(1);
	}
    /*Fica na escuta de ate 5 clientes*/
    if (listen(sockfd, 5) < 0)
    {
      printf("Erro no Socket\n");
      exit(1);
    }
    return sockfd;
}
 
int main()
{
	jogador_recebido[0] = 0;
	jogador_recebido[1] = 0;
	jogador_recebido[2] = 0;
	jogador_recebido[3] = 0;

	jogador_pontuacao[0] = 0;
	jogador_pontuacao[1] = 0;
	jogador_pontuacao[2] = 0;
	jogador_pontuacao[3] = 0;

	jogador_disponivel[0] = 3;
	jogador_disponivel[1] = 3;
	jogador_disponivel[2] = 3;
	jogador_disponivel[3] = 3;

	setbuf(stdout, NULL);
    system("clear");
    /*Declaracao da estrutura*/
    struct sockaddr_in serverAddr;
    /*Retorna da funcao e o descritor*/
    int sockfd = configuracaoServidor();

	lerConf();
	pthread_t thread;
	if (pthread_create(&thread, NULL, atualizaMapa, NULL) != 0)
	{
		printf("Erro na Thread\n");
		exit(1);
	}

	int num_jogador = 1;

    /*Loop "infinito"*/
    while (1)
    {
		if(num_jogador < 5)
		{
			int clienteSockfd;
			struct sockaddr_in clienteAddr;
			/*tamanho da estrutura*/
			unsigned int clntLen;
			clntLen = sizeof (clienteAddr);
		
			/*Fica no aguardo da conexao do cliente*/
			if ((clienteSockfd = accept(sockfd, (struct sockaddr *) & clienteAddr, &clntLen)) < 0)
			{
				printf("Erro no Socket\n");
				exit(1);
			}

			struct argumento *arg = malloc(sizeof(struct argumento));
			arg->socket = clienteSockfd;
			arg->numero = num_jogador;

			/*Inicializa a thread*/
			if (pthread_create(&thread, NULL, receber, arg) != 0)
			{
				printf("Erro na Thread\n");
				exit(1);
			}
			/*Inicializa a thread*/
			if (pthread_create(&thread, NULL, enviar, arg) != 0)
			{
				printf("Erro na Thread\n");
				exit(1);
			}

			pthread_detach(thread);

			num_jogador = num_jogador + 1;
		}
    }
    exit(0);
}
