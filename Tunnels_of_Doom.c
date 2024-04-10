#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

/*
    This function takes a string, integer pointer and an array as a parameter and does the following:
        1. Checks if the string is either 'q' or 'Q', if so exits the app.
        2. Checks if the user input conatins three digits, if not shows an error message and exits the app.
        3. Checks if all the inputs by the user are numbers, if not shows an error message and exits the app.
        4. If the inputs passes all the above requirements, then the function takes the input from the string and stores in an int variable by dereferencing the integer pointer.
        5. Then stores all the digits of the user input in integer array for further operations.
*/
void inputValidator(char input[4], int *userInput, int userNumber[3] ){
    if ((strcmp(input, "q")) == 0 || (strcmp(input, "q") == 0)){
        printf("\nGood Bye!\n");
        exit(0);
    }
    if (strlen(input) != 3) {
        printf("Input does not contain three numbers.");
        exit(0);
    }
    for (int i = 0; i < 3; ++i) {
        if (!isdigit(input[i])) {
            printf("Input contains non-digit characters.");
            exit(0);
        }
    }
    *userInput = atoi(input);
    userNumber[0] =  floor(*userInput / 100);        
    userNumber[1] =  floor((*userInput/ 10) % 10);  
    userNumber[2] =  floor(*userInput % 10);
}


int main() {
    char userInput[3];
    do{
        int tries = 8;

        int num = rand() % (999 - 99 + 1) + 99; // Generate a random three digit value for every new game.
        int number[3];

        printf("\n%d\n", num);
        
        //The next three lines of code store every single digit of the randomly generated number in an integer array for further operations.
        number[0] =  floor(num / 100);        
        number[1] =  floor((num / 10) % 10);  
        number[2] =  floor(num % 10); 

        printf("\t\t\tTunnels of Doom\nEnter q or Q to quit.");
        do{
            int userInput;
            int userNumber[3];
            char input[4];

            printf("\n%d tries remaining, what's the code? ", tries);
            scanf("%3s", input);

            inputValidator(input, &userInput, userNumber); // Call the inputValidator() function to validate the input

            tries -= 1; // Decrease the amount of tries remaining by 1

            if (userInput == num){ // If the user inputs the right number
                printf("You Opened the Vault!");
                break;
            }else{
                char comparison[10];
                int arr[3]; 
                arr[0] = -1; arr[1] = -1; arr[2] = -1; // Intialize the array with -1 for further operations

                if (userInput < num) {strcpy(comparison, "Too Low"); } else{strcpy(comparison, "Too High"); } // Compare the user input and the generated number and assign too high or too low.
                int matchDigits = 0, k=0;
                
                // The following for loop is used to identify digits that are correct and in the right place. 
                for (int i = 0; i < sizeof(userNumber)/sizeof(userNumber[0]); i++){
                    if (userNumber[i] == number[i]){
                        matchDigits++;
                        arr[k++] = i;
                    }
                } 
                
                // The following for loop is used to identify digits that are correct and but in the wrong place. 
                int incorrectPlace = 0;
                for (int i = 0; i < sizeof(userNumber)/sizeof(userNumber[0]);i++){
                    for (int n = 0; n < sizeof(number)/sizeof(number[0]); n++){
                        if (n == arr[0] || n == arr[1] || n == arr[2] ){
                        }
                        else if (userNumber[i] == number[n]){
                            incorrectPlace+=1;
                            arr[k++] = n;
                        }
                    }
                }
                printf("%s, %d digits are correct and in the right place, %d digits are correct and in the wrong place.", comparison, matchDigits, incorrectPlace);

            }
            if (tries == 0){ // Check if the user have used all of its tries, if so break from the loop, display the secret code and start a new game.
                    printf("The vault shuts down permanently due to too many incorrect attempts. You failed to open the vault!\nThe secret code was %d", num);
                    break;
                }

        }while(tries >= 0);

    }while(1);
    
    return 0;
}
