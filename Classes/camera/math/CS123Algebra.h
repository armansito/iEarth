/*!
   @file   CS123Algebra.h
   @author Travis Fischer (fisch0920@gmail.com)
   @date   Fall 2008
   
   @brief
      Convenience header which includes all headers in the CS123 linear 
   algebra package (CS123Matrix.h, CS123Vector.h, and CS123Point.h).
**/

#ifndef __CS123_ALGEBRA_H__
#define __CS123_ALGEBRA_H__

typedef float REAL;

#ifndef MIN
#define MIN(x, y) ({          \
typeof (x) x_ = (x);       \
typeof (y) y_ = (y);       \
((x_ < y_) ? x_ : y_);     \
})
#endif

#ifndef MAX
#define MAX(x, y) ({          \
typeof (x) _x_ = (x);      \
typeof (y) _y_ = (y);      \
((_x_ > _y_) ? _x_ : _y_); \
})
#endif

#include "CS123Matrix.h"
#include "CS123Vector.h"
#include <math.h>



#endif // __CS123_ALGEBRA_H__

