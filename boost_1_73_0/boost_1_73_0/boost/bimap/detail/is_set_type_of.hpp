// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file detail/is_set_type_of.hpp
/// \brief Is set type of and is set type of relation metafunctions.

#ifndef BOOST_BIMAP_DETAIL_IS_SET_TYPE_OF_HPP
#define BOOST_BIMAP_DETAIL_IS_SET_TYPE_OF_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/type_traits/is_base_of.hpp>
#include <boost/bimap/detail/concept_tags.hpp>

/** \struct boost::bimaps::detail::is_set_type_of

\brief Type trait to check if a class is a set_type_of specification

\code
template< class Type >
struct is_set_type_of : {true_|false_} {};
\endcode
                                                                        **/

/** \struct boost::bimaps::detail::is_set_type_of_relation

\brief Type trait to check if a class is a set_type_of_relation specification

\code
template< class Type >
struct is_set_type_of_relation : {true_|false_} {};
\endcode

                                                                               **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace detail {

template< class Type >
struct is_set_type_of :
    is_base_of< set_type_of_tag, Type > {};

template< class Type >
struct is_set_type_of_relation :
    is_base_of< set_type_of_relation_tag, Type > {};

} // namespace detail
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_DETAIL_IS_SET_TYPE_OF_HPP


/* is_set_type_of.hpp
VjLJTjdgS92oHEqxQTCYody0HLUwDnRBcCLPpXVE2Dipq4i0ERyatWUOlhfKahAbIZVISUg4KJ2r7bs4zhqjKPo415mNsy79qHTrfzJ5oCDWYge6duA0NBZD4J0hrHUuC57JEFqsm1RJW4aHaEiqymNtwKJSzEU4ibYNG2G5tyfkbVBTxNLxZHVlWWpb6vUXG8lHZikaU5EQ+UCbck02h9BUORq/2WfeSew99Qb/Z2kO8eagKwoGeuMl3C57kAorbQj3t6vfZncruB8vFuPp6gFmv8B4+sBkH26n11R6SWIG8Lk2aEncgFzXSmK+1/x2Iw6CeAij65vl5Ir157P5a9IVJIfcK1tZPQFNbI1BSgupb/DVmmrvvRvFHZSYvpdVppocYWRdLnVUXh0tcWu0/UHLLOp9o68AK73cKVkWpX7hR0qmTPWj9QH7VhC1SKWSjhqiq8xUU8u4kvrTd3XHb/CvRpKxHQu8iS7OojO2WaR64wtL2cjKsWTV32iZD4K/A4DJ3eIjDBlzub/LdM6EFt7725tk9uEyoGee972fEhR2l8hKuv6AYbLo8/IAmJHeVUNY0lGnc2Aqsca2d4W1W21yjoP3HGgsOjo4niD0irP5Krlb3iym499vQugxTc/LnETNx8vl/WxB7daz
*/