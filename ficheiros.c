#include "auxiliar_projeto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Daniel Azevedo Nº2014200607
Nuno Afonso Santos Nº 2014226541*/
void insere_lista_ficheiro(Lista list, char fich_name[]){
        FILE *f;
        f=fopen(fich_name,"w");
        Lista aux=list->next;
        while(aux!=NULL){
                fprintf(f,"%s\n",aux->info.nome);
                fprintf(f,"%d\n",aux->info.b_i);
                fprintf(f,"%d:%d ",aux->info.t.hora,aux->info.t.minuto);
                fprintf(f,"%d/%d/%d\n%s\n",aux->info.d.dia,aux->info.d.mes,aux->info.d.ano,aux->info.prioridade);
                aux=aux->next;
        }
        fclose(f);
}

void insere_ficheiro_lista(Lista lista, char fname[])
{
    FILE *f;
    f=fopen(fname,"r");
    int p=0;
    while(fgetc(f)!=EOF){
        fseek(f,p,SEEK_SET);
        Dados *doente=malloc(sizeof(Dados));
        doente->nome=malloc(75*sizeof(char));
        doente->prioridade=malloc(75*sizeof(char));
        fgets(doente->nome,75,f);
        doente->nome[strlen(doente->nome)-1]='\0';
        fscanf(f,"%d",&doente->b_i);
        fscanf(f,"%d:%d %d/%d/%d\n%s\n",&doente->t.hora,&doente->t.minuto,&doente->d.dia,&doente->d.mes,&doente->d.ano,doente->prioridade);
        linsere(lista,*doente);
        p=ftell(f);
    }
    fclose(f);
}

int file_exists(char *filename)
{
    FILE *f;
    if ((f = fopen(filename, "r")))
    {
        fclose(f);
        return 1;
    }
    return 0;
}

void create_file(char *filename){

    FILE *f= fopen(filename,"w");
    fclose(f);

}

void create_file_contadores(){

    FILE *f= fopen("contadores.txt","w");
    fprintf(f,"0 0");
    fclose(f);

}


