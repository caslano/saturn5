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