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
JO0ou4z3xV7esNN+JGk/tOvcLvZca8vOir342mk/k7qMscv9Usbl7bbM2wN1mWfXxQ+yIA+7jG6QBfzBTnsFZOk32uX2hqzc2+63QA+U+75dxmDI3vrcll0DWfhOO79QkTXadYmQOt9q1+UGiafGx7ekHcV2vBiJp/otXtqmZGMhazhgy26Vcp+3ZSmQxWTb9ZsmennBjncHZM5Yuy6zIas7ZMfLhqxa1TlPyj1i62qetONNu9z7pYzH7fyKJT/lJxdJ2z6w0z4KWf5hO+3jopdQO22F6FTlt1ry22WnfUrq/LFdxjMSL8FOu1FkT9lpt4j+SmzZz8SGlC9+XtKus+PtlPYqXe0W2WA77S+kfr+30/5S2lZhyw6I7B27zockv3hb9juxA+X/3hL9KTtokXY8a8tOSF3usOv3oZSr/NofPL7uT89AVjLAjnde+jLaLuMLkQXbMi9P+JcmO62vJ8oda8fzl3gJdrxveKK94209XwmZ85Adr7+kVToY5AkdTLd1dTVkdcqGrpX8ZtnxwkWmxscIyNKVDm6SeCfteN+Rcj+yZXGe6MtJdjsSJd4zdl0mQBbpaet+spSRZMdLlbp8ZMtmiOwWu9xZUu6LdrlzJL9f22lzpT+UXc2VtGoNcp/0xx12fg9C1v60nV+J6Fnpfglk4WpeWCb9psb5k6KXNFu2SspQ66u1Uj+1Dnsasgbl738IWUmrnXYzZPmqztukDDX/Pic6HWr3+Ysi62TLakV/DXZ+eyC7/gu7Lq9BVvGcnfbXUpcEO22D6KXOlh2GLKCLLXtTdLDKlr0DWZXqy+Oi++/a5Z6E7Lga5x9L/VTaP0n91Lx1TvJbb7ftImTOQLsMTy/YS5ot6+yFPhpky7p6oY++YZfR3QvtOGnLekEWsNGW9YOs0ctuR5CUu9aON8QL/faaXedhkOU/adflOsjaX7bjRYpMzQHRIlN6+bbUL9LOb4zEy7PjJUj91PgYLzpIsmWTIEs+aKe9DbI6Nc+kSdoaO14GZM537PzuhKzlhC27G7KK7nbafKnfblsHhVJGjC17QHS6yU77sKRdaJdRKnV+x067VGTKXp6Q/Lra+a2ELEj1ZaXoWa1p1oueT9myH4j+ztmyH0s7htt12Sp6qbLjbZe6KJ/zgrRNzQsvi57VmqZO2hZvt20vZNXttuxXXl/fq70habvb8RpF9rZd7hFpr/Kdb4vMy077nujgGlvWKn0+xdbBKWlbZ7sdf5SxqtYvn0LWQ81RF0RXu+14Ht7Q87dsWSdv1KWfXZfLvKH7F+14ASI7ZcfrCVmQ2tv39Uade9mygSJTNhks5frYsqESr5stG+4N/Y22dfpNyKrW2LqK8kZ7F9uyUZAFvGnLRku5v7Nlt0jaa+22JUHmhNnlThQdqP3lVEl7wY53u5Qba8vSpVxlG1mQ5b9m53cXZNUDbdm90m+/tGUFUj81LywQXak15kNSxh9s2SNS53m2rEzyO2LLloueVZ2/K/kds/X3PZEpX7xObEON1Q2ig9/bev6RtLfUlv0Usoomu4xqyNao/eUO0fNHdtqXIKsLtGU/F5nSSz1kDcpn7xe9qLn7dYmn2vFb0XMfW9YEWbjaQxyVeOo87F3Rgeq3D6Qdau5pk3jKX50WO/jYzu8TyF4+a+vqc6mLvW7v+G+QKsMHsqpcW9YFsgA19i+HLDnGjtcDsgY11/aBrGKjXZcBImtT53+Qley144VA5ijdh0k8ZX/XS13UmceNUoY6zxkJWf5MO20sZNVb1fkfZO3qzGMcZHVqfZAsaZUdTIGsRa1jp0v9Dtltmyn5BdhlZIqer7JlOaKDp+363SP9pvZR8yGLUWuuIpGpfls=
*/