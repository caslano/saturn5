// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file support/map_type_by.hpp
/// \brief Metafunction to access the map view types of a bimap

#ifndef BOOST_BIMAP_SUPPORT_MAP_TYPE_BY_HPP
#define BOOST_BIMAP_SUPPORT_MAP_TYPE_BY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/detail/metadata_access_builder.hpp>

/** \struct boost::bimaps::support::map_type_by

\brief Metafunction to obtain the map view type of a bimap indexed by one of the sides.

The tag parameter can be either a user defined tag or \c member_at::{side}.
The returned type is signature-compatible with std::pair.

\code

template< class Tag, class Bimap >
struct map_type_by
{
    typedef typename Bimap::{side}_map_type type;
};

\endcode

See also member_at.
\ingroup bimap_group
                                                                    **/

namespace boost {
namespace bimaps {
namespace support {

// Implementation of map type by metafunction

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    map_type_by,
    left_map,
    right_map
)



} // namespace support
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_SUPPORT_MAP_TYPE_BY_HPP


/* map_type_by.hpp
noumM4v26GhW23pUb1ejx9vW3Njuam1t7JrTqTbOcbd19Hi6vPDos3WvpuJ4jvhsUuY56uFpePnPDMyAd4YPAq381GdWeLbTPQCvKMF/OHCasrVDSeyW/F0PjxV4tP3nPi2fgMYK9Ik54HMoq0MJbAz/8lU1PuPriSsecGzz/LXL3Txr1we6FQQCgUAgEAgEAoFAIP61qIGyKj//w7sq8n0rc3GOnt3rlPpfPLv7tEA/UU/6
*/