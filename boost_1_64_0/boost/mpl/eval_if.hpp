
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
tEDbJvYN/8KNodXe/A/KTvOdpZpi/kjpWmOYfKoJ+VV3NScplVqNOYdTwOZoFxXEya0UmSfb9Zo0PxJX6abGqfQF25CKmt2Ylicm7csvHhVlydlyNIXpo1fJzW7H9Jky075KYp8/1VV5A4EqJNPaoP0yU+PM+VYHvZC0g36zRHfQE+LYKmvhNCl/9SCtgYDdEVXaLC3ECaR0aAItnSFtUcvhNTxuMzUzqjqblYaefjx/AlG3LJBoB8xtYNikNNzT6N7Vs2U57oQlFQspOMTRAJKhgPy7zrR21pP7fhC3noxdn+56EkT8N5TXO0trHdE0peZQsHW7RdxYR44BTUN526yUt41u+mubpvEkuNiknQImwXdm2EkQE7MbDYVIzFY0VKxGfFbpmABn85Fl5Qnhe9yORWk+EeMZ39HsuNKcWrLRnUqU2a+kicPz41Kv2FFgGm5wl31khzfjK8LrFxcbi0YVxHaZlFxQ1laHVJpKbOqML4WGmJ+6E+bMncva4r/upDzj8TWa/yaPf7BC81+L6T6/un2mC+uYOP57m8y8eP77yhyLvQx0spcfq/j/d2n2coenXf5riTpXehJFnQs8mu1ijbWz3b2aKe0Vtru38XhKt53o8JI9ivhZbxvCxUkRfvhO+4KhuVZIzln6jApXFSshMzlZEeRsUFRQz6wlPNsC5uwgwLe69dSQE9Jc3hIZaqZdZGLVjP3fTWqmGWqm0WD8Boy6uV9JCx+DjTA7FaYfFJ6igMzWC8A4Me/oWDCIPYc/bop+zjVOp4WtH5uSNtFqpbqrRQ7T6Pq5qwUOVYG79II4B2vCOVhz6umFfkCw/3vBBQiDZpg+JQhJHInWcPdhKm3B0RotMkEe1Xlntkkram0pZJAkhgVZ2dBJ7gRRoenoo0bQuO9089iKKhhzwCaD/1E/a/4vw/rQDyaasLM7yrl8g57ELkS+ausEJqzAjARx5qyX+5UHhpS3zEwy45r7MCNu6lyyt88mdv4pNtLtX9jvKtOBuxeQ4XqZsSasFVjHh/lLxGW0PiAROdbchNcmeW1XGanjG8H/716n//AqMaFaJ/9ZaQan712ldGFrwTKXV6pX8v1YW8RTdQWmas/IxeH8GTRPK+iP8cI0NU9XyDxdAz3HMpXzEsm5hHM+oHMu0yFLqtjhobG/h3D83vSmVvI1qa1e7yKFYAvl0Lf3rSeN/o8V86KkXWBOq6IlS+rKV/Hmh/5WL+FrOorXhXTUtPrRx8Avo9S4x1b0QUsQlsSZtsSoW93g1DPCK6NUXG7LEKYM9SXrzLPh+vGZG2iirS8zjlpt5RoFg7EGt9NThXxICktyZlxra9OZD1qFjmbEkoJ+1ZbrLxyTJWkjF62ycm3imm9Xfi00cGT6x3+rPLEh5NRSWL6OnsiRhHSQx9QV5xJii8l3ZlGAnoEqfVmLHeRayo3ubYj9lkbVVTmWWlNYvI7BrQE4NEqBy2Nw5XmUZTHhvqgTPaMwfVlDfI5oSDvYEDjg41NgMhu7sdod+orpiuBWoodGL9FONiUb6JwwrDwCVoozyvJ7/62dUdL4Id6FzP+s39xd9Ks+gYUvV3Ug5s7GlvyaKN/YpSelui2V4+hU+noPz/97EuIPHZdQM+vus/nRyJ1CU3Fh8xdkjvck/3VVwZr4JUQ1DfBBGBkULtxHKa1uofJAFK919fzXFO0IQV5UlzIMMlqHipOXOCIlG5wmBxy8Yk1dyk9YYuvrWxgsgWPZA4iFjJ4zxWGknl8p1I7yQFm4l151lV8TBhbmquoXtqBcl2uEjJBRKKl06ZGhJNM/46G7qU4+6cvTvS73eIVmEPkbF9xC1ZP90q3c+a7YoMiF3Hlhfms=
*/