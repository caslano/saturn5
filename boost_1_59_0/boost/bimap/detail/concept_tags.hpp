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

/// \brief Tag of {SetType}_of_relation definition classes

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
    // Maybe a more coherent way of binding the relation can be developed.
    template< class Relation > struct bind_to { typedef void type; };

    typedef mpl::bool_<true>  left_mutable_key;
    typedef mpl::bool_<true> right_mutable_key;
};

struct right_based : ::boost::bimaps::detail::side_based_tag
{
    // I run into troubles if I do not define bind for side based tags.
    // Maybe a more coherent way of binding the relation can be developed.
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
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
*/