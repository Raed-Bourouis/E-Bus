#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
int global_counter=1;
FILE *fvoy; FILE *fbus; FILE *fres;
void endl(){
    printf("\n*********************************************************************************\n");
}

typedef struct voyageur{
    int cin; //num carte d'identité
    char name[100];
}voy;

typedef struct bus{
    int id; //identifiant
    int cap; //capacité de bus
    int tarif;
    int dispo; //Nombre disponible des bus de ce modele
}bus;

typedef struct reservation{
    struct bus b; //bus reservé
    struct voyageur v; //locateur
    char deb[10];//date debut,
    int dur, prix;  //durée de reservation
    int id;
}res;

typedef struct node1
{
  struct voyageur client;
  struct node1 *next;
}voys;

typedef struct node2
{
  struct bus vehicle ;
  struct node2 *next;
}buss;

typedef struct node3
{
  struct reservation book;
  struct node3 *next;
}ress;

voys *accounts=NULL;
buss *fleet=NULL;
ress *orders=NULL;

bool valid_user(int x){
    bool u=false;
    voys *aux=accounts;
    while(aux!=NULL){
        if(aux->client.cin==x){u=true;break;}
        aux=aux->next;
    }
    return u;
}

int new_account(){
    voy tempo;
    voys * last;
    last=(voys*)malloc(sizeof(voys));
    printf("Enter Your Name: "); getchar();
    fgets(tempo.name, 100, stdin);
    printf("Saisir Vote N. cin: "); scanf("%i",&tempo.cin);
    if(valid_user(tempo.cin)){printf("Cet utilisateur existe en avance!\n"); return 0;}
    last->client=tempo;
    last->next=NULL;
    if(accounts==NULL){
        last->next=accounts;
        accounts=last;
    }
    else{
        voys *aux=accounts;
        while(aux->next!=NULL){
            aux=aux->next;
        }
        aux->next=last;
    }
    return 0;
}


int make_reservation(){
    res tempo;
    ress * last;
    last=(ress*)malloc(sizeof(ress));
    printf("Veuillez taper vote N. cin: "); scanf("%i",&tempo.v.cin);
    if(!valid_user(tempo.v.cin)){printf("Cet Utilisateur n'existe pas!\n"); return 0;}
    printf("Veuillez choisir un bus: "); scanf("%i",&tempo.b.id);
    printf("Veuillez taper la date debut et la duree (en jours) de votre reservation: "); scanf("%s %i",&tempo.deb,&tempo.dur);
    buss *btemp = fleet;
    while (btemp != NULL) {
        if (btemp->vehicle.id == tempo.b.id) {
            tempo.b.tarif = btemp->vehicle.tarif;
            break;
        }
        btemp = btemp->next;
    }
    tempo.prix=(tempo.b.tarif)*tempo.dur;
    printf("%d", tempo.prix);
    tempo.id=global_counter;
    global_counter++;
    last->book=tempo;
    last->next=NULL;
    if(orders==NULL){
        last->next=orders;
        orders=last;
    }
    else{
        ress *aux=orders;
        while(aux->next!=NULL){
            aux=aux->next;
        }
        aux->next=last;
    }
    return 0;
}

void see_fleet(){
    if(fleet==NULL) printf("Aucun bus au moment!");
    else{
        buss *aux=fleet;
        while(aux!=NULL){
            if(aux->vehicle.dispo!=0) printf("Identifiant: %i      || Capacité: %i      || Disponibilite: %i      || Tarif/jour: %i DT\n", aux->vehicle.id, aux->vehicle.cap,aux->vehicle.dispo, aux->vehicle.tarif);
            aux=aux->next;
        }
    }
}

bool exist=false;

int see_reservations() {
    printf("Saisir le Numero d'utilisateur: "); int c; scanf("%i",&c);
    if(!valid_user(c)){printf("Aucun utilisateur de cet identifiant\n"); return 0;}
    ress *aux=orders;
    exist=false;
    while(aux!=NULL){
        if(aux->book.v.cin==c) {exist= true; printf("Identifiant: %i      ||Bus: %i      || Date debut: %s      || Duree: %i jours       || Coût: %i DT\n",aux->book.id, aux->book.b.id, aux->book.deb, aux->book.dur, aux->book.prix);}
        aux=aux->next;
    }
    if(!exist) printf("Aucune reservation sous ce nom!\n");
    return 0;
}

int modify_reservation(){
  int mod_id;
  printf("Choisir la reservation a modifier: "); scanf("%i",&mod_id);
  ress *aux=orders;
  while(aux!=NULL){
    if(aux->book.id==mod_id){
            printf("Veuillez choisir un bus: "); scanf("%i",&aux->book.b.id);
            printf("Veuillez taper la date debut et la duree (en jours) de votre reservation: "); scanf("%s %i",&aux->book.deb,&aux->book.dur);
            aux->book.prix=(aux->book.b.tarif)*aux->book.dur;
            return 0;
    }
    aux=aux->next;
  }  
  printf("Aucune reservation de cet identifiant!");
  return 0 ;
}

void write_voys() {
    fvoy = fopen("voyageurs.bin", "wb");
    if (fvoy == NULL) {
        printf("Unable to open file for writing.\n");
        return;
    }

    voys *current = accounts;
    while (current != NULL) {
        fwrite(&current->client, sizeof(voy), 1, fvoy);
        current = current->next;
    }

    fclose(fvoy);
}

void read_voys() {
    fvoy = fopen("voyageurs.bin", "rb");
    if (fvoy == NULL) {
        printf("Unable to open file for reading.\n");
        return;
    }

    
    while (accounts != NULL) {
        voys *temp = accounts;
        accounts = accounts->next;
        free(temp);
    }

    voys *last = NULL;

    while(1) {
        voys *new_node = (voys *)malloc(sizeof(voys));
        if (fread(&new_node->client, sizeof(voy), 1, fvoy) != 1) {
            free(new_node);
            break;
        }
        new_node->next = NULL;
        if (accounts == NULL) {
            accounts = new_node;
            last = accounts;
        }
        else{
            last->next = new_node;
            last = new_node;
        }
    }

    fclose(fvoy);
}

void read_orders() {
    fres = fopen("orders.bin", "rb");
    if (fres == NULL) {
        printf("Unable to open file for reading.\n");
        return;
    }
    while (orders != NULL) {
        ress *temp = orders;
        orders = orders->next;
        free(temp);
    }
    ress *last = NULL;
    while (1) {
        ress *new_node = (ress *)malloc(sizeof(ress));
        if (fread(&new_node->book, sizeof(res), 1, fres) != 1) {
            free(new_node);
            break;
        }
        new_node->next = NULL;
        if (orders == NULL){
            orders = new_node;
            last = orders;
        }
        else{
            last->next = new_node;
            last = new_node;
        }
        if (new_node->book.id >= global_counter) global_counter = new_node->book.id + 1;
        
    }

    fclose(fres);
}

void write_orders() {
    fres = fopen("orders.bin", "wb");
    if (fres == NULL) {
        printf("Unable to open file for writing.\n");
        return;
    }
    ress *current = orders;
    while (current != NULL) {
        fwrite(&current->book, sizeof(res), 1, fres);
        current = current->next;
    }
    fclose(fres);
}

void read_fleet() {
    fbus = fopen("fleet.bin", "rb");
    if (fbus == NULL) {
        printf("Unable to open file for reading.\n");
        return;
    }
    while (fleet != NULL) {
        buss *temp = fleet;
        fleet = fleet->next;
        free(temp);
    }
    buss *last = NULL;
    while (1) {
        buss *new_node = (buss *)malloc(sizeof(buss));
        if (fread(&new_node->vehicle, sizeof(bus), 1, fbus) != 1) {
            free(new_node);
            break;  
        }

        new_node->next = NULL;

        if (fleet == NULL){
            fleet = new_node;
            last = fleet;
        } 
        else{
            last->next = new_node;
            last = new_node;
        }
    }
    fclose(fbus);
}

void see_users() {
    voys *current = accounts;
    if (current == NULL) {
        printf("Aucun Utilisateur inscrit\n");
        return;
    }
    while (current != NULL) {
        printf("Nom: %s      ||Numero cin: %i\n", current->client.name, current->client.cin);
        current = current->next;
}
}

void write_fleet() {
    fbus = fopen("fleet.bin", "wb");
    if (fbus == NULL) {
        printf("Unable to open file for writing.\n");
        return;
    }

    buss *current = fleet;
    while (current != NULL) {
        fwrite(&current->vehicle, sizeof(bus), 1, fbus);
        current = current->next;
    }

    fclose(fbus);
}

void clear_voys() {
    voys *current = accounts;
    voys *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    accounts = NULL;
}

void clear_ress() {
    ress *current = orders;
    ress *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    orders = NULL;
}

void add_bus(){
    bus tempo;
    buss * last;
    last=(buss*)malloc(sizeof(buss));
    printf("Saisir l'identifiant de bus: "); scanf("%d", &tempo.id);
    printf("Saisir la capacite de bus: "); scanf("%i",&tempo.cap);
    printf("Saisir la tarif par journee de bus; "); scanf("%i",&tempo.tarif);
    printf("Saisir le nombre des bus de ce type: "); scanf("%i",&tempo.dispo);
    last->vehicle=tempo;
    last->next=NULL;
    if(fleet==NULL){
        last->next=fleet;
        fleet=last;
    }
    else{
        buss *aux=fleet;
        while(aux->next!=NULL){
            aux=aux->next;
        }
        aux->next=last;
    }
}

int main(){
    read_voys();
    read_orders();
    read_fleet();
    printf("\n------------------------------------E-Bus Booking------------------------------------\n");
    int x=1;
    while(x!=0){
        endl();
        printf("[1] Nouveau Compte          [2] Reserver un bus          [3] Regarder notre flotte\n");
        printf("[4]Mes reservations         [0]Terminer                  [5]Droit d'admin\n");
        printf("Saisir votre action : "); scanf("%d",&x);
        if(x==0) break;
        else{
            switch (x)
            {
            case 1:
                new_account();
                break;
            case 2:
                make_reservation();
                break;
            case 3:
                see_fleet();
                break;
            case 4:
                see_reservations();
                if(exist){
                    printf("[1] Modifier une reservation          [2] En revanche\n"); 
                    printf("Saisir votre action : "); scanf("%i",&x);
                    if(x==1) modify_reservation();
                }
                break;

            case 5:
                printf("Saisir l'identifiant d'admin: "); scanf("%d",&x);
                if(x!=123456789) {printf("Identifiant incorrect!\n"); continue;}
                int choice=9; 
                
                while(choice!=0){
                printf("[1] Effacer tous les compte                 [2] Effacer toutes les reservation          [3] Ajouter un bus a la flotte\n");
                printf("[4] Voire la liste des utilisateur          [0] En revanche\n");
                printf("Saisir votre action : "); scanf("%d",&choice);
                    switch (choice)
                    {
                    case 1:
                        clear_voys();
                        break;
                    case 2:
                        clear_ress();
                        break;
                    case 3:
                        add_bus();
                        break;
                    case 4:
                        see_users();
                        break;
                    case 0:
                        break;
                    }
                    endl();
                }
            }
        }
        printf("\n\n");
    }
    printf("\n\n");
    endl();
    printf("A la prochaine!");
    write_voys();
    write_fleet();
    write_orders();
    return 0;
}
