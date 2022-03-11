//
//=======================================================================
// Copyright 1997-2001 University of Notre Dame.
// Copyright 2009 Trustees of Indiana University.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek, Michael Hansen
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//

#ifndef BOOST_INCREMENTAL_COMPONENTS_HPP
#define BOOST_INCREMENTAL_COMPONENTS_HPP

#include <boost/detail/iterator.hpp>
#include <boost/graph/detail/incremental_components.hpp>
#include <boost/iterator/counting_iterator.hpp>
#include <boost/make_shared.hpp>
#include <boost/pending/disjoint_sets.hpp>
#include <iterator>

namespace boost
{

// A connected component algorithm for the case when dynamically
// adding (but not removing) edges is common.  The
// incremental_components() function is a preparing operation. Call
// same_component to check whether two vertices are in the same
// component, or use disjoint_set::find_set to determine the
// representative for a vertex.

// This version of connected components does not require a full
// Graph. Instead, it just needs an edge list, where the vertices of
// each edge need to be of integer type. The edges are assumed to
// be undirected. The other difference is that the result is stored in
// a container, instead of just a decorator.  The container should be
// empty before the algorithm is called. It will grow during the
// course of the algorithm. The container must be a model of
// BackInsertionSequence and RandomAccessContainer
// (std::vector is a good choice). After running the algorithm the
// index container will map each vertex to the representative
// vertex of the component to which it belongs.
//
// Adapted from an implementation by Alex Stepanov. The disjoint
// sets data structure is from Tarjan's "Data Structures and Network
// Algorithms", and the application to connected components is
// similar to the algorithm described in Ch. 22 of "Intro to
// Algorithms" by Cormen, et. all.
//

// An implementation of disjoint sets can be found in
// boost/pending/disjoint_sets.hpp

template < class EdgeListGraph, class DisjointSets >
void incremental_components(EdgeListGraph& g, DisjointSets& ds)
{
    typename graph_traits< EdgeListGraph >::edge_iterator e, end;
    for (boost::tie(e, end) = edges(g); e != end; ++e)
        ds.union_set(source(*e, g), target(*e, g));
}

template < class ParentIterator >
void compress_components(ParentIterator first, ParentIterator last)
{
    for (ParentIterator current = first; current != last; ++current)
        detail::find_representative_with_full_compression(
            first, current - first);
}

template < class ParentIterator >
typename boost::detail::iterator_traits< ParentIterator >::difference_type
component_count(ParentIterator first, ParentIterator last)
{
    std::ptrdiff_t count = 0;
    for (ParentIterator current = first; current != last; ++current)
        if (*current == current - first)
            ++count;
    return count;
}

// This algorithm can be applied to the result container of the
// connected_components algorithm to normalize
// the components.
template < class ParentIterator >
void normalize_components(ParentIterator first, ParentIterator last)
{
    for (ParentIterator current = first; current != last; ++current)
        detail::normalize_node(first, current - first);
}

template < class VertexListGraph, class DisjointSets >
void initialize_incremental_components(VertexListGraph& G, DisjointSets& ds)
{
    typename graph_traits< VertexListGraph >::vertex_iterator v, vend;
    for (boost::tie(v, vend) = vertices(G); v != vend; ++v)
        ds.make_set(*v);
}

template < class Vertex, class DisjointSet >
inline bool same_component(Vertex u, Vertex v, DisjointSet& ds)
{
    return ds.find_set(u) == ds.find_set(v);
}

// Class that builds a quick-access indexed linked list that allows
// for fast iterating through a parent component's children.
template < typename IndexType > class component_index
{

private:
    typedef std::vector< IndexType > IndexContainer;

public:
    typedef counting_iterator< IndexType > iterator;
    typedef iterator const_iterator;
    typedef IndexType value_type;
    typedef IndexType size_type;

    typedef detail::component_index_iterator<
        typename IndexContainer::iterator >
        component_iterator;

public:
    template < typename ParentIterator, typename ElementIndexMap >
    component_index(ParentIterator parent_start, ParentIterator parent_end,
        const ElementIndexMap& index_map)
    : m_num_elements(std::distance(parent_start, parent_end))
    , m_components(make_shared< IndexContainer >())
    , m_index_list(make_shared< IndexContainer >(m_num_elements))
    {

        build_index_lists(parent_start, index_map);

    } // component_index

    template < typename ParentIterator >
    component_index(ParentIterator parent_start, ParentIterator parent_end)
    : m_num_elements(std::distance(parent_start, parent_end))
    , m_components(make_shared< IndexContainer >())
    , m_index_list(make_shared< IndexContainer >(m_num_elements))
    {

        build_index_lists(parent_start, boost::identity_property_map());

    } // component_index

    // Returns the number of components
    inline std::size_t size() const { return (m_components->size()); }

    // Beginning iterator for component indices
    iterator begin() const { return (iterator(0)); }

    // End iterator for component indices
    iterator end() const { return (iterator(this->size())); }

    // Returns a pair of begin and end iterators for the child
    // elements of component [component_index].
    std::pair< component_iterator, component_iterator > operator[](
        IndexType component_index) const
    {

        IndexType first_index = (*m_components)[component_index];

        return (std::make_pair(
            component_iterator(m_index_list->begin(), first_index),
            component_iterator(m_num_elements)));
    }

private:
    template < typename ParentIterator, typename ElementIndexMap >
    void build_index_lists(
        ParentIterator parent_start, const ElementIndexMap& index_map)
    {

        typedef
            typename std::iterator_traits< ParentIterator >::value_type Element;
        typename IndexContainer::iterator index_list = m_index_list->begin();

        // First pass - find root elements, construct index list
        for (IndexType element_index = 0; element_index < m_num_elements;
             ++element_index)
        {

            Element parent_element = parent_start[element_index];
            IndexType parent_index = get(index_map, parent_element);

            if (element_index != parent_index)
            {
                index_list[element_index] = parent_index;
            }
            else
            {
                m_components->push_back(element_index);

                // m_num_elements is the linked list terminator
                index_list[element_index] = m_num_elements;
            }
        }

        // Second pass - build linked list
        for (IndexType element_index = 0; element_index < m_num_elements;
             ++element_index)
        {

            Element parent_element = parent_start[element_index];
            IndexType parent_index = get(index_map, parent_element);

            if (element_index != parent_index)
            {

                // Follow list until a component parent is found
                while (index_list[parent_index] != m_num_elements)
                {
                    parent_index = index_list[parent_index];
                }

                // Push element to the front of the linked list
                index_list[element_index] = index_list[parent_index];
                index_list[parent_index] = element_index;
            }
        }

    } // build_index_lists

protected:
    IndexType m_num_elements;
    shared_ptr< IndexContainer > m_components, m_index_list;

}; // class component_index

} // namespace boost

#endif // BOOST_INCREMENTAL_COMPONENTS_HPP

/* incremental_components.hpp
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
*/