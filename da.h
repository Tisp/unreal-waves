
#ifndef DYNAMIC_ARRAY_H_
#define DYNAMIC_ARRAY_H_

#define dynamic_array_append(array, element)                                   \
  do {                                                                         \
    if (array.count >= array.capacity) {                                       \
      if (array.capacity == 0)                                                 \
        array.capacity = 2;                                                    \
      else                                                                     \
        array.capacity *= 2;                                                   \
      array.items =                                                            \
          realloc(array.items, array.capacity * sizeof(*array.items));         \
    }                                                                          \
    array.items[array.count++] = element;                                      \
  } while (0)

#define dynamic_array_free(array) free((array).items)

#endif // DYNAMIC_ARRAY_H_
