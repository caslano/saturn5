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
Z6ngcSnz513tRnsfDk/6k+MjEn+pubUzy9WNFR2xNJ2y6CtqrRA2pf8lX6BlHIGXcRkLeWPtrABBjFIxJSzALbqfQERrh+1KTrvxTMgoLWIOh9rEQrVmR2tLROmghMu4nsDZ4M/jy/FZ+Lk/ngxGw3B4eQ5Hv0PnrvP2ddzpkBEDWQt923pz0MIk00WWKYT1AvHN4hjDkSjyqslZZEhrG18x55Q3WcqEbGBOz0WUK80jJWPdglFKQNgyR9s00KaIvhJpoYnZi1ghYvkLK4TSiJgJiW9zRomEGIEFR8xSKCNmuMs1fsdwAaENU4TrdFlpTSwdDogPyzAkLJq1rPNingh0fzA474eDYXg5gQNAF6xrvr0vuLroA9kQqiQJzca30UUA5N7B8HQUBqOgdxZa1kG963wwHJzj8sV49GHcn0zC08vhcYCR6J0NgivUIeiPP/fObE183bFX4xlPNb+vg/PSU+T/P+koFyGZNGrqSTC6CE9GX4Zno95J2DvFzWHwcTAJzzHnwj+vgv6krudvSPEGpm+BvWi+rNPgH4xBbUHKaIMk4HTJ7WaZVamgKRFKkCD+OIZ1qrDSYjDAmgj7FINu43u3QaC1CMDfmVq4+oJb0BvhX6f9MXmjMrTOQ1io/KsNrjaIqggBZuAu
*/