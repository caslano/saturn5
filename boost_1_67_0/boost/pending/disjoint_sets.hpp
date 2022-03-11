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