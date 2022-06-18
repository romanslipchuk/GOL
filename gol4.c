/**Conway's Game of Life**/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
// #include <conio.h>

const int WIDTH = 67;
const int HEIGHT = 47;
const int TRUE = 1;
const int FALSE = 0;

void makingboundarylines (int board[HEIGHT][WIDTH])
{
    int cols, rows;
    for (cols =0; cols <WIDTH; cols++)
    {
        board[0][cols] = '_';
        board[HEIGHT -1][cols]= '_';
    }
    for (rows =1; rows <HEIGHT; rows++)
    {
        board[rows][0] = '|';
        board[rows][WIDTH -1] = '|';
    }
}
void fillarray(int board[HEIGHT][WIDTH])
{
    int i,j;
    for(i =1; i <HEIGHT-1; i++)
        for(j=1; j <WIDTH-1; j++)
            board[i][j] = ' ';
}
void fillarrayrandomly(int board[HEIGHT][WIDTH])
{
    int i, j, num;
    srand((unsigned)time(NULL));
    for(i =1; i <HEIGHT -1; i++)
        for(j=1; j <WIDTH -1;j++)
        { 
            num = rand()%11;
            if (num == 1)
                board[i][j] = 'O';
            else board[i][j] = ' ';
        }
}
void display2Darray(int board[HEIGHT][WIDTH])
{
int rows;
int cols;
    for (rows = 0; rows <HEIGHT; rows++)
    {
        for(cols =0; cols <WIDTH; cols++)
            printf ("%3c", board[rows][cols]);
        printf ("\n");
    }
}
void countneighbors (int board[HEIGHT][WIDTH])
{
    int neighbors;
    int rows;
    int cols;
    int a, b;
    for (rows =1; rows <HEIGHT; rows++)
    {
        for (cols = 1; cols <WIDTH; cols ++)
        {
            neighbors = 0;
            if (board[rows][cols] == 'O')
            {
                for (a = -1; a <2; a++)
                {
                    for (b = -1; b <2; b++)
                        if (((rows +a) == rows) && ((cols +b) == cols))
                             neighbors = neighbors;
                        else if ((board[rows +a][cols +b] == 'O') ||(board[rows +a][cols +b] == 1) || (board[rows +a][cols +b] == 0))
                            neighbors++;
                }
                if ((neighbors == 2) || (neighbors == 3))
                    board[rows][cols] = 1; /*live*/
                else if ((neighbors < 2) || (neighbors >= 4))
                    board[rows][cols] = 0; /*die*/
            }
        }
    }
}
void checknewborns (int board[HEIGHT][WIDTH])
{
    int neighbors;
    int rows;
    int cols;
    int a, b;
    for (rows =1; rows <HEIGHT -1; rows++)
    {
        for (cols = 1; cols <WIDTH -1; cols ++)
        {
            neighbors = 0;
            if (board[rows][cols] == ' ')
            {
                for (a = -1; a <2; a++)
                {
                    for (b = -1; b <2; b++)
                        if (((rows +a) == rows) && ((cols +b) == cols))
                            neighbors = neighbors;
                        else if ((board[rows +a][cols +b] == 'O') || (board[rows +a][cols +b] == 1) || (board[rows +a][cols +b] == 0))
                            neighbors++;
                }
                if ((neighbors == 3))
                    board[rows][cols] = 2; /*newborn*/
            }
        }
    }
}
void anewgeneration (int board[HEIGHT][WIDTH])
{
    int rows;
    int cols;
    for (rows =1; rows <HEIGHT -1; rows++)
    {
        for (cols = 1; cols <WIDTH -1; cols ++)
        {
            if (board[rows][cols] == 1)
                board[rows][cols] = 'O';
            else if (board[rows][cols] == 2)
                board[rows][cols] = 'O';
            else if (board[rows][cols] == 0)
                board[rows][cols] = ' ';
        }
    }
}  
int checkforexistence (int board[HEIGHT][WIDTH])
{
    int rows;
    int cols;
    int creatures =0;
    for (rows =1; rows <HEIGHT -1; rows++)
    {
        for (cols = 1; cols <WIDTH -1; cols ++)
        {
            if (board[rows][cols] == 'O')
                creatures++;
        }  
    }
    if (creatures == 0)
        return TRUE; /*all creatures died*/
    else return FALSE; /*there are still living creatures*/
}
void playgame (int board[HEIGHT][WIDTH], int numgeneration)
{
    int i, c, check;
    for (i = 1; (i <= numgeneration) && (c != 32); i++)
    {
        system("cls");
        countneighbors(board);
        checknewborns(board);
        anewgeneration(board);
        printf ("Generation: %i\n", i);
        printf ("Hit enter to move to the next generation\n");
        display2Darray(board);
        if(kbhit())
        {
            c = getch();
            if(c == 32)
                break;
        }
        check = checkforexistence(board);
        if ((check= checkforexistence(board)) ==TRUE)
        {
            printf ("\nALL CREATURES HAVE DIED: GAME OVER");
            c = 32;
        }
    }
}
int returnnumber(int anumber)
{
    if  ((anumber >50) || (anumber ==0))
    { 
        printf ("ERROR! The number must be between 1 and 50\n");
        printf ("Please enter a valid number!: ");
        scanf ("%i", &anumber);
        returnnumber(anumber);
    }
    else
        return anumber;
}
void entercoordinates (int board[HEIGHT][WIDTH])
{
    int rows = 1;
    int cols =1;
    while ((rows >0) && (cols >0))
    {
        printf ("\nPlease enter x coordinate(a number from 1 to 30): ");
        scanf("%i", &cols);
        cols = returnnumber(cols);
        if (cols >0)
        {
            printf ("Please enter y coordinate(a number from 1 to 50): ");
            scanf("%i", &rows);
            rows = returnnumber(rows);
            if ((rows >0) && (cols >0))
                board[rows][cols] = 'O';
        }
    }
}
void creatingpatterntypes(int board[HEIGHT][WIDTH])
{
    int type;
    printf ("\nEnter <1> for creating  a BOX");
    printf ("\nEnter <2> for creating  a BEEHIVE");
    printf ("\nEnter <3> for creating  a TOAD");
    printf ("\nEnter <4> for creating  a SHIP");
    printf ("\nEnter <5> for creating  a GLIDER");
    printf ("\nEnter <6> for creating  a QUEEN BEE SHUTTLE");
    printf ("\nEnter <7> for creating  a PULSAR");
    printf ("\nEnter <8> for creating  a BLINKER");
    printf ("\nEnter <9> for creating  a PENTADECATHLON\n");
    scanf ("%i", &type);

if (type == 1)
{
    board[10][10] = 'O';
    board[10][11] = 'O';
    board[11][10] = 'O';
    board[11][11] = 'O';
}
else if (type == 9)
{
    board[15][10] = 'O';
    board[15][11] = 'O';
    board[15][12] = 'O';
    board[15][13] = 'O';
    board[15][14] = 'O';
    board[15][15] = 'O';
    board[15][16] = 'O';
    board[15][17] = 'O';
    board[15][18] = 'O';
    board[15][19] = 'O';
}
else if (type == 5)
{
    board[28][3] = 'O';
    board[27][4] = 'O';
    board[26][4] = 'O';
    board[27][5] = 'O';
    board[28][5] = 'O';
}
else if (type == 3)
{
    board[18][12] = 'O';
    board[18][13] = 'O';
    board[18][14] = 'O';
    board[19][11] = 'O';
    board[19][12] = 'O';
    board[19][13] = 'O';
}
else if (type == 6)
{
    board[20][28] = 'O';
    board[20][29] = 'O';
    board[21][30] = 'O';
    board[22][31] = 'O';
    board[23][31] = 'O';
    board[24][31] = 'O';
    board[25][30] = 'O';
    board[26][29] = 'O';
    board[26][28] = 'O';
}
else if (type == 7)
{
    board[12][14] = 'O';
    board[13][13] = 'O';
    board[13][14] = 'O';
    board[13][15] = 'O';
    board[14][13] = 'O';
    board[14][15] = 'O';
    board[15][13] = 'O';
    board[15][14] = 'O';
    board[15][15] = 'O';
    board[16][14] = 'O';
}
else if (type == 8)
{
    board[12][12] = 'O';
    board[12][13] = 'O';
    board[12][14] = 'O';
}
else if (type == 4)
{
    board[12][12] = 'O';
    board[12][13] = 'O';
    board[13][12] = 'O';
    board[14][13] = 'O';
    board[14][14] = 'O';
    board[13][14] = 'O';
}
else if (type ==2)
{
    board[12][14] = 'O';
    board[13][13] = 'O';
    board[13][15] = 'O';
    board[14][13] = 'O';
    board[15][14] = 'O';
    board[14][15] = 'O';
    }
}
 void usermode(int board[HEIGHT][WIDTH])
{
    int i, generation, c, choice;
    printf ("\nDo you want to insert a particular pattern type? <1> for yes and <0> for no: ");
    scanf ("%i", &choice);
    if (choice == 1)
    {
        creatingpatterntypes(board);
        display2Darray(board);
    }
    else
    {
        entercoordinates(board);
        display2Darray(board);
    }

    printf ("\nPlease select a number of generation: ");
    scanf ("%i", &generation);

    playgame(board, generation);
}
void automaticmode(int board[HEIGHT][WIDTH])
{
    int i, generation, c;
    fillarrayrandomly(board);
    display2Darray(board);
    printf ("\nPlease select a number of generation: ");
    scanf ("%i", &generation);

    playgame(board, generation);
}
void hybridmode (int board[HEIGHT][WIDTH])
{
    int i, generation, c;
    fillarrayrandomly(board);
    display2Darray(board);
    entercoordinates(board);
    system("cls");
    display2Darray(board);

    printf ("\nPlease select a number of generation: ");
    scanf ("%i", &generation);

    playgame(board, generation);
}

int main (void)
{
    //printf ("hello. world\n");
    int board[HEIGHT][WIDTH], mode;
    makingboundarylines(board);
    fillarray(board);

    printf ("CONWAY'S GAME OF LIFE\n\n");
    printf ("Please hit space to terminate the program, hit enter to move to the next generation\n");
    printf ("Please enter <1> for User Mode, <2> for Automatic Mode and <3> for Hybrid Mode: ");
    scanf ("%i", &mode);

if (mode == 1)
    usermode(board);
else if (mode == 2)
    automaticmode(board);
else if (mode ==3)
    hybridmode(board);

return 0;
}