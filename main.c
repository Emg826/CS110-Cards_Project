#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define CARD_COUNT  52
#define CARDS_PER_SUIT 13
#define HAND_SIZE 5
#define NUMBER_OF_ROUNDS 1000000
#define OUTCOMES 4
#define NUMBER_OF_SHUFFLES 3

void single_hand_simulation(int* deck_array,int* tally_array);
void hand_analysis(int* deck_array,int* tally_array);
void end_probability_calculation(int* tally_array, double* probability_array);
int random_int(int min, int max);
void shuffle_ints(int* deck_array, int size);
int get_max_rank(int* array);



int main(){
    // Seeding srand()
    srand(time(NULL));

    int deck_array[52];
    // tally_array stores tallies for each of the 4 outcomes
    // 0th element for unique hands, 1st pairs, 2nd 3 of kind, 3rd 4 of kind
    int tally_array[OUTCOMES] = {0,0,0,0};
    double probability_array[OUTCOMES] = {0,0,0,0};

    // Fills array with values from 0 to 51
    for(int n = 0; n < CARD_COUNT; n++)
        deck_array[n] = n;

    int counter = 0;
    while(counter < NUMBER_OF_ROUNDS){
        single_hand_simulation(deck_array, tally_array);
        counter++;
    }

    end_probability_calculation(tally_array, probability_array);

    printf("Probability of a Unique Hand: %.4f%%\n", probability_array[0]);
    printf("Probability of a Pair: %.4f%%\n", probability_array[1]);
    printf("Probability of a 3 of a Kind: %.4f%%\n", probability_array[2]);
    printf("Probability of a 4 of a Kind: %.4f%%\n", probability_array[3]);
}



// Runs a single simulation of a hand, analyzes, and tallies
// for the categories being tracked
void single_hand_simulation(int* deck_array, int* tally_array){
    int shuffles = 0;

    while(shuffles < NUMBER_OF_SHUFFLES){
        shuffle_ints(deck_array, CARD_COUNT);
        shuffles++;
    }

    hand_analysis(deck_array, tally_array);
}



// Analyzes a given hand and tallies accordingly
void hand_analysis(int* deck_array, int* tally_array){
    int rank_counts_array[CARDS_PER_SUIT] = {0,0,0,0,0,0,0,0,0,0,0,0,0};

    // For loop goes through each of the first 5 elements and finds rank
    for (int i = 0; i < HAND_SIZE; i++){
        int rank_i = deck_array[i] % CARDS_PER_SUIT;
        rank_counts_array[rank_i]++;
    }

    // Function get_max_rank finds most frequent rank in rank_counts_array
    double max = get_max_rank(rank_counts_array);

    // If the hand is unique
    if(max == 1)
        tally_array[0]++;
    // If there is a pair
    if(max == 2)
        tally_array[1]++;
    // If there is a 3 of a kind
    if(max == 3)
        tally_array[2]++;
    // If there is a 4 of a kind
    if(max == 4)
        tally_array[3]++;
}



// Gets the maximum value in array
int get_max_rank(int* array){
    int current_max = 0;

    for(int x = 0; x < CARDS_PER_SUIT; x++){
        if(array[x] >= current_max)
            current_max = array[x];
    }

    return current_max;
}



// Calculates the probability of each category based on tallies and # of rounds
void end_probability_calculation(int* tally_array, double* probability_array){
    for(int k = 0; k <= OUTCOMES; k++)
        probability_array[k] = 100.0 * (tally_array[k] / (double) NUMBER_OF_ROUNDS);
}



int random_int(int min, int max){
    int number_of_possible_values = max - min + 1;
    int random_number;

    if(min >= 0)
        random_number = rand() % number_of_possible_values + min;

    return random_number;
}


// Shuffles an array
void shuffle_ints(int* deck_array, int size){
    int temp_number;

    for(int i = 0; i <= size - 2; i++){
        int j = random_int(i, size - 1);
        temp_number = deck_array[i];
        deck_array[i] = deck_array[j];
        deck_array[j] = temp_number;
    }
}
