//-*-c++-*-
//=======================================================================
// Copyright 1997-2001 University of Notre Dame.
// Authors: Lie-Quan Lee, Jeremy Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//
#ifndef BOOST_GRAPH_MINIMUM_DEGREE_ORDERING_HPP
#define BOOST_GRAPH_MINIMUM_DEGREE_ORDERING_HPP

#include <vector>
#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/pending/bucket_sorter.hpp>
#include <boost/detail/numeric_traits.hpp> // for integer_traits
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>

namespace boost
{

namespace detail
{

    //
    // Given a set of n integers (where the integer values range from
    // zero to n-1), we want to keep track of a collection of stacks
    // of integers. It so happens that an integer will appear in at
    // most one stack at a time, so the stacks form disjoint sets.
    // Because of these restrictions, we can use one big array to
    // store all the stacks, intertwined with one another.
    // No allocation/deallocation happens in the push()/pop() methods
    // so this is faster than using std::stack's.
    //
    template < class SignedInteger > class Stacks
    {
        typedef SignedInteger value_type;
        typedef typename std::vector< value_type >::size_type size_type;

    public:
        Stacks(size_type n) : data(n) {}

        //: stack
        class stack
        {
            typedef typename std::vector< value_type >::iterator Iterator;

        public:
            stack(Iterator _data, const value_type& head)
            : data(_data), current(head)
            {
            }

            // did not use default argument here to avoid internal compiler
            // error in g++.
            stack(Iterator _data)
            : data(_data), current(-(std::numeric_limits< value_type >::max)())
            {
            }

            void pop()
            {
                BOOST_ASSERT(!empty());
                current = data[current];
            }
            void push(value_type v)
            {
                data[v] = current;
                current = v;
            }
            bool empty()
            {
                return current == -(std::numeric_limits< value_type >::max)();
            }
            value_type& top() { return current; }

        private:
            Iterator data;
            value_type current;
        };

        // To return a stack object
        stack make_stack() { return stack(data.begin()); }

    protected:
        std::vector< value_type > data;
    };

    // marker class, a generalization of coloring.
    //
    // This class is to provide a generalization of coloring which has
    // complexity of amortized constant time to set all vertices' color
    // back to be untagged. It implemented by increasing a tag.
    //
    // The colors are:
    //   not tagged
    //   tagged
    //   multiple_tagged
    //   done
    //
    template < class SignedInteger, class Vertex, class VertexIndexMap >
    class Marker
    {
        typedef SignedInteger value_type;
        typedef typename std::vector< value_type >::size_type size_type;

        static value_type done()
        {
            return (std::numeric_limits< value_type >::max)() / 2;
        }

    public:
        Marker(size_type _num, VertexIndexMap index_map)
        : tag(1 - (std::numeric_limits< value_type >::max)())
        , data(_num, -(std::numeric_limits< value_type >::max)())
        , id(index_map)
        {
        }

        void mark_done(Vertex node) { data[get(id, node)] = done(); }

        bool is_done(Vertex node) { return data[get(id, node)] == done(); }

        void mark_tagged(Vertex node) { data[get(id, node)] = tag; }

        void mark_multiple_tagged(Vertex node)
        {
            data[get(id, node)] = multiple_tag;
        }

        bool is_tagged(Vertex node) const { return data[get(id, node)] >= tag; }

        bool is_not_tagged(Vertex node) const
        {
            return data[get(id, node)] < tag;
        }

        bool is_multiple_tagged(Vertex node) const
        {
            return data[get(id, node)] >= multiple_tag;
        }

        void increment_tag()
        {
            const size_type num = data.size();
            ++tag;
            if (tag >= done())
            {
                tag = 1 - (std::numeric_limits< value_type >::max)();
                for (size_type i = 0; i < num; ++i)
                    if (data[i] < done())
                        data[i] = -(std::numeric_limits< value_type >::max)();
            }
        }

        void set_multiple_tag(value_type mdeg0)
        {
            const size_type num = data.size();
            multiple_tag = tag + mdeg0;

            if (multiple_tag >= done())
            {
                tag = 1 - (std::numeric_limits< value_type >::max)();

                for (size_type i = 0; i < num; i++)
                    if (data[i] < done())
                        data[i] = -(std::numeric_limits< value_type >::max)();

                multiple_tag = tag + mdeg0;
            }
        }

        void set_tag_as_multiple_tag() { tag = multiple_tag; }

    protected:
        value_type tag;
        value_type multiple_tag;
        std::vector< value_type > data;
        VertexIndexMap id;
    };

    template < class Iterator, class SignedInteger, class Vertex,
        class VertexIndexMap, int offset = 1 >
    class Numbering
    {
        typedef SignedInteger number_type;
        number_type num; // start from 1 instead of zero
        Iterator data;
        number_type max_num;
        VertexIndexMap id;

    public:
        Numbering(Iterator _data, number_type _max_num, VertexIndexMap id)
        : num(1), data(_data), max_num(_max_num), id(id)
        {
        }
        void operator()(Vertex node) { data[get(id, node)] = -num; }
        bool all_done(number_type i = 0) const { return num + i > max_num; }
        void increment(number_type i = 1) { num += i; }
        bool is_numbered(Vertex node) const { return data[get(id, node)] < 0; }
        void indistinguishable(Vertex i, Vertex j)
        {
            data[get(id, i)] = -(get(id, j) + offset);
        }
    };

    template < class SignedInteger, class Vertex, class VertexIndexMap >
    class degreelists_marker
    {
    public:
        typedef SignedInteger value_type;
        typedef typename std::vector< value_type >::size_type size_type;
        degreelists_marker(size_type n, VertexIndexMap id) : marks(n, 0), id(id)
        {
        }
        void mark_need_update(Vertex i) { marks[get(id, i)] = 1; }
        bool need_update(Vertex i) { return marks[get(id, i)] == 1; }
        bool outmatched_or_done(Vertex i) { return marks[get(id, i)] == -1; }
        void mark(Vertex i) { marks[get(id, i)] = -1; }
        void unmark(Vertex i) { marks[get(id, i)] = 0; }

    private:
        std::vector< value_type > marks;
        VertexIndexMap id;
    };

    // Helper function object for edge removal
    template < class Graph, class MarkerP, class NumberD, class Stack,
        class VertexIndexMap >
    class predicateRemoveEdge1
    {
        typedef typename graph_traits< Graph >::vertex_descriptor vertex_t;
        typedef typename graph_traits< Graph >::edge_descriptor edge_t;

    public:
        predicateRemoveEdge1(Graph& _g, MarkerP& _marker, NumberD _numbering,
            Stack& n_e, VertexIndexMap id)
        : g(&_g)
        , marker(&_marker)
        , numbering(_numbering)
        , neighbor_elements(&n_e)
        , id(id)
        {
        }

        bool operator()(edge_t e)
        {
            vertex_t dist = target(e, *g);
            if (marker->is_tagged(dist))
                return true;
            marker->mark_tagged(dist);
            if (numbering.is_numbered(dist))
            {
                neighbor_elements->push(get(id, dist));
                return true;
            }
            return false;
        }

    private:
        Graph* g;
        MarkerP* marker;
        NumberD numbering;
        Stack* neighbor_elements;
        VertexIndexMap id;
    };

    // Helper function object for edge removal
    template < class Graph, class MarkerP > class predicate_remove_tagged_edges
    {
        typedef typename graph_traits< Graph >::vertex_descriptor vertex_t;
        typedef typename graph_traits< Graph >::edge_descriptor edge_t;

    public:
        predicate_remove_tagged_edges(Graph& _g, MarkerP& _marker)
        : g(&_g), marker(&_marker)
        {
        }

        bool operator()(edge_t e)
        {
            vertex_t dist = target(e, *g);
            if (marker->is_tagged(dist))
                return true;
            return false;
        }

    private:
        Graph* g;
        MarkerP* marker;
    };

    template < class Graph, class DegreeMap, class InversePermutationMap,
        class PermutationMap, class SuperNodeMap, class VertexIndexMap >
    class mmd_impl
    {
        // Typedefs
        typedef graph_traits< Graph > Traits;
        typedef typename Traits::vertices_size_type size_type;
        typedef typename detail::integer_traits< size_type >::difference_type
            diff_t;
        typedef typename Traits::vertex_descriptor vertex_t;
        typedef typename Traits::adjacency_iterator adj_iter;
        typedef iterator_property_map< vertex_t*, identity_property_map,
            vertex_t, vertex_t& >
            IndexVertexMap;
        typedef detail::Stacks< diff_t > Workspace;
        typedef bucket_sorter< size_type, vertex_t, DegreeMap, VertexIndexMap >
            DegreeLists;
        typedef Numbering< InversePermutationMap, diff_t, vertex_t,
            VertexIndexMap >
            NumberingD;
        typedef degreelists_marker< diff_t, vertex_t, VertexIndexMap >
            DegreeListsMarker;
        typedef Marker< diff_t, vertex_t, VertexIndexMap > MarkerP;

        // Data Members
        bool has_no_edges;

        // input parameters
        Graph& G;
        int delta;
        DegreeMap degree;
        InversePermutationMap inverse_perm;
        PermutationMap perm;
        SuperNodeMap supernode_size;
        VertexIndexMap vertex_index_map;

        // internal data-structures
        std::vector< vertex_t > index_vertex_vec;
        size_type n;
        IndexVertexMap index_vertex_map;
        DegreeLists degreelists;
        NumberingD numbering;
        DegreeListsMarker degree_lists_marker;
        MarkerP marker;
        Workspace work_space;

    public:
        mmd_impl(Graph& g, size_type n_, int delta, DegreeMap degree,
            InversePermutationMap inverse_perm, PermutationMap perm,
            SuperNodeMap supernode_size, VertexIndexMap id)
        : has_no_edges(true)
        , G(g)
        , delta(delta)
        , degree(degree)
        , inverse_perm(inverse_perm)
        , perm(perm)
        , supernode_size(supernode_size)
        , vertex_index_map(id)
        , index_vertex_vec(n_)
        , n(n_)
        , degreelists(n_ + 1, n_, degree, id)
        , numbering(inverse_perm, n_, vertex_index_map)
        , degree_lists_marker(n_, vertex_index_map)
        , marker(n_, vertex_index_map)
        , work_space(n_)
        {
            typename graph_traits< Graph >::vertex_iterator v, vend;
            size_type vid = 0;
            for (boost::tie(v, vend) = vertices(G); v != vend; ++v, ++vid)
                index_vertex_vec[vid] = *v;
            index_vertex_map = IndexVertexMap(&index_vertex_vec[0]);

            // Initialize degreelists.  Degreelists organizes the nodes
            // according to their degree.
            for (boost::tie(v, vend) = vertices(G); v != vend; ++v)
            {
                typename Traits::degree_size_type d = out_degree(*v, G);
                put(degree, *v, d);
                if (0 < d)
                    has_no_edges = false;
                degreelists.push(*v);
            }
        }

        void do_mmd()
        {
            // Eliminate the isolated nodes -- these are simply the nodes
            // with no neighbors, which are accessible as a list (really, a
            // stack) at location 0.  Since these don't affect any other
            // nodes, we can eliminate them without doing degree updates.
            typename DegreeLists::stack list_isolated = degreelists[0];
            while (!list_isolated.empty())
            {
                vertex_t node = list_isolated.top();
                marker.mark_done(node);
                numbering(node);
                numbering.increment();
                list_isolated.pop();
            }

            if (has_no_edges)
            {
                return;
            }

            size_type min_degree = 1;
            typename DegreeLists::stack list_min_degree
                = degreelists[min_degree];

            while (list_min_degree.empty())
            {
                ++min_degree;
                list_min_degree = degreelists[min_degree];
            }

            // check if the whole eliminating process is done
            while (!numbering.all_done())
            {

                size_type min_degree_limit = min_degree + delta; // WARNING
                typename Workspace::stack llist = work_space.make_stack();

                // multiple elimination
                while (delta >= 0)
                {

                    // Find the next non-empty degree
                    for (list_min_degree = degreelists[min_degree];
                         list_min_degree.empty()
                         && min_degree <= min_degree_limit;
                         ++min_degree,
                        list_min_degree = degreelists[min_degree])
                        ;
                    if (min_degree > min_degree_limit)
                        break;

                    const vertex_t node = list_min_degree.top();
                    const size_type node_id = get(vertex_index_map, node);
                    list_min_degree.pop();
                    numbering(node);

                    // check if node is the last one
                    if (numbering.all_done(supernode_size[node]))
                    {
                        numbering.increment(supernode_size[node]);
                        break;
                    }
                    marker.increment_tag();
                    marker.mark_tagged(node);

                    this->eliminate(node);

                    numbering.increment(supernode_size[node]);
                    llist.push(node_id);
                } // multiple elimination

                if (numbering.all_done())
                    break;

                this->update(llist, min_degree);
            }

        } // do_mmd()

        void eliminate(vertex_t node)
        {
            typename Workspace::stack element_neighbor
                = work_space.make_stack();

            // Create two function objects for edge removal
            typedef typename Workspace::stack WorkStack;
            predicateRemoveEdge1< Graph, MarkerP, NumberingD, WorkStack,
                VertexIndexMap >
                p(G, marker, numbering, element_neighbor, vertex_index_map);

            predicate_remove_tagged_edges< Graph, MarkerP > p2(G, marker);

            // Reconstruct the adjacent node list, push element neighbor in a
            // List.
            remove_out_edge_if(node, p, G);
            // during removal element neighbors are collected.

            while (!element_neighbor.empty())
            {
                // element absorb
                size_type e_id = element_neighbor.top();
                vertex_t element = get(index_vertex_map, e_id);
                adj_iter i, i_end;
                for (boost::tie(i, i_end) = adjacent_vertices(element, G);
                     i != i_end; ++i)
                {
                    vertex_t i_node = *i;
                    if (!marker.is_tagged(i_node)
                        && !numbering.is_numbered(i_node))
                    {
                        marker.mark_tagged(i_node);
                        add_edge(node, i_node, G);
                    }
                }
                element_neighbor.pop();
            }
            adj_iter v, ve;
            for (boost::tie(v, ve) = adjacent_vertices(node, G); v != ve; ++v)
            {
                vertex_t v_node = *v;
                if (!degree_lists_marker.need_update(v_node)
                    && !degree_lists_marker.outmatched_or_done(v_node))
                {
                    degreelists.remove(v_node);
                }
                // update out edges of v_node
                remove_out_edge_if(v_node, p2, G);

                if (out_degree(v_node, G) == 0)
                { // indistinguishable nodes
                    supernode_size[node] += supernode_size[v_node];
                    supernode_size[v_node] = 0;
                    numbering.indistinguishable(v_node, node);
                    marker.mark_done(v_node);
                    degree_lists_marker.mark(v_node);
                }
                else
                { // not indistinguishable nodes
                    add_edge(v_node, node, G);
                    degree_lists_marker.mark_need_update(v_node);
                }
            }
        } // eliminate()

        template < class Stack > void update(Stack llist, size_type& min_degree)
        {
            size_type min_degree0 = min_degree + delta + 1;

            while (!llist.empty())
            {
                size_type deg, deg0 = 0;

                marker.set_multiple_tag(min_degree0);
                typename Workspace::stack q2list = work_space.make_stack();
                typename Workspace::stack qxlist = work_space.make_stack();

                vertex_t current = get(index_vertex_map, llist.top());
                adj_iter i, ie;
                for (boost::tie(i, ie) = adjacent_vertices(current, G); i != ie;
                     ++i)
                {
                    vertex_t i_node = *i;
                    const size_type i_id = get(vertex_index_map, i_node);
                    if (supernode_size[i_node] != 0)
                    {
                        deg0 += supernode_size[i_node];
                        marker.mark_multiple_tagged(i_node);
                        if (degree_lists_marker.need_update(i_node))
                        {
                            if (out_degree(i_node, G) == 2)
                                q2list.push(i_id);
                            else
                                qxlist.push(i_id);
                        }
                    }
                }

                while (!q2list.empty())
                {
                    const size_type u_id = q2list.top();
                    vertex_t u_node = get(index_vertex_map, u_id);
                    // if u_id is outmatched by others, no need to update degree
                    if (degree_lists_marker.outmatched_or_done(u_node))
                    {
                        q2list.pop();
                        continue;
                    }
                    marker.increment_tag();
                    deg = deg0;

                    adj_iter nu = adjacent_vertices(u_node, G).first;
                    vertex_t neighbor = *nu;
                    if (neighbor == u_node)
                    {
                        ++nu;
                        neighbor = *nu;
                    }
                    if (numbering.is_numbered(neighbor))
                    {
                        adj_iter i, ie;
                        for (boost::tie(i, ie) = adjacent_vertices(neighbor, G);
                             i != ie; ++i)
                        {
                            const vertex_t i_node = *i;
                            if (i_node == u_node || supernode_size[i_node] == 0)
                                continue;
                            if (marker.is_tagged(i_node))
                            {
                                if (degree_lists_marker.need_update(i_node))
                                {
                                    if (out_degree(i_node, G) == 2)
                                    { // is indistinguishable
                                        supernode_size[u_node]
                                            += supernode_size[i_node];
                                        supernode_size[i_node] = 0;
                                        numbering.indistinguishable(
                                            i_node, u_node);
                                        marker.mark_done(i_node);
                                        degree_lists_marker.mark(i_node);
                                    }
                                    else // is outmatched
                                        degree_lists_marker.mark(i_node);
                                }
                            }
                            else
                            {
                                marker.mark_tagged(i_node);
                                deg += supernode_size[i_node];
                            }
                        }
                    }
                    else
                        deg += supernode_size[neighbor];

                    deg -= supernode_size[u_node];
                    degree[u_node] = deg; // update degree
                    degreelists[deg].push(u_node);
                    // u_id has been pushed back into degreelists
                    degree_lists_marker.unmark(u_node);
                    if (min_degree > deg)
                        min_degree = deg;
                    q2list.pop();
                } // while (!q2list.empty())

                while (!qxlist.empty())
                {
                    const size_type u_id = qxlist.top();
                    const vertex_t u_node = get(index_vertex_map, u_id);

                    // if u_id is outmatched by others, no need to update degree
                    if (degree_lists_marker.outmatched_or_done(u_node))
                    {
                        qxlist.pop();
                        continue;
                    }
                    marker.increment_tag();
                    deg = deg0;
                    adj_iter i, ie;
                    for (boost::tie(i, ie) = adjacent_vertices(u_node, G);
                         i != ie; ++i)
                    {
                        vertex_t i_node = *i;
                        if (marker.is_tagged(i_node))
                            continue;
                        marker.mark_tagged(i_node);

                        if (numbering.is_numbered(i_node))
                        {
                            adj_iter j, je;
                            for (boost::tie(j, je)
                                 = adjacent_vertices(i_node, G);
                                 j != je; ++j)
                            {
                                const vertex_t j_node = *j;
                                if (marker.is_not_tagged(j_node))
                                {
                                    marker.mark_tagged(j_node);
                                    deg += supernode_size[j_node];
                                }
                            }
                        }
                        else
                            deg += supernode_size[i_node];
                    } // for adjacent vertices of u_node
                    deg -= supernode_size[u_node];
                    degree[u_node] = deg;
                    degreelists[deg].push(u_node);
                    // u_id has been pushed back into degreelists
                    degree_lists_marker.unmark(u_node);
                    if (min_degree > deg)
                        min_degree = deg;
                    qxlist.pop();
                } // while (!qxlist.empty()) {

                marker.set_tag_as_multiple_tag();
                llist.pop();
            } // while (! llist.empty())

        } // update()

        void build_permutation(InversePermutationMap next, PermutationMap prev)
        {
            // collect the permutation info
            size_type i;
            for (i = 0; i < n; ++i)
            {
                diff_t size = supernode_size[get(index_vertex_map, i)];
                if (size <= 0)
                {
                    prev[i] = next[i];
                    supernode_size[get(index_vertex_map, i)]
                        = next[i] + 1; // record the supernode info
                }
                else
                    prev[i] = -next[i];
            }
            for (i = 1; i < n + 1; ++i)
            {
                if (prev[i - 1] > 0)
                    continue;
                diff_t parent = i;
                while (prev[parent - 1] < 0)
                {
                    parent = -prev[parent - 1];
                }

                diff_t root = parent;
                diff_t num = prev[root - 1] + 1;
                next[i - 1] = -num;
                prev[root - 1] = num;

                parent = i;
                diff_t next_node = -prev[parent - 1];
                while (next_node > 0)
                {
                    prev[parent - 1] = -root;
                    parent = next_node;
                    next_node = -prev[parent - 1];
                }
            }
            for (i = 0; i < n; i++)
            {
                diff_t num = -next[i] - 1;
                next[i] = num;
                prev[num] = i;
            }
        } // build_permutation()
    };

} // namespace detail

// MMD algorithm
//
// The implementation presently includes the enhancements for mass
// elimination, incomplete degree update, multiple elimination, and
// external degree.
//
// Important Note: This implementation requires the BGL graph to be
// directed.  Therefore, nonzero entry (i, j) in a symmetrical matrix
// A coresponds to two directed edges (i->j and j->i).
//
// see Alan George and Joseph W. H. Liu, The Evolution of the Minimum
// Degree Ordering Algorithm, SIAM Review, 31, 1989, Page 1-19
template < class Graph, class DegreeMap, class InversePermutationMap,
    class PermutationMap, class SuperNodeMap, class VertexIndexMap >
void minimum_degree_ordering(Graph& G, DegreeMap degree,
    InversePermutationMap inverse_perm, PermutationMap perm,
    SuperNodeMap supernode_size, int delta, VertexIndexMap vertex_index_map)
{
    detail::mmd_impl< Graph, DegreeMap, InversePermutationMap, PermutationMap,
        SuperNodeMap, VertexIndexMap >
        impl(G, num_vertices(G), delta, degree, inverse_perm, perm,
            supernode_size, vertex_index_map);
    impl.do_mmd();
    impl.build_permutation(inverse_perm, perm);
}

} // namespace boost

#endif // BOOST_GRAPH_MINIMUM_DEGREE_ORDERING_HPP

/* minimum_degree_ordering.hpp
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
*/