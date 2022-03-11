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