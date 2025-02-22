#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h"

#define MAX_LENGTH 1000

typedef struct {
    int length;
    int value;
    int max_cut_count;  
} Piece;

Piece pieces[MAX_LENGTH];
int piece_count = 0;

// A functions that reads data in the file
void read_input_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    int length, value, max_cut_count;
    while (1) {
        // Reads the length, value, max_cut_count using fscanf
        if (fscanf(file, "%d, %d, %d", &length, &value, &max_cut_count) == 3) {
            pieces[piece_count].length = length;
            pieces[piece_count].value = value;
            pieces[piece_count].max_cut_count = max_cut_count;
            piece_count++;
        } else if (fscanf(file, "%d, %d", &length, &value) == 2) {
            // If there's no max_cut_count, set as 0
            pieces[piece_count].length = length;
            pieces[piece_count].value = value;
            pieces[piece_count].max_cut_count = 0;
            piece_count++;
        } else if (fscanf(file, "%d", &length) == 1) {
            // If there's only one value in a line (set max_cut_count as 0)
            fprintf(stderr, "Error: Only one value provided for length %d. Please enter both length and value.\n", length);
            exit(1);
        } else {
            break; // Reaches end of the file
        }
    }

    fclose(file);
}

// Dynamic Programming 
int cut_rod(int rod_length) { 
    if (rod_length == 0) return 0;
    
    int cached_value = cache_get(rod_length);
    if (cached_value != -1) return cached_value;

    int max_value = 0;
    for (int i = 0; i < piece_count; i++) {
        if (pieces[i].length <= rod_length) {
            int max_cuts = pieces[i].max_cut_count == 0 ? rod_length / pieces[i].length : pieces[i].max_cut_count;
            for (int cuts = 1; cuts <= max_cuts; cuts++) {
                int value = pieces[i].value * cuts + cut_rod(rod_length - pieces[i].length * cuts);
                if (value > max_value) max_value = value;
            }
        }
    }

    cache_put(rod_length, max_value);
    return max_value;
}

// Print Cutting Rules
void print_cutting_list(int rod_length) {
    int total_value = 0;
    while (rod_length > 0) {
        int best_piece = -1;
        int best_value = 0;

        for (int i = 0; i < piece_count; i++) {
            if (pieces[i].length <= rod_length) {
                int max_cuts = pieces[i].max_cut_count == 0 ? rod_length / pieces[i].length : pieces[i].max_cut_count;
                for (int cuts = 1; cuts <= max_cuts; cuts++) {
                    int value = pieces[i].value * cuts + cut_rod(rod_length - pieces[i].length * cuts);
                    if (value > best_value) {
                        best_value = value;
                        best_piece = i;
                    }
                }
            }
        }

        if (best_piece == -1) break;

        int num_pieces = rod_length / pieces[best_piece].length;
        int piece_length = pieces[best_piece].length;
        int piece_value = pieces[best_piece].value * num_pieces;

        printf("%d @ %d = %d\n", num_pieces, piece_length, piece_value);
        total_value += piece_value;
        rod_length %= piece_length;
    }

    printf("Remainder: %d\n", rod_length);
    printf("Value: %d\n", total_value);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    read_input_file(filename);
    cache_init();

    int rod_length;
    while (scanf("%d", &rod_length) == 1) {
        print_cutting_list(rod_length);
    }

    return 0;
}
