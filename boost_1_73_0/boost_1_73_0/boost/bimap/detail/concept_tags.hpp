// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file detail/concept_tags.hpp
/// \brief Bimap tags and concepts

#ifndef BOOST_BIMAP_DETAIL_CONCEPT_TAGS_HPP
#define BOOST_BIMAP_DETAIL_CONCEPT_TAGS_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/mpl/identity.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/bool.hpp>

namespace boost {
namespace bimaps {
namespace detail {

/// \brief Tag of {SetType}_of definition classes
/**
The {SetType}_of classes are derived from this class so it is easy to construct
metafunctions. For example now is easy to create a is_set_type_of metafunction.
                                                                                **/

struct set_type_of_tag          {};

/// \brief Tag of {SetType}_of_relation defition classes

struct set_type_of_relation_tag {};

/// \brief Tag of {Side}_based identifiers

struct side_based_tag : set_type_of_relation_tag {};

} // namespace detail


/** \struct boost::bimaps::left_based
    \brief Tag to indicate that the main view will be based on the left side.

This is convenient because the multi-index core will be more efficient.
If possible use this options or the right based one.

See also right_based.
                                                                            **/

/** \struct boost::bimaps::right_based
    \brief Tag to indicate that the main view will be based on the right side.

This is convenient because the multi-index core will be more efficient.
If possible use this options or the right based one.

See also left_based.
                                                                            **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

struct left_based : ::boost::bimaps::detail::side_based_tag
{
    // I run into troubles if I do not define bind for side based tags.
    // Maybe a more coherent way of binding the relation can be developped.
    template< class Relation > struct bind_to { typedef void type; };

    typedef mpl::bool_<true>  left_mutable_key;
    typedef mpl::bool_<true> right_mutable_key;
};

struct right_based : ::boost::bimaps::detail::side_based_tag
{
    // I run into troubles if I do not define bind for side based tags.
    // Maybe a more coherent way of binding the relation can be developped.
    template< class Relation > struct bind_to { typedef void type; };

    typedef mpl::bool_<true>  left_mutable_key;
    typedef mpl::bool_<true> right_mutable_key;
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

typedef mpl::_ _relation;

} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_DETAIL_CONCEPT_TAGS_HPP


/* concept_tags.hpp
6NYNtaroD1uueQ+QJsrPSN6ibLqoowTKHvF7GnmdZoP+nglEMuHZ+5Sstmhbt5+sxKbZO4BvG78uOZv2Y7fpGRj3mYllG8403G2YLn8aL7kY2y82rPabjSS+2RRtIgrDAfXDO5ecwfT31ntxjo2o5ImH8YMZd/BMusZoYjLquXz9KfI/ZwdYjUOvcc8Cevyxb+oUk7sKQ14ad8a6qx200GUlYG8p3bK7kBzW/sjnxsE9ovE3FmzcxrqO7Wca9cj3fe+YTC5DVETyyDtCKIwFr8neMZLHcvmKUGxil2nUsiF22yM9Su5Nrq+hodZyhg6f+n0sRvNEyhwOQOe6U1mk16bfb7Cgs+HXHOfU1Fcbtst2Zoy2tErhgeVSGt6+nf3uUtRAPONq3Fb8TUvgsG3b8wVbKyIcU3A3uXpzVMM4JaHFJh5FXWY/buUtInKtC1fOTm+0Vq7mklss1lG75mNt3JjqN1n4pJWuheKG/4XgLMhtFptvtt1Zd7SsVpfWt7yX7f7/itE8VjbD6lUnUVN0mzQdbO+1CIcdKq32r+uifG3vc8gle4HDLYUnTi3d8zclTJPY3kAzTj5RJ6m2kdOYRyqDkS5ghi+nwt4KAQthksen/7x9Wzn658VZa+vt1Ax3J7d91pO0t5muHhrV
*/