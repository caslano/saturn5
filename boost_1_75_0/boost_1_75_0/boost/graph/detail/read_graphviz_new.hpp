// Copyright 2004-9 Trustees of Indiana University

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//
// read_graphviz_new.hpp -
//   Initialize a model of the BGL's MutableGraph concept and an associated
//  collection of property maps using a graph expressed in the GraphViz
// DOT Language.
//
//   Based on the grammar found at:
//   https://web.archive.org/web/20041213234742/http://www.graphviz.org/cvs/doc/info/lang.html
//
//   Jeremiah rewrite used grammar found at:
//   http://www.graphviz.org/doc/info/lang.html
//   and page 34 or http://www.graphviz.org/pdf/dotguide.pdf
//
//   See documentation for this code at:
//     http://www.boost.org/libs/graph/doc/read_graphviz.html
//

// Author: Jeremiah Willcock
//         Ronald Garcia
//

#ifndef BOOST_READ_GRAPHVIZ_NEW_HPP
#define BOOST_READ_GRAPHVIZ_NEW_HPP

#include <boost/ref.hpp>
#include <boost/property_map/dynamic_property_map.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/detail/workaround.hpp>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <utility>
#include <map>
#include <iostream>
#include <cstdlib>

namespace boost
{

namespace read_graphviz_detail
{
    typedef std::string node_name;
    typedef std::string subgraph_name;

    typedef std::map< std::string, std::string > properties;

    struct node_and_port
    {
        node_name name;
        std::string angle; // Or empty if no angle
        std::vector< std::string > location; // Up to two identifiers

        friend inline bool operator==(
            const node_and_port& a, const node_and_port& b)
        {
            return a.name == b.name && a.angle == b.angle
                && a.location == b.location;
        }

        friend inline bool operator<(
            const node_and_port& a, const node_and_port& b)
        {
            if (a.name != b.name)
                return a.name < b.name;
            if (a.angle != b.angle)
                return a.angle < b.angle;
            return a.location < b.location;
        }
    };

    struct edge_info
    {
        node_and_port source;
        node_and_port target;
        properties props;
    };

    struct parser_result
    {
        bool graph_is_directed;
        bool graph_is_strict;
        std::map< node_name, properties > nodes; // Global set
        std::vector< edge_info > edges;
        std::map< subgraph_name, properties > graph_props; // Root and subgraphs
    };

    // The actual parser, from libs/graph/src/read_graphviz_new.cpp
    void parse_graphviz_from_string(
        const std::string& str, parser_result& result, bool want_directed);

    // Translate from those results to a graph
    void translate_results_to_graph(
        const parser_result& r, ::boost::detail::graph::mutate_graph* mg);

} // namespace read_graphviz_detail

namespace detail
{
    namespace graph
    {
        BOOST_GRAPH_DECL bool read_graphviz_new(
            const std::string& str, boost::detail::graph::mutate_graph* mg);
    } // end namespace graph
} // end namespace detail

template < typename MutableGraph >
bool read_graphviz_new(const std::string& str, MutableGraph& graph,
    boost::dynamic_properties& dp, std::string const& node_id = "node_id")
{
    boost::detail::graph::mutate_graph_impl< MutableGraph > mg(
        graph, dp, node_id);
    return detail::graph::read_graphviz_new(str, &mg);
}

} // namespace boost

#endif // BOOST_READ_GRAPHVIZ_NEW_HPP

/* read_graphviz_new.hpp
AN/SNB6Dvc3/GoVU1pVhbuVkD6oQM4WdVQWFQ3KAsBi0sOABixpYcG/EIazEy/WJnKAnoD08rGB+mbFMCNnmqSP5Wl8xQxXSJcjgmi6gjTfERyWhzFKKPTsecLQTT4ob6VH25OPZaDEeeuoQG6kUk0aEb3WBBr5+Ygrw5YFQfM8g++M1DtkiDpliDFJVyBxKUulOBhnySlX6EHSYOBh0MzTQ2Th0HLimxT9IPDY3gAQklRbOCJWEpC8C0P4kzBlIwgGADkbGcV63J1yNz4Ih3qF+WYdAbz2okpSpvoWBbRqMplqww7R1f39d2ub8i7TlIKcOCvKx9yJALnSHQAZ3xB5tBWvii4MGZmGvpgfjVqjywRShUG4PmYlnQHhL69BungMv1iZPaTJXr2S9T00b9jkOY2m6AH4U1toUjbdPoyOXMJsdXuKf44IUXWkbVGB+pq7UOFywvILmjJ9S4Qqd9mCWW/gJfK/gUT/BkatfTmZuBPQnz9RLwzCRPgRSQuePC1mvYmif9uEhBDPPQsdRisdvyOf4cOAczUfvSb9MmjMbIJDmzMK/Y7Fvb4pGb2ExYEmHAqVowz6ln1S7I2/oIJ9f2hsrnv0BVwvNhJvb20hPi8xMD/lbpV3INPmc/8hUsIA38mpKe3ki9pYwJBISAeFYpQra/a4sdzyBK5znJH4HjCrmY2WdGF+amIj4HTKx/KWz2FPp4kTEiA2n
*/