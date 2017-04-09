// ants.h
//
// Header file for the libants library
// For the purpose of handing in this project at TU/e
// Code below "/* start append */" is automatically generated. Do not change.

// List the headers that we want to flatten

/* begin headers */
/* cell.h */
/* command.h */
/* init.h */
/* map.h */
/* play.h */
/* types.h */
/* util.h */
/* vector.h */
/* world.h */
/* einde headers */

// Signal that we want the flattened header file to be appened below
// Any code added below this mark is deleted when this file is re-created

/* start append */
// ant_t is an ant
// vec2_t is a cartesian coordinate
typedef struct {
  uint16_t x : 16;
  uint16_t y : 16;
} vec2_t;

typedef struct ant_s {
  enum { taskIdle = 0, taskExplore = 1, taskGatherFood = 3 } task;

  bool alive : 1;
  vec2_t target;
  vec2_t position;
  uint8_t owner : 8;
} ant_t;

// hill_t is a hill
typedef struct {
  vec2_t position;
  uint8_t owner;
} hill_t;

// food_t is food
typedef struct { vec2_t position; } food_t;

// cell_t is a cell
typedef struct {
  enum {
    stateUnknown = 0,
    stateLand = 1,
    stateWater = 2,
    stateAnt = 3,
    stateHill = 4,
    stateAntOnHill = 5,
    stateFood = 6
  } state : 3;  // State of the cell

  union {
    ant_t *ant;
    hill_t *hill;
    food_t *food;
    void *empty;
  } content;

  uint16_t lastSeen;  // Turn in which this cell was last seen. Can be
                      // useful for strategy
} cell_t;

// cell_t methods
cell_t *newCell();
void destroyCell(cell_t *c);

// direction_t is any direction we want to move towards
typedef enum {
  dirNorth = 'N',
  dirSouth = 'S',
  dirWest = 'W',
  dirEast = 'E'
} direction_t;

// map_t is the worldmap
typedef struct {
  uint16_t width : 16;
  uint16_t height : 16;
  cell_t ***cells;
} map_t;

// map_t methods
map_t *newMap();
void printMap(map_t *m, FILE *out);
void destroyMap(map_t *m);
cell_t *getCellAt(map_t *m, long x, long y);

static inline bool strEqual(const char *a, const char *b) {
  return strcmp(a, b) == 0;
}

static inline long strToInt(const char *str) { return strtol(str, NULL, 10); }

// world_t holds general information about the game
typedef struct {
  map_t *map;  // Pointer to a 2D array

  uint16_t turns : 16;
  uint16_t viewRadius2 : 16;
  uint16_t viewRadius : 16;
  uint16_t attackRadius2 : 16;
  uint16_t spawnRadius2 : 16;
  uint32_t playerSeed : 16;
  uint32_t loadTime : 16;
  uint32_t turnTime : 16;

  uint8_t localPlayer : 8;

  uint32_t hillCount : 32;
  uint32_t foodCount : 32;
  uint16_t antCount : 16;

  ant_t **ants;
  hill_t **hills;
  food_t **foods;
} world_t;

// world_t methods
world_t *newWorld();
void destroyWorld(world_t *w);

void addHill(world_t *w, hill_t *h);
void addAnt(world_t *w, ant_t *a);
void addFood(world_t *w, food_t *f);

bool init(world_t *w);

bool play(world_t *w);
