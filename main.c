/*

TRACCIA: Presa da file una collezione di dati di almeno 7 articoli lattiero caseari di un distributore (creato precedentemente dallo studente), dove ogni articolo è strutturato nel modo seguente:
•	Codice, 
•	nome_articolo,
•	mese_scadenza, 
•	prezzo
ricercare e restituire l’elenco di articoli suddiviso tra quelli che hanno una data di scadenza che sia maggiore di un mese inserito dall’operatore incrementato di un ulteriore mese e quelli rimanenti. 
Gli articoli dovranno essere restituiti comprensivi di tutte le informazioni e il primo gruppo (con scadenza maggiore) dovrà essere visualizzato in ordine decrescente per prezzo mentre il secondo gruppo (la rimanenza) in ordine crescente per prezzo. Indicare quale algoritmo di ordinamento sarebbe più efficiente al crescere del numero di articoli contenuto nel file.

*/

#include <stdlib.h>
#include <stdio.h>

struct dati {

    char codice[5+1];
    char nome[63+1];
    int mese;
    float prezzo;

}typedef struttura;

int conta (FILE*);
void carica (FILE* , struttura*);
void conta_filtro (struttura* , int* , int* , int , int);
void carica_filtrati (struttura* , int , int , int , int , struttura* , struttura*);
void swap (struttura* , int);
void sort (char , int , struttura*);
void print (struttura* , int);

#define BUFFERSIZE 200+1

void main () {

    char percorso[300+1];
    FILE* p;
    int n_articoli;
    struttura* articoli_tot;
    struttura* articoli_min;
    struttura* articoli_mag;
    int dim_min=0 , dim_mag=0;
    int soglia;



    printf ("Inserisci il percorso del file: ");
    scanf ("%s" , percorso);
    p = fopen (percorso , "r");

    if (p == NULL) {

        printf ("Errore: file non aperto correttamente.");
        exit (0);
    }

    do {
        printf ("Inserisci il mese di soglia: ");
        scanf("%d" , &soglia);
        if (soglia <0 || soglia >11){
            printf ("Errore: inserire un numero compreso tra 0 e 11\n");
        }
        
    } while (soglia < 0 || soglia > 11);
    
    soglia = soglia + 1;

    n_articoli = conta (p);

    articoli_tot = malloc (n_articoli * sizeof (struttura));
    carica (p , articoli_tot);
    fclose (p);

    conta_filtro (articoli_tot , &dim_mag , &dim_min , n_articoli , soglia);

    articoli_mag = malloc (dim_mag * sizeof(struttura));
    articoli_min = malloc (dim_min * sizeof(struttura));
    

    carica_filtrati (articoli_tot , n_articoli , dim_mag , dim_min , soglia , articoli_min , articoli_mag);
    free (articoli_tot);
    
    sort ('D' , dim_mag , articoli_mag);
    sort ('C' , dim_min , articoli_min);

    printf("Articoli con mese successivo a soglia+1:\n");
    print (articoli_mag , dim_mag);
    printf("Articoli con mese precedente a soglia+1:\n");
    print (articoli_min , dim_min);

}

int conta (FILE* p) {

    char temp[BUFFERSIZE];
    int i = 0;

    while (!feof(p)) {
    
        fgets (temp , BUFFERSIZE , p);
        i++;
    }

    free (temp);
    rewind (p);
    return (i);
}

void carica (FILE* p , struttura* articoli) {

    int i = 0;    
    while (!feof (p)) {
    
        fscanf (p , "%s %s %d %f" , articoli[i].codice , articoli[i].nome , &articoli[i].mese , &articoli[i].prezzo);
        i++;
    }
}

void conta_filtro (struttura* articoli , int* mag , int* min , int n , int soglia) {

    for (int i = 0; i < n; i++) {
        
        if (articoli[i].mese > soglia) {
    	    (*mag)++;
            
        } else if (articoli[i].mese <= soglia) {
            (*min)++; 
        }
    }
}

void carica_filtrati (struttura* articoli_tot , int n_articoli , int dim_mag , int dim_min , int soglia , struttura* articoli_min , struttura* articoli_mag) {

    int i_mag = 0 , i_min = 0;

    for (int i = 0; i < n_articoli; i++) {
        
        if (articoli_tot[i].mese > soglia) {
            articoli_mag[i_mag] = articoli_tot[i];
            i_mag++;

        } else if (articoli_tot[i].mese <= soglia) {
            articoli_min[i_min] = articoli_tot[i];
            i_min++;
        }
    }
}

void swap (struttura* art , int j) {

    struttura temp = art[j];
    art[j] = art[j+1];
    art[j+1] = temp;

}

void sort (char selezione , int dim , struttura* art) {

    int flag=1 , i=0;

    while (flag==1) {

        flag=0;
        for (int j = 0; j < dim - i - 1; j++) {
            if (selezione == 'C' && art[j].prezzo > art[j+1].prezzo) {
                swap (art , j);
                flag = 1;
            } else if (selezione == 'D' && art[j].prezzo < art[j+1].prezzo) {
                swap (art , j);
                flag = 1;
            }
        }
        i++;
    }
    

}

void print (struttura* art , int dim) {

    for (int i = 0; i < dim; i++) {

        printf("%s %s %d %.2f \n" , art[i].codice , art[i].nome , art[i].mese , art[i].prezzo);

    }


}