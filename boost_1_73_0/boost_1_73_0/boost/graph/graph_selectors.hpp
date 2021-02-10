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
qHMWqp9zIcD94KgCAdOszPuO7mffuRhLVxVqHIBSsrey62IOq913ibiY60eP3Gf1XdaYYUPbt7WSDdM5slQConPF8UmcxJuzTM7BlXdJrW8quQoK1OoOarjK00oConQpugiZC2CO6FzOUvreknIF3VgezPLL6kaOR6hRpda2fb5va85rs7SNqfcBJqE4BYFuLP042L+ozRBbrofzKQbbYIl1KskKt0NMEyYMRRSk19JJ0OBd1uOTE/EztvbQXi9+/untL5hZDIYUnHJ1EkmDt5xwVaaB42/AWOtWj0bTDofcWtzssFvQlI2jilrfqDCVWrQ+MTrZFx+KFo9PNT0eZeWsWj0svbVkgtUFYj/xjNxoO4uneamxWRzShdXKcx0QTSEMPaDfo6ylIP7uV6lrVBNV3g0hes/w7pmq14G05ZMAhQj1/DCYK6tXWkAxEZDX4qEtSh9r4Et5V2UF7KIJHsRk01lfgsrttf/pX5z3Bwd1D/1X57139W/edd61q28uBwcat/bWgFD8qU4sdTp3NHVyin/lzicP9UjUzzw0zkVhVMivzThhQI4vNumxBbnXv9dGY4IpCcV8hvkH/YNDiyHY3OWutfgzXoVl5xpdz3/LNFHpMmEl86o5e50XrUnbA0e2tHCtflO/Ds5/
*/