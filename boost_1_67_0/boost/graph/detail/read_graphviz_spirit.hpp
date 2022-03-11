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