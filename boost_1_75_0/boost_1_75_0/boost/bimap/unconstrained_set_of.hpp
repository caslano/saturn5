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
+NQtPrUeo/TA05XsSdVgQn3WAJBGHx8fwvYW0jega9R545DY0QPqXIhxRvVwpeGaFgwQajOvxEDZ2nZFV4jLBdaNMBrNzxpNz1pbdjSZqzZZm6mTtxw282eFFlXu2fmDuS+aMbLJg2lkmnkPyPbrzO0bEVsm6xFb0JdCui6W86uWyF7olSaQm3cpnpswJKJZo4909/7DhNt+O0rXn/C6VdvL95OO0HUb39fzdQyXL+f7d48aeM9QGb9Xb/aLsGQFN/wgqgaZ/SAwK3hWXvbULEf1rwoHRvhN4YhS+xk/pWOQJBAV/PODFkzDlk62MTKY1KCrA4cEuPYU4Dz3DzvLtr+zUVbIdE/FRghL61U3C0rux+fOB+ACsod3bJh0XPwcvsSmVNUFLnQFr6SqBVyny7s2czTD93NZKhQ51yh8KReiJkZ6tNJQuElijTqKJe+1FZFq56FE1k9s0X99fCiR46yk32gKEDJio6GlEMynVz0C8ZWs1gP9cu0Kuy6Q1/xBV/nULMVRPdTGNOMa8aOyH7tYQ1YtEAiIP0WikcRj19tZu01pQNO1rUAQOYNvtpbVvyVqCOYFTn31CpzQ0w/IeV9gqa/E1p9A9S/aJ+s/aKm//dKY+ldfYceDIMh7BR+RLbi21E0KnniS6uOlTR75/1+BZqiJ5XIMugKgp0e92S5WhFBxGlg7iSPhz5EEaSNjWbONuiqg5d3WwUxk
*/