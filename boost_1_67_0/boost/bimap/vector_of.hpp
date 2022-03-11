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