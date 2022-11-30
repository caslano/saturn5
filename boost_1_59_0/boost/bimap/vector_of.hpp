// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file vector_of.hpp
/// \brief Include support for vector constrains for the bimap container

#ifndef BOOST_BIMAP_VECTOR_OF_HPP
#define BOOST_BIMAP_VECTOR_OF_HPP

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

#include <boost/multi_index/random_access_index.hpp>

#include <boost/bimap/views/vector_map_view.hpp>
#include <boost/bimap/views/vector_set_view.hpp>

namespace boost {
namespace bimaps {


/// \brief Set Type Specification
/**
This struct is used to specify a set specification.
It is not a container, it is just a metaprogramming facility to
express the type of a set. Generally, this specification will
be used in other place to create a container.
It has the same syntax that an std::vector instantiation, except
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

BOOST_STATIC_ASSERT( is_set_type_of< vector_of<Type> >::value )

BOOST_STATIC_ASSERT
(
     is_same
     <
        vector_of<Type>::index_bind
        <
            KeyExtractor,
            Tag

        >::type,

        random_access< tag<Tag>, KeyExtractor >

    >::value
)

typedef bimap
<
    vector_of<Type>, RightKeyType

> bimap_with_left_type_as_vector;

BOOST_STATIC_ASSERT
(
    is_same
    <
        vector_of<Type>::map_view_bind
        <
            member_at::left,
            bimap_with_left_type_as_vector

        >::type,

        vector_map_view< member_at::left, bimap_with_left_type_as_vector >

    >::value
)

\endcode

See also vector_of_relation.
                                                                        **/

template< class Type >
struct vector_of : public ::boost::bimaps::detail::set_type_of_tag
{
    /// User type, can be tagged
    typedef Type user_type;

    /// Type of the object that will be stored in the vector
    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::tags::support::
        value_type_of<user_type>::type value_type;


    struct lazy_concept_checked
    {
        BOOST_CLASS_REQUIRE ( value_type,
                              boost, AssignableConcept );

        typedef vector_of type;
    };

    BOOST_BIMAP_GENERATE_INDEX_BINDER_0CP_NO_EXTRACTOR(

        // binds to
        multi_index::random_access
    )

    BOOST_BIMAP_GENERATE_MAP_VIEW_BINDER(

        // binds to
        views::vector_map_view
    )

    BOOST_BIMAP_GENERATE_SET_VIEW_BINDER(

        // binds to
        views::vector_set_view
    )

    typedef mpl::bool_<true> mutable_key;
};


/// \brief Set Of Relation Specification
/**
This struct is similar to vector_of but it is bind logically to a
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

See also vector_of, is_set_type_of_relation.
                                                                **/

struct vector_of_relation : public ::boost::bimaps::detail::set_type_of_relation_tag
{
    BOOST_BIMAP_GENERATE_RELATION_BINDER_0CP(

        // binds to
        vector_of
    )

    typedef mpl::bool_<true>  left_mutable_key;
    typedef mpl::bool_<true> right_mutable_key;
};


} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_VECTOR_OF_HPP


/* vector_of.hpp
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
*/