/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_JOINT_VIEW_DETAIL_VALUE_OF_DATA_IMPL_HPP
#define BOOST_FUSION_VIEW_JOINT_VIEW_DETAIL_VALUE_OF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of_data.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_data_impl;

    template <>
    struct value_of_data_impl<joint_view_iterator_tag>
    {
        template <typename It>
        struct apply
          : result_of::value_of_data<typename It::first_type>
        {};
    };
}}}

#endif

/* value_of_data_impl.hpp
CvBFQPyhvnrAesBX8b0BXwOECaR6HfCEcx0mguotwHSoD3sBsc/aD9gd8H8BLwQ8ANgf8F3A0YCgsoVLAXcB3gK4GxDKSv3d5snjYm0mj3jE0WXMzRauVLhy4e4U7m7hNgm3Wbg9wu0X7ohwHwuH+gxzrbThOgrXWbjLhBso3EjhRgl3g3CLhfuNcBHhnhXuL8LVC/eGcB8K94lwaGtlLsMyXDfhego3VrhrhCsTrkK4u4S7R7jnhNsm3C7h3hQ=
*/