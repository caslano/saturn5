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
RyuuehAYnXwctExJndNdSc9/mvHg36b3MNmuuxI0aBRB8+SChpWfJ+QNp8uygxpDrv6jQEgW6MXX/X3dAyRn5pBPzhNpLU+2GHDQLpXndBwcY50Npbr745VLpDEV3licUkpqW/phQZSBJXcZNIFMhgRkmBTRMR+bx68fDtlLet++/7oDwGwmMg4jSTTWy4q/NGowUjBSeCzbBOhAU2zlQVm8cDZI0eSLdCTKxrE/I9kvVD6pIPOwKsAgamyAgPSm5QB//ZjAzlD5UqjeVZdDYIxi2l8dvYCeAJv4N4KBUDQVela59GxGtZc7djnWMsYssyQKagH5nUNPe+n34LzQb7HpcCQwKHnyuh4m+yTPRKe5G0TIX1V54EgYDMvZEns+z1LRGxbnC5UaGO8DWE9q8mBqIEzk8MblF9Mr6FZ2geniscHUfzWp0Cp8fghXOYodZG5CvNY5rNpEmeAzlnT6v1WdihSWzRO70wjYfICFh9Z0KUXb302Q4gm1fhEmf5b/FEVk6pbbroSerdGQLmhFsqMBTUm8ukb5TOfMrl1YYUMYp0jbZTHhT9AW2A==
*/