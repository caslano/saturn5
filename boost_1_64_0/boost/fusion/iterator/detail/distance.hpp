/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DISTANCE_09172005_0730)
#define FUSION_DISTANCE_09172005_0730

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>

namespace boost { namespace fusion { namespace distance_detail
{
    // Default distance implementation, linear
    // search for the Last iterator.

    template <typename First, typename Last>
    struct linear_distance;

    template <typename First, typename Last>
    struct next_distance
    {
        typedef typename 
            mpl::next<
                typename linear_distance<
                    typename result_of::next<First>::type
                  , Last
                >::type
            >::type 
        type;
    };

    template <typename First, typename Last>
    struct linear_distance
        : mpl::eval_if<
            result_of::equal_to<First, Last>
          , mpl::identity<mpl::int_<0> >
          , next_distance<First, Last>
        >::type
    {
        typedef typename
            mpl::eval_if<
                result_of::equal_to<First, Last>
              , mpl::identity<mpl::int_<0> >
              , next_distance<First, Last>
            >::type
        type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(First const&, Last const&)
        {
            return type();
        }
    };

}}}

#endif

/* distance.hpp
HRI6vq5+WMYenBsZQK8GNSzr6PiQhqh/3d2+8NEuKkzbATzmOi0cJKotrobLTrUlba39PGD69vNnMS9SiVNqTYH99ffivpp2zp3bbOT1Ouk7cMHEQpRAqWQCys922rIIxKJGngh38L67dxFmvcz4/qQ+e3xHVL+VvU8WafZW3zcdJiyS3jdo7wveKlfSheyN7xgbzCRW5K9xGyMOmrpUyq+f1LZ+7NYtrzonHDN3jgKCQ85qkxkf1QazKpMN36LaOqtvCs1eiNaWfCEOOkwMY9aACVihnJ/EjMufhrtW+pXTpHIfua2AtM/TRtb8ga2vUYLnofcohJWo45cPGX/17tjOi78ZJrwva7lOFIAvnkqD7OF3USg1tqsAcTUw30b1ZpjfBVqsMS0aEcQ2X4Ev8yV8TdWxDkjKFdAgy/Ldpb9XneaGvsw26HpVJ6rJpt2QfwevwS4R8Eg2rKz1wj1Sd3ZIvZdWdffH/DmpM2+LVkKwptNtGi2HfP6MxwOalzJ7jQDHacBkOXDuHsksu8K6WwJoCEh48XBigN3+N72XvCmrDbcCCV43HwvtUw==
*/