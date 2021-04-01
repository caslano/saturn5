
#ifndef BOOST_MPL_AUX_SIZE_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_SIZE_IMPL_HPP_INCLUDED

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

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

namespace boost { namespace mpl {

// default implementation; conrete sequences might override it by 
// specializing either the 'size_impl' or the primary 'size' template

template< typename Tag >
struct size_impl
{
    template< typename Sequence > struct apply
#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x561))
        : distance<
              typename begin<Sequence>::type
            , typename end<Sequence>::type
            >
    {
#else
    {
        typedef typename distance<
              typename begin<Sequence>::type
            , typename end<Sequence>::type
            >::type type;
#endif
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1, size_impl)

}}

#endif // BOOST_MPL_AUX_SIZE_IMPL_HPP_INCLUDED

/* size_impl.hpp
3IyHoiazv4Htr3Nh0ZANCZ8oY0aVrT2OROg8o9mtnobOGbARxPdws+i9+t/Zw0RcKc1mVbqKSXRLOONsly00WsuF8K/v/IkGGC+4H3buG4rcG4e2F/ZdTB/m4U6v7deirLgi9KOpstU+1zm8KFaPoCS9VEB7o2OZSpyXRpETaVoKOynrgJBiqs8WQCIm0lZvsdLPWsAxmKiyBKfYVZiTZhYdA48pjNBl6AAseF05WhjGpEajDDXIE1zzF2uWRzaQjusXKY7tfjnd0tr0sKhV6ZNzLTKZqKXJ4W3gy80v9gwyPqgg/cFJ0auNN/ozs7++yLa4iyYDmSSV/bTkGGiISh+S1RuO+jJgeXwu2rDbtNYTzCrwzjmfFfJ0BXt7cjM7cGYKSkQJT/XHoqOQB1lxausjweQwLpolacplNvREaqUEBQ7tN1Q153wlyrt4sJxgL72Yh47HOlAZCTVF04iypaqsv+B7hFcr1jc5IM2cY7xV9D5DFMqu13shy/bMekKQhfD46Uj5WoXNNAB6/qPeYc75UFroZROdWRDbHxxggBY4UXw2o41uKk7orw==
*/