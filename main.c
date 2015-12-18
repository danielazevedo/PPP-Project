#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auxiliar_projeto.h"
#include <ctype.h>
/*Daniel Azevedo Nº2014200607
Nuno Afonso Santos Nº 2014226541*/

void painel()
{

    printf("\nEscolha uma das seguintes opcoes:\n");
    printf("1. Admitir um doente para triagem;\n");
    printf("2. Cancelar um doente em espera para triagem;\n");
    printf("3. Cancelar um doente em espera para consulta;\n");
    printf("4. Atribuir uma prioridade;\n");
    printf("5. Listar doentes;\n");
    printf("6. Ver proximo doente;\n");
    printf("7. Limpar o ecra;\n");
    printf("8. Quit menu;\n");


}

void opcoes(int n, Lista triagem, Lista green, Lista yellow, Lista red, Lista gl)
{
    switch (n){
        case 1: pedir_dados(triagem); break;
        case 2: cancelar_marcacao(triagem,gl); break;
        case 3: cancelar_consulta(green,yellow,red,gl); break;
        case 4: atribuir_prioridade(triagem,green,yellow,red,gl); break;
        case 5: Listar(triagem,green,yellow,red,gl); break;
        case 6: paciente_next(red,green,yellow,gl); break;
        case 7: system("clear");break;
        }
}




int main()
{
    int n;
    char num[100];
    Lista triagem, green, red, yellow,global;
    triagem=lcria();
    green=lcria();
    red=lcria();
    yellow=lcria();
    global=lcria();
    if(file_exists("lista_triagem.txt")==0 ){
        printf("O ficheiro lista_triagem.txt nao existe\n");
        create_file("lista_triagem.txt");
        printf("Ficheiro criado com sucesso\n");}
    if(file_exists("lista_global.txt")==0 ){
        printf("O ficheiro lista_global.txt nao existe\n");
        create_file("lista_global.txt");
        printf("Ficheiro criado com sucesso\n");}
    if(file_exists("contadores.txt")==0 ){
        printf("O ficheiro contadores.txt nao existe\n");
        create_file_contadores();
        printf("Ficheiro criado com sucesso\n");}
    do
    {
        triagem->next=NULL;
        global->next=NULL;
        yellow->next=NULL;
        green->next=NULL;
        red->next=NULL;
        insere_ficheiro_lista(triagem,"lista_triagem.txt");
        insere_ficheiro_lista(global,"lista_global.txt");
        insere_global_listas(red,yellow,green,"lista_global.txt");
        painel();
        fgets(num,100,stdin);
        if(num[0]=='\n' || atoi(num)<1 || atoi(num)>8)
            printf("\n A opçao e invalida\n");
        else{
            if(isspace(num[1])){
                n=atoi(num);
                opcoes(n,triagem,green,yellow,red,global);}
            else
                printf("\nA opcao e invalida\n");}
        }
    while(n!=8);

    return 0;
}
