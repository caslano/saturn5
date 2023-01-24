
#ifndef BOOST_MPL_AUX_PREPROCESSOR_IS_SEQ_HPP_INCLUDED
#define BOOST_MPL_AUX_PREPROCESSOR_IS_SEQ_HPP_INCLUDED

// Copyright Paul Mensonides 2003
// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/punctuation/paren.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/config/config.hpp>

// returns 1 if 'seq' is a PP-sequence, 0 otherwise:
//
//   BOOST_PP_ASSERT( BOOST_PP_NOT( BOOST_MPL_PP_IS_SEQ( int ) ) )
//   BOOST_PP_ASSERT( BOOST_MPL_PP_IS_SEQ( (int) ) )
//   BOOST_PP_ASSERT( BOOST_MPL_PP_IS_SEQ( (1)(2) ) )

#if (BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_BCC()) || defined(_MSC_VER) && defined(__INTEL_COMPILER) && __INTEL_COMPILER == 1010

#   define BOOST_MPL_PP_IS_SEQ(seq) BOOST_PP_DEC( BOOST_PP_SEQ_SIZE( BOOST_MPL_PP_IS_SEQ_(seq) ) )
#   define BOOST_MPL_PP_IS_SEQ_(seq) BOOST_MPL_PP_IS_SEQ_SEQ_( BOOST_MPL_PP_IS_SEQ_SPLIT_ seq )
#   define BOOST_MPL_PP_IS_SEQ_SEQ_(x) (x)
#   define BOOST_MPL_PP_IS_SEQ_SPLIT_(unused) unused)((unused)

#else

#   if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#       define BOOST_MPL_PP_IS_SEQ(seq) BOOST_MPL_PP_IS_SEQ_MWCC_((seq))
#       define BOOST_MPL_PP_IS_SEQ_MWCC_(args) BOOST_MPL_PP_IS_SEQ_ ## args
#   else
#       define BOOST_MPL_PP_IS_SEQ(seq) BOOST_MPL_PP_IS_SEQ_(seq)
#   endif

#   define BOOST_MPL_PP_IS_SEQ_(seq) BOOST_PP_CAT(BOOST_MPL_PP_IS_SEQ_, BOOST_MPL_PP_IS_SEQ_0 seq BOOST_PP_RPAREN())
#   define BOOST_MPL_PP_IS_SEQ_0(x) BOOST_MPL_PP_IS_SEQ_1(x
#   define BOOST_MPL_PP_IS_SEQ_ALWAYS_0(unused) 0
#   define BOOST_MPL_PP_IS_SEQ_BOOST_MPL_PP_IS_SEQ_0 BOOST_MPL_PP_IS_SEQ_ALWAYS_0(
#   define BOOST_MPL_PP_IS_SEQ_BOOST_MPL_PP_IS_SEQ_1(unused) 1

#endif

#endif // BOOST_MPL_AUX_PREPROCESSOR_IS_SEQ_HPP_INCLUDED

/* is_seq.hpp
mPYT3vs+q759Hf22gnDt4dsu8Kc3uWrOwYA9jo7cF/YT5e9yujXngmfkLP0v1SxrDAoq50WMAW8DMhL2fnpsN0ie+fGIag0eKY6uw0s6XQw+3XVC9H91LwU8DIgGSGgHAHz7ypW9A43MI07zdWT32TpTo4N2FlKzl94qHXUsBgM+sRmTK8rVWctijMoR/fnL3keZWokO3qrWO4w+1+b0022+9JB0LXGn3lWtfL78L5+G7aWTt4R4650MzDFJTz7dvMdsi/78p02NpBNuBYrc0R+ikrzZ8Ybo387mBEynBkk08c0soqdod/yd5ljczjwIbijv3zYxrHT/qAw33acPaMNLRu/+asthTq7bY0WiaM/JAQW/XsL59l65X+V9Jy2x/YH460eKB9kwf/QuE+gcreC1dEkAOLWHJr0t8Svrbz+8TrunvuNrol5lMEGfaEmdUs3EtNLh97XWuouo4RqV4WMcdppMOfcIj6I612Fc3szEjdNmf+9N0mWFhJ5QCaVKO5KdNS1fVKYVTl5NUtig4ldG+4NU8T+rCrOACvnmlWDzf55KUUYa9ihAj+TAUmZ5po8cj/RqszHXYtc4nUp630oQkqjTrYesaouAgtqvhZ0yQDXgnyFF3QVeR7VHlAERXcrwOcgsZObuEHT4JGwTGN5oETnIHEWyDTgiCJD1Kr0ZEEfwjzMg/EFR93ywbm/qR1JiZHXXe4sIQBp0
*/