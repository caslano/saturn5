// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file support/map_by.hpp
/// \brief map_by<tag>(b) function

#ifndef BOOST_BIMAP_SUPPORT_MAP_BY_HPP
#define BOOST_BIMAP_SUPPORT_MAP_BY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/support/map_type_by.hpp>
#include <boost/bimap/relation/detail/access_builder.hpp>


#ifdef BOOST_BIMAP_ONLY_DOXYGEN_WILL_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace support {

/** \brief Gets a map view of a bidirectional map

Convertible to \c map_type_by<Tag,Bimap>::type
Instead of using \c map_type_by<Tag,Bimap>::type this functions use
\b Boost.call_traits to find the best way to return this value. To help
the user of this function the following metafunction is provided
\code

namespace result_of {

template< class Tag, class Bimap >
struct map_by( Bimap & b );

} // namespace result_of

\endcode

See also member_at, value_type_of.
\ingroup bimap_group
                                                                        **/

template< class Tag, class Bimap >
BOOST_DEDUCED_TYPENAME result_of::map_by<Tag,Bimap>::type
    map_by( Bimap & b );

} // namespace support
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_ONLY_DOXYGEN_WILL_PROCESS_THE_FOLLOWING_LINES



#ifndef BOOST_BIMAP_DOXIGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace support {

// Since it is very error-prone to directly write the hole bunch
// of relation accesor. They are buil from litle macro blocks that
// are both more readable, leading to self docummenting code and a
// lot more easier to understand and mantain.
// It is very important to note that the three building blocks have
// to laid in the same namespace in order to work. There is also
// important to keep them in order.
// The forward declaration are not necesary but they help a lot to
// the reader, as they undercover what is the signature of the
// result code.
// In the end, it is not quicker to do it in this way because you
// write a lot. But this code has no complexity at all and almost
// every word writed is for documentation.

// Result of
// -------------------------------------------------------------------------
/*
    namespace result_of {

    template< class Tag, class Bimap >
    struct map_by<Tag,Bimap>;
    {
        typedef -unspecified- type;
    };

    } // namespace result_of

*/

BOOST_BIMAP_SYMMETRIC_ACCESS_RESULT_OF_BUILDER
(
    map_by,
    map_type_by
)

// Implementation
// -------------------------------------------------------------------------

BOOST_BIMAP_SYMMETRIC_ACCESS_IMPLEMENTATION_BUILDER
(
    map_by,
    Bimap,
    b,
    return b.left,
    return b.right
)

// Interface
// --------------------------------------------------------------------------

BOOST_BIMAP_SYMMETRIC_ACCESS_INTERFACE_BUILDER
(
    map_by
)

} // namespace support
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXIGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_SUPPORT_MAP_BY_HPP


/* map_by.hpp
sYpdQLcbXw6ZKimKnZAgaon3OofSd7FkgVPTeCEipcoBw+7hrtna5sjS9DVP4h6QDE9gOB4MWvBrY2tAa/Ey9OnwASQXDl6nB3RyYfwwyzPXmjnHzKdUFxlhG06DT/hHNbqQJFW9zhmB3R+RB0jAdqZPzwqja4t6Q27sch1+r/CTUO6Nv5dqyQCteeUbCVzpFy+MU6FUTHqiQK/Fua0749HOXIG6LBc7A7g2wA3eIk6yFyeQXJW1oJNE+X7Ahnhoj7DzlWQraX9MrikV+I2idwUL2//yTIUHopudDlyE7uPz/YdW3e/PL+u+YyX+0MyvDs/xiJJr+zs5gIzYi3+DDxHpQ4DNM8TTKSxTykSsCLj3dD2ETniBCZxJt/jV0VWrj2fonb7NhJv48UP0u1byUvJvc+guiCXr54Y5mvJZJBmqENL5CYttxPVXJvl1UPBMM6kWAaWOBYGzUUx3FWCqSsG/xSTjmyikz8Gs1WUuWEnizRKFJRx0D9g8HPQWj+tVl+7H4g4ONsv0TZm7Wk/Td++OZdeZ/tT7RPMHt70DOY8UkSy5NeaFjijldcoisFIUtfVJZn8OMq8CI1fmufADN79gi0OgcyDds22Fl0knBemkJFW+1Kvsgbfa7fDagnMONJ2Z5+4vE2SFMB99
*/