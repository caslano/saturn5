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
iHBm9fqVTkLrxw4Kcr/dhDNyhEL9e7ciXLMhAQcUa9363l+fUrYuoShMVGcUHYtkJmj/srgXsg6wsKXuOrYvE6XUICmOOcrAwD46WhnMYf37Po5p2lJngbuMW7IHO5g+aJDWYXBpzPD+WVKIrhQlaiODLP1wl3npvhyasqE7BdBD8YlTi5hb9MI+VyCSzWfESNwbEkXUYrKCMV70DBjsTbWB7Z7AUUs5+WlxJetQYqNgXdwxtqmbnsEc0OhQktEhecfvSl3BZr6ZnAvNN2ahjWcArZfFPaGkUNHnPn2JJNf46bO0n5cqkrVnVwkEmggJumpaVNlh3cTOhB2RIww9GcQL0fN14c9BKWzAtaCKk3PbNzt0mZc3erslhApkpwP5MElD4mY07Pqgt4ZSXt35uZTqfYC1XmDmnvDkp3gIJLAoGMNq40fYy1DvO5A1NKTWWtxfZySo9D7s1SQ1pHg6AQ5iD5XyCAah7DFMSSbAz2KQn5an8s0LxVHB4BnA0MP5vU2LfWtXiLAqmrJyl3OAJaf/IuQJZ9FM6VjsGPhXs2/Y8Bf2LEC808FXXg==
*/