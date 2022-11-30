/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_DEREF_DATA_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_DEREF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_data_impl;

    template <>
    struct deref_data_impl<map_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename result_of::value_of<It>::type::second_type data;

            typedef typename
                mpl::if_<
                    is_const<typename It::seq_type>
                  , typename detail::cref_result<data>::type
                  , typename detail::ref_result<data>::type
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(It const& it)
            {
                return fusion::deref(it).second;
            }
        };
    };
}}}

#endif

/* deref_data_impl.hpp
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
*/