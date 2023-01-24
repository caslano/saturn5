// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file support/value_type_by.hpp
/// \brief Metafunction to access the value types (std::pair compatibles) of a bimap

#ifndef BOOST_BIMAP_SUPPORT_VALUE_TYPE_BY_HPP
#define BOOST_BIMAP_SUPPORT_VALUE_TYPE_BY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/detail/metadata_access_builder.hpp>

/** \struct boost::bimaps::support::value_type_by

\brief Metafunction to obtain the value type of a bimap indexed by one of the sides.

The tag parameter can be either a user defined tag or \c member_at::{side}.
The returned type is signature-compatible with std::pair.

\code

template< class Tag, class Bimap >
struct value_type_by
{
    typedef typename Bimap::{side}_value_type type;
};

\endcode

See also member_at.
\ingroup bimap_group
                                                                    **/

namespace boost {
namespace bimaps {
namespace support {

// Implementation of value type by metafunction

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    value_type_by,
    left_value_type,
    right_value_type
)



} // namespace support
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_SUPPORT_VALUE_TYPE_BY_HPP


/* value_type_by.hpp
fykwp33DPGN/y/X9LQ/ihcqZFyri/pabm1WwKC0IcC4P5nT0WGBHC42iKQseEDz3ThMrXtBvpzaYKBjMhO9V7g5HU6aNpoxG8+ZcOhRRWbsyHk4vXX4Yjl0NNQItyY/N83V9WtD+7RakNFNhvG2L4A1O8N1IQS8huHkkl8hI7pEbzDp6fxxO0XRXcXWYYOh+q37lCTRzNNCsa9c04kmUiEeAoK2g+DRgnX/2QV0ioTbvNKGcTH2tmUaAl1IRn7yl+TcTTAuGxDWoN5lKNCN27CGxY+6tBM3zDRClaSdVJYteO/kmyCgkIMbzZN1yGm5qe7o0Uj6I+blYjKlucF2npmZhGu2zeAnsY9Do8dh3Yi+mB/6/RaePWBqj083Vhql/5LxT3z6Dpn7pfzL1g4TwIjWMlwWtwYo+5mbXYMW3/34NbsI1yBIlaof9/7sGdaFNkDQpeCPvB1RteYiOmknqJvXzRNXgk/LnXBK/h4QwQr8Xxvw+Q99xKXbfs9eAz0uxFitUWEoY8Dcvu2vUUHqpHgeWGnDgRnoHxwnyYzP4PC1M1YgncpdY5q7eY5S5Fa1PCvWpo+yTDjErejqjGOjMUnrnluT35nHzB8wIZGFrC+gp8G4bNXY0yN6t5TIZRe2neRUn817OktwUbOiFVYhUBqsbOkvuhoD9i2+sWqvB91oY39c9UdfDsOE5ZiePTOJhXa1P6mttpJ4Hdi8e
*/