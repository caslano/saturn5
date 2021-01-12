// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/detail/key_extractor.hpp
/// \brief Key extractor for a pair<Key,Data>.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_KEY_EXTRACTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_KEY_EXTRACTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {
namespace detail {

/// \brief Key Extractor

template < class T >
struct key_from_pair_extractor 
{
    typedef T argument_type;
    typedef BOOST_DEDUCED_TYPENAME T::first_type result_type;

    result_type operator()( const T & p ) { return p.first; }
};

} // namespace detail
} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_KEY_EXTRACTOR_HPP



/* key_extractor.hpp
32e8XyXlHmUnSUR5tZ7aWPXo43VqLe1G3M8BpHiLtIp6FXwfVb9eT9ZvhXcdw6291BhnRJhXgBXXML/ftmZRmdvsxk436ifBrQhDvhWncQs3V+6cFmT6LimF97vOePN5ZQNu6OHKj+A+lsH5PyZBiUGPdYcPHgUDLpAUXLwPeOIfpe5w/ony+zgpOeRKNcGbuqD6F1pD3cLPGMrk3MHJ+0YG/D7HWIA7sMTIQ8FuxNsrMnYZ
*/