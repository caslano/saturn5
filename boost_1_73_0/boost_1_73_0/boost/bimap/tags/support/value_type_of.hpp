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
hYUEHc2xNJZyw4MGse3dYVmlPw/6L/77y/Ae3RWG9Wm6086f092Oe0d3tB9amzLt4HtAFCYDwZeQdPDvI+kSQXn/gKHoq4Yb8W66QSJgS/G/Dz119rn9nME96erf4F9C+zqPDQeNy33OWVGVD0d9veHHtcO+zkifLsd/AFBLAwQKAAAACAAtZ0pSJt/UoBcEAACpCgAAJgAJAGN1cmwtbWFzdGVyL2RvY3MvZXhhbXBsZXMvc2VwaGVhZGVycy5jVVQFAAG2SCRgrVVhT+NGEP2eXzGXfkkiXwz3qVcoahoCRI0SlBghJCRrbY/xVrbX8q4Jabn/3pm1kzg5rgjpjMD2et68tzNvB3fw864ODODdy7e/Pl10t4jbUv2NoXk72vdfof4h1CPd3yNxYQ959fvwPuQVehbiNyzn/Oz77xE9sjb+4zLy0edHWiEYI8eq2JTyKTHQG/fh9OvXX+EzfDn5cuLApcglprAymAdYPjlwHtmVPxLx8jLUeOEAGhDpsEnlJVKDVrFZixKBnlMZYq4xAqEhQh2WMqAXmYNJEGKZIowXtw/T+bUD60SGCSfZqAp0oqo0gkQ8I5QYonyucxSiNKBiglPySGpDCSsjVT4kbgSDZaY5B9OLVCsQz0KmIiAiYSAxptC/uW5Y
*/