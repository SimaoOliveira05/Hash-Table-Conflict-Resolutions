#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct open {
    int indice;
    int valor;
    int emUso;
} OPEN;


int verifica(int valor, int size , OPEN table[]){

    for (int i = 0 ; i < size ; i++){
        if (table[i].emUso == 1 && table[i].valor == valor)
            return i;
    }
    return -1;
}

int findDindex(OPEN table[], int start, int end, int size) {
    int i = start;
    do {
        if (table[i].emUso == -1){
            return i;
        }
        i = (i + 1) % size;
    } while (i != end);
    return -1;
}

int Iopen(int valor, int P, OPEN table[]) {
    int indice = valor % P;
    int originalIndice = indice;
    int indValor = verifica(valor , P, table);
    
    if (indValor >= 0){
        int dIndex = findDindex(table, originalIndice, indValor, P);
        if (dIndex >= 0){
            table[dIndex].valor = valor;
            table[dIndex].emUso = 1;
            table[dIndex].indice = dIndex;
            table[indValor].emUso = -1;
        }
        printf("%d EXISTS\n",valor);
        return 1;
    }

    while (table[indice].emUso == 1) {
        indice = (indice + 1) % P;  

        if (indice == originalIndice) {
            printf("GIVING UP!\n");
            return 0;
        }
    }
    table[indice].valor = valor;
    table[indice].indice = indice;
    table[indice].emUso = 1;
    printf("%d -> %d\nOK\n",indice,valor);
    return 1;
}

void Copen(int valor, OPEN table[], int size){

    int indice = valor % size;
    int originalIndice = indice;
    int dIndex = -1;

    if (table[indice].valor == valor && table[indice].emUso == 1){
        
        printf("%d\n",table[indice].indice);
        return;
    }
    if (table[indice].emUso == -1)
        dIndex = indice;
    
    indice = (indice + 1) % size;
    
    while (indice != originalIndice){

        if ((table[indice].emUso == 1) && (table[indice].valor == valor)){
            if (dIndex != -1){
                table[dIndex].valor = valor;
                table[dIndex].emUso = 1;
                table[indice].emUso = -1;
                indice = dIndex;
            }
            printf("%d\n",indice);
            return;
        }
        if (table[indice].emUso == -1 && dIndex == -1)
            dIndex = indice;
        indice = (indice + 1) % size;
    }
    printf("NO\n");
}



int Dopen(int valor, int size, OPEN table[]){

    int indice = valor % size;
    int originalIndice = indice;

    if (table[indice].valor == valor && table[indice].emUso){
        
        table[indice].emUso = -1;
        printf("OK\n");
        return 1;
    }
    indice = (indice + 1) % size;

    while (indice != originalIndice){

        if ((table[indice].emUso && (table[indice].valor == valor))){
            table[indice].emUso = -1;
            printf("OK\n");
            return 1;
        }
        indice = (indice + 1) % size;
    }
    printf("NO\n");
    return 0;
}

void Popen(OPEN table[] , int size){

    for (int i = 0 ; i < size ; i++){
        if (table[i].emUso == 1){
            printf("%d\t%d\n",table[i].indice,table[i].valor);
        }
        else if (table[i].emUso == -1){
            printf("%d\tD\n",table[i].indice);
        }
    }
}

void initializeOpenTable (OPEN* table, int size) {
    for (int i = 0; i < size; i++) {
        table[i].emUso = 0;
    }
}


typedef struct Node {
    int data;
    struct Node* next;
} * Node;

typedef struct Link {
    int indice;
    Node lista;
} LINK;


void appToList(Node* head, int data) {
    Node newNode = (Node)malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->next = *head;

    *head = newNode;
}

int existsInList(Node head, int data) {
    Node current = head;

    while (current != NULL) {
        if (current->data == data) {
            return 1;
        }
        current = current->next;
    }

    return 0;
}

int deleteFromList(Node* head, int data) {
    if (*head == NULL) {
        return 0;
    }

    if ((*head)->data == data) {
        Node temp = *head;
        *head = (*head)->next;
        free(temp);
        return 1;
    }

    Node current = *head;
    while (current->next != NULL && current->next->data != data) {
        current = current->next;
    }

    if (current->next == NULL) {
        return 0;
    }

    Node temp = current->next;
    current->next = current->next->next;
    free(temp);
    return 1;
}

int verifyElement(Node head, int valor){
    while (head != NULL){
        if (head -> data == valor) return 1;
        head = head->next;
    }
    return 0;
}


void printList (Node head){

    while (head != NULL){
        int value = head->data;
        head = head->next;
        if (head != NULL)
            printf("%d ",value);
        else 
            printf("%d",value);

    }
    printf("\n");
}


void initializeLinkTable(LINK* table, int size) {
    for (int i = 0; i < size; i++) {
        table[i].lista = NULL;
    }
}

void Ilink (int valor , int P , LINK table[]){

    int indice = valor % P;
    if (existsInList(table[indice].lista,valor))
        printf("%d EXISTS\n",valor);
    else 
        {appToList(&table[indice].lista,valor);
        printf("%d -> %d\nOK\n", indice , valor);
    }
}

void Dlink (int valor , int P , LINK table[]){

    int indice = valor % P;
    if (deleteFromList (&table[indice].lista,valor))
        printf("OK\n");
    else 
        printf("NO\n");
}

void Clink (int valor , int P , LINK table[]){

    int indice = valor % P;
    if (verifyElement(table[indice].lista,valor))
        printf("%d\n",indice);
    else 
        printf("NO\n");
}

void Plink (LINK table[],int size){

    for (int i = 0 ; i < size ; i++ ){
        if (table[i].lista == NULL);
        else {
            printf("%d ",i);
            printList(table[i].lista);
        }
    }
}


typedef struct CUCKOO{

    int indice;
    int valor;
    int emUso;
}CUCKOO;


void initializeCuckooTable(CUCKOO* table, int size) {
    for (int i = 0; i < size; i++) {
        table[i].emUso = 0;
    }
}


int gave_up = 0;

void Icuckoo(CUCKOO t1[] , CUCKOO t2[] , int valor , int P, int ftype , int limite){
    if (limite > P) {
        printf("GIVING UP!\n");
        gave_up = 1;
        return;
    }

    int indice;
    if (!ftype) {
        indice = valor % P; 
        if (!t1[indice].emUso){
            t1[indice].indice = indice;
            t1[indice].valor = valor;
            t1[indice].emUso = 1;
            printf("%d %d -> %d\n",ftype,indice,valor);
        }
        else if (t1[indice].valor == valor) {
            printf("%d EXISTS\n",valor);
        }
        else{
            int pastValue = t1[indice].valor;
            t1[indice].valor = valor;
            printf("%d %d -> %d\n",ftype,indice,valor);
            Icuckoo(t1 ,t2,pastValue,P,ftype+1,limite+1);
        }
    }
    else {
        indice = (valor/P) % P;
        if (!t2[indice].emUso){
            t2[indice].indice = indice;
            t2[indice].valor = valor;
            t2[indice].emUso = 1;
            printf("%d %d -> %d\n",ftype,indice,valor);
        }
        else if (t2[indice].valor == valor) {
            printf("%d EXISTS\n",valor);
        }
        else{
            int pastValue = t2[indice].valor;
            t2[indice].valor = valor;
            printf("%d %d -> %d\n",ftype,indice,valor);
            Icuckoo(t1 ,t2,pastValue,P,ftype-1,limite+1);           
        }
    }
}

void Ccuckoo(CUCKOO t1[] , CUCKOO t2[], int valor , int P){

    int indice1 = valor % P;
    int indice2 = (valor/P) % P;
    if (t1[indice1].valor == valor && t1[indice1].emUso){
        printf("0\t%d\n",indice1);
    }
    else if (t2[indice2].valor == valor && t2[indice2].emUso){
        printf("1\t%d",indice2);
    }
    else (printf("NO\n"));
}
    
void Dcuckoo(CUCKOO t1[],CUCKOO t2[], int valor, int P){

    int indice1 = valor % P;
    int indice2 = (valor/P) % P;
    
    if (t1[indice1].valor == valor && t1[indice1].emUso){
        t1[indice1].emUso = 0;
        printf("OK\n");
        return;
    }
    else if (t2[indice2].valor == valor && t2[indice2].emUso){
        t2[indice2].emUso = 0;
        printf("OK\n");
    }
    else (printf("NO\n"));
}

void Pcuckoo(CUCKOO t1[], CUCKOO t2[], int P) {
    for (int i = 0; i < P; i++) {
        if (t1[i].emUso) {
            printf("0\t%d\t%d\n", i, t1[i].valor);
        }
    }

    for (int i = 0; i < P; i++) {
        if (t2[i].emUso) {
            printf("1\t%d\t%d\n", i, t2[i].valor);
        }
    }
}

int control = 1;

int main (){
    int slots;
    assert(scanf("%d\n",&slots)==1);
    char *tipo = calloc (7,sizeof (char));
    char linha[10];
    assert(fgets(tipo,7,stdin) != NULL);

    tipo[strcspn(tipo, "\n")] = 0;
    
    if (!strcmp(tipo,"OPEN")){
        
        free(tipo);

        OPEN table[slots];
        
        initializeOpenTable (table,slots);
        while (fgets(linha, sizeof(linha), stdin) && control){
            int valor;
            char type;
            sscanf(linha,"%c %d",&type,&valor);
            
            if (type == 'P'){
                Popen (table,slots);
            }
            else {
                if (type == 'I'){
                    control = Iopen(valor,slots,table);
                }
                if (type == 'C'){
                    Copen(valor,table,slots);
                }
                if (type == 'D'){
                    Dopen(valor , slots , table);
                }
            }   
        }
    }
    else if (!strcmp(tipo,"LINK")){

        free(tipo);

        LINK table[slots];

        initializeLinkTable (table,slots);

        while (fgets(linha, sizeof(linha), stdin)){
            int valor;
            char type;
            sscanf(linha,"%c %d",&type,&valor);
            
            if (type == 'P'){
                Plink (table,slots);
            }
            else{
                if (type == 'I')
                    Ilink (valor,slots,table);
                else if (type == 'D')
                    Dlink (valor,slots,table);
                else if (type == 'C')
                    Clink (valor,slots,table);
            }   

        }
    }
    else if (!strcmp(tipo,"CUCKOO")){

        free(tipo);

        CUCKOO t1[slots],t2[slots];

        initializeCuckooTable(t1,slots);
        initializeCuckooTable(t2,slots);

        while (fgets(linha, sizeof(linha), stdin)){
            int valor;
            char type;
            sscanf(linha,"%c %d",&type,&valor);

            if (type == 'P'){
                Pcuckoo (t1,t2,slots);
            }
            else{
                if (type == 'I'){
                    gave_up = 0;
                    Icuckoo(t1,t2,valor,slots,0,0);
                    if (!gave_up) printf("OK\n");
                }
                if (type == 'C'){
                    Ccuckoo(t1,t2,valor,slots);
                }
                if (type == 'D'){
                    Dcuckoo(t1,t2,valor,slots);
                }

            }
        }
    }
    return 0;
}