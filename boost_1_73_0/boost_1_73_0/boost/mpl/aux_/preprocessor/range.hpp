
#ifndef BOOST_MPL_AUX_PREPROCESSOR_RANGE_HPP_INCLUDED
#define BOOST_MPL_AUX_PREPROCESSOR_RANGE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/preprocessor/seq/subseq.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>

#define BOOST_MPL_PP_RANGE_ITEM(z,n,_) (n)

#define BOOST_MPL_PP_RANGE(first, length) \
    BOOST_PP_SEQ_SUBSEQ( \
        BOOST_PP_REPEAT(BOOST_PP_ADD(first,length), BOOST_MPL_PP_RANGE_ITEM, _), \
        first, length \
    ) \
/**/

#endif // BOOST_MPL_AUX_PREPROCESSOR_RANGE_HPP_INCLUDED

/* range.hpp
GaQiEc0z23N0VI5mfnxgTR3gIDu+QBd9Jb1UhwLLQx4XOVnlWCavLKyiHbm2A6OjNzi2nZT41T6/PKywcKuX9vEgzM3OefV8C7Klp4dq1ZUi5XzaEKHhsx6wJlPSEcb0cFB6hWKtvQGVrFusd2nJSn0XjvMjAltiUo33vvW2dJjDGJrUSQ5EZqrFbVf08ri8KaWEdqlDqzlAbLtb+lTpCJxyI8ZuUGRKQo799THKSvIhQz9twalM0DkToUO9u9w=
*/