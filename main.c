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
typedef struct binaryTreeRelTypes binaryTreeRelTypes_t;
typedef struct binaryTreeEntities binaryTreeEntities_t;

// RB tree structs
struct binaryTreeRelTypes {
    struct binaryTreeRelTypes *p;
    char id[RELATIONS_ID_SIZE];
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

void rbTreeRelTypesLeftRotate(binaryTreeRelTypes_t *T, binaryTreeRelTypes_t *x);

void rbTreeRelTypesRightRotate(binaryTreeRelTypes_t *T, binaryTreeRelTypes_t *x);

void rbTreeRelTypesInsert(binaryTreeRelTypes_t *T, binaryTreeRelTypes_t *z);

void rbTreeRelTypesInsertFixup(binaryTreeRelTypes_t *T, binaryTreeRelTypes_t *z);

binaryTreeRelTypes_t *rbTreeRelTypesDelete(binaryTreeRelTypes_t *T, binaryTreeRelTypes_t *z);

void rbTreeRelTypesDeleteFixup(binaryTreeRelTypes_t *T, binaryTreeRelTypes_t *x);

// Entities trees

binaryTreeEntities_t *rbTreeEntitiesSearch(binaryTreeEntities_t *x, char *k);

binaryTreeEntities_t *rbTreeEntitiesMinimum(binaryTreeEntities_t *x);

binaryTreeEntities_t *rbTreeEntitiesMaximum(binaryTreeEntities_t *x);

binaryTreeEntities_t *rbTreeEntitiesSuccessor(binaryTreeEntities_t *x);

binaryTreeEntities_t *rbTreeEntitiesPredecessor(binaryTreeEntities_t *x);

void rbTreeEntitiesLeftRotate(binaryTreeEntities_t *T, binaryTreeEntities_t *x);

void rbTreeEntitiesRightRotate(binaryTreeEntities_t *T, binaryTreeEntities_t *x);

void rbTreeEntitiesInsert(binaryTreeEntities_t *T, binaryTreeEntities_t *z);

void rbTreeEntitiesInsertFixup(binaryTreeEntities_t *T, binaryTreeEntities_t *z);

binaryTreeEntities_t *rbTreeEntitiesDelete(binaryTreeEntities_t *T, binaryTreeEntities_t *z);

void rbTreeEntitiesDeleteFixup(binaryTreeEntities_t *T, binaryTreeEntities_t *x);

/*
 * Global variables
 */

binaryTreeRelTypes_t *binaryTreeRelTypesNIL;
binaryTreeRelTypes_t *relTypesRoot;

binaryTreeEntities_t *binaryTreeEntitiesNIL;
binaryTreeEntities_t *entitiesRoot;


int main() {
    for (;;) {
        relTypesRoot = malloc(sizeof(binaryTreeRelTypes_t));
        binaryTreeRelTypesNIL = malloc(sizeof(binaryTreeRelTypes_t));

        entitiesRoot = malloc(sizeof(binaryTreeEntities_t));
        binaryTreeEntitiesNIL = malloc(sizeof(binaryTreeEntities_t));
        
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
    while ((x != binaryTreeRelTypesNIL) || (strncmp(k, x->id, RELATIONS_ID_SIZE) != 0)) {
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
void rbTreeRelTypesLeftRotate(binaryTreeRelTypes_t *T, binaryTreeRelTypes_t *x) {
    binaryTreeRelTypes_t *y = x->right;
    x->right = y->left;
    if (y->left != binaryTreeRelTypesNIL) {
        y->left->p = x;
    }
    y->p = x->p;
    if (x->p == binaryTreeRelTypesNIL) {
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
void rbTreeRelTypesRightRotate(binaryTreeRelTypes_t *T, binaryTreeRelTypes_t *x) {
    binaryTreeRelTypes_t *y = x->left;
    x->left = y->right;
    if (y->right != binaryTreeRelTypesNIL) {
        y->right->p = x;
    }
    y->p = x->p;
    if (x->p == binaryTreeRelTypesNIL) {
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
void rbTreeRelTypesInsert(binaryTreeRelTypes_t *T, binaryTreeRelTypes_t *z) {
    binaryTreeRelTypes_t *y=binaryTreeRelTypesNIL;
    binaryTreeRelTypes_t *x=T;
    while(x!=binaryTreeRelTypesNIL) {
        y=x;
        if(strncmp(z->id,x->id,RELATIONS_ID_SIZE)<0) {
            x=x->left;
        } else {
            x=x->right;
        }
    }
    z->p=y;
    if(y==binaryTreeRelTypesNIL) {
        T=z;
    } else if (strncmp(z->id,y->id,RELATIONS_ID_SIZE)<0) {
        y->left=z;
    } else {
        y->right=z;
    }
    z->left=binaryTreeRelTypesNIL;
    z->right=binaryTreeRelTypesNIL;
    z->color=RED;
    rbTreeRelTypesInsertFixup(T, z);
}

/*
 * Fixup insert value in rb trees
 */
void rbTreeRelTypesInsertFixup(binaryTreeRelTypes_t *T, binaryTreeRelTypes_t *z) {
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

/*
 * Delete rb trees selected value
 */

binaryTreeRelTypes_t *rbTreeRelTypesDelete(binaryTreeRelTypes_t *T, binaryTreeRelTypes_t *z) {
    binaryTreeRelTypes_t *y;
    binaryTreeRelTypes_t *x;
    if((z->left == binaryTreeRelTypesNIL)||(z->right==binaryTreeRelTypesNIL)) {
        y=z;
    } else {
        y=rbTreeRelTypesSuccessor(z);
    }
    if(y->left != binaryTreeRelTypesNIL) {
        x=y->left;
    } else {
        x=y->right;
    }
    x->p=y->p;
    if(y->p==binaryTreeRelTypesNIL) {
        T=x;
    } else if (y==y->p->left) {
        y->p->left=x;
    } else {
        y->p->right=x;
    }
    if(y!=z) {
        strncpy(z->id,y->id,RELATIONS_ID_SIZE);
    }
    if(y->color==BLACK) {
        rbTreeRelTypesDeleteFixup(T,x);
    }
    return y;
}

/*
 * Fixup delete rb trees selected value
 */

void rbTreeRelTypesDeleteFixup(binaryTreeRelTypes_t *T, binaryTreeRelTypes_t *x) {
    binaryTreeRelTypes_t *w;
    while ((x!=T)&&(x->color==BLACK)) {
        if(x==x->p->left) {
            w=x->p->right;
            if(w->color==RED) {
                w->color=BLACK;
                x->p->color=RED;
                rbTreeRelTypesLeftRotate(T, x->p);
                w=x->p->right;
            }
            if((w->left->color==BLACK)&&(w->right->color==BLACK)) {
                w->color=RED;
                x=x->p;
            }
            else {
                if (w->right->color==BLACK) {
                    w->left->color=BLACK;
                    w->color=RED;
                    rbTreeRelTypesRightRotate(T,w);
                    w=x->p->right;
                }
                w->color=x->p->color;
                x->p->color=BLACK;
                w->right->color=BLACK;
                rbTreeRelTypesLeftRotate(T, x->p);
                x=T;
            }
        } else {
            w=x->p->left;
            if(w->color==RED) {
                w->color=BLACK;
                x->p->color=RED;
                rbTreeRelTypesRightRotate(T, x->p);
                w=x->p->left;
            }
            if((w->right->color==BLACK)&&(w->left->color==BLACK)) {
                w->color=RED;
                x=x->p;
            }
            else {
                if (w->left->color==BLACK) {
                    w->right->color=BLACK;
                    w->color=RED;
                    rbTreeRelTypesLeftRotate(T,w);
                    w=x->p->left;
                }
                w->color=x->p->color;
                x->p->color=BLACK;
                w->left->color=BLACK;
                rbTreeRelTypesRightRotate(T, x->p);
                x=T;
            }
        }
    }
    x->color=BLACK;
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
    while ((x != binaryTreeEntitiesNIL) || (strncmp(k, x->id, RELATIONS_ID_SIZE) != 0)) {
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
void rbTreeEntitiesLeftRotate(binaryTreeEntities_t *T, binaryTreeEntities_t *x) {
    binaryTreeEntities_t *y = x->right;
    x->right = y->left;
    if (y->left != binaryTreeEntitiesNIL) {
        y->left->p = x;
    }
    y->p = x->p;
    if (x->p == binaryTreeEntitiesNIL) {
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
 * Right rotate the rb tree for entities types
 */
void rbTreeEntitiesRightRotate(binaryTreeEntities_t *T, binaryTreeEntities_t *x) {
    binaryTreeEntities_t *y = x->left;
    x->left = y->right;
    if (y->right != binaryTreeEntitiesNIL) {
        y->right->p = x;
    }
    y->p = x->p;
    if (x->p == binaryTreeEntitiesNIL) {
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
void rbTreeEntitiesInsert(binaryTreeEntities_t *T, binaryTreeEntities_t *z) {
    binaryTreeEntities_t *y=binaryTreeEntitiesNIL;
    binaryTreeEntities_t *x=T;
    while(x!=binaryTreeEntitiesNIL) {
        y=x;
        if(strncmp(z->id,x->id,RELATIONS_ID_SIZE)<0) {
            x=x->left;
        } else {
            x=x->right;
        }
    }
    z->p=y;
    if(y==binaryTreeEntitiesNIL) {
        T=z;
    } else if (strncmp(z->id,y->id,RELATIONS_ID_SIZE)<0) {
        y->left=z;
    } else {
        y->right=z;
    }
    z->left=binaryTreeEntitiesNIL;
    z->right=binaryTreeEntitiesNIL;
    z->color=RED;
    rbTreeEntitiesInsertFixup(T, z);
}

/*
 * Fixup insert value in rb trees
 */
void rbTreeEntitiesInsertFixup(binaryTreeEntities_t *T, binaryTreeEntities_t *z) {
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

/*
 * Delete rb trees selected value
 */

binaryTreeEntities_t *rbTreeEntitiesDelete(binaryTreeEntities_t *T, binaryTreeEntities_t *z) {
    binaryTreeEntities_t *y;
    binaryTreeEntities_t *x;
    if((z->left == binaryTreeEntitiesNIL)||(z->right==binaryTreeEntitiesNIL)) {
        y=z;
    } else {
        y=rbTreeEntitiesSuccessor(z);
    }
    if(y->left != binaryTreeEntitiesNIL) {
        x=y->left;
    } else {
        x=y->right;
    }
    x->p=y->p;
    if(y->p==binaryTreeEntitiesNIL) {
        T=x;
    } else if (y==y->p->left) {
        y->p->left=x;
    } else {
        y->p->right=x;
    }
    if(y!=z) {
        strncpy(z->id,y->id,RELATIONS_ID_SIZE);
    }
    if(y->color==BLACK) {
        rbTreeEntitiesInsertFixup(T,x);
    }
    return y;
}

/*
 * Fixup delete rb trees selected value
 */

void rbTreeEntitiesDeleteFixup(binaryTreeEntities_t *T, binaryTreeEntities_t *x) {
    binaryTreeEntities_t *w;
    while ((x!=T)&&(x->color==BLACK)) {
        if(x==x->p->left) {
            w=x->p->right;
            if(w->color==RED) {
                w->color=BLACK;
                x->p->color=RED;
                rbTreeEntitiesLeftRotate(T, x->p);
                w=x->p->right;
            }
            if((w->left->color==BLACK)&&(w->right->color==BLACK)) {
                w->color=RED;
                x=x->p;
            }
            else {
                if (w->right->color==BLACK) {
                    w->left->color=BLACK;
                    w->color=RED;
                    rbTreeEntitiesRightRotate(T,w);
                    w=x->p->right;
                }
                w->color=x->p->color;
                x->p->color=BLACK;
                w->right->color=BLACK;
                rbTreeEntitiesLeftRotate(T, x->p);
                x=T;
            }
        } else {
            w=x->p->left;
            if(w->color==RED) {
                w->color=BLACK;
                x->p->color=RED;
                rbTreeEntitiesRightRotate(T, x->p);
                w=x->p->left;
            }
            if((w->right->color==BLACK)&&(w->left->color==BLACK)) {
                w->color=RED;
                x=x->p;
            }
            else {
                if (w->left->color==BLACK) {
                    w->right->color=BLACK;
                    w->color=RED;
                    rbTreeEntitiesLeftRotate(T,w);
                    w=x->p->left;
                }
                w->color=x->p->color;
                x->p->color=BLACK;
                w->left->color=BLACK;
                rbTreeEntitiesLeftRotate(T, x->p);
                x=T;
            }
        }
    }
    x->color=BLACK;
}