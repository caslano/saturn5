
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
7LrFL2j+9m9mirK2Vr6J+HaSx6YgGUKxoGXqMPQ9wcV5WRb4uJ3ym5Rgq+4/Ns2Km96ILNz67CY+QRCk8XrDf42Dkhp2vnQxlKqJpXAReNbVz+wz5shlbyZKkqXnK2SbbrmeJPHY7KxbO2dKX01A6fysTj9in2O8INpkY+JKvLFWNnq6W7sR8ULQqsnzvJU0/SkQL6vban4HAr8dvCCtAgKUnDudtl2ZQ2CATArJgcKfYv5b7IEaoXIPqfR5VDFT20cmTFJjmtYq79Py9kpGEx+MkzKZr6YEf7bAcAEj0q1oZTPfhfY5tWXalLbQlWu6OgJR3vW4/kAC7lhlOiA4Y5CEzj3fVbPcnYK95P3kyYrLmHzVLVWatMfnbZrbbbe/Vzkh1ybaLt/dxPlNTw3UFdFpo/rbIq2MgzXSxj/ykmHZGumuq9nqOvmySC7eDJmrla6uVVvGe7SPx8Yy9ZXZQ0LCpFu60XlLke6saHIWixZGxFvhGfjy3GscP4goudWsxeQ8zWg7i2Mdk+yIpC+3mDohivPUJioFiWAQu7SUAkOtYjybj6yb+In13g==
*/