#include "auxiliar_projeto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/*Daniel Azevedo Nº2014200607
Nuno Afonso Santos Nº 2014226541*/

void pedir_dados(Lista triagem)
{
    int n;
    char num[10];
    printf("\nIntroduza 1 para prosseguir e 2 para retroceder:\n\t");
    fgets(num, 10, stdin);
    if (isspace(num[1]))
        n=atoi(num);
    if(n==1){
        Dados *doente=malloc(sizeof(Dados));
        doente->nome=malloc(75*sizeof(char));
        doente->prioridade=malloc(10*sizeof(char));
        pedir_nome(doente->nome);
        doente->b_i=pedir_bi(triagem);
        rec_data(doente);
        strcpy(doente->prioridade,"nenhuma");
        linsere(triagem, *doente);
        insere_lista_ficheiro(triagem,"lista_triagem.txt");
        }
    else if(n!=2){
        printf("\nO numero inserido nao corresponde a uma opcao\n");
        pedir_dados(triagem);}
}


void cancelar_marcacao(Lista lista, Lista glob)
{
    int bi,i;
    char str[100];
    if(lista->next==NULL)
        printf("A lista nao possue doentes.\n");
    else
    {printf("Indique o seu bi:\n\t");
    fgets(str,75,stdin);
    bi = atoi(str);
    for(i=0;i<strlen(str);i++){
        if (isalpha(str[i])){
            printf("\nNumero invalido\n");
            bi=3;
            break;}
    }
    if (bi!=3){
    if (strcmp(lista->info.prioridade,"nenhuma")){
        elimina_lista (lista,bi);
        insere_lista_ficheiro(lista,"lista_triagem.txt");}
    else{
        elimina_lista (glob,bi);
        elimina_lista (lista,bi);
        insere_lista_ficheiro(lista,"lista_global.txt");}

    }
    }
}
void cancelar_consulta(Lista l1,Lista l2,Lista l3, Lista gl)
{
    int num,i;
    char str[100];
    do{
        printf("\n1.Fila de espera das pulseiras verdes.\n2.Fila de espera das pulseiras amarelas.\n3.Fila de espera das pulseiras vermelhas.\n4. Retroceder.\n");
        fgets(str,75,stdin);
        num = atoi(str);
        for(i=0;i<strlen(str);i++){
            if (isalpha(str[i])){
                num=10;
                break;}
        }
        switch (num){
            case 1: cancelar_marcacao(l1,gl); break;
            case 2: cancelar_marcacao(l2,gl); break;
            case 3: cancelar_marcacao(l3,gl); break;
            case 4: break;
            default: printf("\nA opcao nao e valida, tente outra vez\n");
        }
    }
    while(num<1 || num>4 );
}

int doente_next(Lista lista)
{
    Lista aux=lista->next;
    printf("\nNome: %s\n", aux->info.nome);
    printf("B.I.: %d\n", aux->info.b_i);
    return aux->info.b_i;
}

void atribuir_prioridade(Lista triagem,Lista verde, Lista amarela,Lista vermelha, Lista global)
{
    int cor,i;
    char str[100];
    Lista aux=triagem->next;
    if (aux==NULL){
            printf("Nao existem doentes na fila de espera para triagem\n");
        }
    else{
        do{
            printf("\nIndique o numero correspondente a prioridade que deseja atribuir ao doente com o bi %d:\n1.Pulseira verde\n2.Pulseira amarela\n3.Pulseira vermelha\n4.Retroceder\n",aux->info.b_i);
            fgets(str,75,stdin);
            cor = atoi(str);
            for(i=0;i<strlen(str);i++)
        {
            if (isalpha(str[i])){
                cor=10;
                break;}
        }

            switch (cor){
                case 1: {
                    strcpy(aux->info.prioridade,"Verde");
                    linsere(verde,aux->info);
                    break;
                    }
                case 2:{
                    strcpy(aux->info.prioridade,"Amarelo");
                    linsere(amarela,aux->info);
                    break;
                    }
                case 3:{
                    strcpy(aux->info.prioridade,"Vermelho");
                    linsere(vermelha,aux->info);
                    break;
                    }
                case 4: break;
                default: printf("\nA opcao nao e valida, tente outra vez\n");
                }
        }
        while(cor<1 || cor>4);
        if(cor!=4)
        {linsere_first(global,aux->info);
        insere_lista_ficheiro(global,"lista_global.txt");
        elimina_lista(triagem, aux->info.b_i);
        insere_lista_ficheiro(triagem,"lista_triagem.txt");}

    }
}


void paciente_next(Lista r, Lista g, Lista y, Lista global)
{
    int n, vec[2];
    FILE *f=fopen("contadores.txt","r+");
    fscanf(f, "%d %d\n", &vec[0], &vec[1]);
    if((r->next==NULL && y->next==NULL && g->next!=NULL) || vec[1]==5){
        printf("verde\n");
        n=doente_next(g);
        elimina_lista(g, n);
        elimina_lista(global, n);
        vec[0]=0;
        vec[1]=0;
        }
    else if((r->next==NULL || vec[0]==3) && y->next!=NULL){
        printf("amarelo\n");
        n=doente_next(y);
        elimina_lista(y, n);
        elimina_lista(global, n);
        if(vec[0]==3)
            vec[0]=0;
        vec[1]++;
    }
    else if(r->next!=NULL){
        printf("vermelho\n");
        n=doente_next(r);
        elimina_lista(r, n);
        elimina_lista(global, n);
        vec[0]++;
    }
    else
        printf("\nNao existem doentes\n");
    rewind(f);
    fprintf(f,"%d %d",vec[0],vec[1]);
    insere_lista_ficheiro(global, "lista_global.txt");
    fclose(f);
}

void Listar(Lista t,Lista g,Lista y,Lista r,Lista gl)
{   int x,i;
    char str[100];

    do{
    printf("Qual das seguintes filas de espera pretende ver?\n1.Triagem\n2.Consulta\n3.Retroceder\n");
    fgets(str,75,stdin);
    x = atoi(str);
    for(i=0;i<strlen(str);i++)
    {
        if (isalpha(str[i])){
            x=10;
            break;}
    }
    switch (x){
        case 1: limprime (t); break;
        case 2: Listar_consulta(g,y,r,gl); break;
        case 3: break;
        default:printf("\nOpcao invalida, tente outra vez\n\n");break;
            }
    }
    while(1>x || x>3);
}

void Listar_consulta(Lista g,Lista y,Lista r, Lista gl)
{   int x,i;
    char str[100];

     do{

     printf("1.Fila de espera das pulseiras verdes.\n2.Fila de espera das pulseiras amarelas.\n3.Fila de espera das pulseiras vermelhas.\n4.Fila de espera global\n5.Retroceder.\n");
    fgets(str,75,stdin);
     x= atoi(str);

    for(i=0;i<strlen(str);i++)
    {
        if (isalpha(str[i])){
            x=10;
            break;}
    }
    switch (x){
        case 1: limprime(g); break;
        case 2: limprime(y); break;
        case 3: limprime(r); break;
        case 4: limprime(gl); break;
        case 5: break;
        default:printf("\nOpcao invalida,tente outra vez\n\n");break;

    }
    }
    while(1>x || x>5);
}
