#include<stdio.h>
#include<conio.h>
#include <windows.h>

int board[10] = {2,2,2,2,2,2,2,2,2,2};
char square[10] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
int turn = 1,flag = 0;
int player,comp,player1,player2;

void menu();
void go(int n);
void start_game();
void check_draw();
void draw_board();
void player_first();
void two_player();
int checkwin();
void board1();
void clear_board1();
void put_X_O(char ch,int pos);
void clear_board();
COORD coord= {0,0}; // this is global variable
//center of axis is set to the top left cornor of the screen
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void main()
{
    system("cls");
    menu();
    getch();

}

void menu()
{
    int choice;
    again:
    clear_board();
    flag=0;
    system("cls");
    printf("\n\t\t\t--------MENU--------");
    printf("\n\t\t\t1 : Play with X");
    printf("\n\t\t\t2 : Play with O");
    printf("\n\t\t\t3 : Play with a Friend");
    printf("\n\t\t\t4 : exit");
    printf("\n\t\t\tEnter your choice:>");
    scanf("%d",&choice);
    turn = 1;
    switch (choice)
    {
    case 1:
        player = 1;
        comp = 0;
        system("cls");
        printf("\n\n\n\t\t\t player = 'X' and computer = 'O'\n");
        player_first();
        break;
    case 2:
        player = 0;
        comp = 1;
        system("cls");
        printf("\n\n\n\t\t\t computer = 'X' and player = 'O'\n");
        start_game();
        break;
    case 3:
        player1=1;
        player2=0;
        two_player();
        break;
    case 4:
        exit(1);
    default:
        printf("\n\t\t\tInvalid input \n\t\t\t Press any key to choose again\n");
    }
    getch();
    goto again;
}

int make2()
{
    if(board[5] == 2)
        return 5;
    if(board[2] == 2)
        return 2;
    if(board[4] == 2)
        return 4;
    if(board[6] == 2)
        return 6;
    if(board[8] == 2)
        return 8;
    return 0;
}

int make4()
{
    if(board[1] == 2)
        return 1;
    if(board[3] == 2)
        return 3;
    if(board[7] == 2)
        return 7;
    if(board[9] == 2)
        return 9;
    return 0;
}

int posswin(int p)
{
    int i;
    int check_val,pos;

    if(p == 1)
        check_val = 18;
    else
        check_val = 50;

    i = 1;
    while(i<=9)//row check
    {
        if(board[i] * board[i+1] * board[i+2] == check_val)
        {
            if(board[i] == 2)
                return i;
            if(board[i+1] == 2)
                return i+1;
            if(board[i+2] == 2)
                return i+2;
        }
        i+=3;
    }

    i = 1;
    while(i<=3)//column check
    {
        if(board[i] * board[i+3] * board[i+6] == check_val)
        {
            if(board[i] == 2)
                return i;
            if(board[i+3] == 2)
                return i+3;
            if(board[i+6] == 2)
                return i+6;
        }
        i++;
    }

    if(board[1] * board[5] * board[9] == check_val)
    {
        if(board[1] == 2)
            return 1;
        if(board[5] == 2)
            return 5;
        if(board[9] == 2)
            return 9;
    }

    if(board[3] * board[5] * board[7] == check_val)
    {
        if(board[3] == 2)
            return 3;
        if(board[5] == 2)
            return 5;
        if(board[7] == 2)
            return 7;
    }
    return 0;
}

void go(int n)
{
    if(turn % 2)
        board[n] = 3;
    else
        board[n] = 5;
    turn++;
}

void player_first()
{
    int pos;

    check_draw();
    draw_board();
    gotoxy(30,18);
    printf("Your Turn :> ");
    scanf("%d",&pos);

    if(board[pos] != 2)
        player_first();

    if(pos == posswin(player))
    {
        go(pos);
        draw_board();
        gotoxy(30,20);
        printf("Player Wins");
        getch();
        printf("\n\t\t\tPress any key to go menu\n");
        getch();
        menu();
    }

    go(pos);
    draw_board();
    start_game();
}

void start_game()
{
    int pos;
    if(posswin(comp))
    {
        go(posswin(comp));
        flag = 1;
    }
    else if(posswin(player))
        go(posswin(player));
    else if(make2())
        go(make2());
    else
        go(make4());
    draw_board();

    if(flag)
    {
        gotoxy(30,20);
        printf("Computer wins");
        getch();
        printf("\n\t\t\tPress any key to go menu\n");
        getch();
        menu();
    }
    else
        player_first();
}

void check_draw()
{
    if(turn > 9)
    {
        gotoxy(30,20);
        printf("Game Draw");
        printf("\n\t\t\tPress any key to go menu \n");
        getch();
        menu();
        system("cls");
        getch();
    }
}

void draw_board()
{

    int j;

    for(j=9; j<17; j++)
    {
        gotoxy(35,j);
        printf("|       |");
    }
    gotoxy(28,11);
    printf("-----------------------");
    gotoxy(28,14);
    printf("-----------------------");
    for(j=1; j<10; j++)
    {
        if(board[j] == 3)
            put_X_O('X',j);
        else if(board[j] == 5)
            put_X_O('O',j);
    }

}

void put_X_O(char ch,int pos)
{
    int m;
    int x = 31, y = 10;

    m = pos;

    if(m > 3)
    {
        while(m > 3)
        {
            y += 3;
            m -= 3;
        }
    }
    if(pos % 3 == 0)
        x += 16;
    else
    {
        pos %= 3;
        pos--;
        while(pos)
        {
            x+= 8;
            pos--;
        }
    }
    gotoxy(x,y);
    printf("%c",ch);
}
void clear_board()
{
    int j;
    for(j=1;j<10;j++)
    {
        board[j]=2;
    }

}
void two_player()

        {
            int player = 1, i, choice;

            char mark;
            clear_board1();

            do
            {
                board1();
                player = (player % 2) ? 1 : 2;

                printf("\t\t\tPlayer %d, enter a number:  ", player);
                scanf("%d", &choice);

                mark = (player == 1) ? 'X' : 'O';

                if (choice == 1 && square[1] == ' ')
                    square[1] = mark;

                else if (choice == 2 && square[2] == ' ')
                    square[2] = mark;

                else if (choice == 3 && square[3] == ' ')
                    square[3] = mark;

                else if (choice == 4 && square[4] == ' ')
                    square[4] = mark;

                else if (choice == 5 && square[5] == ' ')
                    square[5] = mark;

                else if (choice == 6 && square[6] == ' ')
                    square[6] = mark;

                else if (choice == 7 && square[7] == ' ')
                    square[7] = mark;

                else if (choice == 8 && square[8] == ' ')
                    square[8] = mark;

                else if (choice == 9 && square[9] == ' ')
                    square[9] = mark;

                else
                {
                    printf("Invalid move ");

                    player--;
                    getch();
                }
                i = checkwin();
                player++;
            }while (i ==  -1);

            board1();

            if (i == 1)
                printf("\t\t\t==>\aPlayer %d win ", --player);
            else
                printf("\t\t\t==>\aGame draw");
            printf("\n\t\t\tEnter any two key to go menu\n");
            getch();
        }



int checkwin()
{

    if (!(square[1] == ' ' || square[2] == ' ' || square[3] == ' '))
        {
            if (square[1] == square[2] && square[2] == square[3])
            return 1;
        }

    if (!(square[4] == ' ' || square[5] == ' ' || square[6] == ' '))
        {
            if (square[4] == square[5] && square[5] == square[6])
            return 1;
        }

    if (!(square[7] == ' ' || square[8] == ' ' || square[9] == ' '))
        {
            if (square[7] == square[8] && square[8] == square[9])
            return 1;
        }

    if (!(square[1] == ' ' || square[4] == ' ' || square[7] == ' '))
        {
            if (square[1] == square[4] && square[4] == square[7])
            return 1;
        }

    if (!(square[2] == ' ' || square[5] == ' ' || square[8] == ' '))
        {
            if (square[2] == square[5] && square[5] == square[8])
            return 1;
        }

    if (!(square[3] == ' ' || square[6] == ' ' || square[9] == ' '))
        {
            if (square[3] == square[6] && square[6] == square[9])
            return 1;
        }

    if (!(square[1] == ' ' || square[5] == ' ' || square[9] == ' '))
        {
            if (square[1] == square[5] && square[5] == square[9])
            return 1;
        }
    if (!(square[3] == ' ' || square[5] == ' ' || square[7] == ' '))
        {
            if (square[3] == square[5] && square[5] == square[7])
            return 1;
        }

    if (square[1] != ' ' && square[2] != ' ' && square[3] != ' ' &&
        square[4] != ' ' && square[5] != ' ' && square[6] != ' ' && square[7]
        != ' ' && square[8] != ' ' && square[9] != ' ')
        return 0;
    else
        return -1;

}
void board1()
{
    system("cls");
    printf("\n\n\t\t\tTic Tac Toe\n\n");

    printf("\t\t\tPlayer 1 = 'X'  -  Player 2 = 'O'\n\n\n");


    printf("\t\t\t     |     |     \n");
    printf("\t\t\t  %c  |  %c  |  %c \n", square[1], square[2], square[3]);

    printf("\t\t\t-----------------\n");
    printf("\t\t\t     |     |     \n");

    printf("\t\t\t  %c  |  %c  |  %c \n", square[4], square[5], square[6]);

    printf("\t\t\t-----------------\n");
    printf("\t\t\t     |     |     \n");

    printf("\t\t\t  %c  |  %c  |  %c \n", square[7], square[8], square[9]);
    printf("\n");
}

void clear_board1()
{

    square[1]= ' ';
    square[2]= ' ';
    square[3]= ' ';
    square[4]= ' ';
    square[5]= ' ';
    square[6]= ' ';
    square[7]= ' ';
    square[8]= ' ';
    square[9]= ' ';
}
