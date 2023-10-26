#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define MAX_WORDS 30
#define MAX_WORDS_LENGTH 100
#define MAX_ATTEMPTS 5

int choose_category();
char* Generate_random_word_from_category(char table[MAX_WORDS][MAX_WORDS_LENGTH]);
void Initialize_randomly_selected_word (char selectedword[], char hiddenword[]);
int Evaluate_guess(char playerguess, char selectedword[], char hiddenword[]);

void main () {
    int User_selected_category = -1;
    int wrong_guesses_by_player = 0;
    char letter_guessed_by_player;

    char Asian_countries[MAX_WORDS][MAX_WORDS_LENGTH] = {"INDIA", "NEPAL", "BHUTAN", "SRILANKA", "BANGLADESH", "SINGAPORE", "LAOS", "KAZAKHSTAN", "CHINA", "JAPAN", "AFGHANISTAN", "INDONESIA", "MALAYSIA", "MYANMAR", "THAILAND", "MALDIVES", "PAKISTAN", "VIETNAM", "IRAN", "TURKEY", "CAMBODIA", "JORDAN", "ISRAEL", "KUWAIT", "OMAN", "QATAR", "BRUNEI"};
    char Indian_states[MAX_WORDS][MAX_WORDS_LENGTH] = {"ANDHRAPRADESH", "ASSAM", "ARUNACHALPRADESH", "BIHAR", "CHHATTISGARH", "GOA", "GUJARAT", "HARYANA", "HIMACHALPRADESH", "JHARKHAND", "KARNATAKA", "KERALA", "MADHYAPRADESH", "MAHARASHTRA", "MANIPUR", "MEGHALAYA", "MIZORAM", "NAGALAND", "ODISHA", "PUNJAB", "RAJASTHAN", "SIKKIM", "TAMILNADU", "TELANGANA", "TRIPURA", "UTTARPRADESH", "UTTARAKHAND", "WESTBENGAL"};
    char Animals_birds_and_fish[MAX_WORDS][MAX_WORDS_LENGTH] = {"ELEPHANT", "CROCODILE", "ALBATROSS", "ALLIGATOR", "PORCUPINE", "EMU", "EEL", "JACKAL", "HERMITCRAB", "ANTELOPE", "BEAVER", "CHIHUAHUA", "IGUANA", "CHINCHILLAS", "POSSUM", "BABOON", "LYNX", "PTARMIGAN", "BINTURONG", "CAPYBARA", "URUPLATUS", "MUDPUPPY", "KUSIMANSE", "UAKARI", "COELACANTH", "AXOLOTL", "PLATYPUS", "UOUOA"};
    
    char selected_category_words[MAX_WORDS][MAX_WORDS_LENGTH] = {""};
   
    char* random_selected_word;
    char Hiddenword[MAX_WORDS_LENGTH];
    
    do
    {
       User_selected_category =  choose_category(); 
    } while (User_selected_category == -1);

    switch (User_selected_category)
    {
        case 1: 
            memcpy(selected_category_words, Asian_countries, sizeof(Asian_countries));
            
            printf("You have selected Asian Countries. Cool, Tie your sneakers and be ready to jump into the game !!!\n");
            break;
        case 2:
            memcpy(selected_category_words, Indian_states, sizeof(Indian_states));
            
            printf("You have selected Indian States. Cool, Tie your sneakers and be ready to jump into the game !!!\n");
            break;
        case 3:
            memcpy(selected_category_words, Animals_birds_and_fish, sizeof(Animals_birds_and_fish));

            printf("You have selected Animals, birds and fish. Cool, Tie your sneakers and be ready to jump into the game !!!\n");
            break;
        default:
            break;
    }
    
    
    //strcpy(random_selected_word, selected_category_words[random_word]);
    random_selected_word = Generate_random_word_from_category(selected_category_words);
    Initialize_randomly_selected_word(random_selected_word, Hiddenword);

    // Main game Loop 
    while (wrong_guesses_by_player<MAX_ATTEMPTS)
    {
        printf("\n\n%s", Hiddenword);
        printf("\nGuess a letter for the hidden word:");

        scanf("%c", &letter_guessed_by_player);
        getc(stdin);
        letter_guessed_by_player = toupper(letter_guessed_by_player);
        fflush(stdin);

        if (Evaluate_guess(letter_guessed_by_player, random_selected_word, Hiddenword) == 0)
        {
            printf("\nNope!!! this isn't a part of the hidden word. Please try again! ");
            wrong_guesses_by_player++;
        }
        else
        {
            printf("\nWoohoo!!! You guessed the letter right! Keep on!\n");
        }
        
        // Output for notifying about the status of the game so far.....
        printf("You have %d ", MAX_ATTEMPTS - wrong_guesses_by_player);
        printf("attempts left!\n");

        if (strcmp(random_selected_word, Hiddenword) == 0)
        {
            printf("Congratulations!!! You got the word right!!\n");
            printf("The hidden word was : %s!\n", random_selected_word);
            break; 
        }   
    }
    if (wrong_guesses_by_player == MAX_ATTEMPTS)
    {
        printf("\nToo bad! You have been hanged!\n");
        printf("The hidden word was : %s!\n", random_selected_word);
    }
    
    getch();
 
}

int choose_category () 
{
   printf("Select the category of words to play with: \n");
   printf("Press '1' to select Asian countries.\n");
   printf("Press '2' to select Indian states.\n");
   printf("Press '3' to select AnimalS, birds and fish. \n");

   int user_input;
   scanf("%d", &user_input);
   getc(stdin);
   fflush(stdin);

   if (user_input > 0 && user_input < 4)
   {
        return user_input;
   }
   else 
   {
        printf("INVALID INPUT. Please try again!\n");
        return -1;    
   }
}

char* Generate_random_word_from_category(char table[MAX_WORDS][MAX_WORDS_LENGTH])
{
    srand(time (NULL));
    int random_word = rand() %MAX_WORDS;
    return (char*)table[random_word]; 
}

void Initialize_randomly_selected_word(char selectedword[], char hiddenword[])
{
    int index;
    int word_length = strlen(selectedword);

    if (word_length >3 )
    {
        for (index = 0; index < word_length; index++)
        {
            hiddenword[index] = '-'; 
        }
        hiddenword[index] = '\0';
        
    }
     
}

int Evaluate_guess(char playerguess, char selectedword[], char hiddenword[])
{
    int index;
    int outcome = 0;

    for ( index = 0; selectedword[index] != '\0'; index++)
    {
        // checking whetherr the word has been guessed or not!!!
        if (playerguess == hiddenword[index])
        {
            return 0;
        }
        
        // chhecking whether the guess matches any character in the selected word
        if (playerguess == selectedword[index])
        {
            hiddenword[index] = playerguess;
            outcome++;
        }
        
    }
    return outcome;
}
