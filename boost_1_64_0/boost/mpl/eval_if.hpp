
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
y0SoECDBCIvpzc+nJURbNImC1KMXMdTm/YFkRKzgTea+ifjq24mapvhmeQCAjMBZYi8cVKmBPoWlN/dK1BLrXCz/m615CXv5Tu2LlPK+KzbYbdiVNul4O5G9Ky1omFtwxrCs8/UdCt87wXl0lzv5OVaDsTcWZCVAhzu1J21jBh4cm+3CSOXM4EnhiClQ9ikynzV2iaNgjAlvjbotBwSZTmaI6sM2EfjdxroKPWfXiI5zgUFXGQA36H5WkeqEF8lcybxd13bFzjS/UmvkmdzTdHnMW0Th3+WqpcB88srAnDA0Y5zYLBvyIQepdoX9Adj2E7nRFzCSr0a0ZkNE/kS3Gj3KL/uR7nvjrMfBPtKfIfp/BoBiWvY4UBEVtjfQBQKZSO9QILruW+ONdSVWBpXjHuTXXq9NApy/2nFTojG8DKVqv2ZwzUZcirBZ2a9a3eiq2itf8KCnbDUKH+2aPPrNVIECZalAYZu8Gm79AE5FRSQOxHhajQfhjyqC6FJFQL2Tf2btpUeLZ0bAAuqXK2CPjJ3kwGsnZLqgPhCqvJ3l7kRDAjHb2lsGtSoWcA==
*/