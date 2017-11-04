#ifndef FLEXARRAY_H_
#define FLEXARRAY_H_

typedef struct flexarrayrec *flexarray;

extern void flexarray_append(flexarray , char *);
extern void flexarray_free(flexarray );
extern flexarray flexarray_new();
extern void print_key(char *);
extern void flexarray_visted(flexarray, void (char *));
extern void flexarray_sort(flexarray);
extern int flexarray_isPresent(flexarray , char *);

#endif
