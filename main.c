#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define EMPTY 0
#define CIRCLE 1
#define CROSS 2

void initGameBoard(int gameBoard[3][3]) {
    int i,j;
    for (i=0; i<3; i++){
        for (j=0;j<3;j++){
            gameBoard [j][i]= EMPTY;
        }
    }
    
}

void printGameBoard (int gameBoard [3][3]){
    int i,j;
    printf ("=========\n");
    for (i=0;i<3;i++){
        for (j=0;j<3;j++){
            if (gameBoard [j][i] == EMPTY){
                printf ("|%d|",7-3*i+j);
            }
            else if (gameBoard [j][i] == CIRCLE){
                printf ("|O|");
            }
            else if (gameBoard [j][i] == CROSS){
                printf ("|X|");
            }
        }
        printf ("\n");
    }
    printf ("=========\n");
}

int checkIfPlacedMark(int gameBoard[3][3],int N){
    int i,j;
    for (i=0; i<3; i++){
        for (j=0;j<3;j++){
            if (N == 7-3*i+j){
                if (gameBoard[j][i] == CIRCLE){
                    return 0;
                }
                if (gameBoard[j][i] == CROSS){
                    return 0;
                }
                else return N;
            
            }
        }
    }
    return 0;
}

int getInput(char str[],int gameBoard[3][3]){
    while (1){
    fgets(str,100000,stdin);
    int N= (int)strlen(str);
    if (N>=3){
        printf ("Please enter a valid move (number 1-9)\n");
        printf ("Please place your move (number 1-9) again:\n");
        continue;
            }
    else if (str[0]>= '1'&& str[0]<='9'){
        int N= (int)str[0]-48;
        int tmp =N;
        N = checkIfPlacedMark(gameBoard,N);
        
        if (N==0){
            if (tmp==1){
            printf("There is a mark in the 1st square already!\n");
            printf ("Please place your move again:\n");
            continue;
            }
            else if (tmp==2){
            printf("There is a mark in the 2nd square already!\n");
            printf ("Please place your move again:\n");
            continue;
            }
            else if (tmp==3){
            printf("There is a mark in the 3rd square already!\n");
            printf ("Please place your move again:\n");
            continue;
            }
            else {
            printf("There is a mark in the %dth square already!\n",tmp);
            printf ("Please place your move again:\n");
            continue;
            }
        }
        else
        return N;
        }
    else {
        printf ("Please enter valid move (1-9)\n");
        printf ("Please place your move (1-9) again:\n");
        continue;
            }
    }
}

void placeMarkByHumanPlayer(int gameBoard[3][3], int mark) {
    char pos[100000];
    int i,j;
    int input= getInput(pos,gameBoard);
    for (i=0; i<3; i++){
        for (j=0;j<3;j++){
            if (input == 7-3*i+j && mark == CIRCLE){
            gameBoard [j][i]= CIRCLE;
            }
            if (input == 7-3*i+j && mark == CROSS){
            gameBoard [j][i]= CROSS;
            }
        }
    }

}

int hasWinner(int gameBoard[3][3]) {

    int i,j;
    j=0;
    for (i=0;i<3;i++){
        
        if (gameBoard[0][i]==gameBoard[1][i] && gameBoard[1][i]==gameBoard[2][i] && gameBoard[0][i]!= EMPTY){
            j = 1;
            break;
        }
    
        if (gameBoard[i][0]==gameBoard[i][1] && gameBoard[i][1]==gameBoard[i][2] && gameBoard[i][0]!= EMPTY){
            j = 1;
            break;
        }
    }
    if (gameBoard[0][0]==gameBoard[1][1] && gameBoard[1][1]==gameBoard[2][2] && gameBoard[0][0]!= EMPTY)
        j = 1;
    if (gameBoard[2][0]==gameBoard[1][1] && gameBoard[1][1]==gameBoard[0][2] && gameBoard[2][0]!= EMPTY)
        j = 1;
    return j;
}

int isFull(int gameBoard[3][3]){
    int i,j,count;
    count=0;
    for (i=0;i<3;i++){
        for (j=0;j<3;j++){
            if (gameBoard [j][i]== CIRCLE || gameBoard [j][i]== CROSS)
                count++;
        }
    }
    if (count == 9)return 1;
    else return 0;
}

int bestmove (int gameBoard[3][3]){
    int i,j,mark;
for (mark = CROSS; mark>= CIRCLE; mark--){
    for (i= 2;i>=0;i--) {
        for (j=0;j<3;j++){
                if  (gameBoard[j][i]== mark){
                    int k,a;
                    for (k=0;k<3;k++){
                        if (k != j && gameBoard[k][i]==mark){
                            for (a=0;a<3;a++){
                                if (a !=j && a!=k && gameBoard[a][i]== EMPTY){
                                    gameBoard[a][i] = CROSS;
                                    return 1;
                                }
                            }
                        }
                    }
                    for (k=0;k<3;k++){
                        if (k != i && gameBoard[j][k]==mark){
                            for (a=0;a<3;a++){
                                if (a !=i && a!=k && gameBoard[j][a] == EMPTY){
                                    gameBoard[j][a] = CROSS;
                                    return 1;
                                }
                            }
                        }
                    }
                    if (i==j){
                        for (k=0;k<3;k++){
                            if (k!=i && gameBoard[k][k]==mark){
                                for (a=0;a<3;a++){
                                    if (a !=i && a!=k && gameBoard[a][a] == EMPTY ){
                                        gameBoard[a][a] = CROSS;
                                        return 1;
                                    }
                                }
                            }
                        }
                    }
                    if ((i==0&&j==2)||(i==2&&j==0)||(i==1&&j==1)){
                        for (k=0;k<3;k++){
                            if (k!=i && 2-k!=j && gameBoard[2-k][k]==mark){
                                if (k!=1 && gameBoard[k][2-k]== EMPTY){
                                    gameBoard[k][2-k]=CROSS;
                                    return 1;
                                }
                            }
                        }
                    }
                }
    }
    }
    }
    return 0;
}
void firstmove (int gameBoard[3][3]){
    if (gameBoard [1][1] == EMPTY){
        gameBoard [1][1] = CROSS;
        return;
    }
    else {
        while (1){
        srand((int)time(NULL));
        int corner[4] = { 1,3,7,9};
        int randomIndex = rand() % 4;
        int r = corner[randomIndex];
        int i,j;
        for (i=0; i<3; i++){
            for (j=0;j<3;j++){
                if (r == 7-3*i+j && gameBoard [j][i]== EMPTY){
                gameBoard [j][i]= CROSS;
                    return;
                }
            }
        }
        }
    }
}
void placeMarkByComputerPlayer(int gameBoard[3][3]){
    
    if (bestmove(gameBoard)==1){
        return;
    }
    while(1){
    srand( (int)time (NULL));
    int r = 1 +rand()%9;
    int i,j;
    for (i=0; i<3; i++){
        for (j=0;j<3;j++){
            if (r == 7-3*i+j && gameBoard [j][i]== EMPTY){
            gameBoard [j][i]= CROSS;
                return;
            }
        }
        }
    }
}


    int main() {
    int gameBoard[3][3];
    char numOfHumanPlayers[1000];

    initGameBoard(gameBoard);
        while (1){
    printf("How many human players [1-2]?\n");
    fgets(numOfHumanPlayers,100000,stdin);
    int N= (int)strlen(numOfHumanPlayers);
    if (N>=3){
        printf ("Please enter valid number of human players (1-2)\n");
        continue;
            }
    else if (numOfHumanPlayers[0]== '1'||numOfHumanPlayers[0]=='2')
        break;
    else if (numOfHumanPlayers[0]!= '1' && numOfHumanPlayers[0]!='2'){
        printf ("Please enter valid number of human players (1-2)\n");
        }
             }

        if (numOfHumanPlayers[0]=='2'){
            while ( hasWinner(gameBoard)==0 && isFull(gameBoard)==0){
            printGameBoard(gameBoard);
            printf("Player 1, please place your mark [1-9]:\n");
            placeMarkByHumanPlayer(gameBoard, CIRCLE);
                if (hasWinner(gameBoard)!=0){
                    printGameBoard(gameBoard);
                    printf ("Player 1 wins! Congratulations!\n");
                    break;
                }
                if (isFull(gameBoard)!=0){
                    printGameBoard(gameBoard);
                    printf ("Draw game!\n");
                    break;
                }
                printGameBoard(gameBoard);
                
            printf("Player 2, please place your mark [1-9]:\n");
            placeMarkByHumanPlayer(gameBoard, CROSS);
                if (hasWinner(gameBoard)!=0){
                    printGameBoard(gameBoard);
                    printf ("Player 2 wins! Congratulations!\n");
                    break;
                }
            }
        }
        else if (numOfHumanPlayers[0]=='1'){
            int count = 1;
            while ( hasWinner(gameBoard)==0 && isFull(gameBoard)==0){
            printGameBoard(gameBoard);
            printf("Player 1, please place your mark [1-9]:\n");
            placeMarkByHumanPlayer(gameBoard, CIRCLE);
                if (hasWinner(gameBoard)!=0){
                    printGameBoard(gameBoard);
                    printf ("Player 1 wins! Congratulations!\n");
                    break;
                }
                if (isFull(gameBoard)!=0){
                    printGameBoard(gameBoard);
                    printf ("Draw game!\n");
                    break;
                }
                printGameBoard(gameBoard);

            printf("Computer places the mark:\n");
                if (count ==1) firstmove(gameBoard);
                else {
                placeMarkByComputerPlayer(gameBoard);
                if (hasWinner(gameBoard)!=0){
                    printGameBoard(gameBoard);
                    printf ("Computer wins!\n");
                    break;
                }
                }
                count++;
            }
            
        }
    return 0;
}
