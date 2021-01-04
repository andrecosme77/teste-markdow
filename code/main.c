# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <time.h>
# include <stdbool.h>
# include <string.h>
# include <strings.h>

#define BOARD_SIZE 25
#define TRUE 1
#define FALSE 0
 
char board[BOARD_SIZE][BOARD_SIZE];
char uboard[BOARD_SIZE][BOARD_SIZE]; //Tabuleiro de jogo
 
 
void setupMines(char map[15]);
void buildUserBoard();
void printUserBoard();
int findMines(int row, int column);
void setupGame(int num , int xpos, int ypos);
void UpadteMine(int column, int row, int num);
void ExportFile(char map[15]);
void Menu();

int main()
{
    int escolha = 1;
    char chose[15];
    char map[15];
    int x, y = 0;

    Menu();
    buildUserBoard();

    // se a escolha for diferente de 6, ele continua... o que inicialmente Ã© verdade
    // pois escolha Ã© igual a 1
    while (escolha != 6)
    {       
        printf(">");
        scanf("%s", chose);

        if(strcmp(chose, "read") == 0)
        {
          scanf("%s", map);
          escolha = 1;
        }
        else if(strcmp(chose, "show") == 0){escolha = 2;}
        else if(strcmp(chose, "quit") == 0){escolha = 6;}
        else if(strcmp(chose, "sos") == 0){escolha = 7;}
        else if(strcmp(chose, "trigger") == 0)
        { 
          escolha = 3;
          scanf("%i %i", &x, &y);
        }
        else if(strcmp(chose, "plant") == 0){
          escolha = 4;
          scanf("%i %i", &x, &y);
        }
        else if(strcmp(chose, "export") == 0)
        {
          scanf("%s", map);
          escolha = 5;
        }
        else{
          escolha = 10;
        }

        // estrutura switch
        switch (escolha)
        {

            case 1:
                {
                    setupMines(map);
                    break;
                }

            case 2:
                {
                    printUserBoard();            
                    break;
                }

            case 3:
                {
                    setupGame(3, x, y);
                    break;
                }

            case 4:
                {
                    setupGame(4, x ,y);
                    break;
                }

            case 5:
                {
                    
                    ExportFile(map); 
                    break;
                }
                case 7:
                {
                  Menu();
                  break;
                }


            // opÃ§Ã£o padrÃ£o
            default:
                {
                    // se for escolhida a opÃ§Ã£o 6, ele pula o while utilizando continue para isso 
                    if (escolha == 6)
                    {
                        continue;
                    }
                    // caso o usuÃ¡rio digite um numero acima de 6, ele irÃ¡ informar que nao existe essa opÃ§Ã£o
                    printf("\n\n Nenhuma opcao foi escolhida ");
                    break;
                }
        }

    }
    return 0;
}

void Menu(){
  printf("+-----------------------------------------------------");

  printf("\n read <filename>     - read input file ");
  printf("\n show                - show the mine map ");
  printf("\n trigger <x> <y>     - trigger mine at <x> <y> ");
  printf("\n plant <x> <y>       - place armed mine at <x> <y>");
  printf("\n export <filename>   - save file with current map");
  printf("\n quit                - exit program");
  printf("\n sos                 - show menu");

  printf("\n+-----------------------------------------------------\n");
}

void buildUserBoard()
{
    int column, row;

    // Coloca todos os elementos do tabuleiro como '-'
    for (column = 0; column < BOARD_SIZE; column++)
        for (row = 0; row < BOARD_SIZE; row++)
            board[column][row] = '_';
}

void printUserBoard()
{
    int column, row;

    // Imprime o tabuleiro atual
    for (column = 0; column < BOARD_SIZE; column++)
    {
        for (row = 0; row < BOARD_SIZE; row++)
        {
            printf("%c", board[column][row]);
        }
        printf("\n");
    }
}
// Coloca as minas dentro do tabuleiro
void setupMines(char map[15])
{
    int column, row;

    for (column = 0; column < BOARD_SIZE; column++)
    {
        for (row = 0; row < BOARD_SIZE; row++){
            board[column][row] = '_';
        }
    }

    FILE* f;
    f = fopen(map, "r");

    if (f == NULL)
    {
      printf("Error opening file\n");
      return;
    }

    char chr;
    int count = 0;
      // Estrai caracteres do ficheiro e gurada-os no caracter c 
    for (chr = getc(f); chr != EOF; chr = getc(f)) 
        {
        if (chr == '\n'){ // Incrementa count se o caracter estiver numa nova linha 
            count = count + 1; 
        }
    }
    fclose(f);

    f = fopen(map, "r");

    if (f == NULL)
    {
      fprintf(stdout, "Error opening file\n");
    }

int co = 0;
int linenum = 0;
char a[80][3];
char line[20];

for(int j = 0 ; j < count + 1 ; j++){
  fgets(line, 20, f);
  for (unsigned int h = 0 ; h < strlen(line) ; h++){       
    if(line[h] != ' ' && line[h] != '\n'){
      co++;      
      if(co == 1)
      { 
        linenum++;
        a[linenum][0] = line[h];
      }
      if(co == 2){
        co = 0;
        a[linenum][1] = line[h];
      }      
    }
  }
}

    for (int j = 1 ; j < linenum + 1 ; j++ ){
      int x = (a[j][0] - 48);
      int y = (a[j][1] - 48 );
      if(x >= BOARD_SIZE || y >= BOARD_SIZE || x < 0 || y < 0)
      {
        printf("File is corrupted");
        return;
      }
      board[x][y] = '.';

    }
    fclose(f);
}

//Sets up board and prints intial board for user input.
void setupGame(int num ,int  xpos, int ypos)
{
  //int xpos, ypos;
    if(xpos >= BOARD_SIZE || ypos >= BOARD_SIZE || xpos < 0 || ypos < 0)
    {
      printf("Invalid coordinate\n");
      return;
    }

    if (board[xpos][ypos] == '.')
    {
      if(num == 3){
        board[xpos][ypos] = '*';
      }
    }
    else if (board[xpos][ypos] == '*')
    {
      if(num == 4){
        board[xpos][ypos] = '.';
      }
    }else if(board[xpos][ypos] == '_'){
      if(num == 4){
        board[xpos][ypos] = '.';
      }else{
        printf("No mine at specified coordinate\n");
      }
    } 
}

void ExportFile(char map[15]){
  int column, row;
  FILE* f;
  f = fopen(map, "w");

  if (f == NULL)
  {
    fprintf(stdout, "Error opening file\n");
    exit(1);
  }

  int count = 0;
  int c = 0;
  for (column = 0; column < BOARD_SIZE; column++)
  {
    for (row = 0; row < BOARD_SIZE; row++)
    {
      if(board[column][row] != '_'){
        count++;
      }
    }
  } 

  for (column = 0; column < BOARD_SIZE; column++)
  {
    for (row = 0; row < BOARD_SIZE; row++)
    {      
      if(board[column][row] != '_'){
        c++;
        if(c < count){
          fprintf (f, "%i  %i\n" , column , row);
        }else{
          fprintf (f, "%i  %i" , column , row);
        }
      }
    }
  }    
  fclose(f);
}