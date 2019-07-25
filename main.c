/*
 * API Project
 * Marco Mandelli
 * 24/07/2019 - start
 */

/*
 * Libraries
 */
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

/*
 * Defines
 */
#define COMMAND_READ_SIZE 500
#define ENTITY_ID_SIZE 500
#define RELATIONS_ID_SIZE 500
#define RED 0
#define BLACK 1
#define HASH_TABLE_SIZE 50
#define NOT_FOUND -1

/*
/	Typedef
*/
typedef struct binaryTreeRelTypes binaryTreeRelTypes_t;
typedef struct binaryTreeEntities binaryTreeEntities_t;
typedef struct binaryTreeEntitiesDest binaryTreeEntitiesDest_t;
typedef struct hashEntitiesOrig hashEntitiesOrig_t;

// RB tree structs
struct binaryTreeRelTypes {
    struct binaryTreeRelTypes *p;
    char id[RELATIONS_ID_SIZE];
    binaryTreeEntitiesDest_t *destTreeRoot;
    binaryTreeEntitiesDest_t *maxDestRoot;
    int maxRelations;
    _Bool color;
    struct binaryTreeRelTypes *left;
    struct binaryTreeRelTypes *right;
};

// RB tree structs
struct binaryTreeEntities {
    struct binaryTreeEntities *p;
    char id[ENTITY_ID_SIZE];
    _Bool color;
    struct binaryTreeEntities *left;
    struct binaryTreeEntities *right;
};

struct hashEntitiesOrig {
    char *id;
};

struct binaryTreeEntitiesDest {
    struct binaryTreeEntitiesDest *p;
    char *id;
    hashEntitiesOrig_t *hashDest[HASH_TABLE_SIZE];
    int relationsNum;
    _Bool color;
    struct binaryTreeEntitiesDest *left;
    struct binaryTreeEntitiesDest *right;
};

/*
/	Function prototypes
*/

// Command management
void addEntManager();

void delEntManager();

void addRelManager();

void delRelManager();

void reportManager();

// RB Trees relative functions

// Rel types trees
binaryTreeRelTypes_t *rbTreeRelTypesSearch(binaryTreeRelTypes_t *x, char *k);

binaryTreeRelTypes_t *rbTreeRelTypesMinimum(binaryTreeRelTypes_t *x);

binaryTreeRelTypes_t *rbTreeRelTypesMaximum(binaryTreeRelTypes_t *x);

binaryTreeRelTypes_t *rbTreeRelTypesSuccessor(binaryTreeRelTypes_t *x);

binaryTreeRelTypes_t *rbTreeRelTypesPredecessor(binaryTreeRelTypes_t *x);

void rbTreeRelTypesLeftRotate(binaryTreeRelTypes_t **T, binaryTreeRelTypes_t *x);

void rbTreeRelTypesRightRotate(binaryTreeRelTypes_t **T, binaryTreeRelTypes_t *x);

void rbTreeRelTypesInsert(binaryTreeRelTypes_t **T, binaryTreeRelTypes_t *z);

void rbTreeRelTypesInsertFixup(binaryTreeRelTypes_t **T, binaryTreeRelTypes_t *z);

binaryTreeRelTypes_t *rbTreeRelTypesDelete(binaryTreeRelTypes_t **T, binaryTreeRelTypes_t *z);

void rbTreeRelTypesDeleteFixup(binaryTreeRelTypes_t **T, binaryTreeRelTypes_t *x);

void rbTreeRelTypesPurge(binaryTreeRelTypes_t *T);

// Entities trees

binaryTreeEntities_t *rbTreeEntitiesSearch(binaryTreeEntities_t *x, char *k);

binaryTreeEntities_t *rbTreeEntitiesMinimum(binaryTreeEntities_t *x);

binaryTreeEntities_t *rbTreeEntitiesMaximum(binaryTreeEntities_t *x);

binaryTreeEntities_t *rbTreeEntitiesSuccessor(binaryTreeEntities_t *x);

binaryTreeEntities_t *rbTreeEntitiesPredecessor(binaryTreeEntities_t *x);

void rbTreeEntitiesLeftRotate(binaryTreeEntities_t **T, binaryTreeEntities_t *x);

void rbTreeEntitiesRightRotate(binaryTreeEntities_t **T, binaryTreeEntities_t *x);

void rbTreeEntitiesInsert(binaryTreeEntities_t **T, binaryTreeEntities_t *z);

void rbTreeEntitiesInsertFixup(binaryTreeEntities_t **T, binaryTreeEntities_t *z);

binaryTreeEntities_t *rbTreeEntitiesDelete(binaryTreeEntities_t **T, binaryTreeEntities_t *z);

void rbTreeEntitiesDeleteFixup(binaryTreeEntities_t **T, binaryTreeEntities_t *x);

void rbTreeEntitiesPurge(binaryTreeEntities_t *T);

// Dest entities trees

binaryTreeEntitiesDest_t *rbTreeEntitiesDestSearch(binaryTreeEntitiesDest_t *x, char *k);

binaryTreeEntitiesDest_t *rbTreeEntitiesDestMinimum(binaryTreeEntitiesDest_t *x);

binaryTreeEntitiesDest_t *rbTreeEntitiesDestMaximum(binaryTreeEntitiesDest_t *x);

binaryTreeEntitiesDest_t *rbTreeEntitiesDestSuccessor(binaryTreeEntitiesDest_t *x);

binaryTreeEntitiesDest_t *rbTreeEntitiesDestPredecessor(binaryTreeEntitiesDest_t *x);

void rbTreeEntitiesDestLeftRotate(binaryTreeEntitiesDest_t **T, binaryTreeEntitiesDest_t *x);

void rbTreeEntitiesDestRightRotate(binaryTreeEntitiesDest_t **T, binaryTreeEntitiesDest_t *x);

void rbTreeEntitiesDestInsert(binaryTreeEntitiesDest_t **T, binaryTreeEntitiesDest_t *z);

void rbTreeEntitiesDestInsertFixup(binaryTreeEntitiesDest_t **T, binaryTreeEntitiesDest_t *z);

binaryTreeEntitiesDest_t *rbTreeEntitiesDestDelete(binaryTreeEntitiesDest_t **T, binaryTreeEntitiesDest_t *z);

void rbTreeEntitiesDestDeleteFixup(binaryTreeEntitiesDest_t **T, binaryTreeEntitiesDest_t *x);

void rbTreeEntitiesDestPurge(binaryTreeEntitiesDest_t *T);

// Hash functions

inline int hash(hashEntitiesOrig_t *k, int i);

int hashDestInsert(hashEntitiesOrig_t **T, hashEntitiesOrig_t *k);

int hashDestSearch(hashEntitiesOrig_t **T, hashEntitiesOrig_t *k);

// Creating object and initializing functions

binaryTreeRelTypes_t *createRelType(char *idToSet);

binaryTreeEntities_t *createEntity(char *idToSet);

binaryTreeEntitiesDest_t *createEntityDest(binaryTreeRelTypes_t **relType, char *idToSet);

binaryTreeEntitiesDest_t *addEntityDestMax(binaryTreeRelTypes_t **relType, binaryTreeEntitiesDest_t *destToAdd);

hashEntitiesOrig_t *createHashOrig(binaryTreeEntitiesDest_t **destEnt, char *idToSet);


/*
 * Global variables
 */

binaryTreeRelTypes_t *binaryTreeRelTypesNIL;
binaryTreeRelTypes_t *relTypesRoot;

binaryTreeEntities_t *binaryTreeEntitiesNIL;
binaryTreeEntities_t *entitiesRoot;

binaryTreeEntitiesDest_t *binaryTreeEntitiesDestNIL;


int main() {
    relTypesRoot = malloc(sizeof(binaryTreeRelTypes_t));
    binaryTreeRelTypesNIL = malloc(sizeof(binaryTreeRelTypes_t));
    binaryTreeRelTypesNIL->left = binaryTreeRelTypesNIL;
    binaryTreeRelTypesNIL->right = binaryTreeRelTypesNIL;
    binaryTreeRelTypesNIL->p = binaryTreeRelTypesNIL;
    binaryTreeRelTypesNIL->color = BLACK;

    relTypesRoot = binaryTreeRelTypesNIL;

    entitiesRoot = malloc(sizeof(binaryTreeEntities_t));
    binaryTreeEntitiesNIL = malloc(sizeof(binaryTreeEntities_t));
    binaryTreeEntitiesNIL->p = binaryTreeEntitiesNIL;
    binaryTreeEntitiesNIL->left = binaryTreeEntitiesNIL;
    binaryTreeEntitiesNIL->right = binaryTreeEntitiesNIL;
    binaryTreeEntitiesNIL->color = BLACK;

    entitiesRoot = binaryTreeEntitiesNIL;

    binaryTreeEntitiesDestNIL = malloc(sizeof(binaryTreeEntitiesDest_t));
    binaryTreeEntitiesDestNIL->left = binaryTreeEntitiesDestNIL;
    binaryTreeEntitiesDestNIL->right = binaryTreeEntitiesDestNIL;
    binaryTreeEntitiesDestNIL->p = binaryTreeEntitiesDestNIL;
    binaryTreeEntitiesDestNIL->color = BLACK;

    for (;;) {
        char commandRead[COMMAND_READ_SIZE];
        scanf("%s", commandRead);
        if (strcmp(commandRead, "addent") == 0) {
            addEntManager();
        } else if (strcmp(commandRead, "delent") == 0) {
            delEntManager();
        } else if (strcmp(commandRead, "addrel") == 0) {
            addRelManager();
        } else if (strcmp(commandRead, "delrel") == 0) {
            delRelManager();
        } else if (strcmp(commandRead, "report") == 0) {
            reportManager();
        } else {
            free(relTypesRoot);
            free(entitiesRoot);
            return 0;
        }
    }
}

/*
 * COMMAND MANAGEMENT FUNCTIONS
 */

void addEntManager() {
    char idEntity[ENTITY_ID_SIZE];
    scanf("%s", idEntity); // Reading in buffer from stdin

    if (rbTreeEntitiesSearch(entitiesRoot, idEntity) ==
        binaryTreeEntitiesNIL) { // Go only if entity doesn't already exist (logn)
        binaryTreeEntities_t *newEntity = createEntity(idEntity); // Add the new entity to the entities tree
    }
}

void delEntManager() {

}

void addRelManager() {
    char idOrig[ENTITY_ID_SIZE];
    char idDest[ENTITY_ID_SIZE];
    char idRel[RELATIONS_ID_SIZE];

    scanf("%s", idOrig); // Reading from stdin
    scanf("%s", idDest);
    scanf("%s", idRel);

    binaryTreeEntities_t *checkExistence;
    checkExistence = rbTreeEntitiesSearch(entitiesRoot, idDest);
    if (checkExistence == binaryTreeEntitiesNIL) {
        return;
    }
    char *idDestRef = checkExistence->id; // Store the reference for later use
    checkExistence = rbTreeEntitiesSearch(entitiesRoot, idOrig);
    if (checkExistence == binaryTreeEntitiesNIL) {
        return;
    }
    char *idOrigRef = checkExistence->id; // Store the reference for later use

    binaryTreeRelTypes_t *relType = rbTreeRelTypesSearch(relTypesRoot, idRel);
    if (relType == binaryTreeRelTypesNIL) { // Relation type does not exist, add it
        //Add new relation tipe
        binaryTreeRelTypes_t *newRelType = createRelType(idRel);

        //Add dest to the new relation type
        binaryTreeEntitiesDest_t *newDest = createEntityDest(&newRelType, idDestRef);

        //Add orig to the dest
        hashEntitiesOrig_t *newOrig = createHashOrig(&newDest, idOrigRef);

        //Add the dest to the max dest tree
        addEntityDestMax(&newRelType, newDest);

        // Set maxRelations to the new rel created (1)
        newRelType->maxRelations = newDest->relationsNum;
        return;
    }

    // If i reach there so the rel type already exists, go into it and search for origin
    binaryTreeEntitiesDest_t *destinyEnt = rbTreeEntitiesDestSearch(relType->destTreeRoot, idDest);
    if (destinyEnt == binaryTreeEntitiesDestNIL) { // Relations dest doesn't exist, add it
        //Add dest to the existent rel type
        binaryTreeEntitiesDest_t *newDest = createEntityDest(&relType, idDestRef);

        //Add orig to the new dest
        hashEntitiesOrig_t *newOrig = createHashOrig(&newDest, idOrigRef);

        // Check if maxrelations is greater than 1
        if (relType->maxRelations < newDest->relationsNum) {
            rbTreeEntitiesDestPurge(relType->maxDestRoot);
            addEntityDestMax(&relType, newDest);
            relType->maxRelations = newDest->relationsNum;
        } else if (relType->maxRelations == newDest->relationsNum) { // If it's 1, add it to the max tree
            addEntityDestMax(&relType, newDest);
        }
        return;
    }

    //If i reach there the dest exist, check if the relations already exist
    hashEntitiesOrig_t *newOrig = createHashOrig(&destinyEnt, idOrigRef);

    if(newOrig != NULL) { // If it doesn't exist
        (destinyEnt->relationsNum)++; // Increase the relationsNum number accordingly
        // Check if maxRelations is greater than 1
        if (relType->maxRelations < destinyEnt->relationsNum) {
            rbTreeEntitiesDestPurge(relType->maxDestRoot); // Clean the tree
            rbTreeEntitiesDestInsert(&(relType->maxDestRoot), destinyEnt); // Add dest to the  maxTree
            relType->maxRelations = destinyEnt->relationsNum; // Set maxRelations to the new maxRelations value
        } else if (relType->maxRelations == destinyEnt->relationsNum) { // If it's 1, add it to the max tree
            rbTreeEntitiesDestInsert(&(relType->maxDestRoot), destinyEnt); // Add the value to the tree
        }
        return;
    }
}

void delRelManager() {

}

void reportManager() {
    if (relTypesRoot != binaryTreeRelTypesNIL) {
        binaryTreeRelTypes_t *relTypesWalk = rbTreeRelTypesMinimum(relTypesRoot); // Print rel type name
        do {
            fputs(relTypesWalk->id, stdout);
            binaryTreeEntitiesDest_t *destWalk = rbTreeEntitiesDestMinimum(
                    relTypesWalk->maxDestRoot); // Print dest names
            do {
                fputs(destWalk->id, stdout);
                destWalk = rbTreeEntitiesDestSuccessor(destWalk);
            } while (destWalk != binaryTreeEntitiesDestNIL);
            printf("%i", relTypesWalk->maxRelations);
            relTypesWalk = rbTreeRelTypesSuccessor(relTypesWalk);
        } while (relTypesWalk != binaryTreeRelTypesNIL);
    }
}

/*
 * RB TREES FUNCTIONS
 */

/*
 *  RELATIONS TYPE RB TREES
 */

/*
 * Iterative search in rb trees
 * Uses relations type struct, faster than recursive version
 * Check for string id alphabetical order
 */
binaryTreeRelTypes_t *rbTreeRelTypesSearch(binaryTreeRelTypes_t *x, char *k) {
    while ((x != binaryTreeRelTypesNIL) && (strncmp(k, x->id, RELATIONS_ID_SIZE) != 0)) {
        if (strncmp(k, x->id, RELATIONS_ID_SIZE) < 0) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    return x;
}

/*
 * Search for minimum of rb trees relation type
 */
binaryTreeRelTypes_t *rbTreeRelTypesMinimum(binaryTreeRelTypes_t *x) {
    while (x->left != binaryTreeRelTypesNIL) {
        x = x->left;
    }
    return x;
}

/*
 * Search for maximum of rb trees relation type
 */
binaryTreeRelTypes_t *rbTreeRelTypesMaximum(binaryTreeRelTypes_t *x) {
    while (x->right != binaryTreeRelTypesNIL) {
        x = x->right;
    }
    return x;
}

/*
 * Search for successor of rb trees relation type
 */
binaryTreeRelTypes_t *rbTreeRelTypesSuccessor(binaryTreeRelTypes_t *x) {
    if (x->right != binaryTreeRelTypesNIL) {
        return rbTreeRelTypesMinimum(x->right);
    }
    binaryTreeRelTypes_t *y = x->p;
    while ((y != binaryTreeRelTypesNIL) && (x == y->right)) {
        x = y;
        y = y->p;
    }
    return y;
}

/*
 * Search for predecessor of rb trees relation type
 */
binaryTreeRelTypes_t *rbTreeRelTypesPredecessor(binaryTreeRelTypes_t *x) {
    if (x->left != binaryTreeRelTypesNIL) {
        return rbTreeRelTypesMaximum(x->left);
    }
    binaryTreeRelTypes_t *y = x->p;
    while ((y != binaryTreeRelTypesNIL) && (x == y->left)) {
        x = y;
        y = y->p;
    }
    return y;
}


/*
 * Left rotate the rb tree for rel types
 */
void rbTreeRelTypesLeftRotate(binaryTreeRelTypes_t **T, binaryTreeRelTypes_t *x) {
    binaryTreeRelTypes_t *y = x->right;
    x->right = y->left;
    if (y->left != binaryTreeRelTypesNIL) {
        y->left->p = x;
    }
    y->p = x->p;
    if (x->p == binaryTreeRelTypesNIL) {
        *T = y;
    } else if (x == x->p->left) {
        x->p->left = y;
    } else {
        x->p->right = y;
    }
    y->left = x;
    x->p = y;
}

/*
 * Right rotate the rb tree for rel types
 */
void rbTreeRelTypesRightRotate(binaryTreeRelTypes_t **T, binaryTreeRelTypes_t *x) {
    binaryTreeRelTypes_t *y = x->left;
    x->left = y->right;
    if (y->right != binaryTreeRelTypesNIL) {
        y->right->p = x;
    }
    y->p = x->p;
    if (x->p == binaryTreeRelTypesNIL) {
        *T = y;
    } else if (x == x->p->right) {
        x->p->right = y;
    } else {
        x->p->left = y;
    }
    y->right = x;
    x->p = y;
}

/*
 * Insert value in rb trees
 */
void rbTreeRelTypesInsert(binaryTreeRelTypes_t **T, binaryTreeRelTypes_t *z) {
    binaryTreeRelTypes_t *y = binaryTreeRelTypesNIL;
    binaryTreeRelTypes_t *x = *T;
    while (x != binaryTreeRelTypesNIL) {
        y = x;
        if (strncmp(z->id, x->id, RELATIONS_ID_SIZE) < 0) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->p = y;
    if (y == binaryTreeRelTypesNIL) {
        *T = z;
    } else if (strncmp(z->id, y->id, RELATIONS_ID_SIZE) < 0) {
        y->left = z;
    } else {
        y->right = z;
    }
    z->left = binaryTreeRelTypesNIL;
    z->right = binaryTreeRelTypesNIL;
    z->color = RED;
    rbTreeRelTypesInsertFixup(T, z);
}

/*
 * Fixup insert value in rb trees
 */
void rbTreeRelTypesInsertFixup(binaryTreeRelTypes_t **T, binaryTreeRelTypes_t *z) {
    while (z->p->color == RED) {
        if (z->p == z->p->p->left) {
            binaryTreeRelTypes_t *y = z->p->p->right;
            if (y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else {
                if (z == z->p->right) {
                    z = z->p;
                    rbTreeRelTypesLeftRotate(T, z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                rbTreeRelTypesRightRotate(T, z->p->p);
            }
        } else {
            binaryTreeRelTypes_t *y = z->p->p->left;
            if (y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else {
                if (z == z->p->left) {
                    z = z->p;
                    rbTreeRelTypesRightRotate(T, z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                rbTreeRelTypesLeftRotate(T, z->p->p);
            }
        }
    }
    (*T)->color = BLACK;
}

/*
 * Delete rb trees selected value
 */

binaryTreeRelTypes_t *rbTreeRelTypesDelete(binaryTreeRelTypes_t **T, binaryTreeRelTypes_t *z) {
    binaryTreeRelTypes_t *y;
    binaryTreeRelTypes_t *x;
    if ((z->left == binaryTreeRelTypesNIL) || (z->right == binaryTreeRelTypesNIL)) {
        y = z;
    } else {
        y = rbTreeRelTypesSuccessor(z);
    }
    if (y->left != binaryTreeRelTypesNIL) {
        x = y->left;
    } else {
        x = y->right;
    }
    x->p = y->p;
    if (y->p == binaryTreeRelTypesNIL) {
        *T = x;
    } else if (y == y->p->left) {
        y->p->left = x;
    } else {
        y->p->right = x;
    }
    if (y != z) {
        strncpy(z->id, y->id, RELATIONS_ID_SIZE);
    }
    if (y->color == BLACK) {
        rbTreeRelTypesDeleteFixup(T, x);
    }
    return y;
}

/*
 * Fixup delete rb trees selected value
 */

void rbTreeRelTypesDeleteFixup(binaryTreeRelTypes_t **T, binaryTreeRelTypes_t *x) {
    binaryTreeRelTypes_t *w;
    while ((x != *T) && (x->color == BLACK)) {
        if (x == x->p->left) {
            w = x->p->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->p->color = RED;
                rbTreeRelTypesLeftRotate(T, x->p);
                w = x->p->right;
            }
            if ((w->left->color == BLACK) && (w->right->color == BLACK)) {
                w->color = RED;
                x = x->p;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rbTreeRelTypesRightRotate(T, w);
                    w = x->p->right;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->right->color = BLACK;
                rbTreeRelTypesLeftRotate(T, x->p);
                x = *T;
            }
        } else {
            w = x->p->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->p->color = RED;
                rbTreeRelTypesRightRotate(T, x->p);
                w = x->p->left;
            }
            if ((w->right->color == BLACK) && (w->left->color == BLACK)) {
                w->color = RED;
                x = x->p;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    rbTreeRelTypesLeftRotate(T, w);
                    w = x->p->left;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->left->color = BLACK;
                rbTreeRelTypesRightRotate(T, x->p);
                x = *T;
            }
        }
    }
    x->color = BLACK;
}

/*
 * Free all the tree memory
 */
void rbTreeRelTypesPurge(binaryTreeRelTypes_t *T) {
    if (T == binaryTreeRelTypesNIL) {
        return;
    }
    rbTreeRelTypesPurge(T->left); // Free left memory
    rbTreeRelTypesPurge(T->right); // Free right memory
    free(T);
}

/*
 *  ENTITIES TYPE RB TREES
 */

/*
 * Iterative search in rb trees
 * Uses relations type struct, faster than recursive version
 * Check for string id alphabetical order
 */
binaryTreeEntities_t *rbTreeEntitiesSearch(binaryTreeEntities_t *x, char *k) {
    while ((x != binaryTreeEntitiesNIL) && (strncmp(k, x->id, RELATIONS_ID_SIZE) != 0)) {
        if (strncmp(k, x->id, RELATIONS_ID_SIZE) < 0) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    return x;
}

/*
 * Search for minimum of rb trees entities type
 */
binaryTreeEntities_t *rbTreeEntitiesMinimum(binaryTreeEntities_t *x) {
    while (x->left != binaryTreeEntitiesNIL) {
        x = x->left;
    }
    return x;
}

/*
 * Search for maximum of rb trees entities type
 */
binaryTreeEntities_t *rbTreeEntitiesMaximum(binaryTreeEntities_t *x) {
    while (x->right != binaryTreeEntitiesNIL) {
        x = x->right;
    }
    return x;
}

/*
 * Search for successor of rb trees entities type
 */
binaryTreeEntities_t *rbTreeEntitiesSuccessor(binaryTreeEntities_t *x) {
    if (x->right != binaryTreeEntitiesNIL) {
        return rbTreeEntitiesMinimum(x->right);
    }
    binaryTreeEntities_t *y = x->p;
    while ((y != binaryTreeEntitiesNIL) && (x == y->right)) {
        x = y;
        y = y->p;
    }
    return y;
}

/*
 * Search for predecessor of rb trees entities type
 */
binaryTreeEntities_t *rbTreeEntitiesPredecessor(binaryTreeEntities_t *x) {
    if (x->left != binaryTreeEntitiesNIL) {
        return rbTreeEntitiesMaximum(x->left);
    }
    binaryTreeEntities_t *y = x->p;
    while ((y != binaryTreeEntitiesNIL) && (x == y->left)) {
        x = y;
        y = y->p;
    }
    return y;
}


/*
 * Left rotate the rb tree for entities types
 */
void rbTreeEntitiesLeftRotate(binaryTreeEntities_t **T, binaryTreeEntities_t *x) {
    binaryTreeEntities_t *y = x->right;
    x->right = y->left;
    if (y->left != binaryTreeEntitiesNIL) {
        y->left->p = x;
    }
    y->p = x->p;
    if (x->p == binaryTreeEntitiesNIL) {
        *T = y;
    } else if (x == x->p->left) {
        x->p->left = y;
    } else {
        x->p->right = y;
    }
    y->left = x;
    x->p = y;
}

/*
 * Right rotate the rb tree for entities types
 */
void rbTreeEntitiesRightRotate(binaryTreeEntities_t **T, binaryTreeEntities_t *x) {
    binaryTreeEntities_t *y = x->left;
    x->left = y->right;
    if (y->right != binaryTreeEntitiesNIL) {
        y->right->p = x;
    }
    y->p = x->p;
    if (x->p == binaryTreeEntitiesNIL) {
        *T = y;
    } else if (x == x->p->right) {
        x->p->right = y;
    } else {
        x->p->left = y;
    }
    y->right = x;
    x->p = y;
}

/*
 * Insert value in rb trees
 */
void rbTreeEntitiesInsert(binaryTreeEntities_t **T, binaryTreeEntities_t *z) {
    binaryTreeEntities_t *y = binaryTreeEntitiesNIL;
    binaryTreeEntities_t *x = *T;
    while (x != binaryTreeEntitiesNIL) {
        y = x;
        if (strncmp(z->id, x->id, RELATIONS_ID_SIZE) < 0) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->p = y;
    if (y == binaryTreeEntitiesNIL) {
        *T = z;
    } else if (strncmp(z->id, y->id, RELATIONS_ID_SIZE) < 0) {
        y->left = z;
    } else {
        y->right = z;
    }
    z->left = binaryTreeEntitiesNIL;
    z->right = binaryTreeEntitiesNIL;
    z->color = RED;
    rbTreeEntitiesInsertFixup(T, z);
}

/*
 * Fixup insert value in rb trees
 */
void rbTreeEntitiesInsertFixup(binaryTreeEntities_t **T, binaryTreeEntities_t *z) {
    while (z->p->color == RED) {
        if (z->p == z->p->p->left) {
            binaryTreeEntities_t *y = z->p->p->right;
            if (y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else {
                if (z == z->p->right) {
                    z = z->p;
                    rbTreeEntitiesLeftRotate(T, z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                rbTreeEntitiesRightRotate(T, z->p->p);
            }
        } else {
            binaryTreeEntities_t *y = z->p->p->left;
            if (y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else {
                if (z == z->p->left) {
                    z = z->p;
                    rbTreeEntitiesRightRotate(T, z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                rbTreeEntitiesLeftRotate(T, z->p->p);
            }
        }
    }
    (*T)->color = BLACK;
}

/*
 * Delete rb trees selected value
 */

binaryTreeEntities_t *rbTreeEntitiesDelete(binaryTreeEntities_t **T, binaryTreeEntities_t *z) {
    binaryTreeEntities_t *y;
    binaryTreeEntities_t *x;
    if ((z->left == binaryTreeEntitiesNIL) || (z->right == binaryTreeEntitiesNIL)) {
        y = z;
    } else {
        y = rbTreeEntitiesSuccessor(z);
    }
    if (y->left != binaryTreeEntitiesNIL) {
        x = y->left;
    } else {
        x = y->right;
    }
    x->p = y->p;
    if (y->p == binaryTreeEntitiesNIL) {
        *T = x;
    } else if (y == y->p->left) {
        y->p->left = x;
    } else {
        y->p->right = x;
    }
    if (y != z) {
        strncpy(z->id, y->id, RELATIONS_ID_SIZE);
    }
    if (y->color == BLACK) {
        rbTreeEntitiesDeleteFixup(T, x);
    }
    return y;
}

/*
 * Fixup delete rb trees selected value
 */

void rbTreeEntitiesDeleteFixup(binaryTreeEntities_t **T, binaryTreeEntities_t *x) {
    binaryTreeEntities_t *w;
    while ((x != *T) && (x->color == BLACK)) {
        if (x == x->p->left) {
            w = x->p->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->p->color = RED;
                rbTreeEntitiesLeftRotate(T, x->p);
                w = x->p->right;
            }
            if ((w->left->color == BLACK) && (w->right->color == BLACK)) {
                w->color = RED;
                x = x->p;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rbTreeEntitiesRightRotate(T, w);
                    w = x->p->right;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->right->color = BLACK;
                rbTreeEntitiesLeftRotate(T, x->p);
                x = *T;
            }
        } else {
            w = x->p->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->p->color = RED;
                rbTreeEntitiesRightRotate(T, x->p);
                w = x->p->left;
            }
            if ((w->right->color == BLACK) && (w->left->color == BLACK)) {
                w->color = RED;
                x = x->p;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    rbTreeEntitiesLeftRotate(T, w);
                    w = x->p->left;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->left->color = BLACK;
                rbTreeEntitiesLeftRotate(T, x->p);
                x = *T;
            }
        }
    }
    x->color = BLACK;
}

/*
 * Free all the tree memory
 */
void rbTreeEntitiesPurge(binaryTreeEntities_t *T) {
    if (T == binaryTreeEntitiesNIL) {
        return;
    }
    rbTreeEntitiesPurge(T->left); // Free left memory
    rbTreeEntitiesPurge(T->right); // Free right memory
    free(T);
}

/*
 *  ENTITIES DEST TYPE RB TREES
 */

/*
 * Iterative search in rb trees
 * Uses relations type struct, faster than recursive version
 * Check for string id alphabetical order
 */
binaryTreeEntitiesDest_t *rbTreeEntitiesDestSearch(binaryTreeEntitiesDest_t *x, char *k) {
    while ((x != binaryTreeEntitiesDestNIL) && (strncmp(k, x->id, RELATIONS_ID_SIZE) != 0)) {
        if (strncmp(k, x->id, RELATIONS_ID_SIZE) < 0) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    return x;
}

/*
 * Search for minimum of rb trees entities type
 */
binaryTreeEntitiesDest_t *rbTreeEntitiesDestMinimum(binaryTreeEntitiesDest_t *x) {
    while (x->left != binaryTreeEntitiesDestNIL) {
        x = x->left;
    }
    return x;
}

/*
 * Search for maximum of rb trees entities type
 */
binaryTreeEntitiesDest_t *rbTreeEntitiesDestMaximum(binaryTreeEntitiesDest_t *x) {
    while (x->right != binaryTreeEntitiesDestNIL) {
        x = x->right;
    }
    return x;
}

/*
 * Search for successor of rb trees entities type
 */
binaryTreeEntitiesDest_t *rbTreeEntitiesDestSuccessor(binaryTreeEntitiesDest_t *x) {
    if (x->right != binaryTreeEntitiesDestNIL) {
        return rbTreeEntitiesDestMinimum(x->right);
    }
    binaryTreeEntitiesDest_t *y = x->p;
    while ((y != binaryTreeEntitiesDestNIL) && (x == y->right)) {
        x = y;
        y = y->p;
    }
    return y;
}

/*
 * Search for predecessor of rb trees entities type
 */
binaryTreeEntitiesDest_t *rbTreeEntitiesDestPredecessor(binaryTreeEntitiesDest_t *x) {
    if (x->left != binaryTreeEntitiesDestNIL) {
        return rbTreeEntitiesDestMaximum(x->left);
    }
    binaryTreeEntitiesDest_t *y = x->p;
    while ((y != binaryTreeEntitiesDestNIL) && (x == y->left)) {
        x = y;
        y = y->p;
    }
    return y;
}


/*
 * Left rotate the rb tree for entities types
 */
void rbTreeEntitiesDestLeftRotate(binaryTreeEntitiesDest_t **T, binaryTreeEntitiesDest_t *x) {
    binaryTreeEntitiesDest_t *y = x->right;
    x->right = y->left;
    if (y->left != binaryTreeEntitiesDestNIL) {
        y->left->p = x;
    }
    y->p = x->p;
    if (x->p == binaryTreeEntitiesDestNIL) {
        *T = y;
    } else if (x == x->p->left) {
        x->p->left = y;
    } else {
        x->p->right = y;
    }
    y->left = x;
    x->p = y;
}

/*
 * Right rotate the rb tree for entities types
 */
void rbTreeEntitiesDestRightRotate(binaryTreeEntitiesDest_t **T, binaryTreeEntitiesDest_t *x) {
    binaryTreeEntitiesDest_t *y = x->left;
    x->left = y->right;
    if (y->right != binaryTreeEntitiesDestNIL) {
        y->right->p = x;
    }
    y->p = x->p;
    if (x->p == binaryTreeEntitiesDestNIL) {
        *T = y;
    } else if (x == x->p->right) {
        x->p->right = y;
    } else {
        x->p->left = y;
    }
    y->right = x;
    x->p = y;
}

/*
 * Insert value in rb trees
 */
void rbTreeEntitiesDestInsert(binaryTreeEntitiesDest_t **T, binaryTreeEntitiesDest_t *z) {
    binaryTreeEntitiesDest_t *y = binaryTreeEntitiesDestNIL;
    binaryTreeEntitiesDest_t *x = *T;
    while (x != binaryTreeEntitiesDestNIL) {
        y = x;
        if (strncmp(z->id, x->id, RELATIONS_ID_SIZE) < 0) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->p = y;
    if (y == binaryTreeEntitiesDestNIL) {
        *T = z;
    } else if (strncmp(z->id, y->id, RELATIONS_ID_SIZE) < 0) {
        y->left = z;
    } else {
        y->right = z;
    }
    z->left = binaryTreeEntitiesDestNIL;
    z->right = binaryTreeEntitiesDestNIL;
    z->color = RED;
    rbTreeEntitiesDestInsertFixup(T, z);
}

/*
 * Fixup insert value in rb trees
 */
void rbTreeEntitiesDestInsertFixup(binaryTreeEntitiesDest_t **T, binaryTreeEntitiesDest_t *z) {
    while (z->p->color == RED) {
        if (z->p == z->p->p->left) {
            binaryTreeEntitiesDest_t *y = z->p->p->right;
            if (y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else {
                if (z == z->p->right) {
                    z = z->p;
                    rbTreeEntitiesDestLeftRotate(T, z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                rbTreeEntitiesDestRightRotate(T, z->p->p);
            }
        } else {
            binaryTreeEntitiesDest_t *y = z->p->p->left;
            if (y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else {
                if (z == z->p->left) {
                    z = z->p;
                    rbTreeEntitiesDestRightRotate(T, z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                rbTreeEntitiesDestLeftRotate(T, z->p->p);
            }
        }
    }
    (*T)->color = BLACK;
}

/*
 * Delete rb trees selected value
 */

binaryTreeEntitiesDest_t *rbTreeEntitiesDestDelete(binaryTreeEntitiesDest_t **T, binaryTreeEntitiesDest_t *z) {
    binaryTreeEntitiesDest_t *y;
    binaryTreeEntitiesDest_t *x;
    if ((z->left == binaryTreeEntitiesDestNIL) || (z->right == binaryTreeEntitiesDestNIL)) {
        y = z;
    } else {
        y = rbTreeEntitiesDestSuccessor(z);
    }
    if (y->left != binaryTreeEntitiesDestNIL) {
        x = y->left;
    } else {
        x = y->right;
    }
    x->p = y->p;
    if (y->p == binaryTreeEntitiesDestNIL) {
        *T = x;
    } else if (y == y->p->left) {
        y->p->left = x;
    } else {
        y->p->right = x;
    }
    if (y != z) {
        strncpy(z->id, y->id, RELATIONS_ID_SIZE);
    }
    if (y->color == BLACK) {
        rbTreeEntitiesDestDeleteFixup(T, x);
    }
    return y;
}

/*
 * Fixup delete rb trees selected value
 */

void rbTreeEntitiesDestDeleteFixup(binaryTreeEntitiesDest_t **T, binaryTreeEntitiesDest_t *x) {
    binaryTreeEntitiesDest_t *w;
    while ((x != *T) && (x->color == BLACK)) {
        if (x == x->p->left) {
            w = x->p->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->p->color = RED;
                rbTreeEntitiesDestLeftRotate(T, x->p);
                w = x->p->right;
            }
            if ((w->left->color == BLACK) && (w->right->color == BLACK)) {
                w->color = RED;
                x = x->p;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rbTreeEntitiesDestRightRotate(T, w);
                    w = x->p->right;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->right->color = BLACK;
                rbTreeEntitiesDestLeftRotate(T, x->p);
                x = *T;
            }
        } else {
            w = x->p->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->p->color = RED;
                rbTreeEntitiesDestRightRotate(T, x->p);
                w = x->p->left;
            }
            if ((w->right->color == BLACK) && (w->left->color == BLACK)) {
                w->color = RED;
                x = x->p;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    rbTreeEntitiesDestLeftRotate(T, w);
                    w = x->p->left;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->left->color = BLACK;
                rbTreeEntitiesDestLeftRotate(T, x->p);
                x = *T;
            }
        }
    }
    x->color = BLACK;
}

/*
 * Free all the tree memory
 */
void rbTreeEntitiesDestPurge(binaryTreeEntitiesDest_t *T) {
    if (T == binaryTreeEntitiesDestNIL) {
        return;
    }
    rbTreeEntitiesDestPurge(T->left); // Free left memory
    rbTreeEntitiesDestPurge(T->right); // Free right memory
    free(T);
}

/*
 * HASHING FUNCTIONS
 */

/*
 * Insert a value in the hash
 */
int hash(hashEntitiesOrig_t *k, int i) {
    int res = 0;
    for (int j = 0; j < strlen(k->id); j++) {
        res = res + k->id[j];
    }
    res = (res * i) % HASH_TABLE_SIZE;
    return res;
}

int hashDestInsert(hashEntitiesOrig_t **T, hashEntitiesOrig_t *k) {
    int i = 0;
    do {
        int j = hash(k, i); // FUNZIONE DA CALCOLARE
        if (T[j] == NULL) {
            T[j] = k;
            return j;
        } else {
            i = i + 1;
        }
    } while (i != HASH_TABLE_SIZE);
    return -1;
}

int hashDestSearch(hashEntitiesOrig_t **T, hashEntitiesOrig_t *k) {
    int i = 0;
    int j;
    do {
        j = hash(k, i);
        if (T[j] == k) {
            return j;
        }
        i = i + 1;
    } while ((T[j] != NULL) && (i != HASH_TABLE_SIZE));
    return -1;
}

/*
 * CREATE AND INIT NODES FUNCTIONS
 */
binaryTreeRelTypes_t *createRelType(char *idToSet) {
    binaryTreeRelTypes_t *relType = malloc(sizeof(binaryTreeRelTypes_t));
    relType->destTreeRoot = binaryTreeEntitiesDestNIL;
    relType->maxDestRoot = binaryTreeEntitiesDestNIL;
    relType->maxRelations = 1;
    strncpy(relType->id, idToSet, RELATIONS_ID_SIZE);
    rbTreeRelTypesInsert(&relTypesRoot, relType);
    return relType;
}

binaryTreeEntities_t *createEntity(char *idToSet) {
    binaryTreeEntities_t *entity = malloc(sizeof(binaryTreeEntities_t));
    strncpy(entity->id, idToSet, ENTITY_ID_SIZE);
    rbTreeEntitiesInsert(&entitiesRoot, entity);
    return entity;
}

binaryTreeEntitiesDest_t *createEntityDest(binaryTreeRelTypes_t **relType, char *idToSet) {
    binaryTreeEntitiesDest_t *entityDest = malloc(sizeof(binaryTreeEntitiesDest_t));
    entityDest->id = idToSet;
    entityDest->relationsNum = 1;
    rbTreeEntitiesDestInsert(&((*relType)->destTreeRoot), entityDest);
    return entityDest;
}

binaryTreeEntitiesDest_t *addEntityDestMax(binaryTreeRelTypes_t **relType, binaryTreeEntitiesDest_t *destToAdd) {
    rbTreeEntitiesDestInsert(&((*relType)->maxDestRoot), destToAdd);
    return destToAdd;
}

hashEntitiesOrig_t *createHashOrig(binaryTreeEntitiesDest_t **destEnt, char *idToSet) {
    hashEntitiesOrig_t *newOrig = malloc(sizeof(hashEntitiesOrig_t));
    newOrig->id = idToSet;

    if (hashDestSearch((*destEnt)->hashDest, newOrig) == NOT_FOUND) { // Doesn't exist, add
        hashDestInsert((*destEnt)->hashDest, newOrig);
        return newOrig;
    }

    return NULL; // Already exists, nothing added
}