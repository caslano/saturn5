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
RmoYjbgoSlMxQfEZRH328fgXH9PnoshI1AmQ60tZFt7Re7OpI0Zz231wNU6sUMGr2vCIiL5DaUj85WmInm98B0OTHWeZO1KgGfV/ZSqWWgkYgcxlyLIWnHAYMEMkEmYVCeupAj0CSuOFGEC8OJIfIWuIpTJbbqJ157/ywxhTzeWxaOMBNRAn4OCvf/hAykQ65rVHMMVAwKTirAfPJPezxYpmWKRfGk5YByZj+Y4NqHkH0/FHYZtkq0bZAsVVcAA1d7Wvs0FFjDaUUaUMu5GV4mBCt5V1XwqFmVCpDDSOuSJSgfrB6yqbokRnNXzEldiBifSqVen8WdG2g+tuAy/MeWBVjxqnJUEsX1oRHr1VxX+USnC/hTesZJI7CJaCwbV33L3hbD03Jyk5J94xiBiBj8+jeILCjKzWz4rLGt8fTAtMCgeZpRz24mG9ZeO/INHKU7inkVR5wORFL14MoaH1mTfaeptW9ClruFBGZxCgEFZVcTZk24lwhe9wjcwoUcJmx00dIubkIp1yGthKJZj2A5BtJQnti0xbeAd0DY7T8oDKl+BKTs6X0U+SnQ==
*/