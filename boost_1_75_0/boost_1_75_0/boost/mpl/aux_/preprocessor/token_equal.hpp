
#ifndef BOOST_MPL_AUX_PREPROCESSOR_TOKEN_EQUAL_HPP_INCLUDED
#define BOOST_MPL_AUX_PREPROCESSOR_TOKEN_EQUAL_HPP_INCLUDED

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

#include <boost/mpl/aux_/preprocessor/is_seq.hpp>

#include <boost/preprocessor/if.hpp>
#include <boost/preprocessor/logical/bitand.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/cat.hpp>

// compares tokens 'a' and 'b' for equality:
//
//   #define BOOST_MPL_PP_TOKEN_EQUAL_apple(x) x
//   #define BOOST_MPL_PP_TOKEN_EQUAL_orange(x) x
//
//   BOOST_PP_ASSERT( BOOST_PP_NOT( BOOST_MPL_PP_TOKEN_EQUAL(apple, abc) ) )
//   BOOST_PP_ASSERT( BOOST_PP_NOT( BOOST_MPL_PP_TOKEN_EQUAL(abc, apple) ) )
//   BOOST_PP_ASSERT( BOOST_PP_NOT( BOOST_MPL_PP_TOKEN_EQUAL(apple, orange) ) )
//   BOOST_PP_ASSERT( BOOST_MPL_PP_TOKEN_EQUAL(apple, apple) )
//   BOOST_PP_ASSERT( BOOST_MPL_PP_TOKEN_EQUAL(orange, orange) )

#define BOOST_MPL_PP_TOKEN_EQUAL(a, b) \
    BOOST_PP_IIF( \
        BOOST_PP_BITAND( \
              BOOST_MPL_PP_IS_SEQ( BOOST_PP_CAT(BOOST_MPL_PP_TOKEN_EQUAL_, a)((unused)) ) \
            , BOOST_MPL_PP_IS_SEQ( BOOST_PP_CAT(BOOST_MPL_PP_TOKEN_EQUAL_, b)((unused)) ) \
            ) \
        , BOOST_MPL_PP_TOKEN_EQUAL_I \
        , 0 BOOST_PP_TUPLE_EAT(2) \
        )(a, b) \
/**/

#define BOOST_MPL_PP_TOKEN_EQUAL_I(a, b) \
    BOOST_PP_COMPL(BOOST_MPL_PP_IS_SEQ( \
        BOOST_MPL_PP_TOKEN_EQUAL_ ## a( \
            BOOST_MPL_PP_TOKEN_EQUAL_ ## b \
            )((unused)) \
        )) \
/**/

#endif // BOOST_MPL_AUX_PREPROCESSOR_TOKEN_EQUAL_HPP_INCLUDED

/* token_equal.hpp
ZwomqxfwWYs7SAyBbfOKKso1k2XRqV9z5IOJnlG/h8TKTkgswFIddO7Zt+fI35VNDZ0adO2u+UAtx2dNdU4PifNUYIsHJh7O2GhwG5DVTWA3m6h7pzk0kQPtXLb5mLC51+65+ZGqPt53uFmlPaHNAU7J7GQvkl9GbWhhliy4slmfmiTgC0re9S2w9QYuSCoTqUR7MMsIK4R3UuCMe8VXomwIrqC7hxOJ1y0zyNYhX7lqUpzV7amauNOHLBEZ91G26sM+9W1avov0JxKL101FOtA6/YV9l89P66nxczLzcajCcbniKPiEKEAgqNkGQn/khLRChB2UspIKxL75Ms5KYc5hoXsIV7FKXK/LxWZo12MtiGLb7UKzVMLDUyIoPYQK9JmS33I/ZFbJeVzKflsqyLhcyCHpKSuIP2uZngCZ85SUOwFHlVgtbMyWP+KbhFW8Y0q+kcIlj/H1qPDaccGVb+YAwk81u17jY7MWfMgp6wtXIdiy7RttwBVoNhJwKPESq4ioDk/HHF3/g2CLMv1FsYDmnrfwyRAnESb7k9Asz9XxiRv4cL0sbJPFjNI1alO2axs7QJamNrFJiDdSfncfMy4XoSS2aqQD6Uge5aMS6u2QFQFF0ryOIW5KxB4r/s9cSuNaFcuyfm4K5bWX2Wd1XlF0w07kGdtBB2hyoGpISuWgR/bm5gsJdwaq1w+/eL/wOfD4N4nYGZ7jW3ru
*/