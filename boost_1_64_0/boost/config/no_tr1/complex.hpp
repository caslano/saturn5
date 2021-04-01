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
VGA8bc1kST0O3RoLe1yBbMA76qbsbjMJL0Oy4hPOZUFj8LuW4Bk0H1wXjRN/OilPzV3uel3Zm7fLIUxLprb3mBrw7BE86JeEsrNTz+Fb8KUFU7QovM7ISBdyY/fPYD97b1sIcMNA8Mr6NP9e/EUx/bUyTcSZe6dKRHojsd7RiSL9W4brevFOTWMlR8vjnyVyFLbIovU0YCHxjeodx5JUthG6U6skwSF7iBZ1BNf2aGBY3rieXeSmMxy5jovmRhz9r4FTm+3Pa+I7rHm+/6qXojGlQv+NvIcbRgDtdL0RtPGBuIFTK7Grca1sBoVB3322nFMBwjCV9OtD+O8Bca2+PFQ0vFg/z3QTc+QyTEh9fsMUzZ1UpuIlYEW16yabxfBbKiyYROho4dUp0QEx+Dhld9LR/6nSaFXP3kIVSg09eximdhYWN5s2qXEFBnQ9Wylyq35OgtZC8x9k95qydGnjsWYmJaMXHre8pd2H6iUmG69Kds7FcnN5W59e1j7rALOArIVzD+jAF1Rr4yC2AhwFYrjN+bkR3qRLgVPIEyt77PIbfs16cObFeRGiiQ==
*/