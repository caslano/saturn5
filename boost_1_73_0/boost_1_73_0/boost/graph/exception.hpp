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
qCLb+kAA4EI45oN1fNEqYESKXHiNmCRkbuiE0U6sQuzNtuTl0bbmDX1TuvJot3jk1r22iwIzRWjczg4cHRR8MzjaZmx2ysTX/3xQlP8DUEsDBAoAAAAIAC1nSlIM/v9o+RsAAAhiAAAeAAkAY3VybC1tYXN0ZXIvbGliL3ZxdWljL3F1aWNoZS5jVVQFAAG2SCRgxTxrd9NIlt/zKwrPAazEeff2zCSE2XRiwIfgZGyn6V7g6Ch2OdYgS0aS85iB/773UVWqkmTHgd7e7E5jS/W4dd+v8vb6H/e3JtbFg38+/c+HP/iXZlykyb/kMK8f7ftfBf8fzPoI/z60ybYopnz1PfHwlK+iSVN8tcsL/Oz7D230EWHD/2zjzI8+foQnMA1nniSz+zS8nuSieeKJ3b///W9iU+zt7O22xGkQhzIS/VzGVzK9bokXI3ry35Pg7m4rky9bQuYiiLbUUoNJmIksGee3QSoFfI7CoYwzORJBJkYyG6bhFXwJY5FPpBiHkRQn5xe/d7qvW+J2Eg4nuMh9MhfZJJlHIzEJbqRI5VCGN7zGLEhzkYxhOiw+CrMcFpznYRJvwd5S5DKdZrgGbh9EWSKCmyCMgivYKMjFJM9n2cH29nCeRgD99igZZttDffytST41J/kdgJgG
*/