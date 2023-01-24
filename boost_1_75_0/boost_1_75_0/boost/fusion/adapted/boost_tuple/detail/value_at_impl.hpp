/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VALUE_AT_IMPL_09262006_1926)
#define BOOST_FUSION_VALUE_AT_IMPL_09262006_1926

#include <boost/fusion/support/config.hpp>
#include <boost/tuple/tuple.hpp>

namespace boost { namespace fusion
{
    struct boost_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct value_at_impl;

        template <>
        struct value_at_impl<boost_tuple_tag>
        {
            template <typename Sequence, typename N>
            struct apply : tuples::element<N::value, Sequence> {};
        };
    }
}}

#endif

/* value_at_impl.hpp
jIJJMVkeNcy9Ly39HrtLuTtGOazVZCmxv5ksh7M8g36zpKff1VgTYcfJ7G6W0W3AuJs4v/grtG/yHLdLS2hZRU4dYKwi0FP6WqjlXbPlmmqw566EESO3HlD2ylJGNeNLdcErrK7V+yNSdrog91pZUdVpb4KNCo61zxCtEmdG4NAdavbfcNCyTPh2iVILnpMs3vV0fftuIj+bJhztmTM2+d8755GSKqtkOZ3WjssTN8x5Fv2GuUCEFRhhgel845IRybo7IVm7v4QTM1KB98Mw5HaAn+SYcWp+D4Cq+f4rGBJBzMKftNCWFCZ41g0TzK7bZe+9BSwooFoUAog2eaIGOA7IRg0syrN1o7/pX1k5ZJE9wFytRjdX++EZk7F4gdkI0noEZfp/UWgHwYASONwfTzDDyBL4k24Uv5e1ngH+lKycyPLdkwfd/XlmmyanDZBKHufLCbv6UTpcOyG50bRacvmiukwFDKLehvx8h3MjSFsC3fbZbryOAxVBAsxQiUdrwGsHpRpOkx/QI8CDALrVwiYr0m3pu5sQuvV27PWlaMfUAHAjw+j+yaclfnlCyrTzEeYox4EgR58dJkHyyWFs0pmt+JjaGmfYlvrx1C3jQ/OUd5fVZFy6yUV2PxMKBFRGKtZrtGH/uaszrLBreSArMDJXcwYIQmd1dmg69+0MTWdGOzrf2NkZOocFpzOmYzrPOA2daaehU25HZ1in
*/