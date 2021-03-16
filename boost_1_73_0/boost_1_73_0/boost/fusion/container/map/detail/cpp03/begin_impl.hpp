/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_BEGIN_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_BEGIN_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct begin_impl;

    template <>
    struct begin_impl<map_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    map_iterator_tag
                  , typename Seq::category
                  , Seq
                  , 0
                >
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return type(seq,0);
            }
        };
    };
}}}

#endif

/* begin_impl.hpp
Zl8NosgjqRVIefP59e9GpBI1Koo8klpp+LnSa45iI+ymKPJI6hnDW/6tQWXZE+LZKPJI6lnD78qTE+s8QVSuYuSR1CqkSrm+jyb+zXrsOsXII6lMI97XjJ5sdBhejDySWo2UN6s89PTXF4laU4w8knrO8NYI++wE6wHOFCOPpNYY/nn1Suq6hrVGNHkktdbwfqPkmiNsL6BBNHkktc7wcw2La3uYqEHR5JHUesPPFRx+8AxRmdHkkdQGw1sj/JU=
*/