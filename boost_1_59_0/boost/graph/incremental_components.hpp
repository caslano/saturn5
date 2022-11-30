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

#include <boost/tuple/tuple.hpp>
#include <boost/graph/detail/incremental_components.hpp>
#include <boost/iterator/counting_iterator.hpp>
#include <boost/smart_ptr/make_shared.hpp>
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
typename std::iterator_traits< ParentIterator >::difference_type
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