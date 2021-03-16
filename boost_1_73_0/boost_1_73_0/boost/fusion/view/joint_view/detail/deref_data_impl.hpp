/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_JOINT_VIEW_DETAIL_DEREF_DATA_IMPL_HPP
#define BOOST_FUSION_VIEW_JOINT_VIEW_DETAIL_DEREF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref_data.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_data_impl;

    template <>
    struct deref_data_impl<joint_view_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                result_of::deref_data<typename It::first_type>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(It const& it)
            {
                return fusion::deref_data(it.first);
            }
        };
    };
}}}

#endif

/* deref_data_impl.hpp
hB7wbIf4H2WsFH9WvDtuknoR34+OoOgde8pXcscPkg47FE7ntbtcREdXa/MG6APNb/CwNtabJ+Xqq3L1ffg/n5+rjUXnJ8kZNevL6Ki3Ze5FGwvfeyUc9aOjEXA0hI7Gw9ENlG6qZTaNnG+ZlYkyy4QOr7DMt62Row2WkcsDFtsMkiiMmNc6n5F7X5Q7dssdn8LRUrr6nVzFHW34jja2WQeEeRJ5RSbhDMixM42zzbfhNpv8bUvl3htt/xriyGQ=
*/