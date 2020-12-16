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
jdwXcB8IvIvCbIkE60ApBHPgDmirUgjm5SjYhtmMsWEeiYZtmP4YG2YFxoZ5LAasRwd1BzwaiykPBaBVHGZcxQFejMeUzQWQNQVzTGAqaJN0UK9q0CYZYBwBxZVBMCVzwT3KIJiGQG3AtgBczAf9Auw1wG+FYAyUg3OLwLoEtFkGwUwoBu1ZDsFMB/oNsNGAPuWgzQ+eI4BnK3Dg91hdwPtAJcBuA9xuBGOpDFyzCazrQC7lEMwnzTjgPAjmIFAasKcB7R9h2tkFEL8NB35OUQA6vgJjD9gugH6vwW8V4L6Ait2g/hUQTMIeTL9QAD4FMqyAYIr2gfMrIJh2QIHAdgGcGAXtAuxpwPQxHPj5iwY0fAvarQKCeQeooAKC2QjUUAHBTBoHx1dAMGvG4TjMqAlMPA7Q7h24x8G9ADPeYcYqGpBlBpS/Cow3wLRZzHqCBmSax7QhK2DkPDLeAGkWMH3KCliI2NWAYosYWxEwAuhRAwRzBEixCoJ55COoD7ApAK98xDwXLAAVf9/eWcAsV8Vx+Aii2NjY2NjY6IxrTcwxY2OzsHE6x+wWc9jY2JdX4pJiY2NjM2dgY2Nt6IzX9jn/e+xunX7bb8/P632Jy8P/3PN+m77O8zV9wkPJ0nTNA97g39E1DycJuuaJJEXPwSPf5HtL17x8zLWia95DBnTNB95httA1X33HPT6Ga/g9SunnhW9O51GLtDgOk7N49P2tMBv0yJqSg5NErwtqLo/6lOjPSM3Nz87D8cv4WbjMvB6VoGueQPaia15EMnQbXj2fR65VF04s4FE30ttwppBHtS/zCdcnN9I1V1zQo/p0C75P9GehFvKo5QnXWbgDmb7tEy60sEeF6BG43aIeleNnk/Agwn2a8HQyoGs+RsZ0zVkX86gpL/cJ1yez0eNwHxKla75JLLrm7Yt71LZ0zZdJmq75BsnQxzC5hLxm4StL8jhtjsPxMry2y33CFZfj+tMtuFnEI7MlDhdb3r3mEXjd8u7xLpx9BY87J6FF8Fl4IelfyHWGi6zoPm8ErrmSR+45Lbg/SbZ9wgvIXnTNZVf2qGPpmhuSC+mam5MGPQ5PIO2WT1ggXbrmnqtwPemaM67Ke6Nrzk/UZbxOuD3h/lA4JifTNVXUo2y65hlR9zXbcED4vIRrr+bhPyHoE5bIInTNJ0iUrvkSidHH8MLVPapIt+Hca3rc7yyskBHH23DhtXjvV/iEF5Nj6Zodkqd3YXFtj3LobTgmXHNhxOJ6clzzYhKhaz5N1qcP4TrryPsVnkbevdwnfJT49Tnw4I14jxzPwN02cT/rNHz3MK45x9XhHvUQ2Yrz+/D9I7hW13P8SEjY4wtXz7g/a8Hjj3J7Dt5HbrzCJ3z7aJ6LrjnDMVwH/frh9Me55wfgUiRD19ySnEzX3JkU6ZpN0qFr3kfup2t+RJ6ma25zPN8TehK+fgIzhD6GS57I813tE15J5qVr3k4i9D7c7yTX8wxc4WTzvuDZRO6XYPoMj1qJ45q3EdkzwhfPcs8fw9C5XDe6ZoPwOQo7F3DdOK75FllEn695EzNOXxM4JjyO8NWb3Vk3hjPfws9e6ROeeCs/Q9e8tOdRm9I1eyRJ11zhHl4rXfN+kqX3YfNeHKNrvv+gR11F1zzqIX6erlkiT9M13+pzPemaTzwqx4XLPsb3R88HeAixrvYJ7yZxuuZ0j3vULnTNfQfMQbrmaSRHz8GHiU3XXOAJXg9d8xHSo2v6n+R56ZrzkjfpIXjeUx512DV8LnCO57huV/uENw75DK7xCdd8ns+Lrnk6idE1HyJ70TU3fYm1g65ZfMk93oabvex+FnF444jrxvEu9L7mfu4B+Mgkc4k=
*/