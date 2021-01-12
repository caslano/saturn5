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
/pGRw24WYjK+YmR0Lxakcn/VYMRuvKF/TdL17jvxf71D17vthv6Nls7C3vkY+wvZFyjNg6btwvDq8EpWtn8YXXc3aAjzayNbbslw2/uN0CH5z1r6b4nOb4cy9N+NpO8x9LOGLk4fky1QGXlEjmhjPxyFwdydz4V/ZDAjL0Uy+fmjHOe0Q5nq4ycdXzN+M/n4M/HKIy0sr38xmO6mMOszqDyd4BrC/IIwIvKI190vDYZOQfI+
*/