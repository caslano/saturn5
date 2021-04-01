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
mzmA1LpzW5y8twtZ+xVYKT8GtDZAXcgDHP/0vzOFdPvxTvmexAfN+WmB+WKHmLepxqaysGExzcFoXGV/4PUocdxUlIkCPt8BQqEaqKovusL1PWPj7k09/625VPBrKO+Bdt0MZHoK35DeWd9oGt/N9WNQC4K7M1rUezJi9fM9rH0Z5FVBx1/DeFcWcVaQeJ8P1NMkPmkXRD90YCebMTd4NZpg4RZhHshQl8JkGz+AEbNnO84o8Vxlhr2MO1UDSh5XvJqOMv+obHuDZbgIJIMTkvMoAqVSIne4XAx3h9NCdZsKcK3gtcyk1rvW3Nq8tKA6iHd5/oI/GHabAiKhDXME4h9OILbbL2FEuKJgOvPJGZtYELODYaLHZUyI2rOYFWnLTvPM9900YpxpMUdea6KzliqA/zYZqL6e6LFsTdF5M4if3qwdIE735eN14V+7JHAc5ElNEJvSJ+kYZhSgNbBSmTSQEtsbtt97u6Q43fSchOSOdR/540ca1UfAzc+Ezf2Zo88GG5Dn7ZhtoJqKydUAA0CKOxupKFGWVVsF0KxLqhdzT31FuL/VTjq3qg==
*/