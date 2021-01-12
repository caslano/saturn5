/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_VALUE_OF_DATA_IMPL_HPP
#define BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_VALUE_OF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of_data.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_data_impl;

    template <>
    struct value_of_data_impl<filter_view_iterator_tag>
    {
        template <typename It>
        struct apply
          : result_of::value_of_data<typename It::first_type>
        {};
    };
}}}

#endif

/* value_of_data_impl.hpp
+C6qw4HUQeYkaCA+Msl8vW0dHufY0qpcD+7GtCQsOgnedh8vdIYNkBgOLLR7yaCbLh/HON/+LE18O/XimuseB8o5gX21wKL/yVHhdo2tOyGOfZuojyiOkjJFz49phhbLfW9Cbp4USYiuQ2F7uhWQrs8IXbtOGqJSAmDje9pzbAz9CscVmKuF2LTCvKhtgd311o+BF37lGC+7JWlqGEbMpf4q8o1giDJXY1e7rJ3l+d7+Cd7v
*/