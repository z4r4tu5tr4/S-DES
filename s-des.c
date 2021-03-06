/*

	Geral:

		Código feito e testado no Slackware 14.1 com gcc 4.8.3 e bash 4.3
		Escrito(e muito mal escrito) por Eduardo Mendes (mendesxeduardo@gmail.com)
		É um passo a passo desenvolvido nos laboratórios da Fatec-AM
		Durante as aulas de criptografia
		Esse texto é melhor visualizado no gedit(http://www.gedit.org)

	Versão e Licença:

		Licença:
			GPL.

		Versões:

		V. 0.1	-	03/14 - Eduardo Mendes
		
			Agradecimento:
				Em especial ao Mestre Jedi Alexandre Aguado por me mostrar a arte da criptografia
				e dar o ponta pé inicial a uma área da computação que mudou a minha vida.
				
		V. 0.2	-	08/14 - Eduardo Mendes

			Alterações:

				1.	Inserção de um Menu para organizar as chamadas;
				2.	Redução de algumas(muitas) linhas de código aplicando chaveamento
				3.	Melhor documentação e explicação via comentários no código

			Agradecimento:
				Especial para o Murilo Fujita que me fez voltar a mecher com esse código para que suas linhas
				fossem muito melhor estruturada e limpa na v. 0.2. Um Abraço.
	Sobre o Programa:

		O objetivo desse programa é ser uma alternativa simples para o
		entendimento do algorimito DES, usando uma vertente chamada S-DES
		Apresentada no apendice C do livro: "Criptografia e segurança em redes
		de computadores" - Willian Stallings

	Sobre a Funcionalidade:
		
		Expanção de chaves(void chaves()):

			O programa pede uma entrada de 10 bit para trabalhar com as chaves
			e leva os resultados para k1 e k2 (variáveis globais)
		
		Sobre o funconamento (int sdes()):
		
			Trata a entrada de um texto claro(em bits) e executa a criptografia, ou decriptografia
			do texto usando a chave que foi usada como entrada na primeira função
	
	Sobre o futuro dessas linhas:

		Organização das variáveis e mudança de alguns nomes para melhor entendimento do código.
		Aplicações corretas no uso de funções e migrar para python.
*/

#include <stdlib.h>
#include <stdio.h>
#include <curses.h>

//variaveis_globais

//Chave de 10bits
int chave[10];
//primeira Key gerada pela expansão de chaves
int k1[8];
//segunda Key gerada pela expansão de chaves
int k2[8];
//Texto claro inserido a ser criptografado
int texto[8];

//Chaveamento

int c_cripto, c_exp, c_menu = 0;


//função que cria as Ks
void chaves (){

	system("clear");

	//variaveis_locais
	int j; //Variável contadora
	int p[10]/* Vertor para auxiliar as passagens*/, le[5] /*uso de lados para auxiliar na rotações únicas de bits*/, ld[5];

	printf("Digite os 10 numeros de chave:\n");

	for(j=0;j<=9;j++){
		scanf("%i",&chave[j]);
		if(chave[j]!=1 && chave[j] !=0){
		printf("Digite só 0 ou 1!!!:\n");
		}
	}

	//Permutação10
	p[0]=chave[2];
	p[1]=chave[4];
	p[2]=chave[1];
	p[3]=chave[6];
	p[4]=chave[3];
	p[5]=chave[9];
	p[6]=chave[0];
	p[7]=chave[8];
	p[8]=chave[7];
	p[9]=chave[5];

	//LS-1(le)

	le[0]=p[1];
	le[1]=p[2];
	le[2]=p[3];
	le[3]=p[4];
	le[4]=p[0];

	//LS-1(ld)
	ld[0]=p[6];
	ld[1]=p[7];
	ld[2]=p[8];
	ld[3]=p[9];
	ld[4]=p[5];

	//permutação 8

	//junção dos caracteres
	p[0]=le[0];
	p[1]=le[1];
	p[2]=le[2];
	p[3]=le[3];
	p[4]=le[4];
	p[5]=ld[0];
	p[6]=ld[1];
	p[7]=ld[2];
	p[8]=ld[3];
	p[9]=ld[4];

	//K1

	k1[0]=p[5];
	k1[1]=p[2];
	k1[2]=p[6];
	k1[3]=p[3];
	k1[4]=p[7];
	k1[5]=p[4];
	k1[6]=p[9];
	k1[7]=p[8];

	printf("k1:    ");
	for(j=0;j<8;j++){

		printf("%i",k1[j]);
	}

	printf("\n");

	//LS-2 le
	le[0]=p[3];
	le[1]=p[3];
	le[2]=p[4];
	le[3]=p[0];
	le[4]=p[1];

	//LS-2 ld
	ld[0]=p[7];
	ld[1]=p[8];
	ld[2]=p[9];
	ld[3]=p[5];
	ld[4]=p[6];

	//p8(2)

	p[0]=le[0];
	p[1]=le[1];
	p[2]=le[2];
	p[3]=le[3];
	p[4]=le[4];
	p[5]=ld[0];
	p[6]=ld[1];
	p[7]=ld[2];
	p[8]=ld[3];
	p[9]=ld[4];

	//K2

	k2[0]=p[5];
	k2[1]=p[2];
	k2[2]=p[6];
	k2[3]=p[3];
	k2[4]=p[7];
	k2[5]=p[4];
	k2[6]=p[9];
	k2[7]=p[8];

	printf("k2:    ");

	for(j=0;j<8;j++){

	        printf("%i",k2[j]);
	}

	printf("\n");


	printf("chave: ");

	for(j=0;j<10;j++){

	        printf("%i",chave[j]);
	}

	printf("\n");
}

//Função que executa o algoritimo
void sdes(){

	int p[8]/*Auxiliar para permutação */,ld[4],le[4]/*Divisão para trablhar com lados*/,xor[8]/*Váriavel para o XOR*/;

	int linha[2],coluna[2]/*Variáveis para percorrer a matriz*/,bit[2]/*Recebe o bit percorrido da matriz*/;

	int i,j; //Variáveis contadores

	//Matrizes pré definidas nó algoritimo
	int s0[4][4],s1[4][4];

	//
	int pm[4];

	//ip(final do codigo)
	int ip[8];

	//Váriável que auxilia o chaveamento do chaveamento
	int decripto[8];

	//valores da matriz s0
	s0[0][0]=1;
	s0[0][1]=0;
	s0[0][2]=3;
	s0[0][3]=2;
	s0[1][0]=3;
	s0[1][1]=2;
	s0[1][2]=1;
	s0[1][3]=0;
	s0[2][0]=0;
	s0[2][1]=2;
	s0[2][2]=1;
	s0[2][3]=3;
	s0[3][0]=3;
	s0[3][1]=1;
	s0[3][2]=3;
	s0[3][3]=2;

	//valores da matriz s1
	s1[0][0]=0;
	s1[0][1]=1;
	s1[0][2]=2;
	s1[0][3]=3;
	s1[1][0]=2;
	s1[1][1]=0;
	s1[1][2]=1;
	s1[1][3]=3;
	s1[2][0]=3;
	s1[2][1]=0;
	s1[2][2]=1;
	s1[2][3]=0;
	s1[3][0]=2;
	s1[3][1]=1;
	s1[3][2]=0;
	s1[3][3]=3;

	//Chaveamento em ação

	if (c_exp == 0){

		printf("Por favor, primeiro faca a expansao das chaves\n\n");
		menu();

	}else{
		if(c_cripto == 1){
			c_cripto = 0;
		}
		else if(c_cripto == 1){
			
			for(i = 0; i < 9; i++){

				decripto[i] = k1[i];

			}
			for(i = 0; i < 9; i++){
				k1[i] = k2[i];
			}
			for(i = 0; i < 9; i++){
				k2[i] = decripto[i];
			
			}
		}
	}



	printf("Digite o texto claro em bits: \n");

	for(j=0;j<8;j++){

		scanf("%i",&texto[j]);
		if((texto[j]!=1) && (texto[j] !=0)){
	        	printf("Digite só 0 ou 1!!!:\n");
	        }

	}

	//IP
	p[0]=texto[1];
	p[1]=texto[5];
	p[2]=texto[2];
	p[3]=texto[0];
	p[4]=texto[3];
	p[5]=texto[7];
	p[6]=texto[4];
	p[7]=texto[6];

	//L - R
	le[0]=p[0];
	le[1]=p[1];
	le[2]=p[2];
	le[3]=p[3];
	ld[0]=p[4];
	ld[1]=p[5];
	ld[2]=p[6];
	ld[3]=p[7];

	//E/P
	p[0]=ld[3];
	p[1]=ld[0];
	p[2]=ld[1];
	p[3]=ld[2];
	p[4]=ld[1];
	p[5]=ld[2];
	p[6]=ld[3];
	p[7]=ld[0];

	//XOR K1
	xor[0]=(p[0]^k1[0]);
	xor[1]=(p[1]^k1[1]);
	xor[2]=(p[2]^k1[2]);
	xor[3]=(p[3]^k1[3]);
	xor[4]=(p[4]^k1[4]);
	xor[5]=(p[5]^k1[5]);
	xor[6]=(p[6]^k1[6]);
	xor[7]=(p[7]^k1[7]);

	//matriz s0 1-4

	if( (xor[0]=0) && (xor[3]=0)){
		linha[0]=0;
	}
	if( (xor[0]=0) && (xor[3]=1)){
		linha[0]=1;
	}
	if( (xor[0]=1)  && (xor[3]=0)){
	        linha[0]=2;
	}
	if( (xor[0]=1) && (xor[3]=1)){
	        linha[0]=3;
	}

	//matriz s0 2-3

	if((xor[1]=0)  && (xor[2]=0)){
	        coluna[0]=0;
	}
	if((xor[1]=0) && (xor[2]=1)){
	        coluna[0]=1;
	}
	if((xor[1]=1)  && (xor[2]=0)){
	        coluna[0]=2;
	}
	if((xor[1]=1) && (xor[2]=1)){
	        coluna[0]=3;
	}

	//busca na matriz S0

	for(j=0;j>4;j++){
		if(linha[0]=j){
			for(i=0;i>4;i++){
				if(coluna[0]=i){
					bit[0]=s0[j][i];
				}
			}
		}
	}

	//converçao decimal -> binario
	if(bit[0]=0){

		pm[0]=0;
		pm[1]=0;
	}if(bit[0]=1){

		pm[0]=0;
		pm[1]=1;

	}if(bit[0]=2){

		pm[0]=1;
		pm[1]=0;

	}if(bit[0]=3){

		pm[0]=1;
		pm[1]=1;
	}

	//matriz s1 1-4

	if((xor[4]=0)  && (xor[7]=0)){
	        linha[1]=0;
	}
	if((xor[4]=0) && (xor[7]=1)){
	        linha[1]=1;
	}
	if((xor[4]=1)  && (xor[7]=0)){
	        linha[1]=2;
	}
	if((xor[4]=1) && (xor[7]=1)){
	        linha[1]=3;
	}

	//matriz s1 2-3

	if((xor[5]=0)  && (xor[6]=0)){
	        coluna[1]=0;
	}
	if((xor[5]=0) && (xor[6]=1)){
	        coluna[1]=1;
	}
	if((xor[5]=1)  && (xor[6]=0)){
	        coluna[1]=2;
	}
	if((xor[5]=1) && (xor[6]=1)){
	        coluna[1]=3;
	}

	//busca na matriz S1

	for(j=0;j>4;j++){
	        if(linha[1]=j){
	                for(i=0;i>4;i++){
	                        if(coluna[1]=i){
	                                bit[1]=s1[j][i];
	                        }
	                }
	        }
	}

	//converçao decimal -> binario S1
	if(bit[1]=0){

	        pm[2]=0;
	        pm[3]=0;

	}if(bit[1]=1){

	        pm[2]=0;
	        pm[3]=1;

	}if(bit[1]=2){

	        pm[2]=1;
	        pm[3]=0;

	}if(bit[1]=3){

	        pm[2]=1;
	        pm[3]=1;
	}

	//P4

	p[0]=pm[1];
	p[1]=pm[3];
	p[2]=pm[2];
	p[3]=pm[0];

	//xor Le ^ p4

	xor[0]=(le[0]^p[0]);
	xor[1]=(le[1]^p[1]);
	xor[2]=(le[2]^p[2]);
	xor[3]=(le[3]^p[3]);

	//junçao 8bits

	p[0]=xor[0];
	p[1]=xor[1];
	p[2]=xor[2];
	p[3]=xor[3];
	p[4]=ld[0];
	p[5]=ld[1];
	p[6]=ld[2];
	p[7]=ld[3];

	//SW

	le[0]=p[4];
	le[1]=p[5];
	le[2]=p[6];
	le[3]=p[7];
	ld[0]=p[0];
	ld[1]=p[1];
	ld[2]=p[2];
	ld[3]=p[3];

	//E/P

	p[0]=ld[3];
	p[1]=ld[0];
	p[2]=ld[1];
	p[3]=ld[2];
	p[4]=ld[1];
	p[5]=ld[2];
	p[6]=ld[3];
	p[7]=ld[0];

	//XOR K2

	xor[0]=(p[0]^k2[0]);
	xor[1]=(p[1]^k2[1]);
	xor[2]=(p[2]^k2[2]);
	xor[3]=(p[3]^k2[3]);
	xor[4]=(p[4]^k2[4]);
	xor[5]=(p[5]^k2[5]);
	xor[6]=(p[6]^k2[6]);
	xor[7]=(p[7]^k2[7]);

	//matriz s0 1-4

	if((xor[0]=0)  && (xor[3]=0)){
	        linha[1]=0;
	}
	if((xor[0]=0) && (xor[3]=1)){
	        linha[1]=1;
	}
	if((xor[0]=1)  && (xor[3]=0)){
	        linha[1]=2;
	}
	if((xor[0]=1) && (xor[3]=1)){
	        linha[1]=3;
	}

	//matriz s0 2-3

	if((xor[1]=0)  && (xor[2]=0)){
	        coluna[1]=0;
	}
	if((xor[1]=0) && (xor[2]=1)){
	        coluna[1]=1;
	}
	if((xor[1]=1)  && (xor[2]=0)){
	        coluna[1]=2;
	}
	if((xor[1]=1) && (xor[2]=1)){
	        coluna[1]=3;
	}

	//busca na matriz S0

	for(j=0;j>4;j++){
	        if(linha[1]=j){
	                for(i=0;i>4;i++){
	                        if(coluna[1]=i){
	                                bit[0]=s0[j][i];
	                        }
	                }
	        }
	}

	//converçao decimal -> binario
	if(bit[0]=0){

	        pm[0]=0;
	        pm[1]=0;

	}if(bit[0]=1){

	        pm[0]=0;
	        pm[1]=1;

	}if(bit[0]=2){

	        pm[0]=1;
	        pm[1]=0;

	}if(bit[0]=3){

	        pm[0]=1;
	        pm[1]=1;
	}

	//matriz s1 1-4

	if((xor[4]=0)  && (xor[7]=0)){
	        linha[1]=0;
	}
	if((xor[4]=0) && (xor[7]=1)){
	        linha[1]=1;
	}
	if((xor[4]=1)  && (xor[7]=0)){
	        linha[1]=2;
	}
	if((xor[4]=1) && (xor[7]=1)){
	        linha[1]=3;
	}

	//matriz s1 2-3

	if((xor[5]=0)  && (xor[6]=0)){
	        coluna[1]=0;
	}
	if((xor[5]=0) && (xor[6]=1)){
	        coluna[1]=1;
	}
	if((xor[5]=1)  && (xor[6]=0)){
	        coluna[1]=2;
	}
	if((xor[5]=1) && (xor[6]=1)){
	        coluna[1]=3;
	}

	//busca na matriz S1

	for(j=0;j>4;j++){
	        if(linha[1]=j){
	                for(i=0;i>4;i++){
	                        if(coluna[1]=i){
	                                bit[1]=s1[j][i];
	                        }
	                }
	    }
	}

	//converçao decimal -> binario S1
	if(bit[1]=0){

	        pm[2]=0;
	        pm[3]=0;

	}if(bit[1]=1){

	        pm[2]=0;
	        pm[3]=1;

	}if(bit[1]=2){

	        pm[2]=1;
	        pm[3]=0;

	}if(bit[1]=3){

	        pm[2]=1;
	        pm[3]=1;
	}

	//P4

	p[0]=pm[1];
	p[1]=pm[3];
	p[2]=pm[2];
	p[3]=pm[0];

	//xor Le ^ p4

	xor[0]=(le[0]^p[0]);
	xor[1]=(le[1]^p[1]);
	xor[2]=(le[2]^p[2]);
	xor[3]=(le[3]^p[3]);

	//junçao 8bits

	p[0]=xor[0];
	p[1]=xor[1];
	p[2]=xor[2];
	p[3]=xor[3];
	p[4]=ld[0];
	p[5]=ld[1];
	p[6]=ld[2];
	p[7]=ld[3];

	//IP(reverso)

	ip[0]=p[3];
	ip[1]=p[0];
	ip[2]=p[2];
	ip[3]=p[4];
	ip[4]=p[6];
	ip[5]=p[1];
	ip[6]=p[7];
	ip[7]=p[5];

	printf("Valor criptografado: ");
	for(j=0;j<=7;j++){

		printf("%i",ip[j]);

	}

	printf("\nTexto puro: ");

	for(j=0;j<=7;j++){

		printf("%d",texto[j]);

	//volta dos valores em caso de decriptografia

	if(c_cripto == 1){
			
		for(i = 0; i < 9; i++){

			decripto[i] = k2[i];

		}
		for(i = 0; i < 9; i++){
			k2[i] = k1[i];
		}
		for(i = 0; i < 9; i++){
			k1[i] = decripto[i];
		
		}

	c_cripto = 0;

	}
	printf("\n");
}

//função que executa o menu e faz as chamas para criptografar ou decrtiptografar
void menu(){

	int opt = 0;

	if (c_menu == 0){

	system("clear");

	}
	do{
		printf("=== MENU ====");
		printf("\n\n");
		printf("1. Expandir Chaves\n");
		printf("2. Criptografar\n");
		printf("3. decriptografar\n");
		printf("4. Sair");
		printf("\n\n");
		printf("Opção: ");

	    scanf("%i", &opt);

		system("clear");
		c_menu = 1;

		switch(opt){
			case 1:
				c_exp = 1;
				chaves();
				break;
			case 2:
				c_cripto = 1;
				sdes();
				break;
			case 3:
				c_cripto = 1;
				sdes();
				break;
			case 4:
				exit(0);
				break;
			default:
				exit(0);
				break;
	       }
	}while (opt < 4);
}

//mantem o laço constante
main(){
	
	menu();
}
