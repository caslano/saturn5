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
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
*/