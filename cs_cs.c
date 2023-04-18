// Program name
//
// This program was written by Tri Nguyen (z5481840)
// on [/4/2023]
//
// TODO: Description of program


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

////////////////////////////////////////////////////////////////////////////////
///////////////////////////      Contants       ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Provided constants
#define ID_SIZE 6

// Provided enums
enum carriage_type {INVALID_TYPE, PASSENGER, BUFFET, RESTROOM, FIRST_CLASS};

// TODO: Your #defines/enums can go here:


////////////////////////////////////////////////////////////////////////////////
/////////////////////////// USER DEFINED TYPES  ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



// A Train Carriage
struct carriage {
    // carriage id in the form #"N1002", unique, null terminated
    char carriage_id[ID_SIZE];
    //  Type of the carriage
    enum carriage_type type;
    // Maximum number of passengers 
    int capacity;
    // Current number of passengers
    int occupancy;

    struct carriage *next;
};

// TODO: Any additional structs you want to add can go here:
struct train {
    int train_num;
    struct carriage *carriages;
    // Feel free to add more fields here if you want.
    struct train *next;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////// PROVIDED FUNCTION PROTOTYPE  ////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void print_usage(void);
void print_carriage(struct carriage *carriage);
void scan_id(char id_buffer[ID_SIZE]);
enum carriage_type scan_type(void);
void print_train_summary(
    int is_selected, 
    int n, 
    int capacity, 
    int occupancy,
    int num_carriages
);
int compare_double(double n1, double n2);

// Additional provided function prototypes
// You won't need to use these functions!
// We use just them to implement some of the provided helper functions.
int scan_token(char *buffer, int buffer_size);
char *type_to_string(enum carriage_type type);
enum carriage_type string_to_type(char *type_str);

////////////////////////////////////////////////////////////////////////////////
////////////////////////  YOUR FUNCTION PROTOTYPE  /////////////////////////////
////////////////////////////////////////////////////////////////////////////////
struct carriage *create_carriage(
    char id[ID_SIZE], 
    enum carriage_type type,
    int capacity
);
// TODO: Put your function prototypes here
//struct carriage *carriage_print(struct carriage *information);
//struct node *head(char id[ID_SIZE], enum carriage_type type, int capacity);
//void print_nodes(struct carriage *head);
int check_1(char id[ID_SIZE], struct carriage **head);
int check_2(int capacity);
int check_3(enum carriage_type type);
struct carriage *join_train(char id[ID_SIZE], 
    enum carriage_type type,
    int capacity,
    struct carriage **head);
struct carriage *join_train_2(int position, 
    char id[ID_SIZE], 
    enum carriage_type type,
    int capacity,
    struct carriage **head);
struct carriage *insert_head( 
    char id[ID_SIZE], 
    enum carriage_type type,
    int capacity,
    struct carriage **head);
struct carriage *insert_tail( 
    char id[ID_SIZE], 
    enum carriage_type type,
    int capacity,
    struct carriage **head);
struct carriage *insert_nth(
    char id[ID_SIZE], 
    enum carriage_type type,
    int capacity,
    struct carriage **head);
struct carriage *add_passenger(char id[ID_SIZE], 
    int passenger, 
    struct carriage **head);
struct carriage *remove_passenger(char id[ID_SIZE],
    int passenger, 
    struct carriage **head);
struct carriage *check_carriage_exist(struct carriage *head, 
    char id[ID_SIZE]);
struct train *new_empty_train(struct train *head);
struct train *create_train(void);
struct carriage *remove_carriage(char id[ID_SIZE], struct carriage **head);
struct train *remove_train(struct train **head, struct train *selected);
void move_passenger(char source_id[ID_SIZE], 
    char destination_id[ID_SIZE],
    int move, 
    struct carriage *head);
void count_total(struct carriage **head);
void count_passenger(char start_id[ID_SIZE], 
    char end_id[ID_SIZE], 
    struct carriage **head);
void free_carriages(struct carriage **head);
int count_position(struct train **head);
int count_capacity(struct carriage **head);
int count_carriages(struct carriage **head);
int count_occupancy(struct carriage **head);
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int main(void) {
    char letter;
    printf("Welcome to Carriage Simulator\n");
    printf("All aboard!\n");
    char id[ID_SIZE];
    enum carriage_type type;
    int capacity;
    struct carriage *print_carr;
    struct train *trains = create_train();
    struct train *selected = trains;

    // TODO: Start stage 1.2 here!
    printf("Enter command: ");
    while (scanf(" %c", &letter) != EOF) {
        if (letter == '?') {
            print_usage();
        } else if (letter == 'a') {
        // Create variables to scan arguments into
            // We receive the arguments in the order: [carriage_id] [type] [capacity]
            // 1. Scan id first
            
            scan_id(id);
            // 2. Then scan the carriage type
            type = scan_type();
            // 3. Then scan the capacity. We can just use scanf() for this
            scanf("%d", &capacity);

            if (check_3(type) == 0) {
                printf("ERROR: Invalid carriage type\n");
            }

            else if (check_2(capacity) == 0) {
                printf("ERROR: Capacity should be between 1 and 999\n");
            }

            else if (check_1(id, &selected->carriages) == 0) {
                printf("ERROR: a carriage with id: '%s' already exists in this train\n", id);
            }

            if (check_3(type) == 1 && check_2(capacity) == 1 && check_1(id, &selected->carriages) == 1 ) {
                join_train(id, type, capacity, &selected->carriages);
            }
            
        } else if (letter == 'p') { 
            print_carr = selected->carriages;
            if (print_carr == NULL) {
                printf("This train is empty!\n");
            } else {
                while (print_carr != NULL) {
                    print_carriage(print_carr);
                    print_carr = print_carr->next;
                }
            }
        } else if (letter == 'i') {
            int n;
            scanf("%d", &n);
            scan_id(id);
            type = scan_type();
            scanf("%d", &capacity);
            if (n < 0) {
                printf("ERROR: n must be at least 0\n");
            } else if (check_3(type) == 0) {
                printf("ERROR: Invalid carriage type\n");
            } else if (check_2(capacity) == 0) {
                printf("ERROR: Capacity should be between 1 and 999\n");
            } else if (check_1(id, &selected->carriages) == 0) {
                printf("ERROR: a carriage with id: '%s' already exists in this train\n", id);
            } else if (n == 0 || selected->carriages == NULL) {
                selected->carriages = insert_head(id, type, capacity, &selected->carriages);
            } else {
                int count = 1;
                struct carriage *new_node = create_carriage(id, type, capacity);
                struct carriage *current = selected->carriages;
                while (current != NULL && count < n) {
                    count++;
                    current = current->next;
                }
                if (current == NULL) {
                    selected->carriages = insert_tail(id, type, capacity, &selected->carriages);
                } else {
                    new_node->next = current->next;
                    current->next = new_node;
                    printf("Carriage: '%s' inserted!\n", id);
                }
            }
        } else if (letter == 's') {
            int passenger;
            scan_id(id);
            scanf("%d", &passenger);
            if (passenger <= 0) {
                printf("ERROR: n must be a positive integer\n");
            } else if (check_1(id, &selected->carriages) == 1) {
                printf("ERROR: No carriage exists with id: '%s'\n", id);
            } else {
                selected->carriages = add_passenger(id, passenger, &selected->carriages);
            }
        } else if (letter == 'd') {
            int passenger;
            scan_id(id);
            scanf("%d", &passenger);
            if (passenger <= 0) {
                printf("ERROR: n must be a positive integer\n");
            } else if (check_1(id, &selected->carriages) == 1) {
                printf("ERROR: No carriage exists with id: '%s'\n", id);
            } else {
                selected->carriages = remove_passenger(id, passenger, &selected->carriages);
            }
        } else if (letter == 'T') {
            count_total(&selected->carriages);
        } else if (letter == 'c') {
            char start_id[ID_SIZE]; scan_id(start_id);
            char end_id[ID_SIZE]; scan_id(end_id);
            count_passenger(start_id, end_id, &selected->carriages);
        } else if (letter == 'm') {
            char source_id[ID_SIZE]; scan_id(source_id);
            char destination_id[ID_SIZE]; scan_id(destination_id);
            int passenger; scanf("%d", &passenger);
            move_passenger(source_id, destination_id, passenger, selected->carriages);
        } else if (letter == 'N') {
            trains = new_empty_train(trains);
        } else if (letter == '>') {
            if (selected != NULL && selected->next != NULL) {
                selected = selected->next;
            }
        } else if (letter == '<') {
            if (trains != selected) {
                struct train *current = trains;
                while (current->next != selected) {
                    current = current->next;
                }
                selected = current;
           
            }
        } else if (letter == 'P') {
            int is_selected = 0;
            int position = 0;
            int occupancy, num_carriages;
         
            //capacity = 
            struct train *print_train = trains;
            while (print_train != NULL) {
                if (print_train == selected) {
                    is_selected = 1;
                } else {
                    is_selected = 0;
                }
                occupancy = count_occupancy(&print_train->carriages);
                capacity = count_capacity(&print_train->carriages);
                num_carriages = count_carriages(&print_train->carriages);
                print_train_summary(is_selected, position, capacity, occupancy, num_carriages);
                print_train = print_train->next;
                position++;
            }
            
        } else if (letter == 'r') {
            scan_id(id);
            selected->carriages = remove_carriage(id, &selected->carriages);
        } else if (letter == 'R') {
            selected = remove_train(&trains, selected);
        }
    
        printf("Enter command: ");
    }
    
    printf("\nGoodbye\n");

    
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  YOUR FUNCTIONS //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// STAGE 1.1

// TODO what does this function do?
// 
// Parameters:
//      TODO
// Returns:
//      TODO
//
struct carriage *create_carriage(
    char id[ID_SIZE], 
    enum carriage_type type,
    int capacity
) {
    // STAGE 1.1
    // TODO: malloc, initialise, and return a new carriage.
    struct carriage *information = malloc(sizeof(struct carriage));
    strcpy(information->carriage_id, id);
    information->capacity = capacity;
    information->occupancy = 0;
    information->next = NULL; 
    information->type = type; 
    return information; 
}

// TODO: Put your functions here

struct train *create_train(void) {
    struct train *new_train = malloc(sizeof(struct train));

    new_train->carriages = NULL;
    new_train->next = NULL;
    return new_train;   
}
struct train *new_empty_train(struct train *head) {
    struct train *current = create_train();
    current->next = head;
    return current;
}

struct carriage *join_train(char id[ID_SIZE], 
enum carriage_type type,
int capacity,
struct carriage **head) {
    if (*head == NULL) {
        *head = create_carriage(id, type, capacity);
        printf("Carriage: '%s' attached!\n", id);
    } else {
        struct carriage *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = create_carriage(id, type, capacity);
        printf("Carriage: '%s' attached!\n", id);
    }  

    return *head;
}

int check_1(char id[ID_SIZE], struct carriage **head) {
    struct carriage *current = *head;
    while (current != NULL) {
        if (strcmp(current->carriage_id, id) == 0) {
            return 0;
        }
        current = current->next;
    }
    return 1;
}
int check_2(int capacity) {
    if (capacity <= 0 || capacity >= 1000) {
        return 0;
    } else {
        return 1;
    }
}
int check_3(enum carriage_type type) {
    if (type == INVALID_TYPE) {
        return 0;
    }
    else {
        return 1;
    }
}
//return 1: true
//return 0: false

struct carriage *insert_head( 
    char id[ID_SIZE], 
    enum carriage_type type,
    int capacity,
    struct carriage **head) {
    struct carriage *new_head = create_carriage(id, type, capacity);
    new_head->next = *head;
    printf("Carriage: '%s' inserted!\n", id);
    return new_head;
}

struct carriage *insert_tail(
    char id[ID_SIZE], 
    enum carriage_type type,
    int capacity,
    struct carriage **head) {
    struct carriage *tail = create_carriage(id, type, capacity);
    struct carriage *current = *head;
    // if (current == NULL) {
    //     (*head)->next = current;
    // }
    while (current->next != NULL) {
        current = current->next;
    } 
    current->next = tail;
    printf("Carriage: '%s' inserted!\n", id);
    return *head;
}

struct carriage *add_passenger(char id[ID_SIZE], 
int passenger, 
struct carriage **head) {
    struct carriage *current = *head;
    while (strcmp(current->carriage_id, id) != 0) {
        current = current->next;
    }
    while (current != NULL && passenger > 0) {
        int empty_seat = current->capacity - (current->occupancy);
        if (passenger >= empty_seat && empty_seat != 0) {
            current->occupancy += empty_seat;
            passenger -= empty_seat;
            printf("%d passengers added to %s\n", empty_seat, current->carriage_id);
        } else if (passenger < empty_seat && empty_seat != 0) { 
            printf("%d passengers added to %s\n", passenger, current->carriage_id);
            current->occupancy += passenger;
            passenger = 0;
            
        }
        current = current->next;
    }
    if (passenger > 0) {
        printf("%d passengers could not be seated\n", passenger);
    }
    return *head;
}

struct carriage *remove_passenger(char id[ID_SIZE], 
int passenger, 
struct carriage **head) {
    struct carriage *current = *head;
    while (strcmp(current->carriage_id, id) != 0) {
        current = current->next;
    }
    if (current->occupancy < passenger) {
        printf("ERROR: Cannot remove %d passengers from %s\n", passenger, id);
        return *head;
    }
    current->occupancy -= passenger;
    printf("%d passengers removed from %s\n", passenger, id);
    return *head;
}


void count_total(struct carriage **head) {
    struct carriage *current = *head;
    int unoccupied = 0;
    int occupied = 0;
    while (current != NULL) {
        occupied += current->occupancy;
        unoccupied += current->capacity - (current->occupancy);
        current = current->next;
    }
    printf("Total occupancy: %d\n", occupied);
    printf("Unoccupied capacity: %d\n", unoccupied);
}

void count_passenger(char start_id[ID_SIZE], 
char end_id[ID_SIZE], 
struct carriage **head) {
    struct carriage *current = *head;
    int count = 0;
    int start = -1;
    int end = -1;
    //* check exist of start carriage and end carriage
    while (current != NULL) {
        if (strcmp(start_id, current->carriage_id) == 0) {
            start = count;
        }
        if (strcmp(end_id, current->carriage_id) == 0) {
            end = count;
        }
        count++;
        current = current->next;
    }

    if (start == -1) {
        printf("ERROR: No carriage exists with id: '%s'\n", start_id);
    } else if (end == -1) {
        printf("ERROR: No carriage exists with id: '%s'\n", end_id);
    } else if (start > end) {
        printf("ERROR: Carriages are in the wrong order\n");
        // return;
    } else {
        int occupancy = 0;
        int unoccupied = 0;
        current = *head;
        while (strcmp(start_id, current->carriage_id) != 0) {
            current = current->next;
        }
        while (strcmp(end_id, current->carriage_id) != 0) {
            occupancy += current->occupancy;
            unoccupied += current->capacity - (current->occupancy);
            current = current->next; 
        }
        occupancy += current->occupancy;
        unoccupied += current->capacity - (current->occupancy);
        printf("Occupancy: %d\n", occupancy);
        printf("Unoccupied: %d\n", unoccupied);
    }
}

void move_passenger(char source_id[ID_SIZE], 
char destination_id[ID_SIZE], int move, struct carriage *head) {
    struct carriage *source = check_carriage_exist(head, source_id);
    struct carriage *des = check_carriage_exist(head, destination_id);
    
    if (move <= 0) {
        printf("ERROR: n must be a positive integer\n");
    } else if (check_carriage_exist(head, source_id) == NULL) {
        printf("ERROR: No carriage exists with id: '%s'\n", source_id);
    } else if (move > source->occupancy) {
        printf("ERROR: Cannot remove %d passengers from %s\n", move, source->carriage_id);
    } else if (check_carriage_exist(head, destination_id) == NULL) {
        printf("ERROR: No carriage exists with id: '%s'\n", destination_id);
    } else if (move > des->capacity - des->occupancy && des->next == NULL) {
        printf("ERROR: not enough space to move passengers\n");
    }


    if (move > 0 && check_carriage_exist(head,source_id) != NULL 
    && move <= source->occupancy && check_carriage_exist(head, destination_id) != NULL
    && (move <= des->capacity - des->occupancy || des->next != NULL)) {

    
        int available_move = des->capacity - des->occupancy;
        int pass_move = 0;

    
        while (source->occupancy > 0 && pass_move < move) {
            if (available_move > 0) {
                int move_count = move - pass_move;

                if (move_count > available_move) {
                    move_count = available_move;
                }

                if (move_count > source->occupancy) {
                    move_count = source->occupancy;
                }

                source->occupancy -= move_count;
                des->occupancy += move_count;
                pass_move += move_count;
                available_move -= move_count;

                printf("%d passengers moved from %s to %s\n", move_count, source->carriage_id, des->carriage_id);
            }
            if (available_move == 0) {
                if (des->next == NULL) break;
                des = des->next;
                available_move = des->capacity - des->occupancy;
            }
        }
    }
    
}

struct carriage *check_carriage_exist(struct carriage *head, 
    char id[ID_SIZE]) {

    struct carriage *current = head;
    while (current != NULL) {
        if (strcmp(current->carriage_id, id) == 0) return current;
        current = current->next;
    }
    return NULL;
}

int count_capacity(struct carriage **head) {
    struct carriage *current = *head;
    int unoccupied = 0;
    while (current != NULL) {
        //occupied += current->occupancy;
        unoccupied += current->capacity;
        current = current->next;
    }
    return unoccupied;
}

int count_occupancy(struct carriage **head) {
    struct carriage *current = *head;
    int unoccupied = 0;
    int occupied = 0;
    while (current != NULL) {
        occupied += current->occupancy;
        unoccupied += current->capacity - (current->occupancy);
        current = current->next;
    }
    return occupied;
}
int count_carriages(struct carriage **head) {
    struct carriage *current = *head;
    int counter = 0;
    while (current != NULL) {
        counter++;
        current = current->next;
    } 
    return counter;
}
struct carriage *remove_carriage(char id[ID_SIZE], struct carriage **head) {
    if (check_carriage_exist(*head, id) == NULL) {
        printf("ERROR: No carriage exists with id: '%s'\n", id);
    }
    else {
        struct carriage *current = *head;
        //if (current->carriage_id == NULL) return NULL;
        if (strcmp(id, current->carriage_id) == 0) {
            struct carriage *old_head = *head;
            current = current->next;
            free(old_head);
            return current;
        } 
        struct carriage *previous = *head;
        //struct carriage *current = *head;
        while (current != NULL) {
            if (strcmp(current->carriage_id, id) == 0) {
                previous->next = current->next;
                free(current);
                current = previous->next;
                return *head;
            } else {
                previous = current;
                current = current->next;
            }
        }
    }
    return *head;
}

struct train *remove_train(struct train **head, struct train *selected) {
    if ((*head)->next == NULL) {
        free_carriages(&(*head)->carriages);
        return *head;
    }
    struct train *previous = *head;
    struct train *current = *head;
    while (current != selected) {
        previous = current;
        current = current->next;
    } 
    struct train *next = current->next;
    free_carriages(&current->carriages);
    free(current);
    if (previous != selected) {
        previous->next = next;
        return previous;
    } 
    *head = next;
    return next;
}

void free_carriages(struct carriage **head) {
    struct carriage *current = *head;
    while (current != NULL) {
        struct carriage *previous = current;
        current = current->next;
        free(previous);
    }
}
////////////////////////////////////////////////////////////////////////////////
///////////////////////////  PROVIDED FUNCTIONS  ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Prints the Carriage simulator usage instructions,
// displaying the different commands and their arguments.
//
void print_usage(void) {
    printf(
        "=====================[ Carriage Simulator ]=====================\n"
        "      ===============[     Usage Info     ]===============      \n"
        "  a [carriage_id] [type] [capacity]                             \n"
        "    Add a carriage to the train                                 \n"
        "  p                                                             \n"
        "    Print out all of the carriages in the train                 \n"
        "  i [n] [carriage_id] [type] [capacity]                         \n"
        "    Insert a carriage into the train at position `n`            \n"
        "                                                                \n"
        "  s [carriage_id] [n]                                           \n"
        "    Seat `n` passengers onto the train starting from carriage   \n"
        "    `carriage_id`                                               \n"
        "  d [carriage_id] [n]                                           \n"
        "    Remove `n` passengers from carriage `carriage_id`           \n"
        "  T                                                             \n"
        "    Display the total number of passengers and empty seats on   \n"
        "    the train                                                   \n"
        "  c [start_id] [end_id]                                         \n"
        "    Display the number of passengers and empty seats on between \n"
        "    carriage `start_id` and carriage `end_id`                   \n"
        "  m [source_id] [destination_id] [n]                            \n"
        "    Move `n` passengers from one carrige to another, without    \n"
        "    kicking anyone off the train.                               \n"
        "  h [carriage_id]                                               \n"
        "    Display the happiness of passengers in carriage             \n"
        "    `carriage_id`                                               \n"
        "  H                                                             \n"
        "    Display the average happiness of all passengers on the train\n"
        "                                                                \n"
        "  N                                                             \n"
        "    Create a new empty train                                    \n"
        "  >                                                             \n"
        "    Select the next train in the train list.                    \n"
        "  <                                                             \n"
        "    Select the previous train in the train list.                \n"
        "  P                                                             \n"
        "    Display the train list.                                     \n"
        "  r [carriage_id]                                               \n"
        "    Remove carriage `carriage_id` from the selected train.      \n"
        "  R                                                             \n"
        "    Remove the selected train.                                  \n"
        "                                                                \n"
        "  M                                                             \n"
        "    Merge the selected train with the train after it.           \n"
        "  S [n]                                                         \n"
        "    Split the current train into smaller trains.                \n"
        "  O                                                             \n"
        "    Rearrange passengers on the selected train to optimise      \n"
        "    happiness.                                                  \n"
        "  ?                                                             \n"
        "    Show help                                                   \n"
        "================================================================\n"
    );
}


// Scan in the a carriage id string into the provided buffer, placing 
// '\0' at the end.
//
// Parameters:
//      id_buffer - a char array of length ID_SIZE, which will be used
//                  to store the id.
// 
// Usage: 
// ```
//      char id[ID_SIZE];
//      scan_id(id);
// ```
void scan_id(char id_buffer[ID_SIZE]) {
    scan_token(id_buffer, ID_SIZE);
}


// Scans a string and converts it to a carriage_type.
//
// Returns:
//      The corresponding carriage_type, if the string was valid,
//      Otherwise, returns INVALID_TYPE.
// 
// Usage: 
// ```
//      enum carriage_type type = scan_type();
// ```
//
enum carriage_type scan_type(void) {
    // This 20 should be #defined, but we've kept it like this to
    // avoid adding additional constants to your code.
    char type[20];
    scan_token(type, 20);
    return string_to_type(type);
}


// Formats and prints out a train carriage struct,
//
// Parameters:
//      carriage - The struct carriage to print.
// 
void print_carriage(struct carriage *carriage) {
    int line_length = 20;

    char *id = carriage->carriage_id;
    char *type = type_to_string(carriage->type);

    printf(" ---------\\/--------- \n");

    int padding = line_length - strlen(id);
    printf("|%*s%s%*s|\n", padding / 2, "", id, (padding + 1) / 2, "");

    padding = line_length - 2 - strlen(type);
    printf("|%*s(%s)%*s|\n", padding / 2, "", type, (padding + 1) / 2, "");

    printf("| Occupancy: %3d/%-3d |\n", 
            carriage->occupancy, 
            carriage->capacity);
    printf(" ---------||--------- \n");
}


// Formats and prints out various information about a given train.
//
// Parameters:
//      is_selected - 1, if this train is the currently selected train, 
//                    0, otherwise.
//      n           - The position of the given train in the list of trains, 
//                    starting from 0.
//      capacity    - The total capacity of the given train.
//      capacity    - The total occupancy of the given train
//      num_carriages   - The number of carriages in the given train.
//
void print_train_summary(
    int is_selected, 
    int n, 
    int capacity, 
    int occupancy,
    int num_carriages
) {
    if (is_selected) {
        printf("--->Train #%d\n", n);
    } else  {
        printf("    Train #%d\n", n);
    }

    printf("        Carriages: %3d\n", num_carriages);
    printf("        Capacity : %3d/%-3d\n", occupancy, capacity);
    printf("    ----------------------\n");

}



// Compares two double (floating point) values. Value are considered
// equal if there is a less than 0.01 difference between them.
// Note: You should use this function if you need to compare doubles
//       to eachother, as it reduces inconsistencies caused by double
//       imprecision.
//
// Parameters:
//      n1 - a floating point value
//      n2 - a floating point value
// 
// Returns:
//      0, if the two values are considered equal.
//      a negative number, if n1 is less than n2,
//      a positive number, if n2 is less than n1,
//
// Usage: 
// ```
//      if (compare_double(n1, n2) > 0) {
//          printf("n1 greater than n2\n");
//      } else if (compare_double(n1, n2) == 0) {
//          printf("n1 is equal to n2\n");
//      } else {
//          printf("n1 is less than n2\n");
//      }
// ```
int compare_double(double n1, double n2) {
    double delta = 0.01;

    double difference = n1 - n2;
    // abs(n1 - n2) < delta 
    if (difference < delta && difference > -delta) {
        return 0;
    }
    if (n1 < n2) {
        return -1;
    }

    return 1;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////// ADDITIONAL PROVIDED FUNCTIONS ///////////////////////////
////////////////////////////////////////////////////////////////////////////////
// You don't need to use any of these, or understand how they work!
// We use them to implement some of the provided helper functions.

enum carriage_type string_to_type(char *type_str) {
    int len = strlen(type_str);

    if (strncasecmp(type_str, "passenger", len) == 0) {
        return PASSENGER;
    } 
    if (strncasecmp(type_str, "buffet", len) == 0) {
        return BUFFET;
    } 
    if (strncasecmp(type_str, "restroom", len) == 0) {
        return RESTROOM;
    }
    if (strncasecmp(type_str, "first_class", len) == 0) {
        return FIRST_CLASS;
    } 

    return INVALID_TYPE;
}


char *type_to_string(enum carriage_type type) {
    if (type == PASSENGER) {
        return "PASSENGER";
    } else if (type == BUFFET) {
        return "BUFFET";
    } else if (type == FIRST_CLASS) {
        return "FIRST CLASS";
    } else if (type == RESTROOM) {
        return "RESTROOM";
    }

    return "INVALID";
}

int scan_token(char *buffer, int buffer_size) {
    if (buffer_size == 0) {
        return 0;
    }

    char c;
    int i = 0;
    int num_scanned = 0;

    // consume all leading whitespace
    scanf(" ");

    // Scan in characters until whitespace
    while (i < buffer_size - 1
        && (num_scanned = scanf("%c", &c)) == 1 
        && !isspace(c)) {

        buffer[i++] = c;
    }

    if (i > 0) {
        buffer[i] = '\0';
    }

    return num_scanned;
}
