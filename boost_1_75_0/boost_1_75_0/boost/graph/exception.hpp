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
PofCTZMbHhEzBQUb7Xghf5zEnMnuByf2Cc6jBlrnFl8U+lVXTHZ7HqvpNXDt39LHhNizOX1N/vA/8r0j57Q3+N+bra8Bth3JWfnZkw5ale0WjteZ6qqgd/o6iws63/B8vLyPk5u7OI1jcFy0zRNe1rgrgCfqhVmtpw018csmmObKJCnPbb5mk4SfXt4/YPVRmbfrH3L69mcMm4P+fm4XuDJdrSen4g75fkql8/4JV/0y0jMoSA+gaCkffVGHwhW58egFXvlJ0IZbMVc2dhq25LDx7btDsUE5zZHC6BPAkgdDvZtNZE4vNf2+EPWV06zB5Y4gYAi0PcyS5ZUXYmXO1SSta564R1LPCFgb985e3J3GmBgCfjSxHTwOZWGy6DsOymXleF6RtZ4TXzJGsvZ3RWcLQoSXfDGZuxrIWA06L8FR4NKDV7iT4ubqlG1kDnDzd/bHV0Oq7MbizgTSlff3tQRXTFIb7XOfHO4rOC46ynPXmOWInzq3yaGE0DZ7oYGjwZWg+IaZ+tH14aLN9JbHmc3LQ7U8KyYjg7qcCV3zBouzulRDLWmioUIqRkdI/lCepG44e2e5bzf5Xbxb7RBO/4Kqnnvk+KGMf+pQp0ReErC0svptnbFn/dzpx7liXJdpiQSotLgd8sDVUJdohUgtcJb65z3qtBhvRLtHll8Ob29PoGbXQ3beTkkGoK03bV6Ko9F+XF9aiaWReN8L
*/