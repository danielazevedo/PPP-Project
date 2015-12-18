#include "auxiliar_projeto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Daniel Azevedo Nº2014200607
Nuno Afonso Santos Nº 2014226541*/
Lista lcria(void)
{
    Lista l;
    l= (Lista) malloc (sizeof (Lista_no));
    if (l != NULL){
        l->info.nome = "";
        l->info.prioridade = "";
        l->info.b_i = 0;
        l->info.d.dia=0;
        l->info.d.mes=0;
        l->info.d.ano=0;
        l->info.t.hora=0;
        l->info.t.minuto=0;
        l->next = NULL;
    }
    return l;
 }

void linsere (Lista l, Dados doente)
{
    Lista no;
    no = (Lista) malloc (sizeof (Lista_no));

    if (no != NULL){

        while(l->next!=NULL)
            l=l->next;}

    no->info = doente;
    no->next = l->next;
    l->next = no;


}

void linsere_first (Lista l, Dados doente)
{
    Lista no;
    no = (Lista) malloc (sizeof (Lista_no));
    if (no != NULL) {
        no->info = doente;
        no->next = l->next;
        l->next = no;
        l=NULL;
    }
}

void limprime (Lista l)
{
    Lista ll = l->next;
    if (ll==NULL)
        printf("A lista pedida nao possui nenhum doente\n");
    else{
        while (ll){
            printf("\nNome: %s\n", ll->info.nome);
            printf("B.I.: %d\n", ll->info.b_i);
            printf("Data e hora de entrada: %.2d/%.2d/%.2d  %.2d:%.2d", ll->info.d.dia, ll->info.d.mes, ll->info.d.ano, ll->info.t.hora, ll->info.t.minuto);
            printf("\nPrioridade: %s",ll->info.prioridade);
            printf("\n");
            ll=ll->next;
        }
    }
}

void insere_global_listas(Lista red,Lista yellow,Lista green, char fname[])
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
        fscanf(f,"%d:%d %d/%d/%d\n%s",&doente->t.hora,&doente->t.minuto,&doente->d.dia,&doente->d.mes,&doente->d.ano,doente->prioridade);
        if(strcmp(doente->prioridade,"Verde")==0)
            linsere_first(green,*doente);
        else if(strcmp(doente->prioridade,"Amarelo")==0)
            linsere_first(yellow,*doente);
        else if(strcmp(doente->prioridade,"Vermelho")==0)
            linsere_first(red,*doente);
        p=ftell(f);
    }
    fclose(f);
}

void procura_lista (Lista lista, int bi, Lista *ant, Lista *atual)
{
	*ant = lista; *atual = lista->next;
	while ((*atual) != NULL && (*atual)->info.b_i != bi){
		*ant = *atual;
		*atual = (*atual)->next;
	}
	if((*atual) == NULL)
        printf("Bi nao encontado no sistema.\n");
}

void elimina_lista (Lista lista,int bi)
{
	Lista ant1;
	Lista actual1;
	procura_lista (lista, bi, &ant1, &actual1);
	if (actual1 != NULL) {
		ant1->next = actual1->next;
		free (actual1);
	}
}

void elimina_first(Lista lista)
{
    Lista ant=lista;
    Lista actual=lista->next;
    if (actual != NULL) {
        ant->next = actual->next;
        free (actual);
    }
}


