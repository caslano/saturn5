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
CcEINHUi5hvSHD5RKqOb1X+IRD7U2TtugjPVZLdEYU9mpAzmx3+UIuBOKEiAQ40tvl4O6tDV6BqBsAkuv1qnVxoL9BHmOG/xsZwrsA9BKiCOjPaathX2Yfp2H1pZ53DjDSJUJXVTsVfyVx9jEUI8Upeeg/cI86QVJWbSWnuIl1Svx362NZIBIpo8G7pfHpj/7UvyCgtiGFD6jkxD5DMnvGqI7RvvO4YQcmZ+lWjHEkdv7t+dmkH14rxtz0s+X5gfVF2DbspG6hpuqKWtNA/zWt/cgEjVvbMxfJeeyPcBXQl9AfbB2B/Rm7WMom7LiZ9FiO/QdiIFi5FhqCIisBreuXgajjB8AnLL5W3QFmISRRkQ0KZZna5hgIbYdkC7reLlKtQGsEcXRXZktFmudeVRopPTfpzC5VJJzDJ4fEaR58o68zb0ppkyqZOzLD8McRVwxIQjJUR+J1hdgWILAwvXLxUgbJWOHQj9o4pXT4lJppnN5S/ikeqEV7Y7dLmVOGVvr81VMcUKcOh5LoM9nqwaL2J66Fucy4kEqh9KD8egP42lzuqR7S7nSLhJMA==
*/