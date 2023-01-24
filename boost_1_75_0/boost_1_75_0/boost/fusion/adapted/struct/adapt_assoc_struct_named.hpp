/*=============================================================================
    Copyright (c) 2010-2011 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_ADAPT_ASSOC_STRUCT_NAMED_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_ADAPT_ASSOC_STRUCT_NAMED_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/struct/adapt_assoc_struct.hpp>
#include <boost/fusion/adapted/struct/detail/proxy_type.hpp>

#define BOOST_FUSION_ADAPT_ASSOC_STRUCT_NAMED_NS(                               \
    WRAPPED_TYPE, NAMESPACE_SEQ, NAME, ATTRIBUTES)                              \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_DEFINE_PROXY_TYPE_IMPL(                           \
        WRAPPED_TYPE,(0)NAMESPACE_SEQ,NAME)                                     \
                                                                                \
    BOOST_FUSION_ADAPT_ASSOC_STRUCT_AS_VIEW(                                    \
        BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION((0)NAMESPACE_SEQ)NAME,  \
        ATTRIBUTES)

#define BOOST_FUSION_ADAPT_ASSOC_STRUCT_NAMED(WRAPPED_TYPE, NAME, ATTRIBUTES)   \
    BOOST_FUSION_ADAPT_ASSOC_STRUCT_NAMED_NS(                                   \
        WRAPPED_TYPE,(boost)(fusion)(adapted),NAME,ATTRIBUTES)

#endif

/* adapt_assoc_struct_named.hpp
YkPjxL8tFQVrZlfGiXJSsKkfo4L9+zkq2JhCOU48FWOOE/NamuPEpH+Cx4mfWjcyTiyT48RyOU5UNjxOzD/3OOETlZWX4gjb+Fjh+Z/Gim6Z0nB/3Ltphntfq//jWPHvrbLKlCZW+UCr+saK0a3UsSKzVdBYcXWrJo4Vi3c2NlbUdDX9f82/vu9K0rmRr6u74uiwrCuOFcNp5JjftQljxT2TArYkYYiIRxHeneElFxECLLXCWR9qqUaLb8Zo8dTkxSR0c0NZ1j4IJbOeQ2Z9Anq3ZLPgZQfY9bJQMlbZxoO9ya5nu4s2oV3vCGkpwa73Irtud65J18Cw5wQY9hw07H/HUiYK2GEZSfAhzThlE3u2QG0XhyqSPo0lfS73K25IOWbFos6FL54HCmnfJy4jwXE02aWnCaM4PtYyneStKl+8KzZWukauEw9ME0/ezLPRxgHsBdjyaWzLXXiqktoy9lz6Z0euyjCwvBlHoW1Cf91qqPBBHh2zjIRedjEuTNDy73BhJE7J8fzbhNTfPQc9iw0tFF13W4tbF82L43fGXG/XahPErbZcak8IlmojbnUwS910PfRPPpyIAe4EwDQKez9GjzUzldfayNnE/43os0EFJ8QfaBlEs6XHxSpf012PtdoHDUjZEhwSROe65HhXGNBGHWJj8bv04mnqgJdLSAngPud3GDGohGJ8YBa7I4vrYiwW+wGL/jUj+6T0
*/