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
lZ5WhlNTd3mpcWdC91V1HkTItILd3iIUlMLiPK9csE0ymrWzN9YLz7r62pyI3ovyHqILTnxvB4zS7hxqO5gWvLJRRw9wthGivMQL4NQYOdKhxVgFaDWdvlhzeWDRa1+YCCaHYXeupcG/OPOsTIhYxco/npTmsGjXWRrf4ADM46WU6LLRtY4EJoz3/2qVQ47RA84iKu4d8lvDHKuvKWIElSVgPIEOd5Kl3DyBASYLL0XfPQLFIeSt0XHt2Zs4dSsN+oA91s08GYSrJwe8B7lzA9y2RIVAFHp9rp7haqpMU8qzPFJcwEUC1hAvH4cHv3X7VP9AjS/R59mksUDlJb10Q+Xg0Hk8oKcjHIXFWyR1U4vjdiz2Pw6aJ+PxwzRDNiOHG5UT6OL3KdycfH0Pd2CF9Y2h5kaOcEZ77tfG6JAsQKixVwefLQmn2umKaKVseaZZClyvLXIBkfpTK1gRo1AFLHo2eLV0tPhDBshNfyBENvIj+kCFt8zcNn/wQTfl1q58BzFkYWqaGkltvj5caEnN7RzNpptV4xN9lJCCExtaL734sCXfy2NsQesvOA==
*/