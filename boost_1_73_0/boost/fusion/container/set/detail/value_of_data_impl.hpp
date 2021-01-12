/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_VALUE_OF_DATA_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_VALUE_OF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_data_impl;

    template <>
    struct value_of_data_impl<set_iterator_tag>
      : value_of_impl<set_iterator_tag>
    {};
}}}

#endif

/* value_of_data_impl.hpp
bnXpdFN9brG63H6eHrcwHzAbU0WPnNHl1hy3Z2EX6NbpNgi7S69bXTrdjC43tx63YrjcOUc8XrrcJuO+B86GXjrdtuMWq9NtJX5j9bp1yTW63Q5Lr9s64uoP74G7MQE+6tpjhmOKMdWYhzC7Mfsx2ShbH4opxqzEbMXsxOzBJJT6rY6YkZhKzDrM45h3MM7HYeOy/67etwBmyn9u/X9JwaRKXfb/r637d9bQd0uzzB71rG+V
*/