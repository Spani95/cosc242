#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flexarray.h"

int main(void) {
    char item[80];
    int result;
    flexarray my_flexarray = flexarray_new();
    
    while (1 == scanf("%79s", item)) {
        flexarray_append(my_flexarray, item);
    }
    
    result = flexarray_isPresent(my_flexarray, "hello");
    flexarray_visted(my_flexarray, print_key);
    printf("%d\n", result);
    flexarray_free(my_flexarray);
    
    return EXIT_SUCCESS;
}
