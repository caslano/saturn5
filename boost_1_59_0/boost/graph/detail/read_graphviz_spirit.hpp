// Copyright 2004-9 Trustees of Indiana University

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//
// read_graphviz_spirit.hpp -
//   Initialize a model of the BGL's MutableGraph concept and an associated
//  collection of property maps using a graph expressed in the GraphViz
// DOT Language.
//
//   Based on the grammar found at:
//   https://web.archive.org/web/20041213234742/http://www.graphviz.org/cvs/doc/info/lang.html
//
//   See documentation for this code at:
//     http://www.boost.org/libs/graph/doc/read_graphviz.html
//

// Author: Ronald Garcia
//

#ifndef BOOST_READ_GRAPHVIZ_SPIRIT_HPP
#define BOOST_READ_GRAPHVIZ_SPIRIT_HPP

// Phoenix/Spirit set these limits to 3, but I need more.
#define PHOENIX_LIMIT 6
#define BOOST_SPIRIT_CLOSURE_LIMIT 6

#include <boost/spirit/include/classic_multi_pass.hpp>
#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_confix.hpp>
#include <boost/spirit/include/classic_distinct.hpp>
#include <boost/spirit/include/classic_lists.hpp>
#include <boost/spirit/include/classic_escape_char.hpp>
#include <boost/spirit/include/classic_attribute.hpp>
#include <boost/spirit/include/classic_dynamic.hpp>
#include <boost/spirit/include/classic_actor.hpp>
#include <boost/spirit/include/classic_closure.hpp>
#include <boost/spirit/include/phoenix1.hpp>
#include <boost/spirit/include/phoenix1_binders.hpp>
#include <boost/ref.hpp>
#include <boost/function/function2.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/property_map/dynamic_property_map.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/detail/workaround.hpp>
#include <algorithm>
#include <exception> // for std::exception
#include <string>
#include <vector>
#include <set>
#include <utility>
#include <map>
#include <boost/graph/graphviz.hpp>
#include <boost/throw_exception.hpp>

namespace phoenix
{
// Workaround:  std::map::operator[] uses a different return type than all
// other standard containers.  Phoenix doesn't account for that.
template < typename TK, typename T0, typename T1 >
struct binary_operator< index_op, std::map< TK, T0 >, T1 >
{
    typedef typename std::map< TK, T0 >::mapped_type& result_type;
    static result_type eval(std::map< TK, T0 >& container, T1 const& index)
    {
        return container[index];
    }
};
} // namespace phoenix

namespace boost
{
namespace detail
{
    namespace graph
    {

        /////////////////////////////////////////////////////////////////////////////
        // Application-specific type definitions
        /////////////////////////////////////////////////////////////////////////////

        typedef std::set< edge_t > edges_t;
        typedef std::set< node_t > nodes_t;
        typedef std::set< id_t > ids_t;
        typedef std::map< edge_t, ids_t > edge_map_t;
        typedef std::map< node_t, ids_t > node_map_t;
        typedef std::map< id_t, id_t > props_t;
        typedef std::map< id_t, props_t > subgraph_props_t;
        typedef boost::function2< void, id_t const&, id_t const& > actor_t;
        typedef std::vector< edge_t > edge_stack_t;
        typedef std::map< id_t, nodes_t > subgraph_nodes_t;
        typedef std::map< id_t, edges_t > subgraph_edges_t;

        /////////////////////////////////////////////////////////////////////////////
        // Stack frames used by semantic actions
        /////////////////////////////////////////////////////////////////////////////
        struct id_closure
        : boost::spirit::classic::closure< id_closure, node_t >
        {
            member1 name;
        };

        struct node_id_closure
        : boost::spirit::classic::closure< node_id_closure, node_t >
        {
            member1 name;
        };

        struct attr_list_closure
        : boost::spirit::classic::closure< attr_list_closure, actor_t >
        {
            member1 prop_actor;
        };

        struct property_closure
        : boost::spirit::classic::closure< property_closure, id_t, id_t >
        {
            member1 key;
            member2 value;
        };

        struct data_stmt_closure
        : boost::spirit::classic::closure< data_stmt_closure, nodes_t, nodes_t,
              edge_stack_t, bool, node_t >
        {
            member1 sources;
            member2 dests;
            member3 edge_stack;
            member4 saw_node;
            member5 active_node;
        };

        struct subgraph_closure
        : boost::spirit::classic::closure< subgraph_closure, nodes_t, edges_t,
              node_t >
        {
            member1 nodes;
            member2 edges;
            member3 name;
        };

        /////////////////////////////////////////////////////////////////////////////
        // Grammar and Actions for the DOT Language
        /////////////////////////////////////////////////////////////////////////////

        // Grammar for a dot file.
        struct dot_grammar
        : public boost::spirit::classic::grammar< dot_grammar >
        {
            mutate_graph& graph_;
            explicit dot_grammar(mutate_graph& graph) : graph_(graph) {}

            template < class ScannerT > struct definition
            {

                definition(dot_grammar const& self)
                : self(self), subgraph_depth(0), keyword_p("0-9a-zA-Z_")
                {
                    using namespace boost::spirit::classic;
                    using namespace phoenix;

                    // RG - Future Work
                    // - Handle multi-line strings using \ line continuation
                    // - Make keywords case insensitive
                    ID = (lexeme_d[(
                              (alpha_p | ch_p('_')) >> *(alnum_p | ch_p('_')))]
                        | real_p | lexeme_d[confix_p('"', *c_escape_ch_p, '"')]
                        | comment_nest_p('<', '>'))[ID.name
                        = construct_< std::string >(arg1, arg2)];

                    a_list = list_p(
                        ID[(a_list.key = arg1), (a_list.value = "true")] >> !(
                            ch_p('=') >> ID[a_list.value = arg1])[phoenix::bind(
                            &definition::call_prop_actor)(
                            var(*this), a_list.key, a_list.value)],
                        !ch_p(','));

                    attr_list = +(ch_p('[') >> !a_list >> ch_p(']'));

                    // RG - disregard port id's for now.
                    port_location = (ch_p(':') >> ID)
                        | (ch_p(':') >> ch_p('(') >> ID >> ch_p(',') >> ID
                            >> ch_p(')'));

                    port_angle = ch_p('@') >> ID;

                    port = port_location >> (!port_angle)
                        | port_angle >> (!port_location);

                    node_id
                        = (ID[node_id.name = arg1] >> (!port))[phoenix::bind(
                            &definition::memoize_node)(var(*this))];

                    graph_stmt = (ID[graph_stmt.key = arg1] >> ch_p('=')
                        >> ID[graph_stmt.value = arg1])[phoenix::bind(
                        &definition::call_graph_prop)(var(*this),
                        graph_stmt.key, graph_stmt.value)]; // Graph property.

                    attr_stmt
                        = (as_lower_d[keyword_p("graph")] >> attr_list(actor_t(
                               phoenix::bind(&definition::default_graph_prop)(
                                   var(*this), arg1, arg2))))
                        | (as_lower_d[keyword_p("node")] >> attr_list(actor_t(
                               phoenix::bind(&definition::default_node_prop)(
                                   var(*this), arg1, arg2))))
                        | (as_lower_d[keyword_p("edge")] >> attr_list(actor_t(
                               phoenix::bind(&definition::default_edge_prop)(
                                   var(*this), arg1, arg2))));

                    // edge_head is set depending on the graph type
                    // (directed/undirected)
                    edgeop = ch_p('-') >> ch_p(boost::ref(edge_head));

                    edgeRHS = +(edgeop[(data_stmt.sources = data_stmt.dests),
                                    (data_stmt.dests = construct_< nodes_t >())]
                        >> (subgraph[data_stmt.dests = arg1]
                            | node_id[phoenix::bind(&definition::insert_node)(
                                var(*this), data_stmt.dests, arg1)])
                            [phoenix::bind(&definition::activate_edge)(
                                var(*this), data_stmt.sources, data_stmt.dests,
                                var(edges), var(default_edge_props))]);

                    // To avoid backtracking, edge, node, and subgraph
                    // statements are processed as one nonterminal.
                    data_stmt
                        = (subgraph[(data_stmt.dests
                                        = arg1), // will get moved in rhs
                               (data_stmt.saw_node = false)]
                              | node_id[(phoenix::bind(
                                            &definition::insert_node)(
                                            var(*this), data_stmt.dests, arg1)),
                                  (data_stmt.saw_node = true),
#ifdef BOOST_GRAPH_DEBUG
                                  (std::cout << val("AcTive Node: ") << arg1
                                             << "\n"),
#endif // BOOST_GRAPH_DEBUG
                                  (data_stmt.active_node = arg1)])
                        >> if_p(edgeRHS)[!attr_list(actor_t(phoenix::bind(
                                             &definition::edge_prop)(
                                             var(*this), arg1, arg2)))]
                               .else_p[if_p(data_stmt.saw_node)[!attr_list(
                                   actor_t(phoenix::bind(
                                       &definition::node_prop)(var(*this), arg1,
                                       arg2)))] // otherwise it's a subgraph,
                                                // nothing more to do.
                    ];

                    stmt = graph_stmt | attr_stmt | data_stmt;

                    stmt_list = *(stmt >> !ch_p(';'));

                    subgraph = !(as_lower_d[keyword_p("subgraph")]
                                   >> (!ID[(subgraph.name = arg1),
                                       (subgraph.nodes
                                           = (var(subgraph_nodes))[arg1]),
                                       (subgraph.edges
                                           = (var(subgraph_edges))[arg1])]))
                            >> ch_p('{')[++var(subgraph_depth)] >> stmt_list
                            >> ch_p('}')[--var(subgraph_depth)]
                                        [(var(subgraph_nodes))[subgraph.name]
                                            = subgraph.nodes]
                                        [(var(subgraph_edges))[subgraph.name]
                                            = subgraph.edges]

                        | as_lower_d[keyword_p("subgraph")]
                            >> ID[(subgraph.nodes
                                      = (var(subgraph_nodes))[arg1]),
                                (subgraph.edges = (var(subgraph_edges))[arg1])];

                    the_grammar = (!as_lower_d[keyword_p("strict")])
                        >> (as_lower_d[keyword_p(
                                "graph")][(var(edge_head) = '-'),
                                (phoenix::bind(&definition::check_undirected)(
                                    var(*this)))]
                            | as_lower_d[keyword_p(
                                "digraph")][(var(edge_head) = '>'),
                                (phoenix::bind(&definition::check_directed)(
                                    var(*this)))])
                        >> (!ID) >> ch_p('{') >> stmt_list >> ch_p('}');

                } // definition()

                typedef boost::spirit::classic::rule< ScannerT > rule_t;

                rule_t const& start() const { return the_grammar; }

                //
                // Semantic actions
                //

                void check_undirected()
                {
                    if (self.graph_.is_directed())
                        boost::throw_exception(boost::undirected_graph_error());
                }

                void check_directed()
                {
                    if (!self.graph_.is_directed())
                        boost::throw_exception(boost::directed_graph_error());
                }

                void memoize_node()
                {
                    id_t const& node = node_id.name();
                    props_t& node_props = default_node_props;

                    if (nodes.find(node) == nodes.end())
                    {
                        nodes.insert(node);
                        self.graph_.do_add_vertex(node);

                        node_map.insert(std::make_pair(node, ids_t()));

#ifdef BOOST_GRAPH_DEBUG
                        std::cout << "Add new node " << node << std::endl;
#endif // BOOST_GRAPH_DEBUG
       // Set the default properties for this edge
       // RG: Here I  would actually set the properties
                        for (props_t::iterator i = node_props.begin();
                             i != node_props.end(); ++i)
                        {
                            set_node_property(node, i->first, i->second);
                        }
                        if (subgraph_depth > 0)
                        {
                            subgraph.nodes().insert(node);
                            // Set the subgraph's default properties as well
                            props_t& props
                                = subgraph_node_props[subgraph.name()];
                            for (props_t::iterator i = props.begin();
                                 i != props.end(); ++i)
                            {
                                set_node_property(node, i->first, i->second);
                            }
                        }
                    }
                    else
                    {
#ifdef BOOST_GRAPH_DEBUG
                        std::cout << "See node " << node << std::endl;
#endif // BOOST_GRAPH_DEBUG
                    }
                }

                void activate_edge(nodes_t& sources, nodes_t& dests,
                    edges_t& edges, props_t& edge_props)
                {
                    edge_stack_t& edge_stack = data_stmt.edge_stack();
                    for (nodes_t::iterator i = sources.begin();
                         i != sources.end(); ++i)
                    {
                        for (nodes_t::iterator j = dests.begin();
                             j != dests.end(); ++j)
                        {
                            // Create the edge and push onto the edge stack.
#ifdef BOOST_GRAPH_DEBUG
                            std::cout << "Edge " << *i << " to " << *j
                                      << std::endl;
#endif // BOOST_GRAPH_DEBUG

                            edge_t edge = edge_t::new_edge();
                            edge_stack.push_back(edge);
                            edges.insert(edge);
                            edge_map.insert(std::make_pair(edge, ids_t()));

                            // Add the real edge.
                            self.graph_.do_add_edge(edge, *i, *j);

                            // Set the default properties for this edge
                            for (props_t::iterator k = edge_props.begin();
                                 k != edge_props.end(); ++k)
                            {
                                set_edge_property(edge, k->first, k->second);
                            }
                            if (subgraph_depth > 0)
                            {
                                subgraph.edges().insert(edge);
                                // Set the subgraph's default properties as well
                                props_t& props
                                    = subgraph_edge_props[subgraph.name()];
                                for (props_t::iterator k = props.begin();
                                     k != props.end(); ++k)
                                {
                                    set_edge_property(
                                        edge, k->first, k->second);
                                }
                            }
                        }
                    }
                }

                // node_prop - Assign the property for the current active node.
                void node_prop(id_t const& key, id_t const& value)
                {
                    node_t& active_object = data_stmt.active_node();
                    set_node_property(active_object, key, value);
                }

                // edge_prop - Assign the property for the current active edges.
                void edge_prop(id_t const& key, id_t const& value)
                {
                    edge_stack_t const& active_edges_ = data_stmt.edge_stack();
                    for (edge_stack_t::const_iterator i = active_edges_.begin();
                         i != active_edges_.end(); ++i)
                    {
                        set_edge_property(*i, key, value);
                    }
                }

                // default_graph_prop - Store as a graph property.
                void default_graph_prop(id_t const& key, id_t const& value)
                {
#ifdef BOOST_GRAPH_DEBUG
                    std::cout << key << " = " << value << std::endl;
#endif // BOOST_GRAPH_DEBUG
                    self.graph_.set_graph_property(key, value);
                }

                // default_node_prop - declare default properties for any future
                // new nodes
                void default_node_prop(id_t const& key, id_t const& value)
                {
                    nodes_t& nodes_
                        = subgraph_depth == 0 ? nodes : subgraph.nodes();
                    props_t& node_props_ = subgraph_depth == 0
                        ? default_node_props
                        : subgraph_node_props[subgraph.name()];

                    // add this to the selected list of default node properties.
                    node_props_[key] = value;
                    // for each node, set its property to default-constructed
                    // value
                    //   if it hasn't been set already.
                    // set the dynamic property map value
                    for (nodes_t::iterator i = nodes_.begin();
                         i != nodes_.end(); ++i)
                        if (node_map[*i].find(key) == node_map[*i].end())
                        {
                            set_node_property(*i, key, id_t());
                        }
                }

                // default_edge_prop - declare default properties for any future
                // new edges
                void default_edge_prop(id_t const& key, id_t const& value)
                {
                    edges_t& edges_
                        = subgraph_depth == 0 ? edges : subgraph.edges();
                    props_t& edge_props_ = subgraph_depth == 0
                        ? default_edge_props
                        : subgraph_edge_props[subgraph.name()];

                    // add this to the list of default edge properties.
                    edge_props_[key] = value;
                    // for each edge, set its property to be empty string
                    // set the dynamic property map value
                    for (edges_t::iterator i = edges_.begin();
                         i != edges_.end(); ++i)
                        if (edge_map[*i].find(key) == edge_map[*i].end())
                            set_edge_property(*i, key, id_t());
                }

                // helper function
                void insert_node(nodes_t& nodes, id_t const& name)
                {
                    nodes.insert(name);
                }

                void call_prop_actor(
                    std::string const& lhs, std::string const& rhs)
                {
                    actor_t& actor = attr_list.prop_actor();
                    // If first and last characters of the rhs are
                    // double-quotes, remove them.
                    if (!rhs.empty() && rhs[0] == '"'
                        && rhs[rhs.size() - 1] == '"')
                        actor(lhs, rhs.substr(1, rhs.size() - 2));
                    else
                        actor(lhs, rhs);
                }

                void call_graph_prop(
                    std::string const& lhs, std::string const& rhs)
                {
                    // If first and last characters of the rhs are
                    // double-quotes, remove them.
                    if (!rhs.empty() && rhs[0] == '"'
                        && rhs[rhs.size() - 1] == '"')
                        this->default_graph_prop(
                            lhs, rhs.substr(1, rhs.size() - 2));
                    else
                        this->default_graph_prop(lhs, rhs);
                }

                void set_node_property(
                    node_t const& node, id_t const& key, id_t const& value)
                {

                    // Add the property key to the "set" table to avoid default
                    // overwrite
                    node_map[node].insert(key);
                    // Set the user's property map
                    self.graph_.set_node_property(key, node, value);
#ifdef BOOST_GRAPH_DEBUG
                    // Tell the world
                    std::cout << node << ": " << key << " = " << value
                              << std::endl;
#endif // BOOST_GRAPH_DEBUG
                }

                void set_edge_property(
                    edge_t const& edge, id_t const& key, id_t const& value)
                {

                    // Add the property key to the "set" table to avoid default
                    // overwrite
                    edge_map[edge].insert(key);
                    // Set the user's property map
                    self.graph_.set_edge_property(key, edge, value);
#ifdef BOOST_GRAPH_DEBUG
                    // Tell the world
#if 0 // RG - edge representation changed,
            std::cout << "(" << edge.first << "," << edge.second << "): "
#else
                    std::cout << "an edge: "
#endif // 0
                    << key << " = " << value << std::endl;
#endif // BOOST_GRAPH_DEBUG
                }

                // Variables explicitly initialized
                dot_grammar const& self;
                // if subgraph_depth > 0, then we're processing a subgraph.
                int subgraph_depth;

                // Keywords;
                const boost::spirit::classic::distinct_parser<> keyword_p;
                //
                // rules that make up the grammar
                //
                boost::spirit::classic::rule< ScannerT, id_closure::context_t >
                    ID;
                boost::spirit::classic::rule< ScannerT,
                    property_closure::context_t >
                    a_list;
                boost::spirit::classic::rule< ScannerT,
                    attr_list_closure::context_t >
                    attr_list;
                rule_t port_location;
                rule_t port_angle;
                rule_t port;
                boost::spirit::classic::rule< ScannerT,
                    node_id_closure::context_t >
                    node_id;
                boost::spirit::classic::rule< ScannerT,
                    property_closure::context_t >
                    graph_stmt;
                rule_t attr_stmt;
                boost::spirit::classic::rule< ScannerT,
                    data_stmt_closure::context_t >
                    data_stmt;
                boost::spirit::classic::rule< ScannerT,
                    subgraph_closure::context_t >
                    subgraph;
                rule_t edgeop;
                rule_t edgeRHS;
                rule_t stmt;
                rule_t stmt_list;
                rule_t the_grammar;

                // The grammar uses edge_head to dynamically set the syntax for
                // edges directed graphs: edge_head = '>', and so edgeop = "->"
                // undirected graphs: edge_head = '-', and so edgeop = "--"
                char edge_head;

                //
                // Support data structures
                //

                nodes_t nodes; // list of node names seen
                edges_t edges; // list of edges seen
                node_map_t
                    node_map; // remember the properties set for each node
                edge_map_t
                    edge_map; // remember the properties set for each edge

                subgraph_nodes_t subgraph_nodes; // per-subgraph lists of nodes
                subgraph_edges_t subgraph_edges; // per-subgraph lists of edges

                props_t default_node_props; // global default node properties
                props_t default_edge_props; // global default edge properties
                subgraph_props_t
                    subgraph_node_props; // per-subgraph default node properties
                subgraph_props_t
                    subgraph_edge_props; // per-subgraph default edge properties
            }; // struct definition
        }; // struct dot_grammar

        //
        // dot_skipper - GraphViz whitespace and comment skipper
        //
        struct dot_skipper
        : public boost::spirit::classic::grammar< dot_skipper >
        {
            dot_skipper() {}

            template < typename ScannerT > struct definition
            {
                definition(dot_skipper const& /*self*/)
                {
                    using namespace boost::spirit::classic;
                    using namespace phoenix;
                    // comment forms
                    skip = eol_p >> comment_p("#") | space_p | comment_p("//")
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1400)
                        | confix_p(str_p("/*"), *anychar_p, str_p("*/"))
#else
                        | confix_p("/*", *anychar_p, "*/")
#endif
                        ;

#ifdef BOOST_SPIRIT_DEBUG
                    BOOST_SPIRIT_DEBUG_RULE(skip);
#endif
                }

                boost::spirit::classic::rule< ScannerT > skip;
                boost::spirit::classic::rule< ScannerT > const& start() const
                {
                    return skip;
                }
            }; // definition
        }; // dot_skipper

    } // namespace graph
} // namespace detail

template < typename MultiPassIterator, typename MutableGraph >
bool read_graphviz_spirit(MultiPassIterator begin, MultiPassIterator end,
    MutableGraph& graph, dynamic_properties& dp,
    std::string const& node_id = "node_id")
{
    using namespace boost;
    using namespace boost::spirit::classic;

    typedef MultiPassIterator iterator_t;
    typedef skip_parser_iteration_policy< boost::detail::graph::dot_skipper >
        iter_policy_t;
    typedef scanner_policies< iter_policy_t > scanner_policies_t;
    typedef scanner< iterator_t, scanner_policies_t > scanner_t;

    ::boost::detail::graph::mutate_graph_impl< MutableGraph > m_graph(
        graph, dp, node_id);

    ::boost::detail::graph::dot_grammar p(m_graph);
    ::boost::detail::graph::dot_skipper skip_p;

    iter_policy_t iter_policy(skip_p);
    scanner_policies_t policies(iter_policy);

    scanner_t scan(begin, end, policies);

    bool ok = p.parse(scan);
    m_graph.finish_building_graph();
    return ok;
}

} // namespace boost

#endif // BOOST_READ_GRAPHVIZ_SPIRIT_HPP

/* read_graphviz_spirit.hpp
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
*/