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