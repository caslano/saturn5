//=======================================================================
// Copyright 2002 Indiana University.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_SELECTORS_HPP
#define BOOST_GRAPH_SELECTORS_HPP

#include <boost/mpl/bool.hpp>

namespace boost
{

//===========================================================================
// Selectors for the Directed template parameter of adjacency_list
// and adjacency_matrix.

struct directedS
{
    enum
    {
        is_directed = true,
        is_bidir = false
    };
    typedef mpl::true_ is_directed_t;
    typedef mpl::false_ is_bidir_t;
};
struct undirectedS
{
    enum
    {
        is_directed = false,
        is_bidir = false
    };
    typedef mpl::false_ is_directed_t;
    typedef mpl::false_ is_bidir_t;
};
struct bidirectionalS
{
    enum
    {
        is_directed = true,
        is_bidir = true
    };
    typedef mpl::true_ is_directed_t;
    typedef mpl::true_ is_bidir_t;
};

} // namespace boost

#endif // BOOST_GRAPH_SELECTORS_HPP

/* graph_selectors.hpp
C4u9h1GncnXcfP6BBdvASuoYJa4mInblK7C5nnI+bsOIpm25zJzH8L7vtM799ps0vYKn71hnwu2FafHZWgce42AYmNnZK6ssDdtYohWTbb+zcVTnER3832b+mQjedxSGxY+qUde1cu9KpcADHiNgrMP2wk4hj5zFcfwi1aAyt3YsoBK/TZfzGE24+H/Knmw7ih3J/pj5AMA22E9IqX3XwfSdnqc6BhdcD22b4wLu7b+fCCmzKqXMtJkHlkoplEo=
*/