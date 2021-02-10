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
mlkgUzohIMD1IgHPPsENag2iw2bKm4bC7g18jIQGDEqiUK4zBBcnla36UcEjGkYybzli2nDIa0+b2CgWJVv4OMM4kDonM4nmi4CnHPRGBTD31oiolTka68A0bKdmbhPYsD+2WWXYUdaZJ8OsqrAgxBHt7W0I1H5xVLQg1lgRdLhwlQGxxnxYbzzg+dZV1qPyGcm7ykOYINhwE+Bsh8L1H0QJlzZCdp85x7x67pkKq3Akkfov8vEp55B6shxEf6m5+hhWA8FiJKvkFO1yFUO0RFx9+6nwCs3eiu7S4JmsPhTXMmKQJgKjLMhHwH9oN6u0m4fm7a1Vv4mUvk3/NrOQFFFursxYuRXRInXCyLmKvLstZl/K51clTG18fMJosyqPuDdabyCYE35CWZkPtwRW7rPajw21Ve6xdewHfXpyhdUJIDVkybEl8RGufVpSO05JCeSBT2fvXPH+jPpO+Tn1/CfbEpTKS2GRfOCt8DHSktkr+Svo2wnARBcCJvvEqPpsJPyo4pZZ1vixdip+zCCJnfMrItQO6UYSHHEMl+jIORmcftgwfoazbapj8fijYc2E0qSpOIeloiZSMe186vDamRoUtnsc8luj7UZJ3YpKt07sLtdQqqVDkHybaFA3OVpiIXGn3DiuqVL4Vccb
*/