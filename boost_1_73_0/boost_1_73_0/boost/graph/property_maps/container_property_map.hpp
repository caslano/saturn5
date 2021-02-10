// (C) Copyright 2007-2009 Andrew Sutton
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0 (See accompanying file
// LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_CONTAINER_PROPERTY_MAP_HPP
#define BOOST_GRAPH_CONTAINER_PROPERTY_MAP_HPP

#include <boost/graph/detail/index.hpp>
#include <boost/property_map/property_map.hpp>

namespace boost
{
// This is an adapter built over the iterator property map with
// more useful uniform construction semantics. Specifically, this
// requires the container rather than the iterator and the graph
// rather than the optional index map.
template < typename Graph, typename Key, typename Container >
struct container_property_map
: public boost::put_get_helper<
      typename iterator_property_map< typename Container::iterator,
          typename property_map< Graph,
              typename detail::choose_indexer< Graph,
                  Key >::index_type >::type >::reference,
      container_property_map< Graph, Key, Container > >
{
    typedef typename detail::choose_indexer< Graph, Key >::indexer_type
        indexer_type;
    typedef typename indexer_type::index_type index_type;
    typedef iterator_property_map< typename Container::iterator,
        typename property_map< Graph, index_type >::type >
        map_type;
    typedef typename map_type::key_type key_type;
    typedef typename map_type::value_type value_type;
    typedef typename map_type::reference reference;
    typedef typename map_type::category category;

    // The default constructor will *probably* crash if its actually
    // used for referencing vertices since the underlying iterator
    // map points past the end of an unknown container.
    inline container_property_map() : m_map() {}

    // This is the preferred constructor. It is invoked over the container
    // and the graph explicitly. This requires that the underlying iterator
    // map use the indices of the vertices in g rather than the default
    // identity map.
    //
    // Note the const-cast this ensures the reference type of the
    // vertex index map is non-const, which happens to be an
    // artifact of passing const graph references.
    inline container_property_map(Container& c, const Graph& g)
    : m_map(c.begin(), indexer_type::index_map(const_cast< Graph& >(g)))
    {
    }

    // Typical copy constructor.
    inline container_property_map(const container_property_map& x)
    : m_map(x.m_map)
    {
    }

    // The [] operator delegates to the underlying map/
    inline reference operator[](const key_type& k) const { return m_map[k]; }

    map_type m_map;
};
}

#endif

/* container_property_map.hpp
15Q3vRlTrgEypJngClM8oqveKP2o3Jtht/PWjHovI5mLxJKBZWaGHpArlw1oGE5Ms5xvnaXgYkOUGpJUxYLmV1rgdsJIa27Z8OdptEigS6Tz6ZKaUvvm3VNsjFTwOaCesFA7NIxmU/fSd8fj82552+r7dRZHfX2HSmGLCiDpIeSpp7w4tGHwXXbJAlwQlxhWgBmdKaZqEaq7bPAIFRogl3O+JMX36EKbIBIfXXVthmlMZ2c7NmLZ/wGd/14Gkw/yDmdKtYiTD1qE+SmPZc0myZ0zddPMSWDKxHMHNZWGtuA9MmCDjKoNQx+CTBlcOGe98+57nee4tnT31Slved7nGyyjC0q5+ZwP9QGOlVrLoWMkvfXNQTicjyrcw3J5po59kW+qcMeKpFzLMPrOshscfDxtzaeVvUaJk5pbpoeXjUDKBmRZVyNP3T497J9KmraEblU2d2JaOX/meSuPTfT6vfGxkfneDyvxauYba6ljaf7mGI2SJxnf1buQiYmYzECYRgFh2HR3hu8wVH4A48+9MnPgb+xxBIF+9M/nMC2ks6gwOtl80eI8MItltlIL4Y8cxAwjG9bvMwuNaVyoSdhg3KtNro2m8k14R2kvVMmZZJ8ELN/wdXFLSgo/5sQt6kXTeLNcYDB3/q5l3C+M
*/