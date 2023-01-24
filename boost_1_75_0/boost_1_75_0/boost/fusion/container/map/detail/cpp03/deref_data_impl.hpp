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
WceNINpEn7Z8d+hSauAS4vy9Bfyu0BpKBKuE5V8V/RJhWYpKjpsr0VfU3clnl9ZgmS3FcMkob+Ckmwmb1JKgHQcCbQeXbAQ8NVl//O4G2qX2czhpMIUPDSb8z6LPfw3W3/ZNtt/godo/XyfjPTmCjFcOIspLz3PhhuDKu5u1zVDMMQO1y3KUHZnAZthecvJKILkTAzdr6g0uO8kGjW5srXympsrPYbr+VK/u8vm9qaLUBmJHijF4X6UxwB0DHC5KcRXRNSUTe1qWacgIJIKhiY64vNEQJhjhevoVvZ8FHmV/yfpGcbCUnkhyzhgJq/tucHmUe/0fmnN5WdTkjxMtytNP5n0MPIdPtO/CB2Fat6aDwNKgQ+QW4CM7zviqauLmonWuH2EqWYCRbW3NLkQbc2moI91vU9FVOiu2iX0sH2tWTZZMYVHjbFz+B0jNi0sWtQaRqm1d4yxoy5O2cGowD+SzpoEcFfJgJnXQl+D5nA1FqJxkhYgMmIpoeGGHV4EpXF0uM+dzDSLpfgQEvMji5hJwfZ3Sht/Pvx9iqBEkmdyfHjTvaK6uckczSShMDpFQyC0/Upyjp+RGkPhr8cihR9rGW/73yhJMlVWFL2CwrQIek8UC/v1Hu256rKNXeSTJqzyegnp+G3pr+emrwHtfUWcC5xNPQMmVimbAwSirK1pKZoDeB/6vG1B6uzrbTag9YyDe95PFYj20MdGy
*/