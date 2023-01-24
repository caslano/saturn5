// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file support/iterator_type_by.hpp
/// \brief Metafunctions to access the iterator types of a bimap

#ifndef BOOST_BIMAP_SUPPORT_ITERATOR_TYPE_BY_HPP
#define BOOST_BIMAP_SUPPORT_ITERATOR_TYPE_BY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/detail/metadata_access_builder.hpp>
#include <boost/bimap/relation/detail/static_access_builder.hpp>

/** \struct boost::bimaps::support::iterator_type_by

\brief Metafunction to obtain the iterator type of the map view by one of the sides.
These metafunctions can be used outside the bimap framework for other bimap 
signature compatible classes.
\code

template< class Tag, class Bimap >
struct iterator_type_by
{
    typedef -unspecified- type;
};

template< class Tag, class Bimap >
struct const_iterator_type_by
{
    typedef -unspecified- type;
};

template< class Tag, class Bimap >
struct reverse_iterator_type_by
{
    typedef -unspecified- type;
};

template< class Tag, class Bimap >
struct const_reverse_iterator_type_by
{
    typedef -unspecified- type;
};

template< class Tag, class Bimap >
struct local_iterator_type_by
{
    typedef -unspecified- type;
};

template< class Tag, class Bimap >
struct const_local_iterator_type_by
{
    typedef -unspecified- type;
};

\endcode

See also member_at.
\ingroup bimap_group
                                                                    **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace support {

// Implementation of iterator type by metafunction

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    iterator_type_by,
    left_iterator,
    right_iterator
)

// Implementation of const iterator type by metafunction

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    const_iterator_type_by,
    left_const_iterator,
    right_const_iterator
)


// Implementation of reverse iterator type by metafunction

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    reverse_iterator_type_by,
    left_reverse_iterator,
    right_reverse_iterator
)

// Implementation of const reverse iterator type by metafunction

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    const_reverse_iterator_type_by,
    left_const_reverse_iterator,
    right_const_reverse_iterator
)


// Implementation of local iterator type by metafunction

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    local_iterator_type_by,
    left_local_iterator,
    right_local_iterator
)

// Implementation of const local iterator type by metafunction

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    const_local_iterator_type_by,
    left_const_local_iterator,
    right_const_local_iterator
)

} // namespace support
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_SUPPORT_ITERATOR_TYPE_BY_HPP


/* iterator_type_by.hpp
HCw0wKaxhcrLy96RtX6WjseXFwwLMSBQWoNxLpjfb27laoeisUHkhvfEWti/OiE2jq0oJoy0dkS7OqvTn/Rt9hVO381RoDZ76SnBg9ZFJxyHrYTrL3lOMOONc/q6yhrqNkMdomwvKAvRe9uqlwq0VkJB25i0xbPP6UsRsyCoAHigA39onQVrp3x2F4ha5A8N9Jk0uybtJ2zg99lKiCUt1cwd7J7Uhpqq/SFd7ehRlDIro0S6XI46C45SgEcNCZK2ggdDNKgqJbXwanqUkwLzYBtSYJaYGgHU1hAMC5XZ/NIAPD0o4Ynd+BIwlYSoe9lMe9lv/2JVEDDhvddunA2ByUaXAMnxqkiWkJQZokJSz+PNQ5KkIF1CVFAOJ1BuCpImwl6d3AQUjYD6i7T6i7h+mpa1OGBO5chXytHDaL6mOfAWIvy4v8VWbQwiE1UQmdgsiFz8dxMgUjvlLFxvAe8Bvh8G0UJOHcOrDQYOCygOGQiRgKuTrgMdOsRmvwkjSR/BL3Boiq59bxLgYB7u6/CxNm/hYKj0SRJdrJ38itgekZH67TGHG2g+JC6t0fRjVuMl5GxNnUAUUHWGM4ccVAgS+MADLOabmvMyjgrq6aVErkLfo+epd1Ua1/CXpHGz36GPP7xLz2/4uYuf27RCn6iFMrjQa++y/xd4BvkOwI3os7z4lEoD03Gv8fmBdwGeDIAj8EmpRa7Yh2Y/47WY
*/