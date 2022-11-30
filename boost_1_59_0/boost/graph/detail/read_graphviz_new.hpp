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
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
*/