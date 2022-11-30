//  ratio_fwd.hpp  ---------------------------------------------------------------//

//  Copyright 2008 Howard Hinnant
//  Copyright 2008 Beman Dawes
//  Copyright 2009 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

/*

This code was derived by Beman Dawes from Howard Hinnant's time2_demo prototype.
Many thanks to Howard for making his code available under the Boost license.
The original code was modified to conform to Boost conventions and to section
20.4 Compile-time rational arithmetic [ratio], of the C++ committee working
paper N2798.
See http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2008/n2798.pdf.

time2_demo contained this comment:

    Much thanks to Andrei Alexandrescu,
                   Walter Brown,
                   Peter Dimov,
                   Jeff Garland,
                   Terry Golubiewski,
                   Daniel Krugler,
                   Anthony Williams.
*/

// The way overflow is managed for ratio_less is taken from llvm/libcxx/include/ratio

#ifndef BOOST_RATIO_RATIO_FWD_HPP
#define BOOST_RATIO_RATIO_FWD_HPP

#include <boost/ratio/config.hpp>

#if defined(__GNUC__) && (__GNUC__ >= 4)
#pragma GCC system_header
#endif

namespace boost
{

//----------------------------------------------------------------------------//
//                                                                            //
//              20.6 Compile-time rational arithmetic [ratio]                 //
//                                                                            //
//----------------------------------------------------------------------------//

// ratio
template <boost::intmax_t N, boost::intmax_t D = 1> class ratio;

// ratio arithmetic
template <class R1, class R2> struct ratio_add;
template <class R1, class R2> struct ratio_subtract;
template <class R1, class R2> struct ratio_multiply;
template <class R1, class R2> struct ratio_divide;
#ifdef BOOST_RATIO_EXTENSIONS
template <class R1, class R2> struct ratio_gcd;
template <class R1, class R2> struct ratio_lcm;
template <class R> struct ratio_negate;
template <class R> struct ratio_abs;
template <class R> struct ratio_sign;
template <class R, int P> struct ratio_power;
#endif

// ratio comparison
template <class R1, class R2> struct ratio_equal;
template <class R1, class R2> struct ratio_not_equal;
template <class R1, class R2> struct ratio_less;
template <class R1, class R2> struct ratio_less_equal;
template <class R1, class R2> struct ratio_greater;
template <class R1, class R2> struct ratio_greater_equal;

// convenience SI typedefs
typedef ratio<BOOST_RATIO_INTMAX_C(1), BOOST_RATIO_INTMAX_C(1000000000000000000)> atto;
typedef ratio<BOOST_RATIO_INTMAX_C(1),    BOOST_RATIO_INTMAX_C(1000000000000000)> femto;
typedef ratio<BOOST_RATIO_INTMAX_C(1),       BOOST_RATIO_INTMAX_C(1000000000000)> pico;
typedef ratio<BOOST_RATIO_INTMAX_C(1),          BOOST_RATIO_INTMAX_C(1000000000)> nano;
typedef ratio<BOOST_RATIO_INTMAX_C(1),             BOOST_RATIO_INTMAX_C(1000000)> micro;
typedef ratio<BOOST_RATIO_INTMAX_C(1),                BOOST_RATIO_INTMAX_C(1000)> milli;
typedef ratio<BOOST_RATIO_INTMAX_C(1),                 BOOST_RATIO_INTMAX_C(100)> centi;
typedef ratio<BOOST_RATIO_INTMAX_C(1),                  BOOST_RATIO_INTMAX_C(10)> deci;
typedef ratio<                 BOOST_RATIO_INTMAX_C(10), BOOST_RATIO_INTMAX_C(1)> deca;
typedef ratio<                BOOST_RATIO_INTMAX_C(100), BOOST_RATIO_INTMAX_C(1)> hecto;
typedef ratio<               BOOST_RATIO_INTMAX_C(1000), BOOST_RATIO_INTMAX_C(1)> kilo;
typedef ratio<            BOOST_RATIO_INTMAX_C(1000000), BOOST_RATIO_INTMAX_C(1)> mega;
typedef ratio<         BOOST_RATIO_INTMAX_C(1000000000), BOOST_RATIO_INTMAX_C(1)> giga;
typedef ratio<      BOOST_RATIO_INTMAX_C(1000000000000), BOOST_RATIO_INTMAX_C(1)> tera;
typedef ratio<   BOOST_RATIO_INTMAX_C(1000000000000000), BOOST_RATIO_INTMAX_C(1)> peta;
typedef ratio<BOOST_RATIO_INTMAX_C(1000000000000000000), BOOST_RATIO_INTMAX_C(1)> exa;

#ifdef BOOST_RATIO_EXTENSIONS

#define BOOST_RATIO_1024 BOOST_RATIO_INTMAX_C(1024)

// convenience IEC typedefs
typedef ratio<                                                                                     BOOST_RATIO_1024> kibi;
typedef ratio<                                                                    BOOST_RATIO_1024*BOOST_RATIO_1024> mebi;
typedef ratio<                                                   BOOST_RATIO_1024*BOOST_RATIO_1024*BOOST_RATIO_1024> gibi;
typedef ratio<                                  BOOST_RATIO_1024*BOOST_RATIO_1024*BOOST_RATIO_1024*BOOST_RATIO_1024> tebi;
typedef ratio<                 BOOST_RATIO_1024*BOOST_RATIO_1024*BOOST_RATIO_1024*BOOST_RATIO_1024*BOOST_RATIO_1024> pebi;
typedef ratio<BOOST_RATIO_1024*BOOST_RATIO_1024*BOOST_RATIO_1024*BOOST_RATIO_1024*BOOST_RATIO_1024*BOOST_RATIO_1024> exbi;

#endif
}  // namespace boost


#endif  // BOOST_RATIO_HPP

/* ratio_fwd.hpp
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
*/