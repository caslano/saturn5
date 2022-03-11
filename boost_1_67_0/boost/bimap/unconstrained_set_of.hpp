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