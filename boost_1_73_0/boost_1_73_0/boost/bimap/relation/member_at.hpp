// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/member_at.hpp
/// \brief Defines the tags for the member_at::side idiom

#ifndef BOOST_BIMAP_RELATION_MEMBER_AT_HPP
#define BOOST_BIMAP_RELATION_MEMBER_AT_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

namespace boost {
namespace bimaps {
namespace relation {

/// \brief member_at::side idiom to access relation values and types using metaprogramming. 
/**

This tags are used to specify which member you want to acces when using a metafunction over
a symmetrical type. The idea is to be able to write code like:

\code
result_of::get<member_at::left,relation>::type data = get<member_at::left>(rel);
\endcode

The relation class supports this idiom even when the elements are tagged. This is useful
because a user can decide to start tagging in any moment of the development.

See also member_with_tag, is_tag_of_member_at_left, is_tag_of_member_at_right, get
value_type_of, pair_by, pair_type_by.

\ingroup relation_group
                                                                                        **/
namespace member_at {

    /// \brief Member at left tag
    /**
    See also member_at, rigth.
                                            **/

    struct left  {};

    /// \brief Member at right tag
    /**
    See also member_at, left.
                                            **/

    struct right {};

    /// \brief Member info tag
    /**
    See also member_at, left, right.
                                            **/

    struct info  {};

}

} // namespace relation
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_RELATION_MEMBER_AT_HPP

/* member_at.hpp
BAoAAAAIAC1nSlLKErgceggAAJ0UAAApAAkAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy9wb3N0LWNhbGxiYWNrLmNVVAUAAbZIJGDVWFtTG8sRftev6MiVFCJrCc5TjmVckUHYlCkgSMRx4tTWaHdWmrCa0dmZRZBj//d83bMrBPhykvJL5LJXmu375eseD3Z/3KdDu/TdTyp/U3zwFI6Lyv1LZ+HL1Gn6ieIfcH3E83tKBnTP8int0fdZPtGOsKSNlpf8PU2/p+gj28b/DJjzY8pfcQI25jx0q7vKzBeBdg57tP/zz3+i5/TT3k97CR0pa3RJk6DtTFfzhF7mcvLnhbq97Xv9KiEdSJX9RtR0YTx5V4S1qjThe2kybb3OSXnKtc8qM8MPYyksNBWm1HR4fvHh5OxNQuuFyRYs5M7V5BeuLnNaqBtNlc60uYkyVqoK5AqwQ3hufIDAOhhn+9CtKehq6VkGq1eld6RulCnVDIpUoEUIK/9iMMjqqoT1g9xlfpC17vcXYbnx5AOMWKo7cqtAwVHtdUJMmdDS5abgJwKCw1U9K41fJPfWQJXNB64ir8uSZYHPaB/N1jRpwpMwGa1gsQn88M56VrVeuOUDQsSRpRR1ZaEIcQBR7hDmhGqb60qIxfNWRRNT
*/