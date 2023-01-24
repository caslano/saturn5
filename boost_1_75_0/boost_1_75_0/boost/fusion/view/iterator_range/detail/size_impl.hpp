/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_ITERATOR_RANGE_SIZE_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_ITERATOR_RANGE_SIZE_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/distance.hpp>

namespace boost { namespace fusion
{
    struct iterator_range_tag;

    namespace extension
    {
        template <typename Tag>
        struct size_impl;

        template <>
        struct size_impl<iterator_range_tag>
        {
            template <typename Seq>
            struct apply
              : result_of::distance<
                    typename Seq::begin_type,
                    typename Seq::end_type
                >
            {};
        };
    }
}}

#endif


/* size_impl.hpp
yazrousviDzknFbzs+GXtL8xstnavre/cvXtiS/UfqPhh99HOfs36zS0PTgROWFkn6A7a7XdOD2+f9jPj32SuP7WtZ/tipy4a+bo9xbtn/Vr+Ox/jfs2uE3w3TfsWhB3877t0SsveznL3alHrQ+n1/zX0rf2x2yvkdS8SUHBvmmP1tt6bmJW7IK3H+wxu+23X139a8vOtwx6xDmu59PTjjQrCWn+4cMD9++c5pxemH3o2r0bc6fXvCU9Yuy6mFf/qBG2/+Z7Bv/yc+ltdS/NjRkX/fDkbz8YtPjw7QsazAgpjVky/4Gmp4rv/vJ0Yo97t1y5MeKFF9LeiI7q8u30bpHj2jQ4FTZ99NxhG+aGdBnWPL/3Fc3GJow/4tpYs+HgeTc3avbPJjNzwh8dcNWskL+ipz9z1XUbPji9IX7LyIScNnUnbx/T//j2Oqs7R0/f9uSE6BZBu0LvHt7tyxqdoh7NGjf3pi1JibMnnRz6yYEfIsYdKa21o+Gh0/M+//ClL2ccj5y5/diBepfMKxj3ddzI+aMnxY9/8ebO16fPrZ/x4mU1Pkz5R/wry19tn9sja+a57yNm75z5XK8NUQe+jl8Ze+Ta09ltZl9SErm4zZf/6vNQo5gX50/Lenn1LbEbbzv7Tud6t34S9FTiVV+2PubcFr9u4eNRDX4NavTMs+vSP+05f1RQrWc/fWt4bvplO09duzHq8dCWnyc9
*/