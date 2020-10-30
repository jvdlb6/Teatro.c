#include<stdio.h>
#include<time.h>
#define LIM 18
#define COL 23
#define MAX 3
#define MAXF 5// QUANTIDADE FILA
//CAPACIDADE DA FILA
//VAGO = 0
//RESEVADOR = 1
//VENDIDO =2

//ESTRUTURA PARA TRABALHAR COM O TEMPO
typedef struct{
	int tm_sec; /* Segundos, 0-59*/
	int tm_min; /* Minutos, 0-59*/
	int tm_hour; /*Horas 0-23 */
	int tm_mday; /*dia do mês, 1-31 */
	int tm_mon; /* mês a partir de janeiro, 0-11 */
	int tm_year; /* anos a partir de 1900 */
	int tm_wday; /* dias a partir de domingo, 0-6 */
	int tm_yday; /* dias a partir de 1 de janeiro 1-365 */
	int tm_isdst; /* Indicador de horário de verão */
}tm;

//ESTRUTURA DA MATRIZ(PESSOA)
typedef struct{
	int cdg;
	char nome[40];
	int telefone;
	int tipo;
}pessoa;
typedef pessoa Matriz[LIM][COL];

//ESTRUTURA DA SECAO(MATRIZ)
typedef struct {
    int cod;
    char Nome[40];
    char data[10]; // dd/mm/yyyy
    Matriz Secao;
}Secao;

//ESTRUTURA DA LISTA
typedef struct {
    Secao Item[MAX];
    int Prim, Ult;
}Lista_est;

//ESTRUTURA DA FILA
typedef struct { pessoa Item[MAXF];
                 int Inicio, Fim, Total;
                }Fila_est;

//DECLARACAO GLOBAL DO TIPO FILA E NOME
//FUNCAO PARA REGISTRAR O TEMPO
void registarDataHorario(){
	int dia, mes, ano, segundo, minuto, hora;

	struct tm *local;
	time_t t;
	t= time(NULL);
	local=localtime(&t);

	dia=local->tm_mday;
	mes=local->tm_mon+1;
	ano=local->tm_year+1900;
	segundo=local->tm_sec;
	minuto=local->tm_min;
	hora=local->tm_hour;

    FILE *file;
    file=fopen("InfoSecao.txt", "a");
    fprintf(file,"Data do Sistema: %d/%d/%d\n",dia,mes,ano);
    fprintf(file,"Horario do Sistema: %d:%d:%d\n",hora,minuto,segundo);
    fclose(file);

	printf("Data do Sistema: %d/%d/%d\n",dia,mes,ano);
    printf("Horario do Sistema: %d:%d:%d\n",hora,minuto,segundo);
}

//FUNCOES DA MATRIZ SECAO
void printMatriz(Matriz X){
    int i,j;
    printf("|------------------------------------------------------------------------------------------|\n");
    printf("|                                    PALCO TEATRO                                          |\n");
    printf("|                                    TRABALHO ED                                           |\n");
    printf("|------------------------------------------------------------------------------------------|\n\n");

    for(i=0;i<LIM;i++){
        for(j=0;j<COL;j++){
            printf("%4i", X[i][j].cdg);
                }
        printf("\n");
        }
}
void popularMatrizInicio(Secao *X){
    int i,j,aux=0;
    for (i=0;i<LIM;i++){
        for(j=0;j<COL;j++){
                if(j==0){
                    X->Secao[i][j].cdg=88;
                }
                else if(j==11){
                    X->Secao[i][j].cdg=88;
                }
                else if(j==22){
                    X->Secao[i][j].cdg=88;
                }
                else{
                X->Secao[i][j].cdg=aux;
                }
        }
    }
    printMatriz(X->Secao);
}
int verifica_sessao_cheia(Secao X){
	 int j,i,flag=1;
        for(j=1;j<22;j++){
            for(i=0;i<18;i++){
                	/*if(j==11){
						flag=0;
					*/
					if(X.Secao[i][j].cdg==0){
                    	flag=0;
                }
            }
        }
	return flag;
}
void vendaMtriz(Lista_est *L, int posicao, int tipo){
    int p,cod;
	char op;
	printf("DIGITE O CODIGO DA SESSAO\n");
	scanf("%i", &cod);
	if (Verifica_Lista_Vazia(*L))
	  printf("\n Lista está vazia - consulta elemento\n");
	 else { p = L->Prim;
		    while ((p < L->Ult) && (cod > L->Item[p].cod))
	           p++;
            if ((p==L->Ult) || (cod != L->Item[p].cod))
               printf("Elemento nao Encontrado na lista \n ");
              else{
                //return L.Item[p];

				if(verifica_sessao_cheia(L->Item[p])== 1){
					printf("SESSAO CHEIA IMPOSSIVEL A VENDA OU RESERVA DE POLTRONAS\n");
				}
				else{
    printf("ESCOLHA O LADO DO TEATRO: [E/D]:");
    scanf(" %c", &op);
    if((op == 'E' || op == 'e')){
        if(posicao <=180){
            if(posicao>0 && posicao<=18){
                int j=1;
                if(L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg==0){
                    L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg=tipo;
                     printMatriz(L->Item[p].Secao);
                }

            	else{
                    if(L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg==1){
                        printf("POSICAO JA FOI VENDIDA\n");
                    }
                    if(L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg==2){
                        printf("POSICAO RESERVADAR\n");
                    }
                }
            }
            else if(posicao>18 && posicao<=36){
                int j=2;
                if(L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg==0){
                    L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg=tipo;
                    printMatriz(L->Item[p].Secao);
                }
                else{
                    if(L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg==1){
                        printf("POSICAO JA FOI VENDIDA\n");
                    }
                    if(L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg==2){
                        printf("POSICAO RESERVADAR\n");
                    }
                }
            }
            else if(posicao>36 && posicao<=54){
                int j=3;
                if(L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg==0){
                    L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg=tipo;
                    printMatriz(L->Item[p].Secao);
                }
                else{
                    if(L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg==1){
                        printf("POSICAO JA FOI VENDIDA\n");
                    }
                    if(L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg==2){
                        printf("POSICAO RESERVADAR\n");
                    }
                }            }
            else if(posicao>54 && posicao<=72){
                int j=4;
                 if(L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg==0){
                    L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg=tipo;
                    printMatriz(L->Item[p].Secao);
                }
                else{
                    if(L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg==1){
                        printf("POSICAO JA FOI VENDIDA\n");
                    }
                    if(L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg==2){
                        printf("POSICAO RESERVADAR\n");
                    }
                }
            }
            else if(posicao>72 && posicao<=90){
                int j=5;
                 if(L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg==0){
                    L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg=tipo;
                    printMatriz(L->Item[p].Secao);
                }
                else{
                    if(L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg==1){
                        printf("POSICAO JA FOI VENDIDA\n");
                    }
                    if(L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg==2){
                        printf("POSICAO RESERVADAR\n");
                    }
                }
            }
            else if(posicao>90 && posicao<=108){
                int j=6;
                 if(L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg==0){
                    L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg=tipo;
                    printMatriz(L->Item[p].Secao);
                }
                else{
                    if(L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg==1){
                        printf("POSICAO JA FOI VENDIDA\n");
                    }
                    if(L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg==2){
                        printf("POSICAO RESERVADAR\n");
                    }
                }
            }
            else if(posicao>108 && posicao<=126){
                int j=7;
                 if(L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg==0){
                    L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg=tipo;
                    printMatriz(L->Item[p].Secao);
                }
                else{
                    if(L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg==1){
                        printf("POSICAO JA FOI VENDIDA\n");
                    }
                    if(L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg==2){
                        printf("POSICAO RESERVADAR\n");
                    }
                }
            }
            else if(posicao>126 && posicao<=144){
                int j=8;
                 if(L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg==0){
                    L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg=tipo;
                    printMatriz(L->Item[p].Secao);
                }
                else{
                    if(L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg==1){
                        printf("POSICAO JA FOI VENDIDA\n");
                    }
                    if(L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg==2){
                        printf("POSICAO RESERVADAR\n");
                    }
                }
            }
            else if(posicao>144 && posicao<=162){
                int j=9;
                 if(L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg==0){
                    L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg=tipo;
                    printMatriz(L->Item[p].Secao);
                }
                else{
                    if(L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg==1){
                        printf("POSICAO JA FOI VENDIDA\n");
                    }
                    if(L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg==2){
                        printf("POSICAO RESERVADAR\n");
                    }
                }
            }
            else if(posicao>162 && posicao<=180){
                int j=10;
                 if(L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg==0){
                    L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg=tipo;
                    printMatriz(L->Item[p].Secao);
                }
                else{
                    if(L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg==1){
                        printf("POSICAO JA FOI VENDIDA\n");
                    }
                    if(L->Item[p].Secao[posicao-(LIM*(j-1))-1][j].cdg==2){
                        printf("POSICAO RESERVADAR\n");
                    }
                }
            }
        }
        else{
            printf("NUMERO DA POLTRONA NAO EXISTE\n");
        }
    }
    else if(op == 'D' || op == 'd'){
        if(posicao <=180){
            if(posicao>0 && posicao<=18){
                int j=12,i=1;
                if(L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg==0){
                    L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg=tipo;
                    printMatriz(L->Item[p].Secao);
                }
                else{
                    if(L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg==1){
                        printf("POSICAO JA FOI VENDIDA\n");
                    }
                    if(L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg==2){
                        printf("POSICAO RESERVADAR\n");
                    }
                }
            }
            else if(posicao>18 && posicao<=36){
                int j=13,i=2;
                if(L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg==0){
                    L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg=tipo;
                    printMatriz(L->Item[p].Secao);
                }
                else{
                    if(L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg==1){
                        printf("POSICAO JA FOI VENDIDA\n");
                    }
                    if(L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg==2){
                        printf("POSICAO RESERVADAR\n");
                    }
                }
            }
            else if(posicao>36 && posicao<=54){
                int j=14,i=3;
                if(L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg==0){
                    L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg=tipo;
                    printMatriz(L->Item[p].Secao);
                }
                else{
                    if(L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg==1){
                        printf("POSICAO JA FOI VENDIDA\n");
                    }
                    if(L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg==2){
                        printf("POSICAO RESERVADAR\n");
                    }
                }
            }
            else if(posicao>54 && posicao<=72){
                int j=15,i=4;
                if(L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg==0){
                    L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg=tipo;
                    printMatriz(L->Item[p].Secao);
                }
                else{
                    if(L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg==1){
                        printf("POSICAO JA FOI VENDIDA\n");
                    }
                    if(L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg==2){
                        printf("POSICAO RESERVADAR\n");
                    }
                }
            }
            else if(posicao>72 && posicao<=90){
                int j=15,i=5;
                if(L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg==0){
                    L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg=tipo;
                    printMatriz(L->Item[p].Secao);
                }
                else{
                    if(L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg==1){
                        printf("POSICAO JA FOI VENDIDA\n");
                    }
                    if(L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg==2){
                        printf("POSICAO RESERVADAR\n");
                    }
                }
            }
            else if(posicao>90 && posicao<=108){
                int j=17,i=6;
                if(L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg==0){
                    L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg=tipo;
                    printMatriz(L->Item[p].Secao);
                }
                else{
                    if(L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg==1){
                        printf("POSICAO JA FOI VENDIDA\n");
                    }
                    if(L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg==2){
                        printf("POSICAO RESERVADAR\n");
                    }
                }
            }
            else if(posicao>108 && posicao<=126){
                int j=18,i=7;
                if(L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg==0){
                    L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg=tipo;
                    printMatriz(L->Item[p].Secao);
                }
                else{
                    if(L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg==1){
                        printf("POSICAO JA FOI VENDIDA\n");
                    }
                    if(L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg==2){
                        printf("POSICAO RESERVADAR\n");
                    }
                }
            }
            else if(posicao>126 && posicao<=144){
                int j=19,i=8;
                if(L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg==0){
                    L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg=tipo;
                    printMatriz(L->Item[p].Secao);
                }
                else{
                    if(L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg==1){
                        printf("POSICAO JA FOI VENDIDA\n");
                    }
                    if(L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg==2){
                        printf("POSICAO RESERVADAR\n");
                    }
                }
            }
            else if(posicao>144 && posicao<=162){
                int j=20,i=9;
                if(L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg==0){
                    L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg=tipo;
                    printMatriz(L->Item[p].Secao);
                }
                else{
                    if(L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg==1){
                        printf("POSICAO JA FOI VENDIDA\n");
                    }
                    if(L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg==2){
                        printf("POSICAO RESERVADAR\n");
                    }
                }
            }
            else if(posicao>162 && posicao<=180){
                int j=21,i=10;
                if(L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg==0){
                    L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg=tipo;
                    printMatriz(L->Item[p].Secao);
                }
                else{
                    if(L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg==1){
                        printf("POSICAO JA FOI VENDIDA\n");
                    }
                    if(L->Item[p].Secao[posicao-(LIM*(i-1))-1][j].cdg==2){
                        printf("POSICAO RESERVADAR\n");
                    }
                }
            }

        }
        else{
            printf("NUMERO DA POLTRONA NAO EXISTE\n");
        }
    }
    else{
        printf("DIRECAO IMVALIDA\n");
    }
}
}
}
}
void Exibir_Secao (Secao X){
   printf("\nELEMENTO DE COD = %4d \n",X.cod);
   printf(" ===================== \n");
   printf(" NOME: %s \n",X.Nome);
   printf(" DATA DA SECAO: %s \n",X.data);
   printf(" ================= \n");
}
void Ler_Secao (Secao *X){
      printf("\n Entre com o Codigo : ");
	  scanf("%d",&X->cod);
	  printf("\n Entre com o Nome da Secao: ");
	  scanf("%s",X->Nome);
	  printf("\n Entre com o Data da Secao : ");
	  scanf("%s",X->data);
    FILE *file;
    file=fopen("InfoSecao.txt", "a");
    fprintf(file,"Codigo da secao: %i \n Nome da secao: %s \n Data da secao: %s \n", X->cod, X->Nome, X->data);
}
Secao Consulta_Elemento(Lista_est L, int cod){
	int p;
	if (Verifica_Lista_Vazia(L))
	  printf("\n Lista está vazia - consulta elemento\n");
	 else { p = L.Prim;
		    while ((p < L.Ult) && (cod > L.Item[p].cod))
	           p++;
            if ((p==L.Ult) || (cod != L.Item[p].cod))
               printf("Elemento nao Encontrado na lista \n ");
              else
                return L.Item[p];
		   }
}
void ConsultarPoltrona(Secao X, int poltrona){
	  int i,j,aux=1;
	  char op;
	  printf("DIGITE O LADAO DO TEATRO[E/D]\n");
	  scanf(" %c",&op);
	  if(op=='E'||op=='e'){
        for(j=1;j<22;j++){
            for(i=0;i>=0&&i<18;i++){
                if(aux==poltrona){
                    if( X.Secao[i][j].cdg== 0){
						printf("POLTRONA------VAGA\n");
					}
					if( X.Secao[i][j].cdg == 1){
						printf("POLTRONA------VENDIDA\n");
					}
					if( X.Secao[i][j].cdg== 2){
						printf("POLTRONA------RESERVADA\n");
					}
                }
                aux++;
            }
        }
	}
	else if(op=='D'||op=='d'){
	for(j=12;j<22;j++){
            for(i=0;i<18;i++){
                if(aux==poltrona){
                    if( X.Secao[i][j].cdg== 0){
						printf("POLTRONA------VAGA\n");
					}
					if( X.Secao[i][j].cdg == 1){
						printf("POLTRONA------VENDIDA\n");
					}
					if( X.Secao[i][j].cdg== 2){
						printf("POLTRONA------RESERVADA\n");
					}
                }
                aux++;
            }
        }
	}
	else{printf("DIRECAO ERRADA\n");}
}
void info_poltronas(Secao X){
	    int j,i,contvaga=0,contresv=0, contvendida=0;
        for(j=1;j<22;j++){
            for(i=0;i<18;i++){
                if(X.Secao[i][j].cdg==0){
                    contvaga++;
                }
                if(X.Secao[i][j].cdg==1){
					contvendida++;
				}
				if(X.Secao[i][j].cdg==2){
					contresv++;
				}
            }
        }
     Exibir_Secao(X);
     printf(" ---------------------------------\n");
     printf("|NUMERO DE POLTRONAS VAGA:%i      |\n",contvaga);
	 printf("|NUMERO DE POLTRONAS VENDIDAS:%i  |\n",contvendida);
	 printf("|NUMERO DE POLTRONAS RESERVADAS:%i|\n",contresv);
	 printf(" ---------------------------------\n");

    FILE *file;
    file=fopen("InfoSecao.txt", "a");
    fprintf(file,"Quantidades de vagas: %i Quantidade vendida: %i Quantidade reservada: %i \n", contvaga, contvendida, contresv);
    fprintf(file,"============================================================================================='\n'");
}

//FUNCOES DA ESTRUTURA LISTA
int Verifica_Lista_Vazia(Lista_est L){
	   return (L.Prim==L.Ult);
   }
int Verifica_Lista_Cheia(Lista_est L){
	   return (L.Ult==MAX);
   }
void Criar_Lista_Vazia (Lista_est *L){
   L->Prim = 0;
   L->Ult = 0;
 }
void Insere_Elemento_Lista(Lista_est *L, Secao X){
  int p;
  if (Verifica_Lista_Cheia(*L)){
       printf("A Lista está Cheia \n");
  }
    else {
        p = L->Prim;
	     while ((p < L->Ult) && (X.cod > L->Item[p].cod))
	        p++;
	     if (p==L->Ult){
            L->Item[p] = X;
			 L->Ult++;
			} else if (X.cod != L-> Item[p].cod){
                    int i;
					for(i = L->Ult; i>p; i--)
					  L->Item[i] = L->Item[i-1];
					L->Item[p] = X;
					L->Ult++;
                }
	              else printf(" ELEMENTO JÁ EXISTE NA LISTA \n");
	     }
}
void Remove_Elemento_Lista(Lista_est *L, Secao *X){
    int p, i;
	if(Verifica_Lista_Vazia(*L))
	  printf("A Lista está vazia - Remocao negada \n");
	 else {
        p = L->Prim;
		    while ((p < L->Ult) && (X->cod > L->Item[p].cod))
		      p++;
		    if ((p==L->Ult) || (X->cod != L->Item[p].cod))
		       printf("Elemento nao foi encontrado na Lista - Remove \n");
		      else {
				     *X = L->Item[p];
				     for (i=p; i<L->Ult; i++)
				       L->Item[i]=L->Item[i+1];
				     L->Ult--;
				    }
	     }
 }
void Exibir_Lista(Lista_est L){
	int p;
	if (Verifica_Lista_Vazia(L))
	   printf("\n LISTA VAZIA - SEM EXIBIR \n");
	  else { p = L.Prim;
		     while (p < L.Ult)
		       {Exibir_Secao(L.Item[p]);
				printMatriz(L.Item[p].Secao);
				p++;
			    }
	        printf("\n FIM DA LISTA ******* FIM DA LISTA \n");
	       }
  }

//FUNCOES DA ESTRUTURA FILA/NOME
void Criar_Fila_Vazia(Fila_est *F)
  { F-> Inicio = 0;
    F-> Fim = 0;
    F-> Total = 0;
  }
    int Verifica_Fila_Vazia(Fila_est F)
  {
    return(F.Inicio == F.Fim);
  }
  int Verifica_Fila_Cheia(Fila_est F)
  {
    return((F.Fim+1)%MAXF == F.Fim);
  }
  void Enfileirar (Fila_est *F, pessoa X)
{  if(Verifica_Fila_Cheia(*F))
      printf("A Fila está cheia - Enfileirar\n");
     else { F->Item[F->Fim] = X;
            F->Fim = (F->Fim + 1)% MAXF;
            F->Total++;
           }
}
pessoa Passar_fila(Fila_est *F,int valor){

        return F->Item[valor];
}
void Desenfileirar(Fila_est *F, pessoa *X)
{ if(Verifica_Fila_Vazia(*F))
	  printf("A Fila esta Vazia - Desenfileirar\n ");
	 else { *X = F->Item[F->Inicio];
		    F->Inicio = (F->Inicio + 1)%MAXF;
		    F->Total--;
		   }
	 }
void Exibir_Elemento (pessoa X)
 {
   printf(" NOME: %s \n",X.nome);
   printf(" TELEFONE: %i \n",X.telefone);
   printf(" ================= \n");
}
	 void Ler_Elemento (pessoa *X)
    {
	  printf("\n Entre com o Nome : ");
	  scanf("%s",&X->nome);
	  printf("\n Entre com o Telefone : ");
	  scanf("%d",&X->telefone);
	  X->tipo=1;
	 }
//FUNCAO DE EXIBICAO DA INTERFACE MENU
void MENU(){
	 printf("\n M E N U   F U N C I O N A L\n ");
	 printf(" = = = = = = = = = = = = = =\n");
	 printf("1 - Insere Secao na Lista \n");
	 printf("2 - Remove secao da Lista \n");
	 printf("3 - Consultar Secao na Lista \n");
	 printf("4 - Exibir a Lista \n");
	 printf("5 - VENDA DE POLTROMNAS\n");
	 printf("6 - RESERVA DE POLTRONAS \n");
	 printf("7 - CONSULTAS POLTRONAS\n");
	 printf("8 - EXIBIR POLTRONAS \n");
	 printf("9 - PREENCHER  A FILA DE ESPERA \n");
	 printf("10 - DESENFILEIRAR A FILA DE ESPERA\n");
	 printf("11 - Sair do Programa \n");
	 printf(" = = = = = = = = = = = = = =\n ");
	 printf("Opcao: ");
   }
int main(){
    registarDataHorario();
    Secao X,Y;
    //popularMatrizInicio(&X);
    //vendaMtriz(&X, 1, 1);//primeiro passa a secao q deve ser alocado a matriz, depois a poltrona que quer sentar e por fim o tipo 1:VENDA 2:RESERVA
	Lista_est L;
	Criar_Lista_Vazia(&L);
	pessoa P;// CRIAR VARIAVEL TIPO PESSOA
	Fila_est F;// CRIAR VARIAVEL TIPO FILA
	Criar_Fila_Vazia(&F);// INICIALIZAR A FILA
	int op, pol;
	do{
		MENU();
		int i,fil;
		scanf("%d",&op);
		getchar();
		switch (op){
		  case 1:	printf("\n Entre com a Secao a ser Inserida \n");
		         	Ler_Secao(&X);
		        	popularMatrizInicio(&X);
				 	//vendaMtriz(&X, 1, 1);//primeiro passa a secao q deve ser alocado a matriz, depois a poltrona que quer sentar e por fim o tipo 1:VENDA 2:RESERV
				 	Insere_Elemento_Lista(&L, X);
		         	break;
		  case 2 :	printf("\n Entre com o codigo da Secao a ser Removida \n");
		         	scanf("%d",&X.cod);
		         	Remove_Elemento_Lista(&L, &X);
		         	printf("\n Elemento a ser Removido \n");
		         	Exibir_Secao(X);
		         	break;
		  case 3 :	printf("\n Entre com o codigo da Sessao a ser Consultada \n");
		         	scanf("%d",&X.cod);
		         	Y=Consulta_Elemento(L, X.cod);
	 	            Exibir_Secao(Y);
		            printMatriz(Y.Secao);
				    break;
		  case 4 :  Exibir_Lista(L);
		            break;
		  case 5 :  printf("\n ENTRE COM O NUMERO DA POLTRONA A SER VENDIDA\n");
		   			scanf("%i",&pol);
					vendaMtriz(&L, pol, 1);
					break;
		  case 6 :  printf("\n ENTRE COM O NUMERO DA POLTRONA A SER RESERVADA\n");
		   			scanf("%i",&pol);
					vendaMtriz(&L, pol, 2);
					break;
		  case 7 :  printf("\n ENTRE COM O NUMERO DA SESSAO A SER CONSULTADA\n");
		   			scanf("%i",&X.cod);
					Y = Consulta_Elemento(L, X.cod);
					printf("\n ENTRE COM O NUMERO DA POLTRONA\n");
		   			scanf("%i",&pol);
					ConsultarPoltrona(Y, pol);
					break;
		  case 8 :	printf("\n ENTRE COM O NUMERO DA SESSAO A SER CONSULTADA\n");
		   			scanf("%i",&X.cod);
					Y = Consulta_Elemento(L, X.cod);
					info_poltronas(Y);
					break;
		  case 9 :  /*printf("\n ENTRE COM O NUMERO DA SESSAO A SER CONSULTADA\n");
		   			scanf("%i",&X.cod);
                    fil=verifica_sessao_cheia(X);
                    if(fil==0){
                        printf("\n\nA SESSAO AINDA NAO ESTA CHEIA,COMPRE OU RESERVE SUA POLTRONA\n\n");
                    }else if(fil==1){*/
                    printf("\n Entre com o Elemento a ser Enfileirado \n");
                    Ler_Elemento(&P);
                    Enfileirar(&F, P);
                    //}
		  			break;
          case 10 :  printf("\n Elemento a ser Desempilhado: \n");
                     Exibir_Elemento(P);
		  			break;
          case 11 :  printf(" FIM...OBRIGADO POR USAR NOSSO SOFTWARE \n");
		  			break;
    	  default : printf("\n Opcao nao existe escolha outra correta \n");
		         	break;
		}
	}while (op !=11);
	return 0;
}
