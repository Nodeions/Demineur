#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


typedef struct Tile {
    bool isRevealed;
    bool isBombing;
    bool isTouch;
    int touchNumber;
    bool isFlag; //pour plus tard
}Tile;

typedef struct Grid {
    Tile** tile;
    int size;
}Grid;



Grid InitGrid() {

    Grid grid;
    printf("Entrez la longueur de la grille : ");
    scanf_s("%d", &grid.size);
    Tile** line = (Tile**)malloc(sizeof(Tile*) * grid.size);
    if (line == NULL) {
        exit(1);
    }

    for (int i = 0; i < grid.size; i++) {

        Tile* cell = (Tile*)malloc(sizeof(Tile) * grid.size);
        if (cell == NULL) {
            exit(1);
        }

        for (int j = 0; j < grid.size; j++) {

            cell[j].isBombing = false;
            cell[j].isFlag = false;
            cell[j].isRevealed = false;
            cell[j].isTouch = false;
            cell[j].touchNumber = 0;
        }
        line[i] = cell;
        
    }

    grid.tile = line;
    return grid;
}

void PrintGrid(Grid* grid, int x, int y) {

    for (int i = 0; i < grid->size; i++) {
        for (int j = 0; j < grid->size; j++) {
            if (grid->tile[j][i].isBombing) {
                printf("| X |");
            }
            else if (grid->tile[j][i].isRevealed) {
                printf("| %d |", grid->tile[x][y].touchNumber);
            }
            else
                printf("|%d %d|", i, j);
        }
        printf("\n");
    }

}

void PutRandomBomb(Grid* grid) {
    srand(time(NULL));
    int bomb;    
    printf("Entrez le nombre de mines voulue : ");
    scanf_s("%d", &bomb);
    printf("%d", bomb);
    int sizeTab = pow(grid->size, 2);

    int* tab = (int*)malloc(sizeof(int) * sizeTab); // tableau 1 dim
    if (tab == NULL) {
        exit(1);
    }

    for (int i = 0; i < sizeTab; i++) {
        tab[i] = i;
    }

    for (int i = 0; i < bomb; i++) {

        int rdnElem = tab[rand() % sizeTab]; // elem random du tableau

        int xTab = rdnElem % grid->size; // transform du tab 1 dim en deux
        int yTab = rdnElem / grid->size;
        printf("%d et %d\n", xTab, yTab);

        grid->tile[xTab][yTab].isBombing = true;

        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {

                    grid->tile[xTab+i][yTab+j].touchNumber++; //bloque ici

            }
        }

        tab[rdnElem] = tab[sizeTab - 1];
        sizeTab--;
    }

        free(tab);
}

void AskCoord(int* x, int* y) {

    printf("quelle case voulez-vous reveler ? coord X : ");
    scanf_s("%d", x);
    printf("quelle case voulez-vous reveler ? coord Y : ");
    scanf_s("%d", y);
  
}

void RevealCell(Grid* grid, int x, int y) {

    if (grid->tile[x][y].isRevealed) {

        printf("Case deja revelee");
    }
    else {
        
        grid->tile[x][y].isRevealed = true;

        if (grid->tile[x][y].isBombing == true) {
            printf("Perdu !");
            exit(1);
        }
         
    }
}



int main() {

    int x = 0;
    int y = 0;
    Grid grid = InitGrid();
    PrintGrid(&grid, x, y); //pointeur vers la variable
    PutRandomBomb(&grid);
    printf("\n");
    PrintGrid(&grid, x, y);
    while (1) {

        AskCoord(&x,&y);
        RevealCell(&grid, x, y);
        PrintGrid(&grid, x, y);

    }
    return 0;
}