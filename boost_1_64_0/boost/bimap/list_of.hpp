// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file list_of.hpp
/// \brief Include support for list constrains for the bimap container

#ifndef BOOST_BIMAP_LIST_OF_HPP
#define BOOST_BIMAP_LIST_OF_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/detail/user_interface_config.hpp>

#include <boost/mpl/bool.hpp>

#include <boost/concept_check.hpp>

#include <boost/bimap/detail/concept_tags.hpp>

#include <boost/bimap/tags/support/value_type_of.hpp>

#include <boost/bimap/detail/generate_index_binder.hpp>
#include <boost/bimap/detail/generate_view_binder.hpp>
#include <boost/bimap/detail/generate_relation_binder.hpp>

#include <boost/multi_index/sequenced_index.hpp>

#include <boost/bimap/views/list_map_view.hpp>
#include <boost/bimap/views/list_set_view.hpp>

namespace boost {
namespace bimaps {


/// \brief Set Type Specification
/**
This struct is used to specify a set specification.
It is not a container, it is just a metaprogramming facility to
express the type of a set. Generally, this specification will
be used in other place to create a container.
It has the same syntax that an std::list instantiation, except
that the allocator cannot be specified. The rationale behind
this difference is that the allocator is not part of the set
type specification, rather it is a container configuration
parameter.

\code
using namespace support;

BOOST_STATIC_ASSERT( is_set_type_of< list_of<Type> >::value )

BOOST_STATIC_ASSERT
(
     is_same
     <
        list_of<Type>::index_bind
        <
            KeyExtractor,
            Tag

        >::type,

        sequenced< tag<Tag>, KeyExtractor >

    >::value
)

typedef bimap
<
    list_of<Type>, RightKeyType

> bimap_with_left_type_as_list;

BOOST_STATIC_ASSERT
(
    is_same
    <
        list_of<Type>::map_view_bind
        <
            member_at::left,
            bimap_with_left_type_as_list

        >::type,
        list_map_view< member_at::left, bimap_with_left_type_as_list >

    >::value
)

\endcode

See also list_of_relation.
                                                                        **/

template< class Type >
struct list_of : public ::boost::bimaps::detail::set_type_of_tag
{
    /// User type, can be tagged
    typedef Type user_type;

    /// Type of the object that will be stored in the list
    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::tags::support::
        value_type_of<user_type>::type value_type;


    struct lazy_concept_checked
    {
        BOOST_CLASS_REQUIRE ( value_type,
                              boost, AssignableConcept );

        typedef list_of type;
    };

    BOOST_BIMAP_GENERATE_INDEX_BINDER_0CP_NO_EXTRACTOR(

        // binds to
        multi_index::sequenced
    )

    BOOST_BIMAP_GENERATE_MAP_VIEW_BINDER(

        // binds to
        views::list_map_view
    )

    BOOST_BIMAP_GENERATE_SET_VIEW_BINDER(

        // binds to
        views::list_set_view
    )

    typedef mpl::bool_<true> mutable_key;
};


/// \brief List Of Relation Specification
/**
This struct is similar to list_of but it is bind logically to a
relation. It is used in the bimap instantiation to specify the
desired type of the main view. This struct implements internally
a metafunction named bind_to that manages the quite complicated
task of finding the right type of the set for the relation.

\code
template<class Relation>
struct bind_to
{
    typedef -unspecified- type;
};
\endcode

See also list_of, is_set_type_of_relation.
                                                                **/

struct list_of_relation : public ::boost::bimaps::detail::set_type_of_relation_tag
{
    BOOST_BIMAP_GENERATE_RELATION_BINDER_0CP(

        // binds to
        list_of
    )

    typedef mpl::bool_<true>  left_mutable_key;
    typedef mpl::bool_<true> right_mutable_key;
};


} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_LIST_OF_HPP


/* list_of.hpp
hTmtc0uE+VznlgLzk86tF4wjUeuWBtNc55YB01XnNgjmGnILI7cQ1hOXRW4NhVsmzH56bgPhNgbmZXLzFW5ZMGd0bpNhzuvcpsEoiVq3PJhgnVshTBudWxFMos6tFKa/5FaouOaJT9FzH1C/nUh1dFsLC6TySW4Qf/9uC8nZaX/rPOxryQ7NIPr6dn4Tjes8CpTaQ2mRqzmIOF6lON6xDEEfda7bv/XCHM7ZR61lDpu3w+pw2Lzq9bcX/g512NE1qD+r8WWgrd/tjK9hnsMe6Gjg47D5Oxp41+tvvxCHrTHHp+5zb0Rc98DcC7OJz90x1hj8QcFRWfYIQv9EX1eo709TxLjh0f8wbqBOjMcNnAtS/0E5wk/0K/F9ARu59yX7edhRf7DnU5yoAw6nrZ8wlmU/qht1rOnIe9zTeCrwMOdxJ9gM8oHdaazJLS6ZS+0lnPa3K3g8V/1t4pvNIWTf4fotMMlW8rihyj5Mfkir+BZolvCD3gPUZwoqN9oXY2Mk8lsT5d/e2+qoXmyTvkVYZYnn3+omJznD3QQ/uyUcph1MIkw6TCbMVJgimAUwzvpV41+qxl+9rs74H6J0Lb/i+B0NXPH7+/h3cEZfY3P1t0rOt/r77CYUv7fm2V352V3Ib8Fln63qzYgi+QBKh7O9WszebdyefMFwahMVZHcGaEr2SrKHw456gn265jwkhvWPNOQIA2BaIlxssuu+yJzKnCILjy+lUn7RTVnGW/LLJT+b6gcblxP+zBd3yHo4/ZDXOvI1RM5XKaeb88X2XE2b38L5COMIGsOcaorx3ZWPGfnZsa56ofdoIbd51T+s3mlBeDy7UPPsKL5zE8kBmvGzS8Wz44yezf6Rv+nZav1d5GdP5wA5MI2cc1HxbLoAYPR8lplOflObk+4W7t9GfgU8RxN+V5xutf4QH+wzuF2q9gJNvjoH8DmdqjsbpjnyFZWi5ouGMSlfMzhfqoy3GMfakX2lR16GCtm1Hv25UPg5DPtzKvlV1as/z0RcHUg+8ArLbIauzApEmVUa9OVPucyacT8OhGmMMjsryoy+iGbUFlimmWFbYD++r1Z32mN19Z2iqW+cn1BcGLORSDntX/AAdJIjfBOmFdIemCrSXj4vp9SoviGjre8wsp8QsqK+hexJo/pmP3+5vsWYFU5+L//m+oPdrP7E3YVL/N3oV6yYo4AHwTbONt+Dy4AWBtPnQ32Jvg5pvpfRC3KwcblwuE7irtko8l8nfw+Y1wblXD5qmPN0JyGEUlOYrN7LG6lAtif88YWJKGUrzQdpzCW300qwCJObU1Y2v7t89+A2ksmxSPHGyt/rnET+q+Xnau42l5H/XP0zkuX16SaSuVV+Rhz5c3kMovwHi3aymvL6uIJ80J2E+8ieadU9I1aO4w16Rr5FJ5Mkn7e3oueUy+lIIH8u4znkf4P7XiM9tyWloxRyZ8geaJXCi3Pj0ZB/jtLQUV8W/Ay+l05xfK9PpxoPnovnUDyb9DKp8v3lA5TWQJH/thSms5y3FPlMuy3JH5X9NfG16KmNbyLJV4s6eYvsjWFPp37UkeSf0+eVnqmGuZbCTJafmSTfR/iB4vhSn09qG2rf2EHlFSC3v+5yWT1Kz+ghvlN7juTt+rbCbZbHGgqTRfPg8w1hh+DvI7HGsjns1Scxk7T7S7qtoKMIN4zlsvqRnuHvmgNyHFlqHAhdc4MzpsnOv3zqiseL0hGkiafWHY9XN0rQGuffjrri+dogPZ9K8dSUOaNIcP7VqK54TvV0p6cjx5MZiv1zxOOwd3KGH+Pfx9vusNu9fRCXt7fDJ8ThFVJXnIcpbSHi/vCjZP8Mq5mWmvRuCJXK7xrno5o7//I=
*/