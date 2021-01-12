// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file tags/support/value_type_of.hpp
/// \brief Consistent way to access the value type of a tagged or untagged type.

#ifndef BOOST_BIMAP_TAGS_SUPPORT_VALUE_TYPE_OF_HPP
#define BOOST_BIMAP_TAGS_SUPPORT_VALUE_TYPE_OF_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/tags/tagged.hpp>

/** \struct boost::bimaps::tags::support::value_type_of
\brief Metafunction to work with tagged and untagged type uniformly

\code
template< class Type >
struct value_type_of
{
    typedef {UntaggedType} type;
};
\endcode

If the type is tagged this metafunction returns Type::value_type, and if it is not
tagged it return the same type. This allows to work consistenly with tagged and
untagged types.

See also tagged, tag_of.
                                                                                **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES


namespace boost {
namespace bimaps {
namespace tags {
namespace support {


// value_type_of metafunction

template< class Type >
struct value_type_of
{
    typedef Type type;
};

template< class Type, class Tag >
struct value_type_of< tagged< Type, Tag > >
{
    typedef Type type;
};


} // namespace support
} // namespace tags
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_TAGS_SUPPORT_VALUE_TYPE_OF_HPP



/* value_type_of.hpp
lsmt/eo+c76+A/5OMuWfe+Wchb4l+6110Em3nPzqUd+9R/6WI+HvuXJ+S/DouQ/1HnLtmddvPh9eqruJ2q8/MhBYeO7ZVx7+9ekbbZWbAS9oT5tN+EvXevSmGeH3vflN/a+P37VkAOJD+Teua6jZaO6mpc8evPbEHze8AR4olVYg/PwLTt3wy10eX7jMC2ed8Vhw+0WK8jW0uydo50F5Ckr9DHjnBEoayilQHoOyPPyyQAhK
*/