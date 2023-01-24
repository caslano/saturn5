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
X+ETdcEAP+EpHnoxk5HESTEL3T0deyLnRVZwPBQkjrbgaOJoAadeclB6MhWMeXSqYGkg8DTmRTAjjCALW4Ag+18clCD/WNyfILtTr0+Qm+4cjCDPd0cS5NtvI/Esv6QQ5NAdvJdUCXK8X8Z5l7QEyf0yTJCdAwjy61QNQSyXBhDkILRVO2q6QpC4X6kEOYsSsgseScEkUphCnMkw/OLEQcrku/NkMYnAiCeRnERFlArb6NCFkB2MoLmmntNp+x0qnXZDwvjCi5Fk+i5VIdOTWjKVfxNJphPdkdjP71LINO+bSLl5rV/Gm7u0ZBr/jwFyM4IUtAGdyAhGKfEODaU+BykjDVpCPTMNCPWjOxVCtf8SCJWChBqOkvP4C/8nQl3M70eo4mnXJdSJOwYj1LyvIwn12jf98P9KIdSG2yPl6bF+GS9/qSVUb3CAPEUSasE0DaHe+7I/odZBa7WlNoVQ+57nhEqpfQUJ5QG6kUKVOKBex+ibCxTca3Yg7o52BNV2mhxjqJ+ZpqA+iblTPo+C/kV6n6IFgCFD/7dfq1hxyCZ8ydC/SMdHZNTTyn4Zr/yD05GjXwfod7yLai1HmWsOcq/q0FSFYdW/Zx4sUMetipG55nkONw7zZZHy7goqZAw8RodzDHxlEdA/1aUFKprSSwwogwpUyT8U6FdFZIyhh/plnB0BfRRAb5NVxibDO9KEzDkbcLYw+zcF7d9M
*/