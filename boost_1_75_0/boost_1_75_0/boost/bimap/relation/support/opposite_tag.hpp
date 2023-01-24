// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/support/opposite_tag.hpp
/// \brief Metafunction to obtain the opposite tag in a relation.

#ifndef BOOST_BIMAP_RELATION_SUPPORT_OPPOSITE_TAG_HPP
#define BOOST_BIMAP_RELATION_SUPPORT_OPPOSITE_TAG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/detail/metadata_access_builder.hpp>

/** \struct boost::bimaps::relation::support::opposite_tag

\brief Metafunction to obtain the opposite tag in a relation.

\code

template< class Tag, class Relation >
struct opposite_tag
{
        typedef {OppositeTag} type;
};

\endcode

\ingroup relation_group
                                                                    **/

namespace boost {
namespace bimaps {
namespace relation {
namespace support {

// Implementation of const pair reference type by metafunction

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    opossite_tag,
    right_tag,
    left_tag
)

} // namespace support
} // namespace relation
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_RELATION_SUPPORT_OPPOSITE_TAG_HPP


/* opposite_tag.hpp
1lQ49sPur3DspbvAc/PUo88aNMoSQLKfjPjx6hIz3MMJRvbaFpanFFnFr/22gkNI7wUiHUhNG2xo5flKLOrN3NVuvFylukW/Gu+peTqAH5wKVFlXK+GC6kJWgThXYpp9WQWJTeOeRkxdqcfUuWJi5mqYup4WmLwrLCBEXS9Boj4YUecHEE9fw80N5HZOPm3SNIYCHpbZQPURqAv15dY0VgYpUv+laLYUZK20rJDvhqDNGuFqVMRUKcN5A/y6U1UavLGDkr7cGRYc90GTraLIeqLnElW2MuHM1iqL80CuOgj6WCfJVbtCWrOLkhIvXKECkyk0ojkcCgt1b2wOmCmD3VGaKlHtD5US1U6vFdXDGHRSZBYS1WOqRBXezaJayju8vYVEdV8YZEpPKXuCM6UrP3WlTItDdRJVupSoYqRE9UhbTaLKUyWqVCEDeqWHDhanipHUbEQZq4Ica4E4BQ1n0qXQn80W03FBfcopSkXPbVAHWjN6yXMFi1xlVEMlilwmIXKtRKtIEJ3Iyah9xgXhGBLGHznLLMSmK6NoLGjb5eNc5GQP+ixvcgiZaav6WWyLKGc+1axXObcEQLU7IwUeSTiuSVFXRRqkqLhIlKIO2goARMFkIlOlRxvbMD16ow30EpHmRMlYAwstZM4aejQQfx3Si/hro7fQKmXqrxZ8XpdvBZOKZLOPSiYEREcn+KpAgFKkAHXA3JwA9alZ
*/