/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_DEREF_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_DEREF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_impl;

    template <>
    struct deref_impl<map_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                result_of::at<
                    typename mpl::if_<
                        is_const<typename It::seq_type>
                      , typename It::seq_type::storage_type const
                      , typename It::seq_type::storage_type
                    >::type
                  , typename It::index
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(It const& it)
            {
                return fusion::at<typename It::index>(it.seq->get_data());
            }
        };
    };
}}}

#endif

/* deref_impl.hpp
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
*/