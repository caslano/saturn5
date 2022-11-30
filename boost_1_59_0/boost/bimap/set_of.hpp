// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file set_of.hpp
/// \brief Include support for set constrains for the bimap container

#ifndef BOOST_BIMAP_SET_OF_HPP
#define BOOST_BIMAP_SET_OF_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/detail/user_interface_config.hpp>

#include <functional>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/na.hpp>

#include <boost/concept_check.hpp>

#include <boost/bimap/detail/concept_tags.hpp>

#include <boost/bimap/detail/generate_index_binder.hpp>
#include <boost/bimap/detail/generate_view_binder.hpp>
#include <boost/bimap/detail/generate_relation_binder.hpp>

#include <boost/bimap/tags/support/value_type_of.hpp>

#include <boost/multi_index/ordered_index.hpp>

#include <boost/bimap/views/map_view.hpp>
#include <boost/bimap/views/set_view.hpp>

namespace boost {
namespace bimaps {

/// \brief Set Type Specification
/**
This struct is used to specify a set specification.
It is not a container, it is just a metaprogramming facility to
express the type of a set. Generally, this specification will
be used in other place to create a container.
It has the same syntax that an std::set instantiation, except
that the allocator cannot be specified. The rationale behind
this difference is that the allocator is not part of the set
type specification, rather it is a container configuration
parameter.
The first parameter is the type of the objects in the set, and
the second one is a Functor that compares them.
Bimap binding metafunctions can be used with this class in
the following way:

\code
using namespace support;

BOOST_STATIC_ASSERT( is_set_type_of< set_of<Type> >::value )

BOOST_STATIC_ASSERT
(
     is_same
     <
        set_of<Type,KeyCompare>::index_bind
        <
            KeyExtractor,
            Tag

        >::type,

        ordered_unique< tag<Tag>, KeyExtractor, KeyCompare >

    >::value
)

typedef bimap
<
    set_of<Type>, RightKeyType

> bimap_with_left_type_as_set;

BOOST_STATIC_ASSERT
(
    is_same
    <
        set_of<Type>::map_view_bind
        <
            member_at::left,
            bimap_with_left_type_as_set

        >::type,

        map_view< member_at::left, bimap_with_left_type_as_set >

    >::value
)

\endcode

See also set_of_relation.
                                                                        **/

template
<
    class KeyType,
    class KeyCompare = std::less< BOOST_DEDUCED_TYPENAME 
        ::boost::bimaps::tags::support::value_type_of<KeyType>::type >
>
struct set_of : public ::boost::bimaps::detail::set_type_of_tag
{
    /// User type, can be tagged
    typedef KeyType user_type;

    /// Type of the object that will be stored in the set
    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::tags::support::
        value_type_of<user_type>::type value_type;

    /// Functor that compare two keys
    typedef KeyCompare key_compare;

    struct lazy_concept_checked
    {
        BOOST_CLASS_REQUIRE ( value_type,
                              boost, AssignableConcept );

        BOOST_CLASS_REQUIRE4( key_compare, bool, value_type, value_type,
                              boost, BinaryFunctionConcept );

        typedef set_of type;
    };

    BOOST_BIMAP_GENERATE_INDEX_BINDER_1CP(

        // binds to
        multi_index::ordered_unique,

        // with
        key_compare
    )

    BOOST_BIMAP_GENERATE_MAP_VIEW_BINDER(

        // binds to
        views::map_view
    )

    BOOST_BIMAP_GENERATE_SET_VIEW_BINDER(

        // binds to
        views::set_view
    )

    typedef mpl::bool_<false> mutable_key;
};


/// \brief Set Of Relation Specification
/**
This struct is similar to set_of but it is bind logically to a
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

See also set_of, is_set_type_of_relation.
                                                                **/

template< class KeyCompare = std::less< _relation > >
struct set_of_relation : public ::boost::bimaps::detail::set_type_of_relation_tag
{
    /// Functor that compare two keys
    typedef KeyCompare key_compare;

    BOOST_BIMAP_GENERATE_RELATION_BINDER_1CP(

        // binds to
        set_of,

        // with
        key_compare
    )

    typedef mpl::bool_<false>  left_mutable_key;
    typedef mpl::bool_<false> right_mutable_key;
};

} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_SET_OF_HPP


/* set_of.hpp
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
*/