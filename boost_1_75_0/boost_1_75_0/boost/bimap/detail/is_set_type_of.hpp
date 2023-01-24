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
Jjf5MrKgR4r4YglHSrhW4luV9twPEd0v4Y0fNqqZMkYi6XgGUdwCUc1amnlVj1BH2Tzz224THxdrxduO5HwRUAh8cSwWGI9BIxhD9du6iFKPaKUOEr16Kqu6CUT+uZhnG6hli9E68DbR/WLegUu1TPMzgybuB6Im9Iyz0lj1BWKLzVTivmwU5oh6vjGo9QzJ1GZqEsuI+L3Sz2dcpijxllZiaqZGEEaRsc9impozeaaaO/jUPCLYVEuCz30PgnJ+EU3N4XxqPpNJU3MZ53MZTt9MI87P7fXmJ+qHx2vKo9hg+9W7R2n6edg3xGRKvvFx70t5p8hG1nS4t4g1PUSSv03yjy2acVIqyTBMNvwLz38dN/7OFvalIy2G35lw3du60vQ2+z22yHG1VJJpGG9wU64BTHb/jcnXv7EdUqtl4vbGbcVsx2BYbDJQbGjrzdy1PVykMGoi+xlWgZmJZmf8tjtfI8ntNxTXHWdWf3AYrU9EVivL2p1ltTI8B2a1rl5EWSW5fKx3xplwz3XsYQ339M2b4d/FhFBPpORz3Fh9GUuWtGLJTiw5gFXVO29GR5TQrY4N1RHs5UkmCv0r3QKDxjhIKdxHycTr/UomGrNg6+++Srs8BvOrrwpAmBDZEhAhNIHpQzD+eVsyNS4mU+MYpzwN9EgoKVZn0fjIbAQyol1FqTGuIikWIp4ziQnU4L6JMYxlKjvZio9BzV3y
*/