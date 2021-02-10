/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_VALUE_OF_DATA_IMPL_HPP
#define BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_VALUE_OF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of_data.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_data_impl;

    template <>
    struct value_of_data_impl<reverse_view_iterator_tag>
    {
        template <typename It>
        struct apply
          : result_of::value_of_data<typename It::first_type>
        {};
    };
}}}

#endif

/* value_of_data_impl.hpp
uY4NHUwGdPTdd9/SIT1+9PiRQy/8VIqEFkakK5GtHXoa2pUfYv/qytXiuUPCkJ+4JdQylpq0iszOzwTheyIDkWoRkq8pFDrI5Ao/ZEomFhTJRNDk4vLtbP6TQ7tYBjGDXKucdKzyJKTY/yAoE4GQHwqMrZ8ZUhHUAR5KbQCYG6lSF7YFGZFtNGOweT/RivwPvkz8FQz5hmJjtvpkNAryLIH3o1AFehRU4bux2dSRvIUTG/+a1NaQUZRr4RBLOrRRoYz4EwnB4jZfJVLHTuMNTKXhSGWkRZIwFvSk0IXbghZlehwWoy08loY/tEo1m9rFatMRRB4ZJcqzFIaQBwiFCml2KE9DkVlhG3llosypTfAXS9P4G5JK4Qz1xwuaLfq08rXUDr2ZLc8uXi/pzfjVq/F8+ZYuXtJ4/pbBfp7NX6D0EsYyElfbTGgYz0hutokUYWnzv3uNer37Mg2SPBTU5+p5Wph868Z93ohArUimIjx4vZh6F5fT+WJxPvjn3kZT9NBPnzqqPy1+ni3vVNynuZicjefz6fmgNxpyCbRAFoP3Ig01cwfFSwOmqaYos+VFASz9i9AiYNHZ+NepN58uZ3h7s7l31sT8NBUGtsxIpm78vHcfuDL6gt7xFxSPW5qtbMZKmyAWwXtOZrMM
*/