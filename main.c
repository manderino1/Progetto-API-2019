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

/*
/	Typedef
*/
typedef struct entityDest entityDest_t;
typedef struct relationsType relationsType_t;
typedef struct entityOrigin entityOrigin_t;
typedef struct entity entity_t;
typedef struct binaryTreeRelTypes binaryTreeRelTypes_t;

// RB tree structs
struct binaryTreeRelTypes {
    struct binaryTreeRelTypes *p;
    char id[RELATIONS_ID_SIZE];
    int maxRelations;
    _Bool color;
    struct binaryTreeRelTypes *left;
    struct binaryTreeRelTypes *right;
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
binaryTreeRelTypes_t *rbTreeRelTypesSearch(binaryTreeRelTypes_t *x, char *k);

binaryTreeRelTypes_t *rbTreeRelTypesMinimum(binaryTreeRelTypes_t *x);

binaryTreeRelTypes_t *rbTreeRelTypesMaximum(binaryTreeRelTypes_t *x);

binaryTreeRelTypes_t *rbTreeRelTypesSuccessor(binaryTreeRelTypes_t *x);

binaryTreeRelTypes_t *rbTreeRelTypesPredecessor(binaryTreeRelTypes_t *x);

binaryTreeRelTypes_t *rbTreeRelTypesLeftRotate(binaryTreeRelTypes_t *T, binaryTreeRelTypes_t *x);

binaryTreeRelTypes_t *rbTreeRelTypesRightRotate(binaryTreeRelTypes_t *T, binaryTreeRelTypes_t *x);

binaryTreeRelTypes_t *rbTreeRelTypesInsert(binaryTreeRelTypes_t *T, binaryTreeRelTypes_t *z);

binaryTreeRelTypes_t *rbTreeRelTypesInsertFixup(binaryTreeRelTypes_t *T, binaryTreeRelTypes_t *z);

/*
 * Global variables
 */

binaryTreeRelTypes_t *binaryTreeRelNIL;


int main() {
    for (;;) {
        binaryTreeRelNIL = malloc(sizeof(binaryTreeRelTypes_t));
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
            return 0;
        }
    }
}

/*
 * Iterative search in rb trees
 * Uses relations type struct, faster than recursive version
 * Check for string id alphabetical order
 */
binaryTreeRelTypes_t *rbTreeRelTypesSearch(binaryTreeRelTypes_t *x, char *k) {
    while ((x != binaryTreeRelNIL) || (strncmp(k, x->id, RELATIONS_ID_SIZE) != 0)) {
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
    while (x->left != binaryTreeRelNIL) {
        x = x->left;
    }
    return x;
}

/*
 * Search for maximum of rb trees relation type
 */
binaryTreeRelTypes_t *rbTreeRelTypesMaximum(binaryTreeRelTypes_t *x) {
    while (x->right != binaryTreeRelNIL) {
        x = x->right;
    }
    return x;
}

/*
 * Search for successor of rb trees relation type
 */
binaryTreeRelTypes_t *rbTreeRelTypesSuccessor(binaryTreeRelTypes_t *x) {
    if (x->right != binaryTreeRelNIL) {
        return rbTreeRelTypesMinimum(x->right);
    }
    binaryTreeRelTypes_t *y = x->p;
    while ((y != binaryTreeRelNIL) && (x == y->right)) {
        x = y;
        y = y->p;
    }
    return y;
}

/*
 * Search for predecessor of rb trees relation type
 */
binaryTreeRelTypes_t *rbTreeRelTypesPredecessor(binaryTreeRelTypes_t *x) {
    if (x->left != binaryTreeRelNIL) {
        return rbTreeRelTypesMaximum(x->left);
    }
    binaryTreeRelTypes_t *y = x->p;
    while ((y != binaryTreeRelNIL) && (x == y->left)) {
        x = y;
        y = y->p;
    }
    return y;
}


/*
 * Left rotate the rb tree for rel types
 */
binaryTreeRelTypes_t *rbTreeRelTypesLeftRotate(binaryTreeRelTypes_t *T, binaryTreeRelTypes_t *x) {
    binaryTreeRelTypes_t *y = x->right;
    x->right = y->left;
    if (y->left != binaryTreeRelNIL) {
        y->left->p = x;
    }
    y->p = x->p;
    if (x->p == binaryTreeRelNIL) {
        T = y;
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
binaryTreeRelTypes_t *rbTreeRelTypesRightRotate(binaryTreeRelTypes_t *T, binaryTreeRelTypes_t *x) {
    binaryTreeRelTypes_t *y = x->left;
    x->left = y->right;
    if (y->right != binaryTreeRelNIL) {
        y->right->p = x;
    }
    y->p = x->p;
    if (x->p == binaryTreeRelNIL) {
        T = y;
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
binaryTreeRelTypes_t *rbTreeRelTypesInsert(binaryTreeRelTypes_t *T, binaryTreeRelTypes_t *z) {
    binaryTreeRelTypes_t *y=binaryTreeRelNIL;
    binaryTreeRelTypes_t *x=T;
    while(x!=binaryTreeRelNIL) {
        y=x;
        if(strncmp(z->id,x->id,RELATIONS_ID_SIZE)<0) {
            x=x->left;
        } else {
            x=x->right;
        }
    }
    z->p=y;
    if(y==binaryTreeRelNIL) {
        T=z;
    } else if (strncmp(z->id,y->id,RELATIONS_ID_SIZE)<0) {
        y->left=z;
    } else {
        y->right=z;
    }
    z->left=binaryTreeRelNIL;
    z->right=binaryTreeRelNIL;
    z->color=RED;
    rbTreeRelTypesInsertFixup(T, z);
}

/*
 * Fixup insert value in rb trees
 */
binaryTreeRelTypes_t *rbTreeRelTypesInsertFixup(binaryTreeRelTypes_t *T, binaryTreeRelTypes_t *z) {
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