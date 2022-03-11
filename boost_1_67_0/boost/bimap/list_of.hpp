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
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
*/