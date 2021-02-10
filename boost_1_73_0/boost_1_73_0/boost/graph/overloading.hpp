// Copyright 2004 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine

//
// This file contains helps that enable concept-based overloading
// within the Boost Graph Library.
//
#ifndef BOOST_GRAPH_OVERLOADING_HPP
#define BOOST_GRAPH_OVERLOADING_HPP

#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost
{
namespace graph
{
    namespace detail
    {

        struct no_parameter
        {
        };

    }
}
} // end namespace boost::graph::detail

#ifndef BOOST_NO_SFINAE

#define BOOST_GRAPH_ENABLE_IF_MODELS(Graph, Tag, Type)                    \
    typename enable_if_c<                                                 \
        (is_base_and_derived< Tag,                                        \
            typename graph_traits< Graph >::traversal_category >::value), \
        Type >::type

#define BOOST_GRAPH_ENABLE_IF_MODELS_PARM(Graph, Tag)         \
    ,                                                         \
        BOOST_GRAPH_ENABLE_IF_MODELS(                         \
            Graph, Tag, ::boost::graph::detail::no_parameter) \
        = ::boost::graph::detail::no_parameter()

#else

#define BOOST_GRAPH_ENABLE_IF_MODELS(Graph, Tag, Type) Type
#define BOOST_GRAPH_ENABLE_IF_MODELS_PARM(Graph, Tag)

#endif // no SFINAE support

#endif // BOOST_GRAPH_OVERLOADING_HPP

/* overloading.hpp
DssVeCaQUqBTiluCEq3K5p5XZaQr2afqMmvr+EqlIbn6ATpNpsQgsnEz0mZdpqFnKap1VaNKLFc6KukjUv7R44eEQoG5RWgI0ulSjmgdMV1OolyrFUU073O7TquaKmq1EuJK2B/mUYbTssD0WlN/Et8vYV+KCwGwOIja3+3hfGn/bZRh1WNoyL+himyikx7cjvfXfsde66fdHzgGi+6KYvfKuyAFfmDHtSxNsvItRYlnT4amlmOoS2PREiRyAHhyH05Ik3Yv/asgrELxGn7fWsEafP3CTdtz8yrX2jHlIh8M/MN4sfz1NYZ5BT9GqtCS1AnPq0Fk5J9+rmI5lM3BBNYngIlQz4BVXY06+GXh2OsZA/6KwsZLzWYm1qvcGlBYHY3UlCwM/5VRftz04613g7VUucRNwwQ9LMZ1U0A05lHnpCeUX1kLoDfMermgVOqa+HgJkWKywmyNydBk+ZCj+ibnM58WUibUZbZKjeSdcWjdikgydjZBmthU8haVI995ntViqkJYOWsCcIfF9msVniwO7yf+MkX/MWUMkOEIM5C6pbovpHm+dS50vASEuSDB0PXrYIIX0c39K28uTtVEHVpBXrOJF8qM5vyODHMYA4DWP458pzFgBxhiHsBCeKz1eeE9N0JZczDTIzY3
*/