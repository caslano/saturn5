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
R6w2zSKV26vLzAZ+va3CbytYZkarO4k7yhqe6rdd8z5uOjR9wtGepHfKdspsFZGnxDrlH+7bpDwLd7Cs0aZjr1ogjlfYpjS5nctn2uiLouh+lrR+bT0x8sCIfvYIT7Q80NLPbvFY5IFR/exR7vZ2/want9Ri956NmrwX7Sc3JZVu2s7qyxP1pWbqjbp8H8XVgZF73imLCbUUVyRzxBVg3Gn5rItQ+B0GvvtiIpxoy1/koOVqQTE82PeJaXM/LowAdyPvd8DbRHus+Vm4/Q6T5K0YmXh+TqRBf+nVWbQY36DB3p89DXA8xy+nvcLWf7YffK/USHGsc9LlNumwqWNoAt19KjnAyuCa4/s+YtvyLWC8UAMVsgHLkAtyGTTeo0bQ8vJohMBp9tM9G2t+Jc+ZCv+SS0Q0PyasFtTw3/EYexwM4pNKwU9rpd/2zaegxLw1W/ItgFzKlwxQp2+xBW0xwXZX+XASmIzug58Zk00GruvNUJ6fxP0TVf0Bm2pdTDF92z5qG9gWXt/2pddQaLFMBcnGb7s9CIIUhGA+QQAOUK+EhiA/NtsVm0Vfa36IOJZZQ+8jBDjVj6DuY/p75C4pvcZvm8h+w+EEd5Q06UNNwfwWkAh3lITz5rurQM3EMnPXTb6obtCIshE2UVDxpg9IFZ2RVMsYWpzEQ2qhRuhuE9AXvkSZEm9CDddekv2v41rFbl3xzVh7wi4eL5jl
*/