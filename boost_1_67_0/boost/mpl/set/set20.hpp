
#ifndef BOOST_MPL_SET_SET20_HPP_INCLUDED
#define BOOST_MPL_SET_SET20_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/set/set10.hpp>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER set20.hpp
#   include <boost/mpl/set/aux_/include_preprocessed.hpp>

#else

#   include <boost/preprocessor/iterate.hpp>

namespace boost { namespace mpl {

#   define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(11, 20, <boost/mpl/set/aux_/numbered.hpp>))
#   include BOOST_PP_ITERATE()

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

#endif // BOOST_MPL_SET_SET20_HPP_INCLUDED

/* set20.hpp
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
*/