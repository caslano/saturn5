
#ifndef BOOST_MPL_EVAL_IF_HPP_INCLUDED
#define BOOST_MPL_EVAL_IF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/if.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/gcc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(C)
    , typename BOOST_MPL_AUX_NA_PARAM(F1)
    , typename BOOST_MPL_AUX_NA_PARAM(F2)
    >
struct eval_if
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300) \
     || ( BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, >= 0x0300) \
        && BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, BOOST_TESTED_AT(0x0304)) \
        )
{
    typedef typename if_<C,F1,F2>::type f_;
    typedef typename f_::type type;
#else
    : if_<C,F1,F2>::type
{
#endif
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,eval_if,(C,F1,F2))
};

// (almost) copy & paste in order to save one more
// recursively nested template instantiation to user
template<
      bool C
    , typename F1
    , typename F2
    >
struct eval_if_c
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300) \
     || ( BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, >= 0x0300) \
        && BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, BOOST_TESTED_AT(0x0304)) \
        )
{
    typedef typename if_c<C,F1,F2>::type f_;
    typedef typename f_::type type;
#else
    : if_c<C,F1,F2>::type
{
#endif
};

BOOST_MPL_AUX_NA_SPEC(3, eval_if)

}}

#endif // BOOST_MPL_EVAL_IF_HPP_INCLUDED

/* eval_if.hpp
yHeVz9o6B8mXUE19TZbEc8znTBf5fMtFPp/S5HN3yeccyedeBE+H96xrVPmD8r2a5Q9Uxm8uZfzwQnKOyLnjj/UJXeV84u/plTAAq2ErrIfB2AxDsAO2wYnYDmdge3wBO+Ay7IwrsCu+jt3wXeyOP2JPvIG9sGgh0oLlMQz9sS9Wx35YF/tjIA7Cx3EwDschOAaH4gR8EjfjMHwLh+N2HIGf40j8CnWYjZF4GqOlTBuDP+NY
*/