
#ifndef BOOST_MPL_AUX_ARG_TYPEDEF_HPP_INCLUDED
#define BOOST_MPL_AUX_ARG_TYPEDEF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/lambda.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT) \
    || BOOST_WORKAROUND(__DMC__, BOOST_TESTED_AT(0x840))
    
#   define BOOST_MPL_AUX_ARG_TYPEDEF(T, name) typedef T name;

#else

#   define BOOST_MPL_AUX_ARG_TYPEDEF(T, name) /**/

#endif

#endif // BOOST_MPL_AUX_ARG_TYPEDEF_HPP_INCLUDED

/* arg_typedef.hpp
7VJZLvfX0pf5dT+WUmISwY0DaS3ZNl6NVcL6b9K+hga9sbpH6AkNY9Q4VlTrr6plBJp2VijxDrzjGALQTTwPGfj6L5yQqD2siyQ0qsIfkBPR4w1KrKzlXBs898jBrlzxYvbDC5L4b/Fn2kFTNjdeZF0Foi7kXppLxDW1wQDBm1Ru64Qc71fdTAMbnXxhu+ef9HNd0zkELKZSPmP7l+et9csnJFhmTgnQaxZAOKhVuqM4lUZhVT8rs5uFXF9Yn7x7gpIlU6fmtL20YmJ9y8GD3Yu3pbWVr4WXn81x833N9nd9bYHBbhr71XrTjsKcdyR+fvY6zu/pwrj9FiNp0oB/7H4bt3dwsMleXJqawmAyfFX9zVGgUdejYtSk32oEgvPMhFUB1JyhfvdgN/uX53icM8qzV9XiIsr4jfl2f1sJdFMoGbyiCZItdHXYL7RII/jNQIibDzqFkxTM7oDmFIoE7yN/84E2Lg62vfaFrA2tfzqq+RM4ejJQSb7eNQnsqcEzQysja9D68OQVWcx4rdQHf51qgxh573dC8sRefzcB/a9bklVyX3/Nsuf4njE1MNzG+Ls8gq9nrmeSZVTg+5ecI7DLq2HqxwVbZZ9HMMHblT5APwu5XlNrq+fqXlSrM4+nQgO7jI+RI+uCoAl8A78Ht2xfvnwZg3dWwb9Y8ClTw82J7xItvKugFqZeLLOrxazUvA44Pz44KeLMY5+k
*/