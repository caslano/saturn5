#ifndef BOOST_QVM_MATH_HPP_INCLUDED
#define BOOST_QVM_MATH_HPP_INCLUDED

// Copyright 2008-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <math.h>
#include <boost/qvm/inline.hpp>

namespace boost { namespace qvm {

template <class T> T acos( T );
template <class T> T asin( T );
template <class T> T atan( T );
template <class T> T atan2( T, T );
template <class T> T cos( T );
template <class T> T sin( T );
template <class T> T tan( T );
template <class T> T cosh( T );
template <class T> T sinh( T );
template <class T> T tanh( T );
template <class T> T exp( T );
template <class T> T log( T );
template <class T> T log10( T );
template <class T> T mod( T , T );
template <class T> T pow( T, T );
template <class T> T sqrt( T );
template <class T> T ceil( T );
template <class T> T abs( T );
template <class T> T floor( T );
template <class T> T mod( T, T );
template <class T> T ldexp( T, int );
template <class T> T sign( T );

template <> BOOST_QVM_INLINE_TRIVIAL float acos<float>( float x ) { return ::acosf(x); }
template <> BOOST_QVM_INLINE_TRIVIAL float asin<float>( float x ) { return ::asinf(x); }
template <> BOOST_QVM_INLINE_TRIVIAL float atan<float>( float x ) { return ::atanf(x); }
template <> BOOST_QVM_INLINE_TRIVIAL float atan2<float>( float x, float y ) { return ::atan2f(x,y); }
template <> BOOST_QVM_INLINE_TRIVIAL float cos<float>( float x ) { return ::cosf(x); }
template <> BOOST_QVM_INLINE_TRIVIAL float sin<float>( float x ) { return ::sinf(x); }
template <> BOOST_QVM_INLINE_TRIVIAL float tan<float>( float x ) { return ::tanf(x); }
template <> BOOST_QVM_INLINE_TRIVIAL float cosh<float>( float x ) { return ::coshf(x); }
template <> BOOST_QVM_INLINE_TRIVIAL float sinh<float>( float x ) { return ::sinhf(x); }
template <> BOOST_QVM_INLINE_TRIVIAL float tanh<float>( float x ) { return ::tanhf(x); }
template <> BOOST_QVM_INLINE_TRIVIAL float exp<float>( float x ) { return ::expf(x); }
template <> BOOST_QVM_INLINE_TRIVIAL float log<float>( float x ) { return ::logf(x); }
template <> BOOST_QVM_INLINE_TRIVIAL float log10<float>( float x ) { return ::log10f(x); }
template <> BOOST_QVM_INLINE_TRIVIAL float mod<float>( float x, float y ) { return ::fmodf(x,y); }
template <> BOOST_QVM_INLINE_TRIVIAL float pow<float>( float x, float y ) { return ::powf(x,y); }
template <> BOOST_QVM_INLINE_TRIVIAL float sqrt<float>( float x ) { return ::sqrtf(x); }
template <> BOOST_QVM_INLINE_TRIVIAL float ceil<float>( float x ) { return ::ceilf(x); }
template <> BOOST_QVM_INLINE_TRIVIAL float abs<float>( float x ) { return ::fabsf(x); }
template <> BOOST_QVM_INLINE_TRIVIAL float floor<float>( float x ) { return ::floorf(x); }
template <> BOOST_QVM_INLINE_TRIVIAL float ldexp<float>( float x, int y ) { return ::ldexpf(x,y); }
template <> BOOST_QVM_INLINE_TRIVIAL float sign<float>( float x ) { return x<0 ? -1.f : +1.f; }

template <> BOOST_QVM_INLINE_TRIVIAL double acos<double>( double x ) { return ::acos(x); }
template <> BOOST_QVM_INLINE_TRIVIAL double asin<double>( double x ) { return ::asin(x); }
template <> BOOST_QVM_INLINE_TRIVIAL double atan<double>( double x ) { return ::atan(x); }
template <> BOOST_QVM_INLINE_TRIVIAL double atan2<double>( double x, double y ) { return ::atan2(x,y); }
template <> BOOST_QVM_INLINE_TRIVIAL double cos<double>( double x ) { return ::cos(x); }
template <> BOOST_QVM_INLINE_TRIVIAL double sin<double>( double x ) { return ::sin(x); }
template <> BOOST_QVM_INLINE_TRIVIAL double tan<double>( double x ) { return ::tan(x); }
template <> BOOST_QVM_INLINE_TRIVIAL double cosh<double>( double x ) { return ::cosh(x); }
template <> BOOST_QVM_INLINE_TRIVIAL double sinh<double>( double x ) { return ::sinh(x); }
template <> BOOST_QVM_INLINE_TRIVIAL double tanh<double>( double x ) { return ::tanh(x); }
template <> BOOST_QVM_INLINE_TRIVIAL double exp<double>( double x ) { return ::exp(x); }
template <> BOOST_QVM_INLINE_TRIVIAL double log<double>( double x ) { return ::log(x); }
template <> BOOST_QVM_INLINE_TRIVIAL double log10<double>( double x ) { return ::log10(x); }
template <> BOOST_QVM_INLINE_TRIVIAL double mod<double>( double x, double y ) { return ::fmod(x,y); }
template <> BOOST_QVM_INLINE_TRIVIAL double pow<double>( double x, double y ) { return ::pow(x,y); }
template <> BOOST_QVM_INLINE_TRIVIAL double sqrt<double>( double x ) { return ::sqrt(x); }
template <> BOOST_QVM_INLINE_TRIVIAL double ceil<double>( double x ) { return ::ceil(x); }
template <> BOOST_QVM_INLINE_TRIVIAL double abs<double>( double x ) { return ::fabs(x); }
template <> BOOST_QVM_INLINE_TRIVIAL double floor<double>( double x ) { return ::floor(x); }
template <> BOOST_QVM_INLINE_TRIVIAL double ldexp<double>( double x, int y ) { return ::ldexp(x,y); }
template <> BOOST_QVM_INLINE_TRIVIAL double sign<double>( double x ) { return x<0 ? -1.0 : +1.0; }

template <> BOOST_QVM_INLINE_TRIVIAL long double acos<long double>( long double x ) { return ::acosl(x); }
template <> BOOST_QVM_INLINE_TRIVIAL long double asin<long double>( long double x ) { return ::asinl(x); }
template <> BOOST_QVM_INLINE_TRIVIAL long double atan<long double>( long double x ) { return ::atanl(x); }
template <> BOOST_QVM_INLINE_TRIVIAL long double atan2<long double>( long double x, long double y ) { return ::atan2l(x,y); }
template <> BOOST_QVM_INLINE_TRIVIAL long double cos<long double>( long double x ) { return ::cosl(x); }
template <> BOOST_QVM_INLINE_TRIVIAL long double sin<long double>( long double x ) { return ::sinl(x); }
template <> BOOST_QVM_INLINE_TRIVIAL long double tan<long double>( long double x ) { return ::tanl(x); }
template <> BOOST_QVM_INLINE_TRIVIAL long double cosh<long double>( long double x ) { return ::coshl(x); }
template <> BOOST_QVM_INLINE_TRIVIAL long double sinh<long double>( long double x ) { return ::sinhl(x); }
template <> BOOST_QVM_INLINE_TRIVIAL long double tanh<long double>( long double x ) { return ::tanhl(x); }
template <> BOOST_QVM_INLINE_TRIVIAL long double exp<long double>( long double x ) { return ::expl(x); }
template <> BOOST_QVM_INLINE_TRIVIAL long double log<long double>( long double x ) { return ::logl(x); }
template <> BOOST_QVM_INLINE_TRIVIAL long double log10<long double>( long double x ) { return ::log10l(x); }
template <> BOOST_QVM_INLINE_TRIVIAL long double mod<long double>( long double x, long double y ) { return ::fmodl(x,y); }
template <> BOOST_QVM_INLINE_TRIVIAL long double pow<long double>( long double x, long double y ) { return ::powl(x,y); }
template <> BOOST_QVM_INLINE_TRIVIAL long double sqrt<long double>( long double x ) { return ::sqrtl(x); }
template <> BOOST_QVM_INLINE_TRIVIAL long double ceil<long double>( long double x ) { return ::ceill(x); }
template <> BOOST_QVM_INLINE_TRIVIAL long double abs<long double>( long double x ) { return ::fabsl(x); }
template <> BOOST_QVM_INLINE_TRIVIAL long double floor<long double>( long double x ) { return ::floorl(x); }
template <> BOOST_QVM_INLINE_TRIVIAL long double ldexp<long double>( long double x, int y ) { return ::ldexpl(x,y); }
template <> BOOST_QVM_INLINE_TRIVIAL long double sign<long double>( long double x ) { return x<0 ? -1.0 : +1.0; }

} }

#endif

/* math.hpp
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
*/