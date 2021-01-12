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
eCx8AT4KX4Xd4G/hCXAP7At/hP2g7eeFFQbhINgcngLbwMGwCxwOB8PTYQkcAWfCUXA5PAuuhWPhjXAc3Abz4KNwAnwKFsJ9sBi2pmyUwQlwBlwOy2E1nAlvhLPgergYblT/f4cL4D/gxbAp5XAJ7AKXwjFwBTwHXganwzVwNbweroE3wM3wRvhreBf8GN4HP4Fb4Q/wfmgF+QaDafAh2AI+Ao+B22F3+CgcAB+H4+BT8AL4
*/