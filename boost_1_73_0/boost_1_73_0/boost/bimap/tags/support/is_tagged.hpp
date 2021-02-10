// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file tags/support/is_tagged.hpp
/// \brief type_traits extension

#ifndef BOOST_BIMAP_TAGS_SUPPORT_IS_TAGGED_HPP
#define BOOST_BIMAP_TAGS_SUPPORT_IS_TAGGED_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/bimap/tags/tagged.hpp>

/** \struct boost::bimaps::tags::support::is_tagged
\brief Type trait to check if a type is tagged.

\code
template< class Type >
struct is_tagged
{
    typedef {mpl::true_/mpl::false_} type;
};
\endcode

See also tagged.
                                                                                **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace tags {
namespace support {


// is_tagged metafunction

template< class Type >
struct is_tagged :
    ::boost::mpl::false_ {};

template< class Type, class Tag >
struct is_tagged< tagged< Type, Tag > > :
    ::boost::mpl::true_ {};

} // namespace support
} // namespace tags
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_TAGS_SUPPORT_IS_TAGGED_HPP


/* is_tagged.hpp
D+GMFYLnMDe8WHK1CuEksSvfZezurqv5yxC4AZZ3a1OLTGjQMjW3THHA91zEvNA8AaYh4TpWYol/iAJMxiEVOYfx7PL6YvoqhNtMxBkZ2coKdCarPIGMbTgoHnOxcTZKpgzIFNXReCK0QYOVEbLoom8Ohqu1JhvknuVaAtswkbMlOmIGMmNKfdzrxZXKMfpeImPdi/3xu5lZ705yjUGs2RZkacBIqDQPgSRDWMtEpPREQHCxrJa50Fm4jwZdFUlPKtA8z8kW6gmuXdgc5jU8IYlBiRELQw8tC02ubjO5PhBEHMlKWqkCHSEOKJRIhDmEqki4ssL25N5FjakF+LOp2cebgCwwGGiP5nAxb8OSaaFDeHexeD37YQHvRldXo+niGmbnMJpek7E3F9MzTL1AZwr4Xam4RucKxLrMBU9qn3/fp9fqPYOTs8l8/JLcjwp0ytAXpxNTNiPO9DbSvEg6gcV1v4j02eBipdnKggEnPW+o12r9RxRxXiUcTrRJhOxmLw+WlChWh2tk2BEIlymsUXUncsHUFjNUxMRFzAGS7ZYJo0E6qmsZv+emSy61YUbEWANOJJJF5HY7Nmb3HhmrkiahFUylsucIIZfFCoxYc1mZaK2D1v9bABhnhV2JljcsB7MZ4mKaIB4G1ckI
*/