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
hGOLefPDLvVyltCNMzntAqqqVa/D+p8YtbsOdEA7T897wrVl3KwuCl2l/Asc/NgVLbCUyBQ76/D8VetAT5zFPBOou2OcXtbZQvDaeW8YfYuqQTXv6gqpQ3tIm8Inw3UBBEKnsJTGAJaUMsynIuuAtjUOhRJmPKJ6tW13rxOn3xNJWzRREBzLVnc7McCsp0lW8oi3J97TNgn98eAR0XBD0lpLz79MU3Fv28evOIxrHYdGHgfdUtk7mt2hSWKQPrMZDfeeMFh0Oxo5Qo/o5CEBmLhBG4AHHAZ1vlTG7nCZxPo4vLo8pV1GsWHzK3M5Q6UXR5+UyTrI+Tr0W+8PROMwHm78PWBWdPUOv4xBg40nltbG5m6NxhK31oBMQAh6j0sB77zLrsGK9EQ/YQhksX3pvHQzVaZMvcOGpm9Oz1+PTtOj8fHo6nTaG0YdhwsNEQUAR1eVq5p4oVBY1O8OxMdxev6uLdliBWgPBToCgxT57j5R1qMCG4TOX9Dv/UfbTTrbi5VQa+XvUjgsGllRr/cgv/vDNmUwcM77kvBhubE5OkMslIODLXlR9zAaz8dbTXZsKsCK1zFunMOwADojomrmakl9szMRmk3GUL/tri2LdcByI7ITicv5xTTFA0Fo9yR9qzDQdT9zywEyp2/7
*/