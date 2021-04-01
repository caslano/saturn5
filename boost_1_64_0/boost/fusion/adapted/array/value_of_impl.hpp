/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_VALUE_OF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_VALUE_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/remove_extent.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_impl;

    template <>
    struct value_of_impl<po_array_iterator_tag>
    {
        template <typename It>
        struct apply
          : remove_extent<typename It::seq_type>
        {};
    };
}}}

#endif

/* value_of_impl.hpp
VwMSy3hZ7/Masj4gpe0CoTq/dKWnY4+Z5LzZu7bWP3lqq+tRFuz14ysjOgUvPABj74OzMF40QY4/thGzFDHotjxCnbd18GcAViBc5++lNVi3RDMK62SQ8n1LtpPGAcJddEAHQaL0yIg7lY+w8st0R+YCdVxad4fwLWiwcdemMYWvT9Sotf88p8uBWlTI+CUJR4H1B9rVwLTqFbImPhQVTS/bsMiTxyyxOxg31ang7lfDXOJzJqlgD0tSUGHc299GRwUpR3abICINyhfvMDgqEADEEMPjP5ufd8EQy4Ro4bStkp0Zo+jm9uDfeYQE5HE0/+tU0VE+7/fjWhhsg0vInzzQ4UTYxZ8rO8Gv6vlvoPCx6bEq4jjTRoqYI4nDISreecLIFcZRfTflP/HbKOR+RnV2+U619eF/Dzc5NzfwQ50Wxn/y2JZJ340gT+VabABiknocGCD4ZTSR9XS9jg8yEIsaNeiFix/Sz1zk4BAudOUPpCy01CIkNTMS7s5OUh118BU6/cGmc8shHiFrYVb8DzBUvcyqjl6oXO0Afj6fsjYMzxcVveThcWUBfw==
*/