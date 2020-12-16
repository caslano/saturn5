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
Cd+Aj8Ifw13wJ6rrfws+C38G6+Hb8FX4C3gY/krzb4/R9zA4QdOXZaTcyDZW6+cFsDOcqPm/BObDSZquKfAOOA0+AGfAx+HFmo458EV4CfwRnAvfhPO0fJeozn4BTHL7YrVcL4J58ArYBxbB8+ASW+/1mQkrY9T7IdqeDIWD4NlaX4fDi+FIOEdtDfYmmrg+P67Pj+vz/8P0+Xu3tTSHkKNI1j0tzQikDPk0sgPZjxy5J67vj2/xLb7967Z/if0/XcgnS/e/0Wf/P0u/Y7qoniUL+U4PY+ofkn6S8JRAIeW/0TmyIucFUr9dQn1T+s30ec6R3qJ1enKaCfUDHXfdbf/8UfMj9CKztHP/l8Sbq7r0P+DvSEQaZUamCjWd983LRMbV0GekfXGZD8s65vRJpppCrl6vQePqYfvonnpE+oJF112q8R3sETUvmobrJu45uNtK/PU+HS93tsRNgyTP9klXOqRJ/D7n+OYDs/2RQzWdmRG67AXLVyyrtevt9xQ/jzotTKKkb7baMvj7ES8TP5c4mdqPWCTuNU5r9mV7561xk6gp1DXV+SYVvx+aZPIl3+zT/eE4ap2O5mxngYPtPfe9mHPlJercY6ln+ufjkvs/T/yEdNG34CdxZdq4lDaJyWn90vqkLU5JTcxKO939ldY3rSIlKbFrSkpidtrCtDPYd3naBPZkpqQifRPTUxIS26dNwtUxbXJav5SE9NRWnGc052sDZxD3JmQeshm51ZUc+S39FFuQLyC3I3eo3JkbZQti+6K/LNea4PzaZNl+32ekbORKmOkSpnL5YkMY1XfcLmG6OMlOFnnGPpvvy53JJlny7Hh5XyH+050ccn8MkhmV91mO6nzY0AepLqQKhvx80smU45q+EtEpqH2G5yc7rNNTfbF603oA5Vpbyz0M3+fUZJ0zrnVp1Jxxx9N7qP5d5zCTuml1FAdln2S/1P8BWv9z1JbmRuQ05eX4LXrU1n9rmzQ7xriVK8RflbZXGs5nm/S6uNnDtSSbE7NLmh2+rga63Tf1GtI1UBrSsid/HrPXQF/0ILczmscCy5nUmKhxOJp+DZPu09kRyrZJ9niTdZR2rIruy7A6J+JtoG+l2MS8jowG1+GWOMpz4DVkaBoz7TVoCL+9wglcR3bEdWjcDe5JbWrsa8lrcC2uemF+7YrqhSb4evKi7gmh/HrjE7iWyHtCvOE5/vQ60lva9xDZEpFWrr444jrkljD7bPWakto1VY1ci4ZLaiytk4PS6k/Xbk1XXw3UB/kKfgsi02Wzt0RUD4Hp0nBt1U2pF3fiR06nZ0MQnX9pboe0P512mtDg9NUdP98C77G/XB6KYdOQTno2+tKj9gw1tfOXVjWSZ4Rpnr1CwzSNDdeVtOg8+i1+t0WmSV/B3OWYamq5qTWNpW3bCeZX+P4lpds0yZaAtHZtLSPTputEBadn5/HLU5PSs1/TMyVcCLXc13vp4aG/gFfyyoW1CwPTo/6nyPtVKnFuQqrc527vzmLbV4p7I7KKfYmd03rxLtQmxYSew6581OsYEH7vbm1km4u0Vh3qCvzm7bTXoXa0ke+emfruUCD+RqHbadHAlvb4c2/768OmNt56ZDk6l+NVbtnz0lET69k5OzpPNUx3q3d9QdyDrd2IYyL18M/L8TxxT7Hhu+rYVPXv2ZHIO+Oz4idf3EU2TCd9V/ro7xOqp1VbDs7rzVGuNkWalgbl8YjaeNyq+XcjsoZ4M3Z5+dfwmT07xnjtoeK/0vT3bMo0jl5qCxzwHBc/3e079VniLjHDTIraW3nhNPnWtmyA+F1lzuOv5qfG19WWqblNtLlRWwJfnqotgc1TTbvqv4tsvvrTFlk2B8k=
*/