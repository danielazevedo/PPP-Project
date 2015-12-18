#include "auxiliar_projeto.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

/*Daniel Azevedo Nº2014200607
Nuno Afonso Santos Nº 2014226541*/
void pedir_nome(char* name)
{
    char * ptr=malloc(sizeof(char));
    *name="";
    printf("Insira o nome do doente:\n\t");
    fgets(name,75,stdin);
    name[strlen(name)-1]='\0';
    //ptr[0] == '\0';
    ptr=name;
    if (*ptr==' ' || *ptr =='\0'){
        printf("O nome que introduziu nao e valido.\n");
        pedir_nome(name);
    }
    while(*ptr!='\0'){
        if(isalpha(*ptr) || (*ptr== ' ' && *(ptr+1)!= ' ' ))
            ptr++;
        else{
            printf("O nome que introduziu nao e valido.\n");
            pedir_nome(name);
        }
    }
    if (*(ptr-1)==' '){
       printf("O nome que introduziu nao e valido.\n");
       pedir_nome(name);
    }
}

int pedir_bi(Lista triagem)
{
    char str[100];
    int num;
    printf("Indique o seu bi\n\t");
    fgets(str,100,stdin);
    num = atoi(str);
    if(9999999<num && num<100000000 && verifica_bi(triagem,num,str)==0)
        return num;
    else if(verifica_bi(triagem,num,str)==1){
        printf("O numero introduzido ja se encontra no sistema\n");
        pedir_bi(triagem);
    }
    else{
        printf("O numero introduzido e invalido\n");
        pedir_bi(triagem);
    }
}

int verifica_bi(Lista lista,int n, char p[])
{
    Lista ptr=lista;
    int i;
    while(ptr->next!=NULL){
        ptr=ptr->next;
        if (ptr->info.b_i==n)
            return 1;
    }
    for(i=0;i<strlen(p);i++){
        if(isalpha(p[i]))
            return 2;
    }
    return 0;
}


void rec_data(Dados *doente)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    doente->d.dia=tm.tm_mday;
    doente->d.mes=tm.tm_mon +1;
    doente->d.ano=tm.tm_year+1900;
    doente->t.hora=tm.tm_hour;
    doente->t.minuto=tm.tm_min;
}
