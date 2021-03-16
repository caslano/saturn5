/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_VALUE_OF_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_VALUE_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_impl;

    template <>
    struct value_of_impl<map_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                result_of::value_at<
                    typename mpl::if_<
                        is_const<typename It::seq_type>
                      , typename It::seq_type::storage_type const
                      , typename It::seq_type::storage_type
                    >::type
                  , typename It::index
                >::type
            type;
        };
    };
}}}

#endif

/* value_of_impl.hpp
kVS8OFfL1jvDiepWnzySqu/jfdSscyvYU/bi+uSRVAMfv+aLj/uSrWK9VZ88kmooqGIhue8R9Wt98kiqkY9fUcFny7QjqmQD8kiqsTjXG616vE9UrwbkkVQTpNxFf3O6xZUSRC1sQB5JNRWf19763X8i6mgD8kgqASlvXH73hapsj+PHBuSRVDMfvw4/nhldiajohuSRVKK4Np5cWLYyu78akkdSzZEKc313f6t1iqgpDckjqRZIebOv5u1+ZzM=
*/