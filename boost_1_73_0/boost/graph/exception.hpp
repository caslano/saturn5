//=======================================================================
// Copyright 2002 Indiana University.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_EXCEPTION_HPP
#define BOOST_GRAPH_EXCEPTION_HPP

#include <stdexcept>
#include <string>

namespace boost
{

struct BOOST_SYMBOL_VISIBLE bad_graph : public std::invalid_argument
{
    bad_graph(const std::string& what_arg) : std::invalid_argument(what_arg) {}
};

struct BOOST_SYMBOL_VISIBLE not_a_dag : public bad_graph
{
    not_a_dag() : bad_graph("The graph must be a DAG.") {}
};

struct BOOST_SYMBOL_VISIBLE negative_edge : public bad_graph
{
    negative_edge()
    : bad_graph("The graph may not contain an edge with negative weight.")
    {
    }
};

struct BOOST_SYMBOL_VISIBLE negative_cycle : public bad_graph
{
    negative_cycle() : bad_graph("The graph may not contain negative cycles.")
    {
    }
};

struct BOOST_SYMBOL_VISIBLE not_connected : public bad_graph
{
    not_connected() : bad_graph("The graph must be connected.") {}
};

struct BOOST_SYMBOL_VISIBLE not_complete : public bad_graph
{
    not_complete() : bad_graph("The graph must be complete.") {}
};

} // namespace boost

#endif // BOOST_GRAPH_EXCEPTION_HPP

/* exception.hpp
IWFdxDOvW/Ro9UT6jB6Nox/bdouuNaN6kKdpW/k8Wh3VjT6LYryhJ1Pp0Xvq+77RmN4gmkScv0EQ06MVW8VWsVVsFVvFVrFVbBVbxVaxVWz/1+11NMf+SGLfev9tzzd1jq2TdujjmQH7b6ayy9/OtLiU7ThirS7CbWw0Kjouuv9llhaymY8SVefzRuu5u6fG5COD30uC/YJQFmNmFT4ta7pJPqdWt26uH5Mv3740EtB6V17Y
*/