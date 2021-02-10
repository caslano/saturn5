///////////////////////////////////////////////////////////////////////////////
/// \file static_const.hpp
/// Contains definition of static_const for declaring static constants that 
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_DETAIL_STATIC_CONST_HPP_EAN_20_07_2012
#define BOOST_PROTO_DETAIL_STATIC_CONST_HPP_EAN_20_07_2012

namespace boost { namespace proto
{
    namespace detail
    {
        template<typename T>
        struct static_const
        {
            static T const value;
        };

        template<typename T>
        T const static_const<T>::value = {};
    }
}}

#endif

/* static_const.hpp
AAAAAAEAAAAAAOEFPABjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QzNDBVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSS/J53KEBAAAuAwAAHgAJAAAAAAABAAAAAABUBzwAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MzQxVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUvfwqy31AQAATQMAAB4ACQAAAAAAAQAAAAAAOgk8AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDM0MlVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKFis+YCQIAAJYDAAAeAAkAAAAAAAEAAAAAAHQLPABjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QzNDNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS4BwrJv4BAABfAwAAHgAJAAAAAAABAAAAAADCDTwAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MzQ0VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUv3pye0VAgAArAMAAB4ACQAAAAAAAQAAAAAABRA8AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDM0NVVUBQABtkgkYFBLAQIAAAoAAAAIAC1n
*/