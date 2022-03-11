// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/support/member_with_tag.hpp
/// \brief member_with_tag<tag,relation> metafunction

#ifndef BOOST_BIMAP_RELATION_SUPPORT_MEMBER_WITH_TAG_HPP
#define BOOST_BIMAP_RELATION_SUPPORT_MEMBER_WITH_TAG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/member_at.hpp>
#include <boost/bimap/detail/debug/static_error.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/and.hpp>

/** \struct boost::bimaps::relation::support::member_with_tag

\brief Metafunction to convert user tags to the member_at idiom.

\code

template< class Tag, class Relation >
struct member_with_tag
{
    typedef member_at::{side} type;
};

\endcode

We have to allow that all the metafunctions that works with tags
and retrieves data from a Relation will work with member_at idiom
even if the type was tagged. This will be great for the user,
because he can choose to tag a member after he is using the
relation and the code will still work.

If we perform this check in every metafunction it will be very
tedious and error prone, so instead of that all metafunctions
that works with relations first call this metafunction that
convert the tag to a member_at tag.

See also member_at, is_tag_of_member_at_left, is_tag_of_member_at_right.
\ingroup relation_group
                                                                    **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace relation {
namespace support {

template
<
    class Tag,
    class Relation,
    class Enable = void
>
struct member_with_tag
{
    BOOST_BIMAP_STATIC_ERROR( MEMBER_WITH_TAG_FAILURE, (Relation,Tag) );
};

template< class Relation >
struct member_with_tag
<
    member_at::left, Relation, void
>
{
    typedef member_at::left type;
};

template< class Relation >
struct member_with_tag
<
    member_at::right, Relation, void
>
{
    typedef member_at::right type;
};

template< class Relation >
struct member_with_tag
<
    member_at::info, Relation, void
>
{
    typedef member_at::info type;
};


template< class Tag, class Relation >
struct member_with_tag
<
    Tag, Relation,
    BOOST_DEDUCED_TYPENAME enable_if
    <
        mpl::and_
        <
            mpl::not_< is_same<Tag,member_at::left> >,
            is_same
            <
                Tag,
                BOOST_DEDUCED_TYPENAME Relation::left_tag
            >
        >

    >::type
>
{
    typedef member_at::left type;
};

template< class Tag, class Relation >
struct member_with_tag
<
    Tag,
    Relation,
    BOOST_DEDUCED_TYPENAME enable_if
    <
        mpl::and_
        <
            mpl::not_< is_same<Tag,member_at::right> >,
            is_same
            <
                Tag,
                BOOST_DEDUCED_TYPENAME Relation::right_tag
            >
        >

    >::type
>
{
    typedef member_at::right type;
};

template< class Tag, class Relation >
struct member_with_tag
<
    Tag, Relation,
    BOOST_DEDUCED_TYPENAME enable_if
    <
        mpl::and_
        <
            mpl::not_< is_same<Tag,member_at::info> >,
            is_same
            <
                Tag,
                BOOST_DEDUCED_TYPENAME Relation::info_tag
            >
        >

    >::type
>
{
    typedef member_at::info type;
};

} // namespace support
} // namespace relation
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_RELATION_SUPPORT_MEMBER_WITH_TAG_HPP



/* member_with_tag.hpp
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
*/