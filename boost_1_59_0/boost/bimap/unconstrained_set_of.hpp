// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file unconstrained_set_of.hpp
/// \brief Include support for set constrains for the bimap container

#ifndef BOOST_BIMAP_UNCONSTRAINED_SET_OF_HPP
#define BOOST_BIMAP_UNCONSTRAINED_SET_OF_HPP

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

#include <boost/bimap/views/unconstrained_map_view.hpp>
#include <boost/bimap/views/unconstrained_set_view.hpp>

namespace boost {
namespace bimaps {

/// \brief Set Type Specification
/**
This struct is used to specify a set specification.
It is not a container, it is just a metaprogramming facility to
express the type of a set. Generally, this specification will
be used in other place to create a container.
The first parameter is the type of the objects in the set.

\code

using namespace support;

BOOST_STATIC_ASSERT( is_set_type_of< unconstrained_set_of<Type> >::value )

\endcode

See also unconstrained_set_of_relation.
                                                                        **/

template
<
    class KeyType
>
struct unconstrained_set_of : public ::boost::bimaps::detail::set_type_of_tag
{
    /// User type, can be tagged
    typedef KeyType user_type;

    /// Type of the object that will be stored in the container
    typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::tags::support::
        value_type_of<user_type>::type value_type;

    struct lazy_concept_checked
    {
        BOOST_CLASS_REQUIRE ( value_type,
                              boost, AssignableConcept );

        typedef unconstrained_set_of type;
    };

    BOOST_BIMAP_GENERATE_INDEX_BINDER_FAKE

    BOOST_BIMAP_GENERATE_MAP_VIEW_BINDER(

        // binds to
        views::unconstrained_map_view
    )

    BOOST_BIMAP_GENERATE_SET_VIEW_BINDER(

        // binds to
        views::unconstrained_set_view
    )

    typedef mpl::bool_<true> mutable_key;
};

/// \brief Set Of Relation Specification
/**
This struct is similar to unconstrained_set_of but it is bind
logically to a relation. It is used in the bimap instantiation to
specify the desired type of the main view.

See also unconstrained_set_of, is_set_type_of_relation.
                                                                **/

struct unconstrained_set_of_relation : public ::boost::bimaps::detail::set_type_of_relation_tag
{

    BOOST_BIMAP_GENERATE_RELATION_BINDER_0CP(

        // binds to
        unconstrained_set_of
    )

    typedef mpl::bool_<true>  left_mutable_key;
    typedef mpl::bool_<true> right_mutable_key;
};

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace detail {

template<class T>
struct is_unconstrained_set_of :
    ::boost::mpl::false_ {};

template<class T>
struct is_unconstrained_set_of< unconstrained_set_of<T> > :
    ::boost::mpl::true_ {};

} // namespace detail

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

} // namespace bimaps
} // namespace boost


/** \struct boost::bimaps::detail::is_unconstrained_set_of
\brief Trait to check if a type is unconstrained_set_of.
\code
template< class T >
struct is_unconstrained_set_of;
\endcode
                                                                            **/


#endif // BOOST_BIMAP_UNCONSTRAINED_SET_OF_HPP


/* unconstrained_set_of.hpp
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
*/