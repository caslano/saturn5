// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/support/is_tag_of_member_at.hpp
/// \brief is_tag_of_member_at<tag,relation> metafunction

#ifndef BOOST_BIMAP_RELATION_SUPPORT_IS_TAG_OF_MEMBER_AT_HPP
#define BOOST_BIMAP_RELATION_SUPPORT_IS_TAG_OF_MEMBER_AT_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/member_at.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/bimap/relation/support/member_with_tag.hpp>

/** \struct boost::bimaps::relation::support::is_tag_of_member_at_left

\brief Metafunction to test if a user tag is refering to the left member.

\code

template< class Tag, class Relation >
struct is_tag_of_member_at_left : {true_|false_} {};

\endcode

This metafunction is somewhat redundant with member_with_tag, but it is included
because it is a lot easier to metaprogram with it. The result type is the
same that:

\code

 is_same< member_with_tag<Tag,Relation>::type , member_at::left >::type

\endcode

See also member_with_tag, member_at, is_tag_of_member_at_right.
\ingroup relation_group
                                                                             **/


/** \struct boost::bimaps::relation::support::is_tag_of_member_at_right

\brief Metafunction to test if a user tag is refering to the left member.

\code

template< class Tag, class Relation >
struct is_tag_of_member_at_right : {true_|false_} {};

\endcode

This metafunction is somewhat redundat with member_with_tag, but it is included
because it is a lot easier to metaprogram with it. The result type is the
same that:

\code

 is_same< member_with_tag<Tag,Relation>::type , member_at::right >::type

\endcode

See also member_with_tag, member_at, is_tag_of_member_at_left.
\ingroup relation_group
                                                                             **/


#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace relation {
namespace support {

// Metafunction is_tag_of_member_at_left
// Easiear metaprogramming

template
<
    class Tag,
    class Relation,
    class Enable = void
>
struct is_tag_of_member_at_left :
    ::boost::mpl::false_ {};

template< class Tag, class Relation >
struct is_tag_of_member_at_left
<
    Tag, Relation,
    BOOST_DEDUCED_TYPENAME enable_if
    <
        is_same
        <
            BOOST_DEDUCED_TYPENAME member_with_tag<Tag,Relation>::type,
            member_at::left
        >

    >::type
> :
    ::boost::mpl::true_ {};

// Metafunction is_tag_of_member_at_right
// Easiear metaprogramming

template
<
    class Tag,
    class Relation,
    class Enable = void
>
struct is_tag_of_member_at_right :
    ::boost::mpl::false_ {};

template< class Tag, class Relation >
struct is_tag_of_member_at_right
<
    Tag, Relation,
    BOOST_DEDUCED_TYPENAME enable_if
    <
        is_same
        <
            BOOST_DEDUCED_TYPENAME member_with_tag<Tag,Relation>::type,
            member_at::right
        >

    >::type
> :
    ::boost::mpl::true_ {};


// Metafunction is_tag_of_member_at_info
// Easiear metaprogramming

template
<
    class Tag,
    class Relation,
    class Enable = void
>
struct is_tag_of_member_at_info :
    ::boost::mpl::false_ {};

template< class Tag, class Relation >
struct is_tag_of_member_at_info
<
    Tag, Relation,
    BOOST_DEDUCED_TYPENAME enable_if
    <
        is_same
        <
            BOOST_DEDUCED_TYPENAME member_with_tag<Tag,Relation>::type,
            member_at::info
        >

    >::type
> :
    ::boost::mpl::true_ {};

} // namespace support
} // namespace relation
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_RELATION_SUPPORT_IS_TAG_OF_MEMBER_AT_HPP



/* is_tag_of_member_at.hpp
EqKXWR6n4mE9xLohDzsJ2ym4DczKsO44+Q3gZx0YEjN4Qph9Ad4JLlgjOpWcOC12lMc1gfh5vIW4Q0k5TOuzTGT39JwwSHzL7rYtNTYdT1VFli+BzdwRTsXT67pwygy43NGKX4qEpAKOEjeBatw/LJCStE0IN6Kd0bjOcDIkmpqKUu80ULxXbDDj0CI/a9Fa9PJwd15Q0jEsiw4X64KDelb8TAlscySdsD29FI4l/JYj8brlkZ4aCpt1mKlfbF5q8Ad/mVYJCFX2LzqHm+ouwzYvEG3WPQcrvXSuVfTug/Ywh9kdNkwWwJuyAAcs+NP+QLiJfMc+cTnsh53KXC9iV5Wtn4P4BzBe67mE8eLR+mmMwHRTko13GJF8X/gVIblXviHkl/I1PQfx8zJ+9oHnevAAqPzxZViQTwj2ffv4Cs33LfqfdftHCE7+W7f/+v3OGVvAcm0zkbk/xfrEImyBV7An8sWbyRN2eXndTeJnnCm5SGyw7OtTffnlgMZAn5PatyK7O/wTnZKvhGa3S02q8ESil+wdCpid19nReyynDIAtN1tUkjxbi67yz5wmoqtUKjd8RWemGTcHmWFkiSG9+pLqm83tq0FXYCcRo0+qIRm9hqhxij/jDlzAZZ0RZ2aHwZkYOWMVvBBQFlFGvME9kNTYOLwjD/S1xoXXNSqVxHyziezmy5XYfXgo0b0YYgWA3RW6jNVuPAyDGw+e
*/