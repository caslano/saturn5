//  (C) Copyright John Maddock 2008.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// The aim of this header is just to include <cmath> but to do
// so in a way that does not result in recursive inclusion of
// the Boost TR1 components if boost/tr1/tr1/cmath is in the
// include search path.  We have to do this to avoid circular
// dependencies:
//

#ifndef BOOST_CONFIG_CMATH
#  define BOOST_CONFIG_CMATH

#  ifndef BOOST_TR1_NO_RECURSION
#     define BOOST_TR1_NO_RECURSION
#     define BOOST_CONFIG_NO_CMATH_RECURSION
#  endif

#  include <cmath>

#  ifdef BOOST_CONFIG_NO_CMATH_RECURSION
#     undef BOOST_TR1_NO_RECURSION
#     undef BOOST_CONFIG_NO_CMATH_RECURSION
#  endif

#endif

/* cmath.hpp
LpfMdmAgNIjv1va+jatoSM76drNR49ARiecL7B5a3y23orp23jfPn3tf/LmfLiyvLM1ZfuDu77m72iGepRdxAN+8+cXMijWDgIcdUNNQZrjUWSP6VoVHSnP6GceL4CwIL4Ms1P2rQIxL0012MpuBN09CHMwv8cvMgj16P8Yqv+iFzQcNe0h8FPvnXrwww7yBPiuLHz1g/wNQSwMECgAAAAgALWdKUiQitF8MBAAA3QgAADgACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMSU5GT19OQU1FTE9PS1VQX1RJTUUuM1VUBQABtkgkYK1UYW/bNhD9rl9x0LDBCVS5aTusadNiauIuQhzJsORmBgwItERZ3GhSEyk7wdL/viMl18vcrPlQGbZk6u6947t39BcuHH+3y/ENHHzzyuw3wwvvu6RJI/+guf56QpbdQ/fBxAXen0A1hH3WfXYET8q6h4HNynquM/OcZU+gW5gizc/QJC8y84grXWaffy7ru4atKg2D8yM4OT19Dc/gxfOTUw8uiGCUQ6KpWNJm5cFZYVd+rcjtra/oew+oBsL9B4BpxRQoWeotaSjgM2c5FYoWQBQUVOUNW+IfJkBXFErGKZzHk3kY/ebBtmJ51ePcyRZUJVte
*/