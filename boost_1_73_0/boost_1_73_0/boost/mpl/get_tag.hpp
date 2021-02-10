
#ifndef BOOST_MPL_GET_TAG_HPP_INCLUDED
#define BOOST_MPL_GET_TAG_HPP_INCLUDED

// Copyright Sergey Krivonos 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$


#define BOOST_MPL_GET_TAG_DEF(TAG) \
    namespace boost { namespace mpl { \
        template<typename T> \
        struct get_##TAG { \
            typedef typename T::TAG type; \
        }; \
    }}

#endif

/* get_tag.hpp
AAgALWdKUn3oM7aSAQAAZwMAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNTY3VVQFAAG2SCRgxVNRa9swEH4/yH84KKVQ8GR7rAUjDCFsS5iZQ+uyx6HJcizqSEG6LPTfT4rduNC97WFPuuO+++6++xAn5UkKr0rg2nQ2PM/q5WRd60tYN80Wnh4qXG43sApBvW1+xvfpkn2pq6r+UdWrZbOpvwNnczdnIyFc4aNyv5VLvG4VcKcOw0sot4LEOINlHzL8mOZYf4OVNaQMJZUyO+oLvIPKSkHamgJZ9unuPk3THCDprE3CiJHkzJW/IcvT9G9kWQbgVKudkqTaqT2f+mWv5HP5tv4OOkE4mzQEaatBxwmjNHlOAsCfBZfQEx0C/DW9QrJ2QO3x1AsKCR69Qm08KdGi7fBGHt1wAzzCShj0r6g4EIw5IDdir+KOiTsanPdDcsL4Tjk8aertkdArIm12eLYLo4liJ7QJFGzkQC7tfi9MO25ZMHa9rh+bzba4jmfc1g8Nm6ZfgCGcFAIPgnQXfTw4S1bG/b5+bkaP8NWIBaytpwLfUS9gKaU6hNItu13AYu6N/v5L/3+Yzdl8A84uh2Hz3/oDUEsDBAoAAAAIAC1nSlJRDTixlgIAALMGAAAf
*/