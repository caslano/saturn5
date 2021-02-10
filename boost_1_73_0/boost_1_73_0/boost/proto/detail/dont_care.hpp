///////////////////////////////////////////////////////////////////////////////
/// \file dont_care.hpp
/// Definintion of dont_care, a dummy parameter
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_DETAIL_DONT_CARE_HPP_EAN_11_07_2007
#define BOOST_PROTO_DETAIL_DONT_CARE_HPP_EAN_11_07_2007

#include <boost/config.hpp>

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4714) // function 'xxx' marked as __forceinline not inlined
#endif

namespace boost { namespace proto
{
    namespace detail
    {
        struct dont_care
        {
            BOOST_FORCEINLINE dont_care(...);
        };
    }
}}

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif

/* dont_care.hpp
NDVVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS0tszhsQCAABcBwAAHgAJAAAAAAABAAAAAACW5joAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MjQ2VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUs7nfop8AQAAUwIAAB4ACQAAAAAAAQAAAAAAn+k6AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDI0N1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJUwn8alAEAAKECAAAeAAkAAAAAAAEAAAAAAGDrOgBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyNDhVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS25qpnu8BAAAyAwAAHgAJAAAAAAABAAAAAAA57ToAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MjQ5VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUk/UPWzVAQAAWQgAAB0ACQAAAAAAAQAAAAAAbe86AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDI1VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUvXh7tovAgAAogQAAB4ACQAAAAAAAQAAAAAAhvE6AGN1cmwtbWFzdGVy
*/