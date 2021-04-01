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
3B/vqEBDJsOhT1pzqDqlCHCB4O1CIAN3XMm89mVdTBiBUo6SkQ5aUl0FkCoaByXzlv63aPHEES9Kst/MLpyBdDljxoQd9pMXdPHeAIerS8FCAJpmdLQ+oerGw20ev1ldS86Et36OzrzkQubydJp05hSde3kOL97WkjVud6h/ar5f1j/PcYn7Z8jpwyfa2PBqt5QsdEXylYZvp99ad07icUQ+8142nOUYSrzp4Wj36HejYGK3LcPxRZnc0cZzK+GRrNmec6+i0YNbG4JUPluRSKxnI/+4NiCZJbP8eE2+74gpV1Z64ANfd3bhqpm3TsDD3quIKkV5HtpsmoYFRh+i16j+Pgpe2e91aa3ET1BlTyd2nRLZL+zLE1Sva4r2lvmwGMBP0EPzHysZEzWdmX6HYqVxcsyE/b1Ltgmlmo7hAF9pjur9+4U9UtipK56B/IpWOSgKygYhrpc3/ycTku9wKo3Mwt8m+Yx4VpGjJaZYTwwS92UPTXZsH4rl0/OX61XXaIbF44v0A7eX6keQ2jqeeAm1QvNr+yfDSCuTxSKYrTK36rqq+iuJKuh3eQ==
*/