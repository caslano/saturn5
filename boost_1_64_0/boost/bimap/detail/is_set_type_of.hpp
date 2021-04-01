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
08T1pRJQ3THdL/g6+/rYAr/u1cYLuJHD0i1SEA24QoqJpX941Ok/MgdSJ5PHlNAspzWjC/D5W6hY1a0aJfY9WGZVcDfmq78rit4+qLbYg4lOzUQ8liCmfupt92M+Lvv+8SuUojWWGpp1YZ297RcjUjROhz7iEA2NMPkpl7i3coxl31Twqbe5ygZpx4ejMQLWlM6UKPLzSZy9DgLfPkCiVeF/qIU7qXZLdoMgMt5Rz99WpZd/1vReM0QywlSVHj5CH3rwiVWGaQS/Mm6MDp4+jR6crVS8B72lqwZCu15PaThi8NzRsYDbd/j4eqwvQKXBcLxGJXoqXED9RS11Q7rXIWeZNa3Ah4k8YzYWw+PHDYnHQBi8jQpYzqAA7Bx3VAw1kPWsb8oHgnebKCDOgWYqcC+znqirbVTZM3P2c8V03kGUTyrL6PCGvGuomZwPrNMOJbIUFTqdm6Y8F+mFAm83ycItrxTJqXq5AGbBQmLb5+GN+yknjn3kPyh/AJDOfoRICtS/UFs1gCtAfzMoQEZX7pb0/bDxRgjSHbWvyaMJMs/jZgHjxZV4J8TlkQ==
*/