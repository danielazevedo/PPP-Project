#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED
/*Daniel Azevedo Nº2014200607
Nuno Afonso Santos Nº 2014226541*/
typedef struct
{
    int dia;
    int mes;
    int ano;
}Data;


typedef struct
{
    int hora;
    int minuto;
}Tempo;

typedef struct
{
    char *nome;
    int b_i;
    Data d;
    Tempo t;
    char *prioridade;
}Dados;

typedef struct no *Lista;
typedef struct no
{
    Dados info;
    Lista next;
}Lista_no;

Lista lcria(void);
void pedir_nome(char* name);
void linsere (Lista l, Dados doente);
void linsere_first  (Lista l, Dados doente);
void pedir_dados(Lista triagem);
char verifica_nome(Dados doente);
void limprime (Lista l);
void rec_data(Dados *doente);
int verifica_bi(Lista lista,int n, char p[]);
void elimina_lista (Lista lista,int bi);
void procura_lista (Lista lista, int bi, Lista *ant, Lista *actual);
void cancelar_marcacao(Lista lista, Lista glob);
void cancelar_consulta(Lista l1,Lista l2,Lista l3, Lista gl);
int doente_next(Lista lista);
void Listar_consulta(Lista g,Lista y,Lista r, Lista gl);
void insere_final(Lista l,Dados doente);
void insere_ficheiro_lista(Lista lista, char fname[]);
void insere_lista_ficheiro(Lista list, char fich_name[]);
void paciente_next(Lista r, Lista g, Lista y, Lista global);
void atribuir_prioridade(Lista triagem,Lista verde, Lista amarela,Lista vermelha, Lista global);
void insere_global_listas(Lista red,Lista yellow,Lista green, char fname[]);
int file_exists(char *filename);
void create_file(char *filename);
void create_file_contadores();


#endif // DATA_H_INCLUDED
