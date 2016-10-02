//Written by Nick Sallinger
//for CS0449 with Dr.Misurda
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

int main() {

    char answer[20];
    char yes[4] = "yes";
    char guess[3];
    int colorstemp[4];
    char color_comp[4];
    char colors[4];
    int play = -1;
    int correctplace = 0;
    int correctcolor = 0;
    int cnt[] = {-1,-1,-1,-1};
    //bool winning = false;
    int attempt = 1;
    int i, j;

    printf("Welcome to Mastermind!\n\n");


    /*printf("Would you like to play?");
    scanf("%s", answer);

    if(strcmp(answer,yes) == 0){
       play = true;
    }ab
    else{

    }
     */
    play = 1;
    //seed and create rng


    while(play){

        if(play && attempt == 1) {
            srand((unsigned int) time(NULL));
//red orange yellow blue green purple
            colorstemp[0] = rand() % 6;
            colorstemp[1] = rand() % 6;
            colorstemp[2] = rand() % 6;
            colorstemp[3] = rand() % 6;

            for (i = 0; i < 4; i++) {
                if (colorstemp[i] == 0)
                    colors[i] = 'r';
                if (colorstemp[i] == 1)
                    colors[i] = 'o';
                if (colorstemp[i] == 2)
                    colors[i] = 'y';
                if (colorstemp[i] == 3)
                    colors[i] = 'b';
                if (colorstemp[i] == 4)
                    colors[i] = 'g';
                if (colorstemp[i] == 5)
                    colors[i] = 'p';
            }
        }

        printf("enter guess number %d: ", attempt);

        scanf("%s",guess);

        //computes correct places
        for(i = 0; i < 4; i++){
            if(guess[i] == colors[i])
                correctplace++;
        }

        for(i = 0; i < 4; i++){
            color_comp[i] = colors[i];
        }
       //computes correct colors
        for(i = 0; i < 4; i++) {
            for(j = 0; j < 4; j++){
                if(guess[i] == color_comp[j]){
                    color_comp[j] = 'x';
                    correctcolor++;
                    break;
                }
            }
        }
        printf("correct colors: %d\n", correctcolor);
        printf("correct place: %d\n", correctplace);

        if(correctplace == 4){
            printf("You win");
            play = 0;
            attempt = 11;
        }
        attempt++;
        correctcolor = 0;
        correctplace = 0;
        if(attempt == 11){
            play = 0;
            printf("Sorry you have lost\n");
            printf("Would you like to play again?\n");
            scanf("%s", answer);

            if(strcmp(answer,yes) == 0) {
                play = 1;
                attempt = 1;
            }
            else{
                printf("Thanks for playing!\n");
            }
        }
    }//end playing while




}
