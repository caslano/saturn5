// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/support/pair_by.hpp
/// \brief pair_by<member>(r) function

#ifndef BOOST_BIMAP_RELATION_SUPPORT_PAIR_BY_HPP
#define BOOST_BIMAP_RELATION_SUPPORT_PAIR_BY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/support/pair_type_by.hpp>
#include <boost/bimap/relation/detail/access_builder.hpp>

#ifdef BOOST_BIMAP_ONLY_DOXYGEN_WILL_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace relation {
namespace support {

/** \brief Gets a pair view of the relation.

\ingroup relation_group
                                                                        **/

template< class Tag, class Relation >
BOOST_DEDUCED_TYPENAME result_of::pair_by<Tag,Relation>::type
    pair_by( Relation & rel );

} // namespace support
} // namespace relation
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_ONLY_DOXYGEN_WILL_PROCESS_THE_FOLLOWING_LINES


#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace relation {
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

    template< class Tag, class Relation >
    struct pair_by<Tag,Relation>;
    {
        typedef -unspecified- type;
    };

    } // namespace result_of
*/

BOOST_BIMAP_SYMMETRIC_ACCESS_RESULT_OF_BUILDER
(
    pair_by,
    pair_type_by
)



// Implementation
// -------------------------------------------------------------------------

BOOST_BIMAP_SYMMETRIC_ACCESS_IMPLEMENTATION_BUILDER
(
    pair_by,
    Relation,
    rel,
    return rel.get_left_pair(),
    return rel.get_right_pair()
)

// Interface
// --------------------------------------------------------------------------

BOOST_BIMAP_SYMMETRIC_ACCESS_INTERFACE_BUILDER
(
    pair_by
)

} // namespace support
} // namespace relation
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_DOXIGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_RELATION_SUPPORT_PAIR_BY_HPP

/* pair_by.hpp
J0D98JUqQDnBHObVA+S2/bBJpdWAv1oDhUs6O3kJtjU5qK0pzbZ1m76tybq2yOzUVw1X4eGue3HetNhkk62g0NBudStudy7EBYvVTYvOY+l5ZBfIJha2xkST+6muFjjvsHcQa1c3fMNTLcEscjlEcb68FztQnY2dGCE6UTsN3WFXKdtmgFRTY21aqlnZC1boc6VsmhlIvTVNlWrQNa9AM1fOIBIdZT6nVDOigqhy1XbCMw9W0vMefo6pVKWZmAq2MWY7bJUsgYnsqoU69r8BOcaDcI0BbiYI8dIFx473eMwmogHAV+9QAvl4WaI6iGmPHaai//VbGP1HVCPjXk2s8wpMtr+whTDzXdOY1pBRu6D6OlIwXiDgudVN0PpsQetTdLS+FeU10gJHwXFPR0dRb2r3Em7wj2kmA5OkysTeFkImVrnx96ZbtXAod0h3/+MrVV5816dN8uKqbdzqCHAqO+Mwdd9y/QKeYzRnc/l+JPmqCK8IX/e0WZCjM3CLVcxvEc5HH7oiXyPtjv32yk/ZYgqEFjycreH7dJBL3qcTBM2buxjSyKFFPZ69uUuUtgI3giDUYLSLamC7z29QNTepOKXsSTQSyShW/rITivwkDKJlEb73iLnbpSnQUnzfBOzTWxG+/y3VOylM/JkSdqeUoS0e3GBOEAJpWTzgLke8Lcre7nC4SYBcxhVeR6YtyvJXHb467vUWQglbVOQX
*/