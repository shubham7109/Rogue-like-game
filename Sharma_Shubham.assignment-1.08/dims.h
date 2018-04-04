#ifndef DIMS_H
# define DIMS_H

/* You can't forward reference enums or array types, so most of the headers *
 * need this, thus we put it in it's own file.                              */

typedef enum dim {
  dim_x,
  dim_y,
  num_dims
} dim_t;

// Changed to handle error
//12:29: error: cannot convert 'int16_t* {aka short int*}' to 'int8_t*
//{aka signed char*}' in return
//return ((character *) c)->position
typedef int8_t pair_t[num_dims];

#endif
