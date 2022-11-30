//
//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//
#ifndef BOOST_DISJOINT_SETS_HPP
#define BOOST_DISJOINT_SETS_HPP

#include <vector>
#include <boost/graph/properties.hpp>
#include <boost/pending/detail/disjoint_sets.hpp>

namespace boost
{

struct find_with_path_halving
{
    template < class ParentPA, class Vertex >
    Vertex operator()(ParentPA p, Vertex v)
    {
        return detail::find_representative_with_path_halving(p, v);
    }
};

struct find_with_full_path_compression
{
    template < class ParentPA, class Vertex >
    Vertex operator()(ParentPA p, Vertex v)
    {
        return detail::find_representative_with_full_compression(p, v);
    }
};

// This is a generalized functor to provide disjoint sets operations
// with "union by rank" and "path compression".  A disjoint-set data
// structure maintains a collection S={S1, S2, ..., Sk} of disjoint
// sets. Each set is identified by a representative, which is some
// member of of the set. Sets are represented by rooted trees. Two
// heuristics: "union by rank" and "path compression" are used to
// speed up the operations.

// Disjoint Set requires two vertex properties for internal use.  A
// RankPA and a ParentPA. The RankPA must map Vertex to some Integral type
// (preferably the size_type associated with Vertex). The ParentPA
// must map Vertex to Vertex.
template < class RankPA, class ParentPA,
    class FindCompress = find_with_full_path_compression >
class disjoint_sets
{
    typedef disjoint_sets self;

    inline disjoint_sets() {}

public:
    inline disjoint_sets(RankPA r, ParentPA p) : rank(r), parent(p) {}

    inline disjoint_sets(const self& c) : rank(c.rank), parent(c.parent) {}

    // Make Set -- Create a singleton set containing vertex x
    template < class Element > inline void make_set(Element x)
    {
        put(parent, x, x);
        typedef typename property_traits< RankPA >::value_type R;
        put(rank, x, R());
    }

    // Link - union the two sets represented by vertex x and y
    template < class Element > inline void link(Element x, Element y)
    {
        detail::link_sets(parent, rank, x, y, rep);
    }

    // Union-Set - union the two sets containing vertex x and y
    template < class Element > inline void union_set(Element x, Element y)
    {
        link(find_set(x), find_set(y));
    }

    // Find-Set - returns the Element representative of the set
    // containing Element x and applies path compression.
    template < class Element > inline Element find_set(Element x)
    {
        return rep(parent, x);
    }

    template < class ElementIterator >
    inline std::size_t count_sets(ElementIterator first, ElementIterator last)
    {
        std::size_t count = 0;
        for (; first != last; ++first)
            if (get(parent, *first) == *first)
                ++count;
        return count;
    }

    template < class ElementIterator >
    inline void normalize_sets(ElementIterator first, ElementIterator last)
    {
        for (; first != last; ++first)
            detail::normalize_node(parent, *first);
    }

    template < class ElementIterator >
    inline void compress_sets(ElementIterator first, ElementIterator last)
    {
        for (; first != last; ++first)
            detail::find_representative_with_full_compression(parent, *first);
    }

protected:
    RankPA rank;
    ParentPA parent;
    FindCompress rep;
};

template < class ID = identity_property_map,
    class InverseID = identity_property_map,
    class FindCompress = find_with_full_path_compression >
class disjoint_sets_with_storage
{
    typedef typename property_traits< ID >::value_type Index;
    typedef std::vector< Index > ParentContainer;
    typedef std::vector< unsigned char > RankContainer;

public:
    typedef typename ParentContainer::size_type size_type;

    disjoint_sets_with_storage(
        size_type n = 0, ID id_ = ID(), InverseID inv = InverseID())
    : id(id_), id_to_vertex(inv), rank(n, 0), parent(n)
    {
        for (Index i = 0; i < n; ++i)
            parent[i] = i;
    }
    // note this is not normally needed
    template < class Element > inline void make_set(Element x)
    {
        parent[x] = x;
        rank[x] = 0;
    }
    template < class Element > inline void link(Element x, Element y)
    {
        extend_sets(x, y);
        detail::link_sets(&parent[0], &rank[0], get(id, x), get(id, y), rep);
    }
    template < class Element > inline void union_set(Element x, Element y)
    {
        Element rx = find_set(x);
        Element ry = find_set(y);
        link(rx, ry);
    }
    template < class Element > inline Element find_set(Element x)
    {
        return id_to_vertex[rep(&parent[0], get(id, x))];
    }

    template < class ElementIterator >
    inline std::size_t count_sets(ElementIterator first, ElementIterator last)
    {
        std::size_t count = 0;
        for (; first != last; ++first)
            if (parent[*first] == *first)
                ++count;
        return count;
    }

    template < class ElementIterator >
    inline void normalize_sets(ElementIterator first, ElementIterator last)
    {
        for (; first != last; ++first)
            detail::normalize_node(&parent[0], *first);
    }

    template < class ElementIterator >
    inline void compress_sets(ElementIterator first, ElementIterator last)
    {
        for (; first != last; ++first)
            detail::find_representative_with_full_compression(
                &parent[0], *first);
    }

    const ParentContainer& parents() { return parent; }

protected:
    template < class Element > inline void extend_sets(Element x, Element y)
    {
        Index needed
            = get(id, x) > get(id, y) ? get(id, x) + 1 : get(id, y) + 1;
        if (needed > parent.size())
        {
            rank.insert(rank.end(), needed - rank.size(), 0);
            for (Index k = parent.size(); k < needed; ++k)
                parent.push_back(k);
        }
    }

    ID id;
    InverseID id_to_vertex;
    RankContainer rank;
    ParentContainer parent;
    FindCompress rep;
};

} // namespace boost

#endif // BOOST_DISJOINT_SETS_HPP

/* disjoint_sets.hpp
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
*/