
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
CUAqmR454dR9SfU+Npyq7PMp9um/e3mW/vq+rF5/If+khJ7FVUTeyX63zd4OAz2OJ+I9KMk9PCcg4+6LiCXfhkdoJ+YWeBwjlBcXJJMLIKf/Kxp/rNv/E/HmPtIX707fjApX9WS01LxIEeZWFCA+dPQUk/UejwxJ/qu//7a7I3v+wgyeMrP9LXfYrmtPtTd11qV+dRpGwWP0qWW5bgubxlJNNXpBC0341btZkuKBhQrli6qJT7BYd1xWQOWTmvp6F8I1LaUX30SLwoH71DRtwIoa3Bhyzjnb7U7QWLtPd366uWLEW8Utnqyima3/Yy7fPJKpLpuqAwbvwjQlXJ7Pnb70zyB3LglpLfRkHuzMUpKE4AycRObmQ1On9pi5ntOQy3QBlI+nYbYlEhL77VyqX4zq3HodW4MmePpUl6cnx21OqUrWrKQNQC3Ee0132NkiXUvCpCNkFGxIsq3V1W6214j9fsbObFWEgy8iWLL+QikZdxbyYj5CJSFOV8VbFj78UYSdGuvBhGp6EV4wqNsTOodhdb6c5ke4eZUqkQOrSiGVCLbqn+feVBYD+g==
*/