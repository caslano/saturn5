/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_INSERT_10022005_1837)
#define FUSION_INSERT_10022005_1837

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/insert.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct insert_impl;

    template <>
    struct insert_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename Pos, typename T>
        struct apply
        {
            typedef typename
                fusion::result_of::insert<Sequence, Pos, T>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* insert.hpp
f3Lk51Y2hxmdXnQQO11P/aaWkNK2rT7W6fHUnhFsRaNnki7rdMejsc6idEYN/gk2WL3jPrJ0x/W3hPrbo8v+3nCf0d+2E5f39w3H/7K/p/dRf79Y3Lm/Kw/E9bdE72/Kf+1v3/2d+9uzq/56sMHqg+WqFvO1QuuwVwSvhxY6xUqTI1MzKx/KMQV67HLlAC2WbzMTjD2uh4T4rLyYqv8QcjFxBJCVac44cAk5vNpJCj8na9kTYH8NPLnMeDy5n90Uj4d61qu0ooL4gje0sMmkY8mF3zYzJFoPdDZG1LPjiAkLX4ClZsMi8Sn783d7lSlOuTBF+mVdUTg9T44sS/NHnLANtZiDn2ItjrfN/wuYtLeqOrMVPc70sni1/xQmxKspP0+jCB4C6NBs49426947djrD4zoUeNbM3+3CHADT0cTZDjeKW5nGFlBVi/rmwDTHrpVXkFVBq9WT4hXQhDm9jVT2K/UncsinjMwLcHf523T3Ho3MI1wiLfpHx65Vg6i2xLr+yHVN0Es6NwqGSyaA50NxJgAR+qZ2L2N/k0PHaCfZyx87jolziMFPJ/SCh7Vhv4f2JFyfyNfXievk54xOksdiGAhTC/T8Hv19yhwQ3D9Q5jy4aTiJQfPXVB/yhT1PhOcoW0ZDVRE5zR32/07y1PnCc2p4e/fXyIrnDngZGs3tUM1foXOKZ27Y83vFc2/Ys07K9K/zhee/LV3r
*/