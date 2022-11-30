//
//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_DETAIL_EDGE_HPP
#define BOOST_GRAPH_DETAIL_EDGE_HPP

#include <iosfwd>

#include <boost/functional/hash.hpp>

namespace boost
{

namespace detail
{

    template < typename Directed, typename Vertex > struct edge_base
    {
        inline edge_base() {}
        inline edge_base(Vertex s, Vertex d) : m_source(s), m_target(d) {}
        Vertex m_source;
        Vertex m_target;
    };

    template < typename Directed, typename Vertex >
    class edge_desc_impl : public edge_base< Directed, Vertex >
    {
        typedef edge_desc_impl self;
        typedef edge_base< Directed, Vertex > Base;

    public:
        typedef void property_type;

        inline edge_desc_impl() : m_eproperty(0) {}

        inline edge_desc_impl(Vertex s, Vertex d, const property_type* eplug)
        : Base(s, d), m_eproperty(const_cast< property_type* >(eplug))
        {
        }

        property_type* get_property() { return m_eproperty; }
        const property_type* get_property() const { return m_eproperty; }

        //  protected:
        property_type* m_eproperty;
    };

    template < class D, class V >
    inline bool operator==(const detail::edge_desc_impl< D, V >& a,
        const detail::edge_desc_impl< D, V >& b)
    {
        return a.get_property() == b.get_property();
    }
    template < class D, class V >
    inline bool operator!=(const detail::edge_desc_impl< D, V >& a,
        const detail::edge_desc_impl< D, V >& b)
    {
        return !(a.get_property() == b.get_property());
    }

    // Order edges according to the address of their property object
    template < class D, class V >
    inline bool operator<(const detail::edge_desc_impl< D, V >& a,
        const detail::edge_desc_impl< D, V >& b)
    {
        return a.get_property() < b.get_property();
    }
    template < class D, class V >
    inline bool operator<=(const detail::edge_desc_impl< D, V >& a,
        const detail::edge_desc_impl< D, V >& b)
    {
        return a.get_property() <= b.get_property();
    }
    template < class D, class V >
    inline bool operator>(const detail::edge_desc_impl< D, V >& a,
        const detail::edge_desc_impl< D, V >& b)
    {
        return a.get_property() > b.get_property();
    }
    template < class D, class V >
    inline bool operator>=(const detail::edge_desc_impl< D, V >& a,
        const detail::edge_desc_impl< D, V >& b)
    {
        return a.get_property() >= b.get_property();
    }

} // namespace detail

} // namespace boost

namespace std
{
template < class Char, class Traits, class D, class V >
std::basic_ostream< Char, Traits >& operator<<(
    std::basic_ostream< Char, Traits >& os,
    const boost::detail::edge_desc_impl< D, V >& e)
{
    return os << "(" << e.m_source << "," << e.m_target << ")";
}
}

// Boost's functional/hash
namespace boost
{
template < typename D, typename V >
struct hash< boost::detail::edge_desc_impl< D, V > >
{
    std::size_t operator()(const boost::detail::edge_desc_impl< D, V >& x) const
    {
        return hash_value(x.get_property());
    }
};
}

#endif // BOOST_GRAPH_DETAIL_DETAIL_EDGE_HPP

/* edge.hpp
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
*/