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
0ilOWtB3XHK2xWgEA8j9Q568uBZFIP08plcUGKAlBBfQLySUjQLnhEFDy1RZbVSJ3s44EK56K8j2031VPwsxG7RGnShzD2jmSxCGqXimkcoQRrowJATaYT9nowoLGWzRCalZoy8JGA8qOQzMAEB8vUu14mi+3Mj5DPehDisfkvnubNfUd/NqxbNIgkeA8SnuHksbK0UhJzUJa1qwa00isizrF6e2vUoP3v/UuIqI8N4bZ6shKTbuAUM9w6o5Llajz2slb+JGk09V7+tO6T5QD+SlIrNHd9GOhyHUsC2CuCy4pbX11XF0rs80lgdOkF642neRH/lc7DTOVIJE3rY6n6cXj5Hlr7my8Z/U3CDUQIHPaYNXuU6geo5apOEdBvCa2aQtGY3jpRv/XpEbf8xqnwBx5T1yIEScmICp1BKorVILZ9CVSbQKVVfIIIW4ahYwjW3JMVT23YfDGJsu+Ngn3XpWKqXjjekhsUyOSSkVhiwakixIXHVT10cVQkuNxCP5rD/4MfmFqlL9k7qeZsf3b9DBgdNYRLoyYd4bdOVNh8EhNvuTfrRZH73pvQ==
*/