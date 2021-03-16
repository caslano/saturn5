//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// The aim of this header is just to include <complex> but to do
// so in a way that does not result in recursive inclusion of
// the Boost TR1 components if boost/tr1/tr1/complex is in the
// include search path.  We have to do this to avoid circular
// dependencies:
//

#ifndef BOOST_CONFIG_COMPLEX
#  define BOOST_CONFIG_COMPLEX

#  ifndef BOOST_TR1_NO_RECURSION
#     define BOOST_TR1_NO_RECURSION
#     define BOOST_CONFIG_NO_COMPLEX_RECURSION
#  endif

#  include <complex>

#  ifdef BOOST_CONFIG_NO_COMPLEX_RECURSION
#     undef BOOST_TR1_NO_RECURSION
#     undef BOOST_CONFIG_NO_COMPLEX_RECURSION
#  endif

#endif

/* complex.hpp
n7tWhg5266QTsMl9znVLnQIjCVnkSGP5SF2z7gGbFL4KnYZbaB/CovA5boVaFDKNEpxfI7Y+J8fuwiOy7WxHJ+5/B+wVrXL/Pe41zvUX5tpBr3/8tU6yUUjVwvmtU2YUwYfqEHEUhWydaMsi4R/AaRTO9mwIk/PEhtAp+9ziG5Dco7DVceM7cNyc7DaPa5scfW69OfZa+sI8PEAW8AV+QnPoSwfKAr5LafulDFvFvx+X0bbb1hRzuEiNLi5zvTA=
*/