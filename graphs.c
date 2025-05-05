#include <stdio.h>

#define INT_MAX 100

typedef struct {
    int matricaSusedstva[100][100];
    int brojCvorova;
} Graf;

void pravimGraf(Graf *graf, int n) {
    graf->brojCvorova = n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graf->matricaSusedstva[i][j] = 0;
        }
    }
}

void ispisiGraf(const Graf *graf) {
    for (int i = 0; i < graf->brojCvorova; i++) {
        for (int j = 0; j < graf->brojCvorova; j++) {
            printf("%d ", graf->matricaSusedstva[i][j]);
        }
        printf("\n");
    }
}

void dodavanjeCvora(Graf* graf) {
    int novo = graf->brojCvorova;
    graf->brojCvorova++;

    for (int i = 0; i < graf->brojCvorova; i++) {
        graf->matricaSusedstva[novo][i] = 0;
        graf->matricaSusedstva[i][novo] = 0;
    }
}


void povezivanjeGrane(Graf* graf, int x, int y){
    graf->matricaSusedstva[x][y] = 1;
    graf->matricaSusedstva[y][x] = 1;

}
void brisanjeCvora(Graf* graf, int x, int y){
    graf->matricaSusedstva[x][y] = 0;
    graf->matricaSusedstva[y][x] = 0;


}
void brisanjeGrane(Graf *graf, int z) {
    for (int i = 0; i < graf->brojCvorova; i++) {
        for (int j = z; j < graf->brojCvorova - 1; j++) {
            graf->matricaSusedstva[i][j] = graf->matricaSusedstva[i][j + 1];
        }
    }

    for (int i = z; i < graf->brojCvorova - 1; i++) {
        for (int j = 0; j < graf->brojCvorova; j++) {
            graf->matricaSusedstva[i][j] = graf->matricaSusedstva[i + 1][j];
        }
    }

    int zadnji = graf->brojCvorova - 1;
    for (int i = 0; i < graf->brojCvorova; i++) {
        graf->matricaSusedstva[i][zadnji] = 0;
        graf->matricaSusedstva[zadnji][i] = 0;
    }

    graf->brojCvorova--;
}


int kopiranje(Graf*graf, int dist[100][100]){


    for (int i = 0; i < graf->brojCvorova; i++) {
        for (int j = 0; j < graf->brojCvorova; j++) {
            if (i == j) {
                dist[i][j] = 0;
            } else if (graf->matricaSusedstva[i][j] == 0) {
                dist[i][j] = INT_MAX;
            } else {
                dist[i][j] = graf->matricaSusedstva[i][j];
            }
        }
    }
    return dist[100][100];
}

int floydalg(Graf *graf, int dist[100][100]) {

    dist[100][100] = kopiranje(graf, dist);

    for (int k = 0; k < graf->brojCvorova; k++) {
        for (int i = 0; i < graf->brojCvorova; i++) {
            for (int j = 0; j < graf->brojCvorova; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&dist[i][k] + dist[k][j] < dist[i][j]) {

                    dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

    return dist[100][100];
}

int  RelacionaCentralnost(Graf *graf, int c) {
    float centar = 0;
    int dist[100][100];


    floydalg(graf, dist);

    for (int i = 0; i < graf->brojCvorova; i++) {
        for (int j = 0; j < graf->brojCvorova; j++) {
            if (i != j && i != c && j != c &&
                dist[i][c] != INT_MAX && dist[c][j] != INT_MAX && dist[i][j] != INT_MAX) {
                if (dist[i][j] == dist[i][c] + dist[c][j]) {
                    centar++;
                }
            }
        }
    }

    return centar;
}

void dodavanjeskraceno(Graf*graf){
    int x,y;
    printf("Izaberite izvorni cvor: \n");
    scanf("%d", &x);

    printf("Izaberite krajnji cvor:\n");
    scanf("%d", &y);
    if(x == y){
        printf("Ne mozete spojiti granu samu sa sobom!\n");
        putchar('\n');
        return;
    } else {
        putchar('\n');

        povezivanjeGrane(graf, x, y);
    }

}


int main() {
    Graf graf;
    int n, izbor,x,y, z, dist[100][100],c,m;

    printf("Unesite broj cvorova:\n");
    scanf("%d", &n);
    pravimGraf(&graf, n);
    printf("Unesite grana:\\n\"");
    scanf("%d", &m);
    for(int i = 0; i < m; i++){
        dodavanjeskraceno(&graf);

    }



    while (1) {
        printf("---ODABERITE OPCIJU---\n");
        printf("1. Dodaj Cvor\n");
        printf("2. Makni Cvor\n");
        printf("3. Dodaj Granu\n");
        printf("4. Makni Granu\n");
        printf("5. Ispis Grafa\n");
        printf("6. Brisanje Grafa\n");
        printf("7. Geodezijska distanca\n");
        printf("8. Dijametar grafa\n");
        printf("9. Relaciona centralnost cvora\n");
        printf("10. Izlaz\n");
        scanf("%d", &izbor);
        switch (izbor) {
            case 1:
                dodavanjeCvora(&graf);
                continue;
            case 2:
                printf("Izaberite cvor koji micete: ");
                scanf("%d", &z);
                brisanjeGrane(&graf, z);

                continue;
            case 3:
                dodavanjeskraceno(&graf);
                continue;
            case 4:
                printf("Izaberite izvorni cvor: ");
                scanf("%d", &x);
                putchar('\n');
                printf("Izaberite krajnji cvor: ");
                scanf("%d", &y);
                putchar('\n');

                brisanjeCvora(&graf, x, y);
                continue;

            case 5:
                ispisiGraf(&graf);
                continue;
            case 6:
                pravimGraf(&graf, 0);
                continue;
            case 7:
                printf("Izaberite izvorni cvor: ");
                scanf("%d", &x);
                putchar('\n');
                printf("Izaberite krajnji cvor: ");
                scanf("%d", &y);
                putchar('\n');
                dist[100][100] = floydalg(&graf,dist);
                if(dist[x][y] == INT_MAX){
                    printf("Ne postoji geodezijska distanca\n");
                }
                else{
                printf("Geodezijska distanca je: %d \n", dist[x][y]);}

                continue;
            case 8:
                dist[100][100] = floydalg(&graf,dist);
                int d = 0;
                for(int i =0 ; i < graf.brojCvorova; i++){
                    for(int j =0 ; j < graf.brojCvorova; j++) {
                        if(dist[i][j] > d && dist[i][j] != INT_MAX){
                            d = dist[i][j];
                        }
                    }
                }
                printf("Dijametr grafa je: %d\n", d);
                continue;
            case 9:
                printf("Unesi cvor za racionalnu: ");
                scanf("%d", &c);
                int t = RelacionaCentralnost(&graf, c);
                printf("Relaciona centralnost cvora je %d\n", t);
                continue;
            case 10:
                return 0;
        }

    }

}
