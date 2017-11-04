#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rbt.h"
#include "emalloc.h"

#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))

typedef enum { RED, BLACK } rbt_colour;

struct rbt_node {
  char *key;
  int frequency;
  rbt_colour colour;
  rbt left;
  rbt right;
};

/*
 *  Creates a new empty red black tree.
 * @return rbt.
 */
rbt rbt_new() {
    return NULL;
}

/*
 *  Frees the entire rbt.
 *
 * @param b is a rbt.
 * @return rbt.
 */
rbt rbt_free(rbt b) {
    if (b == NULL) {
        return b;
    }
    if (b->left != NULL) {
        b->left = rbt_free(b->left);
    }
    if (b->right != NULL) {
        b->right = rbt_free(b->right);
    }
    free(b->key);
    free(b);
    return NULL;
}

/*
 *  Searches a given rbt for the specified "key".
 *
 * @param key is a char array that is to be searched for.
 * @return an integer: 1 if key is found, otherwise 0.
 */
int rbt_search(rbt b, char *key) {
    if (b == NULL) {
        return 0;
    }
    if (strcmp(b->key, key) == 0) {
        return 1;
    }
    if (strcmp(b->key, key) > 0) {
        return rbt_search(b->left, key);
    } else {
        return rbt_search(b->right, key);
    }
}

/*
 *  Goes down the left side of the rbt until it finds the left most node and
 *  prints it out.
 *
 * @param b is an rbt.
 * @return an rbt.
 */
rbt rbt_min(rbt b) {
  rbt current = b;
  while(current->left != NULL) {
    current = current->left;
  }
  return current;
}

/*
 *  Rotates the rbt right around the root of the given rbt.
 *
 * @param b is an rbt.
 * @return an rbt.
 */
rbt right_rotate(rbt b) {
  rbt temp = b;
  b = b->left;
  temp->left = b->right;
  b->right = temp;
  return b;
}

/*
 *  Rotates the rbt left around the root of the given rbt.
 *
 * @param b is an rbt.
 * @return an rbt.
 */
rbt left_rotate(rbt b) {
  rbt temp = b;
  b = b->right;
  temp->right = b->left;
  b->left = temp;
  return b;
}

/*
 *  */
rbt rbt_fix(rbt b) {
  if (IS_RED(b->left) && IS_RED(b->left->left)) {
    if (IS_RED(b->right)) {
      b->colour = RED;
      b->left->colour = BLACK;
      b->right->colour = BLACK;
      return b;
    } else {
      b = right_rotate(b);
      b->colour = BLACK;
      b->right->colour = RED;
      return b;
    }
  }

  else if (IS_RED(b->left) && IS_RED(b->left->right)) {
    if (IS_RED(b->right)) {
      b->colour = RED;
      b->left->colour = BLACK;
      b->right->colour = BLACK;
      return b;
    } else {
      b->left = left_rotate(b->left);
      b = right_rotate(b);
      b->colour = BLACK;
      b->right->colour = RED;
      return b;
    }
  }

  else if (IS_RED(b->right) && IS_RED(b->right->left)) {
    if (IS_RED(b->left)) {
      b->colour = RED;
      b->left->colour = BLACK;
      b->right->colour = BLACK;
      return b;
    } else {
      b->right = right_rotate(b->right);
      b = left_rotate(b);
      b->colour = BLACK;
      b->left->colour = RED;
      return b;
    }
  }

  else if (IS_RED(b->right) && IS_RED(b->right->right)) {
    if (IS_RED(b->left)) {
      b->colour = RED;
      b->left->colour = BLACK;
      b->right->colour = BLACK;
      return b;
    } else {
      b = left_rotate(b);
      b->colour = BLACK;
      b->left->colour = RED;
      return b;
    }
  }
  
  return b;
}
      
rbt rbt_rootNode(rbt b) {
  /*NOTWORKING*/
  b->colour = BLACK;
  return b;
}

rbt rbt_insert(rbt b, char *word) {
    if (b == NULL) {
        b = emalloc(sizeof *b);
        b->key = emalloc((strlen(word) + 1) * sizeof b->key[0]);
	b->frequency = 0;
        strcpy(b->key, word);
	b->colour = RED;
	b->left = rbt_new();
	b->right = rbt_new();
    }
    if (strcmp(word, b->key) == 0) {
      /* Adding frequency word occurs */
      b->frequency += 1;
      return b;
    }
    if (strcmp(word, b->key) < 0) {
      b->left = rbt_insert(b->left, word);
    } else {
      b->right = rbt_insert(b->right, word);
    }

    b = rbt_fix(b);
    return b;
}

void rbt_inorder(rbt b, void f(rbt b)) {
  if (b == NULL) {
    return;
  }

  rbt_inorder(b->left, f);
  f(b);
  rbt_inorder(b->right, f);
}

void rbt_preorder(rbt b, void f(rbt b)) {
  if (b == NULL) {
    return;
  }

  f(b);
  rbt_preorder(b->left, f);
  rbt_preorder(b->right, f);
}

void print(rbt b) {
  printf("%s: %s (%d)\n", ((b->colour==BLACK) ? ("black") : ("red")), b->key, b->frequency);
}

rbt rbt_delete(rbt b, char *key) {
  if(rbt_search(b, key) == 0){
    return b;
  }
  if(strcmp(b->key, key) == 0) {
    if(b->left == NULL && b->right == NULL) {
        free(b->key);
        free(b);
        b = NULL;
        return b;
    } else if(b->left == NULL && b->right != NULL) {
        rbt temp = b->right;
        free(b->key);
        free(b);
        return temp;
    } else if(b->right == NULL && b->left != NULL) {
        rbt temp = b->left;
        free(b->key);
        free(b);
        return temp;
    } else {
        char *swap = b->key;
        rbt temp = rbt_min(b->right);
        b->key = temp->key;
        temp->key = swap;
        b->right = rbt_delete(b->right, key);
        return b;
    }
  }
  if(strcmp(key, b->key) < 0){
    b->left = rbt_delete(b->left, key);
    return b;
  } else {
    b->right = rbt_delete(b->right, key);
    return b;
  }
}
