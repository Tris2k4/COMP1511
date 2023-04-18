// CS defence 
//
// This program was written by Tri Nguyen (z5481840)
// on 27/3/2023
//
// TODO: Description of program

#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAP_ROWS 6
#define MAP_COLUMNS 12

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// USER DEFINED TYPES  ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
enum land_type {
    GRASS,
    WATER,
    PATH_START,
    PATH_END,
    PATH_UP,
    PATH_RIGHT,
    PATH_DOWN,
    PATH_LEFT,
    TELEPORTER
};

enum entity {
    EMPTY,
    ENEMY,
    BASIC_TOWER,
    POWER_TOWER,
    FORTIFIED_TOWER,
};

struct tile {
    enum land_type land;
    enum entity entity;
    int n_enemies;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////  YOUR FUNCTION PROTOTYPE  /////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// TODO: Put your function prototypes here

////////////////////////////////////////////////////////////////////////////////
////////////////////// PROVIDED FUNCTION PROTOTYPE  ////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void initialise_map(struct tile map[MAP_ROWS][MAP_COLUMNS]);
void print_map(struct tile map[MAP_ROWS][MAP_COLUMNS], int lives, int money);
void print_tile(struct tile tile, int entity_print);
void valid_point(struct tile map[MAP_ROWS][MAP_COLUMNS], int x_lake, int y_lake, int h, int w, int lives, int money);
void path_creation(struct tile map[MAP_ROWS][MAP_COLUMNS], int start_x, int end_x, int start_y, int end_y, int lives, int money); 
void spawning_enemies(struct tile map[MAP_ROWS][MAP_COLUMNS], int x_start_coordinate, int y_start_coordinate, int initial_enemies, int lives, int money);
void moving_enemies(struct tile map[MAP_ROWS][MAP_COLUMNS], int x_start, int y_start, int initial_enemies, int movements, int lives, int money);
void rain(struct tile map[MAP_ROWS][MAP_COLUMNS], int x_rows, int y_rows, int x_2_rows, int y_2_cols, int lives, int money);
void move_enemies(struct tile map[MAP_ROWS][MAP_COLUMNS], int x_start, int y_start, int x_end, int y_end, int moving, int *enemies, int *lives, int money);
void tower_creation(struct tile map [MAP_ROWS][MAP_COLUMNS], int rows, int cols, int lives, int *money);
int tower_upgrade(struct tile map [MAP_ROWS][MAP_COLUMNS], int rows, int cols, int lives, int money);
int main(void) {
    // This `map` variable is a 2D array of `struct tile`s.
    // It is `MAP_ROWS` x `MAP_COLUMNS` in size (which is 6x12 for this
    // assignment!)
    struct tile map[MAP_ROWS][MAP_COLUMNS];

    // This will initialise all tiles in the map to have GRASS land and EMPTY
    // entity values.
    initialise_map(map);
    
    // TODO: Start writing code here!
    
    // TODO: Stage 1.1 - Scan in lives, money and start/ending points, then
    // print out the map!
    int lives, money;
    printf("Starting Lives: ");
    scanf("%d", &lives);
    printf("Starting Money($): ");
    scanf("%d", &money);
   
    int x_start_coordinate = 0, y_start_coordinate = 0;
    int x_end_coordinate = 0, y_end_coordinate = 0;

    printf("Start Point: ");
    scanf("%d%d", &x_start_coordinate, &y_start_coordinate);
    printf("End Point: ");
    scanf("%d%d", &x_end_coordinate, &y_end_coordinate);
    map[x_start_coordinate][y_start_coordinate].land = PATH_START;
    map[x_end_coordinate][y_end_coordinate].land = PATH_END;
    print_map(map, lives, money);
    
    // TODO: Stage 1.2 - Scan in the initial enemies. Make sure you change the
    // `entity` at the starting position to be ENEMY, and that you update the
    // `n_enemies` value at that position to be this scanned value!
    int initial_enemies = 0;
    printf("Initial Enemies: ");
    scanf("%d", &initial_enemies);

    if (initial_enemies > 0) {
        map[x_start_coordinate][y_start_coordinate].entity = ENEMY;
        map[x_start_coordinate][y_start_coordinate].n_enemies = initial_enemies;
    }
    
    print_map(map, lives, money);

    int x_lake_coordinate, y_lake_coordinate, height, width;
    printf("Enter Lake: ");
    scanf("%d %d %d %d", &x_lake_coordinate, &y_lake_coordinate, &height, &width);
    valid_point(map, x_lake_coordinate, y_lake_coordinate, height, width, lives, money);
    
    char letter;
    //TODO: Stage 2.1 - Path creation
    path_creation(map, x_start_coordinate, y_start_coordinate, x_end_coordinate, y_end_coordinate, lives, money);
    //TODO: Stage 2.2 & 2.3: Command Loop + Spawning Enemies and spawning towers
    printf("Enter Command: ");
    int enemies = 0;
    while (scanf(" %c", &letter) != EOF) {
        if (letter == 'e') {
            spawning_enemies(map, x_start_coordinate, y_start_coordinate, initial_enemies, lives, money);
        } else if (letter == 't') {
            int tower_rows, tower_cols;
            scanf("%d %d", &tower_rows, &tower_cols);
            tower_creation(map, tower_rows, tower_cols, lives, &money);
        } else if (letter == 'm') {
            int moving_number;
            scanf("%d", &moving_number);
            for (int i = 0; i < moving_number; i++) {
                move_enemies(map, x_start_coordinate, y_start_coordinate, x_end_coordinate, y_end_coordinate, moving_number, &enemies, &lives, money); 
            }
            print_map(map, lives, money);
            if (lives == 0) {
                break;
            }
        } else if (letter == 'u') {
            int upgrade_rows, upgrade_cols;
            scanf("%d %d", &upgrade_rows, &upgrade_cols);
            money = tower_upgrade(map, upgrade_rows, upgrade_cols, lives, money);
        } else if (letter == 'r') {
            int row_spacing, column_spacing, row_offset, column_offset;
            scanf("%d %d %d %d", &row_spacing, &column_spacing, &row_offset, &column_offset);
            //* rain(map, row_spacing, column_spacing, row_offset, column_offset, lives, money);
        }
        printf("Enter Command: ");
    }
    printf("\n");
    printf("Game Over!\n");
}
////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  YOUR FUNCTIONS //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// TODO: Put your functions here
// lake creation and valid point check
 void valid_point(struct tile map[MAP_ROWS][MAP_COLUMNS], int x_lake, int y_lake, int h, int w, int lives, int money) { 
    if (x_lake < 0 || y_lake < 0) {
        printf("Error: Lake out of bounds, ignoring...\n");
        print_map(map, lives, money);
    } else if (x_lake >= MAP_ROWS || y_lake >= MAP_COLUMNS)  {
        printf("Error: Lake out of bounds, ignoring...\n");
        print_map(map, lives, money);
    } else if ((x_lake + h) - 1 >= MAP_ROWS 
    || (y_lake + w) - 1 >= MAP_COLUMNS) {
        printf("Error: Lake out of bounds, ignoring...\n");
        print_map(map, lives, money);
    } else if ((x_lake + h) - 1 < 0 
    || (y_lake + w) - 1 < 0) {
        printf("Error: Lake out of bounds, ignoring...\n");
        print_map(map, lives, money);
    }
    else {
        for (int i = x_lake; i < x_lake + h; ++i) {
            for (int k = y_lake; k < y_lake + w; ++k) {
                map[i][k].land = WATER;
            }
        }
        print_map(map, lives, money);
    }
}


// path creation function

void path_creation(struct tile map[MAP_ROWS][MAP_COLUMNS], int start_x, int end_x, 
int start_y, int end_y, int lives, int money) {
    char direction;
    int i = 0;
    printf("Enter Path: ");
    while ((start_x != start_y 
    || end_x != end_y) && scanf(" %c", &direction) == 1 ) {
        if (direction == 'r') {
            map[start_x][end_x].land = PATH_RIGHT;
            end_x += 1;
        } else if (direction == 'l') {
            map[start_x][end_x].land = PATH_LEFT;
            end_x -= 1;
        } else if (direction == 'u') {
            map[start_x][end_x].land = PATH_UP;
            start_x -= 1;
        } else if (direction == 'd') {
            map[start_x][end_x].land = PATH_DOWN;
            start_x += 1;
        }
        map[start_x][end_x].land = PATH_END;
        i++;

    }
    print_map(map, lives, money);
}
// spawning enemies function
void spawning_enemies(struct tile map[MAP_ROWS][MAP_COLUMNS], int x_start_coordinate, int y_start_coordinate, int initial_enemies, int lives, int money) {
    int enemies = 0;
    scanf("%d", &enemies);
    map[x_start_coordinate][y_start_coordinate].entity = ENEMY;   
    map[x_start_coordinate][y_start_coordinate].n_enemies += enemies;         
    print_map(map, lives, money); 
}
// tower creation function
void tower_creation(struct tile map [MAP_ROWS][MAP_COLUMNS], int rows, int cols, int lives, int *money) {
    int tower_money = 200;
    if (map[rows][cols].land == WATER || map[rows][cols].land == PATH_UP 
    || map[rows][cols].land == PATH_DOWN || map[rows][cols].land == PATH_LEFT 
    || map[rows][cols].land == PATH_RIGHT 
    ||rows < 0 || cols < 0 || rows >= MAP_ROWS || cols >= MAP_COLUMNS || *money < tower_money) {
        printf("Error: Tower creation unsuccessful. Make sure you have at least $200 and that the tower is placed on a grass block with no entity.\n");
        print_map(map, lives, *money);
    }  else {
        map[rows][cols].entity = BASIC_TOWER;
        *money -= tower_money;
        printf("Tower successfully created!\n");
        print_map(map, lives, *money);
    }
}
// TODO:
// ! ask about how the return valued works
// ! change int money -> int m in the int tower_creation
// ! function declaration for tower creation does not change (however, the code is still able to process??)
// ! Fix code (HOW CAN WE STORE THE VALUES OF ENEMIES?) -> take that number of enemies and pass it through to the parameter of move_enemies function
// ! SMASH 3.1 3.3 && 3.4 
// ! if possible, smash stage 4
// TODO 3.1

void move_enemies(struct tile map[MAP_ROWS][MAP_COLUMNS], int x_start, int y_start, int x_end, int y_end, int moving, int *n_enemies, int *lives, int money) {
    int x_previous = 0;
    int y_previous = 0;
    int x_current = x_start;
    int y_current = y_start;
    while (x_end != x_start || y_end != y_start) {
        while (x_current != x_end || y_current != y_end) {
            x_previous = x_current;
            y_previous = y_current;
            if (map[x_current][y_current].land == PATH_UP) {
                x_current--;
            } else if (map[x_current][y_current].land == PATH_DOWN) {
                x_current++;
            } else if (map[x_current][y_current].land == PATH_RIGHT) {
                y_current++;
            } else if (map[x_current][y_current].land == PATH_LEFT) {
                y_current--;
            } 
        }

        if (map[x_current][y_current].land == PATH_END) {
            *lives -= map[x_previous][y_previous].n_enemies;
            *n_enemies -= map[x_previous][y_previous].n_enemies;
            map[x_previous][y_previous].entity = EMPTY;
            map[x_previous][y_previous].n_enemies = 0;
        }

        map[x_current][y_current].entity = map[x_previous][y_previous].entity;
        map[x_current][y_current].n_enemies = map[x_previous][y_previous].n_enemies;
        map[x_previous][y_previous].entity = EMPTY;
        map[x_previous][y_previous].n_enemies = 0;

        x_end = x_previous;
        y_end = y_previous;
        x_current = x_start;
        y_current = y_start;
    }
    
    printf("%d%d", x_previous, y_previous);
    printf("%d enemies reached the end!", *n_enemies);
}

// TODO 3.2
 // consider the case: money >= 300, money >= 500, and money >= 300 and it has fortified tower
int tower_upgrade(struct tile map [MAP_ROWS][MAP_COLUMNS], int rows, int cols, int lives, int money) {
    int power_tower_cost = 300;
    int fortified_tower_cost = 500;
    if (rows < 0 || cols < 0 || rows >= MAP_ROWS || cols >= MAP_COLUMNS) {
        printf("Error: Upgrade target is out-of-bounds.\n");
        print_map(map, lives, money);
    } else if (money < 300) {
        printf("Error: Insufficient Funds.\n");
        print_map(map, lives, money);
    } else if (money >= 300 && map[rows][cols].entity == BASIC_TOWER) {
        map[rows][cols].entity = POWER_TOWER;
        money -= power_tower_cost;
        printf("Upgrade Successful!\n");
        print_map(map, lives, money);
    } else if (money >= 500 && map[rows][cols].entity == POWER_TOWER) {
        map[rows][cols].entity = FORTIFIED_TOWER;
        money -= fortified_tower_cost;
        printf("Upgrade Successful!\n");
        print_map(map, lives, money);
    } else if (money >= 300 && map[rows][cols].entity == FORTIFIED_TOWER) {
        printf("Error: Tower cannot be upgraded further.\n");
        print_map(map, lives, money);
    } else if (map[rows][cols].entity != BASIC_TOWER) {
        printf("Error: Upgrade target contains no tower entity.\n");
        print_map(map, lives, money);
    }
    return money;
}
// TODO 3.3 
// * consider that rain can be only on GRASS
// ! x_rows and y_cols are > 0 and can exceed the size of map 
// ! x_2_rows and y_2_cols can be any integers and including negative integers
// ! basic tower and power tower can be destroyed by rain
// ! fortified tower can't be destroyed

//* Hint from friend for 3.4
// ! xài chia phần dư nhe. Gòi chia trg hợp row offset âm vs dương
// ! làm là cái điểm bắt đầu của row, nó sẽ khác đối cs trg hợp row offset âm và dương
// ! Nếu mà dương á thì lấy rowoffset % row spacing
// ! Nếu mà âm á -> làm choa nó dương
// ! Xong òi điểm bắt đầu sẽ là rowspacing - số dư này
// ! Ròi h coá đỉm bắt đầu của row vs col roài ông bỏ dô vòng lặp nữa là xong
// TODO 3.4
/*
void rain(struct tile map[MAP_ROWS][MAP_COLUMNS], int x_rows, int y_cols, int x_2_rows, int y_2_cols, int lives, int money) {
   if () {
        
   }
}
*/
////////////////////////////////////////////////////////////////////////////////
/////////////////////////// PROVIDED FUNCTIONS  ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/*
 * Initialises map tiles to contain GRASS land and EMPTY entity.
 * 
 * Parameters:
 *     map - The map to initialise.
 * Returns:
 *     Nothing.
 */
void initialise_map(struct tile map[MAP_ROWS][MAP_COLUMNS]) {
    for (int row = 0; row < MAP_ROWS; ++row) {
        for (int col = 0; col < MAP_COLUMNS; ++col) {
            map[row][col].land = GRASS;
            map[row][col].entity = EMPTY;
            map[row][col].n_enemies = 0;
        }
    }
}

/*
 * Prints all map tiles based on their value, with a header displaying lives
 * and money.
 * 
 * Parameters:
 *     map   - The map to print tiles from.
 *     lives - The number of lives to print with the map.
 *     money - The amount of money to print with the map.
 * Returns:
 *     Nothing.
 */
void print_map(struct tile map[MAP_ROWS][MAP_COLUMNS], int lives, int money) {
    printf("\nLives: %d Money: $%d\n", lives, money);
    for (int row = 0; row < MAP_ROWS * 2; ++row) {
        for (int col = 0; col < MAP_COLUMNS; ++col) {
            print_tile(map[row / 2][col], row % 2);
        }
        printf("\n");
    }
}

/*
 * Prints either the land or entity component of a single tile, based on
 * the `land_print` parameter;
 * 
 * Parameters:
 *     tile         - The tile to print the land/entity from
 *     land_print - Whether to print the land part of the tile or the entity
 *         part of the tile. If this value is 0, it prints the land, otherwise
 *         it prints the entity.
 * Returns:
 *     Nothing.
 */ 
void print_tile(struct tile tile, int land_print) {
    if (land_print) {
        if (tile.land == GRASS) {
            printf(" . ");
        } else if (tile.land == WATER) {
            printf(" ~ ");
        } else if (tile.land == PATH_START) {
            printf(" S ");
        } else if (tile.land == PATH_END) {
            printf(" E ");
        } else if (tile.land == PATH_UP) {
            printf(" ^ ");
        } else if (tile.land == PATH_RIGHT) {
            printf(" > ");
        } else if (tile.land == PATH_DOWN) {
            printf(" v ");
        } else if (tile.land == PATH_LEFT) {
            printf(" < ");
        } else if (tile.land == TELEPORTER) {
            printf("( )");
        } else {
            printf(" ? ");
        }
    } else {
        if (tile.entity == EMPTY) {
            printf("   ");
        } else if (tile.entity == ENEMY) {
            printf("%03d", tile.n_enemies);
        } else if (tile.entity == BASIC_TOWER) {
            printf("[B]");
        } else if (tile.entity == POWER_TOWER) {
            printf("[P]");
        } else if (tile.entity == FORTIFIED_TOWER) {
            printf("[F]");
        } else {
            printf(" ? ");
        }
    }
}

