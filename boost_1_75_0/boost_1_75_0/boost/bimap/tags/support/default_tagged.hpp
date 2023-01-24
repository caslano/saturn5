// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file tags/support/default_tagged.hpp
/// \brief Weak tagging

#ifndef BOOST_BIMAP_TAGS_SUPPORT_DEFAULT_TAGGED_HPP
#define BOOST_BIMAP_TAGS_SUPPORT_DEFAULT_TAGGED_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/tags/tagged.hpp>

/** \struct boost::bimaps::tags::support::default_tagged
\brief Weak tagging metafunction

\code
template< class Type, class Tag >
struct default_tagged
{
    typedef {TaggedType} type;
};
\endcode

If the type is not tagged, this metafunction returns a tagged type with the
default tag. If it is tagged, the returns the type unchanged.

See also tagged, overwrite_tagged.
                                                                                **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace tags {
namespace support {


// Default Tagging
// A metafunction that create a tagged type with a default tag value.

template< class Type, class DefaultTag >
struct default_tagged
{
    typedef tagged<Type,DefaultTag> type;
};

template< class Type, class OldTag, class NewTag >
struct default_tagged< tagged< Type, OldTag >, NewTag >
{
    typedef tagged<Type,OldTag> type;
};

} // namespace support
} // namespace tags
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_TAGS_SUPPORT_DEFAULT_TAGGED_HPP




/* default_tagged.hpp
frxPWRgNW30HztBCUll8rmQlI3rwq8dcbyJWiMS+YmW1S0xqOb89uxBd8iqJySbS510bjYu+WDUUByjPwdr9qvVDIcmc3/AVj9BotI2h6xp++JZQjmyOWIkcPT1nPiS5IOCxUxeg7Y3JgAlTZ5+oC0kA91jVv2hrKBrl3dWl6dNIly+3qNF2EJXc86tWSZD2VL3YfmKn1eQoOF67ugNhyYk4YzMjjVgSrS4GiCGi1zHvJjzc8HOMGYHw/GV4LCAQDhaAEd0tJjoVrlWthW9QfqlYZfBMZit41sIhyO7uxIj1tk4aYl13DsRavU4g1n2PE2Lt1ulfIdbfOyJi7b6CEWvajLOEWB22ddsIsR7dKxBrIrrEGVoJiFXIE9lxFI0jXTmylRDrgx1REheIFYMjwKe3bxDETsWryZR/TRri1dMzCa96H2C8mqwM3HZuvBrNegInILowQnScNrWSEF20Uv+pildH07dr0prFq6OVLZ82i1ejqHgPbC6CmuO0cG4uSpnxqYZXTcqX84LxqknDq0/am8ert9rPjVcf/gxRCdtxtf70X+LVfdefH6/On6Hh1QPzVLzq8gHzhIj1aBYh1ivOiVj/+lGPWHOfRCTZoJTPNSLJGHLbrN5cXbAdR9YgyqRRmXplTlCZw+VUpp7LZFKZeg2xTt2uIVZLh0aI9Y1yA2KN2d40Yj14q0Sst4sZTdcj1nQ9Yi1qjwiS
*/