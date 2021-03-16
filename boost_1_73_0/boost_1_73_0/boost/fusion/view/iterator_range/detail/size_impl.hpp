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
GhCr6RjA1zTL5QDgNfhdgNcCfgEII2kYNw+fCJgOOAmwG+AUfH/AqYBDAKcBTnD4WRY/ZwFgps162yJt9DY8Yls2c7OEu1m4lcKtE+5O4bYIt1W4vwq3U7gDwh0UrlG4b4VDRZO5JG24vsJdJtxI4UYJt0i4MuFuFm6lcOuEu1O4zcL9SbiXhPubcPuFe0e4j4X7XDjLMlwry3AdhessXF/hLhNutnDFwpULFxLuXuE2CrdJuM3C7RLuTeG+Ee4=
*/