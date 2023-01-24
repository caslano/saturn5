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
EXvUa494009gZiC5xp7R7JLpVoCQCwOAUVDgXDrhPrm/JFqscMcB0z/zPn3GCmFtaJ0bhSURh9STnqVoEp2ZIoRSN+6HZsZgRriLrsnfj95A1ICzi16DwYvE/8YJdRPVBt3hjyYb0rkPAEPQNqYNkgOKAwbgjUmw2gGBVIMy5TDVl51IG+qid/NoIJQuJKStKIHaDcVnRJBK1Ix5NVCEtBVnbHiygjD628Kj2c6v6J+USYxRFkjTpA309DHyIit8A8BrADvF3pC5sNiXtZhG4R2A3B/zSDD1Uwa/S+vSmcupMr7LXLLOVwDrWdHZGsLaN8ynE0fQYSnfbJMo+UoU4sVE8JP0G6WDskS/Uch+oiOsgkZhjUqMtKHju/rVIDxXfpnzcKES4XuJVOldrZrCoiQ+fJWRA3uHAP27AzFuxpLvvj9HdWmkb1JypD/TxVRk3Ky+a8yXhtOb5XOnLQxZt5OSNxQbzCAPz2lMe0k8BZOSK+eErYREp4HGgcxoauaVNzAkGFX86NV+9mnC27HDjpBoHny+8UPpT2PbI3rL51wY7HWnCZvD7wjbLWvFU11w/LF/+mg2aqUM/nBsIgMXTaap0qXKu82mPNqobVLxl/KSCJoxKnMU5hWXqOpVTqyttPLsQrf2f4Pc/Fpobe5v/bm0vnPtjAVpx0De1gHO6ZgC5/hv+HGtS/GDuFOixwGKn89IahjyKOQ/AMe7
*/