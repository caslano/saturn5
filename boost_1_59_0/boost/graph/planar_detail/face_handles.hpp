//=======================================================================
// Copyright (c) Aaron Windsor 2007
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef __FACE_HANDLES_HPP__
#define __FACE_HANDLES_HPP__

#include <list>
#include <boost/graph/graph_traits.hpp>
#include <boost/shared_ptr.hpp>

// A "face handle" is an optimization meant to serve two purposes in
// the implementation of the Boyer-Myrvold planarity test: (1) it holds
// the partial planar embedding of a particular vertex as it's being
// constructed, and (2) it allows for efficient traversal around the
// outer face of the partial embedding at that particular vertex. A face
// handle is lightweight, just a shared pointer to the actual implementation,
// since it is passed around/copied liberally in the algorithm. It consists
// of an "anchor" (the actual vertex it's associated with) as well as a
// sequence of edges. The functions first_vertex/second_vertex and
// first_edge/second_edge allow fast access to the beginning and end of the
// stored sequence, which allows one to traverse the outer face of the partial
// planar embedding as it's being created.
//
// There are some policies below that define the contents of the face handles:
// in the case no embedding is needed (for example, if one just wants to use
// the Boyer-Myrvold algorithm as a true/false test for planarity, the
// no_embedding class can be passed as the StoreEmbedding policy. Otherwise,
// either std_list (which uses as std::list) or recursive_lazy_list can be
// passed as this policy. recursive_lazy_list has the best theoretical
// performance (O(n) for a sequence of interleaved concatenations and reversals
// of the underlying list), but I've noticed little difference between std_list
// and recursive_lazy_list in my tests, even though using std_list changes
// the worst-case complexity of the planarity test to O(n^2)
//
// Another policy is StoreOldHandlesPolicy, which specifies whether or not
// to keep a record of the previous first/second vertex/edge - this is needed
// if a Kuratowski subgraph needs to be isolated.

namespace boost
{
namespace graph
{
    namespace detail
    {

        // face handle policies

        // EmbeddingStorage policy
        struct store_embedding
        {
        };
        struct recursive_lazy_list : public store_embedding
        {
        };
        struct std_list : public store_embedding
        {
        };
        struct no_embedding
        {
        };

        // StoreOldHandlesPolicy
        struct store_old_handles
        {
        };
        struct no_old_handles
        {
        };

        template < typename DataType > struct lazy_list_node
        {
            typedef shared_ptr< lazy_list_node< DataType > > ptr_t;

            lazy_list_node(const DataType& data)
            : m_reversed(false), m_data(data), m_has_data(true)
            {
            }

            lazy_list_node(ptr_t left_child, ptr_t right_child)
            : m_reversed(false)
            , m_has_data(false)
            , m_left_child(left_child)
            , m_right_child(right_child)
            {
            }

            bool m_reversed;
            DataType m_data;
            bool m_has_data;
            shared_ptr< lazy_list_node > m_left_child;
            shared_ptr< lazy_list_node > m_right_child;
        };

        template < typename StoreOldHandlesPolicy, typename Vertex,
            typename Edge >
        struct old_handles_storage;

        template < typename Vertex, typename Edge >
        struct old_handles_storage< store_old_handles, Vertex, Edge >
        {
            Vertex first_vertex;
            Vertex second_vertex;
            Edge first_edge;
            Edge second_edge;
        };

        template < typename Vertex, typename Edge >
        struct old_handles_storage< no_old_handles, Vertex, Edge >
        {
        };

        template < typename StoreEmbeddingPolicy, typename Edge >
        struct edge_list_storage;

        template < typename Edge >
        struct edge_list_storage< no_embedding, Edge >
        {
            typedef void type;

            void push_back(Edge) {}
            void push_front(Edge) {}
            void reverse() {}
            void concat_front(edge_list_storage< no_embedding, Edge >) {}
            void concat_back(edge_list_storage< no_embedding, Edge >) {}
            template < typename OutputIterator > void get_list(OutputIterator)
            {
            }
        };

        template < typename Edge >
        struct edge_list_storage< recursive_lazy_list, Edge >
        {
            typedef lazy_list_node< Edge > node_type;
            typedef shared_ptr< node_type > type;
            type value;

            void push_back(Edge e)
            {
                type new_node(new node_type(e));
                value = type(new node_type(value, new_node));
            }

            void push_front(Edge e)
            {
                type new_node(new node_type(e));
                value = type(new node_type(new_node, value));
            }

            void reverse() { value->m_reversed = !value->m_reversed; }

            void concat_front(
                edge_list_storage< recursive_lazy_list, Edge > other)
            {
                value = type(new node_type(other.value, value));
            }

            void concat_back(
                edge_list_storage< recursive_lazy_list, Edge > other)
            {
                value = type(new node_type(value, other.value));
            }

            template < typename OutputIterator >
            void get_list(OutputIterator out)
            {
                get_list_helper(out, value);
            }

        private:
            template < typename OutputIterator >
            void get_list_helper(
                OutputIterator o_itr, type root, bool flipped = false)
            {
                if (!root)
                    return;

                if (root->m_has_data)
                    *o_itr = root->m_data;

                if ((flipped && !root->m_reversed)
                    || (!flipped && root->m_reversed))
                {
                    get_list_helper(o_itr, root->m_right_child, true);
                    get_list_helper(o_itr, root->m_left_child, true);
                }
                else
                {
                    get_list_helper(o_itr, root->m_left_child, false);
                    get_list_helper(o_itr, root->m_right_child, false);
                }
            }
        };

        template < typename Edge > struct edge_list_storage< std_list, Edge >
        {
            typedef std::list< Edge > type;
            type value;

            void push_back(Edge e) { value.push_back(e); }

            void push_front(Edge e) { value.push_front(e); }

            void reverse() { value.reverse(); }

            void concat_front(edge_list_storage< std_list, Edge > other)
            {
                value.splice(value.begin(), other.value);
            }

            void concat_back(edge_list_storage< std_list, Edge > other)
            {
                value.splice(value.end(), other.value);
            }

            template < typename OutputIterator >
            void get_list(OutputIterator out)
            {
                std::copy(value.begin(), value.end(), out);
            }
        };

        template < typename Graph, typename StoreOldHandlesPolicy,
            typename StoreEmbeddingPolicy >
        struct face_handle_impl
        {
            typedef typename graph_traits< Graph >::vertex_descriptor vertex_t;
            typedef typename graph_traits< Graph >::edge_descriptor edge_t;
            typedef
                typename edge_list_storage< StoreEmbeddingPolicy, edge_t >::type
                    edge_list_storage_t;

            face_handle_impl()
            : cached_first_vertex(graph_traits< Graph >::null_vertex())
            , cached_second_vertex(graph_traits< Graph >::null_vertex())
            , true_first_vertex(graph_traits< Graph >::null_vertex())
            , true_second_vertex(graph_traits< Graph >::null_vertex())
            , anchor(graph_traits< Graph >::null_vertex())
            {
                initialize_old_vertices_dispatch(StoreOldHandlesPolicy());
            }

            void initialize_old_vertices_dispatch(store_old_handles)
            {
                old_handles.first_vertex = graph_traits< Graph >::null_vertex();
                old_handles.second_vertex
                    = graph_traits< Graph >::null_vertex();
            }

            void initialize_old_vertices_dispatch(no_old_handles) {}

            vertex_t cached_first_vertex;
            vertex_t cached_second_vertex;
            vertex_t true_first_vertex;
            vertex_t true_second_vertex;
            vertex_t anchor;
            edge_t cached_first_edge;
            edge_t cached_second_edge;

            edge_list_storage< StoreEmbeddingPolicy, edge_t > edge_list;
            old_handles_storage< StoreOldHandlesPolicy, vertex_t, edge_t >
                old_handles;
        };

        template < typename Graph,
            typename StoreOldHandlesPolicy = store_old_handles,
            typename StoreEmbeddingPolicy = recursive_lazy_list >
        class face_handle
        {
        public:
            typedef typename graph_traits< Graph >::vertex_descriptor vertex_t;
            typedef typename graph_traits< Graph >::edge_descriptor edge_t;
            typedef face_handle_impl< Graph, StoreOldHandlesPolicy,
                StoreEmbeddingPolicy >
                impl_t;
            typedef face_handle< Graph, StoreOldHandlesPolicy,
                StoreEmbeddingPolicy >
                self_t;

            face_handle(vertex_t anchor = graph_traits< Graph >::null_vertex())
            : pimpl(new impl_t())
            {
                pimpl->anchor = anchor;
            }

            face_handle(vertex_t anchor, edge_t initial_edge, const Graph& g)
            : pimpl(new impl_t())
            {
                vertex_t s(source(initial_edge, g));
                vertex_t t(target(initial_edge, g));
                vertex_t other_vertex = s == anchor ? t : s;
                pimpl->anchor = anchor;
                pimpl->cached_first_edge = initial_edge;
                pimpl->cached_second_edge = initial_edge;
                pimpl->cached_first_vertex = other_vertex;
                pimpl->cached_second_vertex = other_vertex;
                pimpl->true_first_vertex = other_vertex;
                pimpl->true_second_vertex = other_vertex;

                pimpl->edge_list.push_back(initial_edge);
                store_old_face_handles_dispatch(StoreOldHandlesPolicy());
            }

            // default copy construction, assignment okay.

            void push_first(edge_t e, const Graph& g)
            {
                pimpl->edge_list.push_front(e);
                pimpl->cached_first_vertex = pimpl->true_first_vertex
                    = source(e, g) == pimpl->anchor ? target(e, g)
                                                    : source(e, g);
                pimpl->cached_first_edge = e;
            }

            void push_second(edge_t e, const Graph& g)
            {
                pimpl->edge_list.push_back(e);
                pimpl->cached_second_vertex = pimpl->true_second_vertex
                    = source(e, g) == pimpl->anchor ? target(e, g)
                                                    : source(e, g);
                pimpl->cached_second_edge = e;
            }

            inline void store_old_face_handles()
            {
                store_old_face_handles_dispatch(StoreOldHandlesPolicy());
            }

            inline vertex_t first_vertex() const
            {
                return pimpl->cached_first_vertex;
            }

            inline vertex_t second_vertex() const
            {
                return pimpl->cached_second_vertex;
            }

            inline vertex_t true_first_vertex() const
            {
                return pimpl->true_first_vertex;
            }

            inline vertex_t true_second_vertex() const
            {
                return pimpl->true_second_vertex;
            }

            inline vertex_t old_first_vertex() const
            {
                return pimpl->old_handles.first_vertex;
            }

            inline vertex_t old_second_vertex() const
            {
                return pimpl->old_handles.second_vertex;
            }

            inline edge_t old_first_edge() const
            {
                return pimpl->old_handles.first_edge;
            }

            inline edge_t old_second_edge() const
            {
                return pimpl->old_handles.second_edge;
            }

            inline edge_t first_edge() const
            {
                return pimpl->cached_first_edge;
            }

            inline edge_t second_edge() const
            {
                return pimpl->cached_second_edge;
            }

            inline vertex_t get_anchor() const { return pimpl->anchor; }

            void glue_first_to_second(face_handle< Graph, StoreOldHandlesPolicy,
                StoreEmbeddingPolicy >& bottom)
            {
                pimpl->edge_list.concat_front(bottom.pimpl->edge_list);
                pimpl->true_first_vertex = bottom.pimpl->true_first_vertex;
                pimpl->cached_first_vertex = bottom.pimpl->cached_first_vertex;
                pimpl->cached_first_edge = bottom.pimpl->cached_first_edge;
            }

            void glue_second_to_first(face_handle< Graph, StoreOldHandlesPolicy,
                StoreEmbeddingPolicy >& bottom)
            {
                pimpl->edge_list.concat_back(bottom.pimpl->edge_list);
                pimpl->true_second_vertex = bottom.pimpl->true_second_vertex;
                pimpl->cached_second_vertex
                    = bottom.pimpl->cached_second_vertex;
                pimpl->cached_second_edge = bottom.pimpl->cached_second_edge;
            }

            void flip()
            {
                pimpl->edge_list.reverse();
                std::swap(pimpl->true_first_vertex, pimpl->true_second_vertex);
                std::swap(
                    pimpl->cached_first_vertex, pimpl->cached_second_vertex);
                std::swap(pimpl->cached_first_edge, pimpl->cached_second_edge);
            }

            template < typename OutputIterator >
            void get_list(OutputIterator o_itr)
            {
                pimpl->edge_list.get_list(o_itr);
            }

            void reset_vertex_cache()
            {
                pimpl->cached_first_vertex = pimpl->true_first_vertex;
                pimpl->cached_second_vertex = pimpl->true_second_vertex;
            }

            inline void set_first_vertex(vertex_t v)
            {
                pimpl->cached_first_vertex = v;
            }

            inline void set_second_vertex(vertex_t v)
            {
                pimpl->cached_second_vertex = v;
            }

        private:
            void store_old_face_handles_dispatch(store_old_handles)
            {
                pimpl->old_handles.first_vertex = pimpl->true_first_vertex;
                pimpl->old_handles.second_vertex = pimpl->true_second_vertex;
                pimpl->old_handles.first_edge = pimpl->cached_first_edge;
                pimpl->old_handles.second_edge = pimpl->cached_second_edge;
            }

            void store_old_face_handles_dispatch(no_old_handles) {}

            boost::shared_ptr< impl_t > pimpl;
        };

    } /* namespace detail */
} /* namespace graph */
} /* namespace boost */

#endif //__FACE_HANDLES_HPP__

/* face_handles.hpp
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
*/