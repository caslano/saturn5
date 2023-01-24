// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file tags/support/overwrite_tagged.hpp
/// \brief Hard tagging

#ifndef BOOST_BIMAP_TAGS_SUPPORT_OVERWRITE_TAGGED_HPP
#define BOOST_BIMAP_TAGS_SUPPORT_OVERWRITE_TAGGED_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/tags/tagged.hpp>

/** \struct boost::bimaps::tags::support::overwrite_tagged
\brief Hard tagging metafunction

\code
template< class Type, class Tag >
struct overwrite_tagged
{
    typedef {TaggedType} type;
};
\endcode

If the type is not tagged, this metafunction returns a tagged type with the
passed tag. If it is tagged it returns a new tagged type with the tag replaced
by the one passed as a parameter.

See also tagged, default_tagged.
                                                                                **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace tags {
namespace support {


// Change the tag

template< class Type, class NewTag >
struct overwrite_tagged
{
    typedef tagged<Type,NewTag> type;
};

template< class Type, class OldTag, class NewTag >
struct overwrite_tagged< tagged< Type, OldTag >, NewTag >
{
    typedef tagged<Type,NewTag> type;
};


} // namespace support
} // namespace tags
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_TAGS_SUPPORT_OVERWRITE_TAGGED_HPP



/* overwrite_tagged.hpp
l3dMNH9CXUzAvukT+C5rFhR2icu3i/HehU8S3vtlICIrr0OQUogEBfG6xGpNAG7G7duJfOseZVa8Gd2Z4Km0EGJBRTpumJW8x6JsLoRnMzFBieytK95gTYn+Y9H+IbwC7R/SnwqXVQXsI8TWE7NwhUh36tMTKL2bSE/Wp3fFdFvhNTju7gcXA+O0jMxGA8A62fKfAfQgeAyx+dEAtbQKySr8rn2ftj355WXILP4YIbOBqD9p53gtnHq6A5Gz5DT6FjqZ7rx4BdEdp6Q7/dHgOokqhdTabqhKBvvaj0gwLs8egNQRu9fvQ+LgIiOlaAzARP0FG71DDoFkfGMwJhuVaP8xDKhSeWEkRWWj1JMfUz1miBIm0mjXEZ+akaUMnQRme5w3bSPUMLYYNQifYlyqsYv1jhNemYga31fIdOIV0v++kqxilWSJVbIK1dBa/mRVJYNWs3Sv6NbWsox6GIxY6KrWWOViZsnn9wSWvFL22LeQDj38UEgZuZKGdqoVEmPVoYMfewn6YmbA9gSKAW2lkre8T+AAWXU/9lo5IWvoJa29INKbDLpOvzzYELviiXJcQOq0P177MI4+cP8mSpWxSJqor0v1nBowezrwtoGBPpxgQs+3o/W3ay3T9jZF989pKmEk+O2/VSuYLfAxshMCAUeiv5K3NyPHJhCtH8hBgVj0pRHqgIrxK5MMv7QailQpI4bAEGIcSkUXhSOv
*/