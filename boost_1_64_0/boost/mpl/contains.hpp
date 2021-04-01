
#ifndef BOOST_MPL_CONTAINS_HPP_INCLUDED
#define BOOST_MPL_CONTAINS_HPP_INCLUDED

// Copyright Eric Friedman 2002
// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/contains_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/contains_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct contains
    : contains_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,T >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,contains,(Sequence,T))
};

BOOST_MPL_AUX_NA_SPEC(2, contains)

}}

#endif // BOOST_MPL_CONTAINS_HPP_INCLUDED

/* contains.hpp
a00BgsG9qIvDRUBdODnEpcXbQSiKLlbXWAL1VU+6WD2gfabMmmGyNt23LCT6Xe0a0H+2hyt1Kv60I7AOGs5UAw7TLnaUOT7g9GaWvskPfPTOovgB4tyZd10nu8lQ8o6ezjlTde4F267mtqifyd9GOSzRX4eufcv8EKhOzl1Du76LySx6CkxCb4+eJSYsqQn7NU8R0KAo9WQKkScgTumRivg1hkWoNmu23oV/+x9av9kKnOHsjCClo8Si8F8R4ekMJmB++WV7YD7b5HufVG3grhxJ5ViIp/X6RqUKP0RwBK6xmxFNNx3jHl/1JNfa52dLJkFr4xWrhpj6DgVhiMTKqCSPk7JNUvq36Lax+iNBC7J9a2MiDiEOi+m13UAf738oB1rSgHRR/+cnzqzdqOXMvdjT/Wxo6Espf4vxzndXOdespIjVV8GfzgGwlSpg7PswlTig2g/zFFwaBI1CGq6xZ0N/R/drNIUG69JFIEZnzNj5ed23KV5atcOY9SkrmdNUMqNXP/IlVES2M5fdmpf5CMeI57ylyq8lgpLZEJWEoOum3lgziVUCiNUwBQ==
*/