///////////////////////////////////////////////////////////////////////////////
/// \file as_lvalue.hpp
/// Contains definition the as_lvalue() functions.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_TRANSFORM_AS_LVALUE_HPP_EAN_12_27_2007
#define BOOST_PROTO_TRANSFORM_AS_LVALUE_HPP_EAN_12_27_2007

#include <boost/proto/proto_fwd.hpp>

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4714) // function 'xxx' marked as __forceinline not inlined
#endif

namespace boost { namespace proto
{
    namespace detail
    {
        template<typename T>
        BOOST_FORCEINLINE
        T &as_lvalue(T &t)
        {
            return t;
        }

        template<typename T>
        BOOST_FORCEINLINE
        T const &as_lvalue(T const &t)
        {
            return t;
        }
    }
}}

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif

/* as_lvalue.hpp
bC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MjA3NlVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJ1OraJQwEAABECAAAfAAkAAAAAAAEAAAAAAFRNOgBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyMDc3VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUg78WKC4AQAA6wIAAB8ACQAAAAAAAQAAAAAA3U46AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDIwNzhVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSxpCcRDMCAAAJBAAAHgAJAAAAAAABAAAAAADbUDoAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MjA4VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUq7infxxAQAAs1AAAB8ACQAAAAAAAAAAAAAAU1M6AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDIwODBVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS1AjmvL0EAABqDAAAHgAJAAAAAAABAAAAAAAKVToAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MjA5VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUlmQL7zzAAAAjgEA
*/