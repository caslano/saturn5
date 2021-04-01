// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/pair_layout.hpp
/// \brief Tags for pair layouts

#ifndef BOOST_BIMAP_RELATION_PAIR_LAYOUT_HPP
#define BOOST_BIMAP_RELATION_PAIR_LAYOUT_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

namespace boost {
namespace bimaps {
namespace relation {

//@{

/// \brief Tag for normal layout. ( A,B -> A,B )

struct normal_layout {};

/// \brief Tag for mirror layout. ( A,B -> B,A )

struct mirror_layout {};

//@}

/** \struct boost::bimaps::relation::inverse_layout
\brief Metafunction to obtain the inverse of a layout.

\code
template< class Layout >
struct inverse_layout
{
    typedef {InverseLayout} type;
};
\endcode

See also normal_layout, mirror_layout.
                                                                    **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class Layout >
struct inverse_layout
{
    typedef normal_layout type;
};

template<>
struct inverse_layout< normal_layout >
{
    typedef mirror_layout type;
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

} // namespace relation
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_RELATION_DETAIL_PAIR_LAYOUT_HPP


/* pair_layout.hpp
2cZO0Fyu/PgRzna3+faeGBWduqcKil3YNiJ3q7YQxqkdk0W39ZGwOMjSxSZvAOud6hPcwN93wKkvU4zgmPUtY9LG1V3kt4tNW1d7T12rL1IzkyI8jsiSKzhId3oTbxCF3xv8BiAncloZQtvX6u8//7z4wnuBNc01zvhmnAJ+M0HZ/tap9G8gLLo6TO9Hj6/n4We+3+3PBB69J8rZFjV4AgO7EelwuI4g5jMHcv+dCkkseXBB92+qtTyR9zBonaRGoT6ALuD3BjpEWkAk2+YSN0qwU3ZYImKI20xjf5zOXDL/Y3uYT0FD9Cix362wMtQdh3DpcH7Qj7LzfeJMubguou1oly2Lyv8K5yQMYqKSq08TgIq5fTZHUWGfzUKdKhnwm+dQqkcCIKS+dVR8durQbK5IiJ+WQyZeU58T/4sTI648m2sJSFLXiwRwkPGHgBWNsfvLZZ5igjoHLsnMWdMNNQeAaKaqzWKx580TxR75Nxv/L97kn8ywB+8Ug3jt25rWJ8SKSB7ZI7rW2adgPrmoS3wcCweKE6YxWlu9pepMG32xbQT/LgdzpHoIqg==
*/