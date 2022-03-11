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