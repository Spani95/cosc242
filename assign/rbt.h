#ifndef RBT_H_
#define RBT_H_


typedef struct rbt_node *rbt;

extern void print(rbt b);
extern rbt rbt_delete(rbt b, char *str);
extern rbt rbt_free(rbt b);
extern void rbt_inorder(rbt b, void f(rbt b));
extern rbt rbt_insert(rbt b, char *str);
extern rbt rbt_new();
extern void rbt_preorder(rbt b, void f(rbt b));
extern int rbt_search(rbt b, char *str);
extern rbt rbt_rootNode(rbt b);

#endif
