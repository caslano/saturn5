/*=============================================================================
    Copyright (c) 2012-2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CONVERT_IMPL_10172012_0940)
#define BOOST_FUSION_CONVERT_IMPL_10172012_0940

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/std_tuple/detail/build_std_tuple.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<std_tuple_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef detail::build_std_tuple<
                    typename result_of::begin<Sequence>::type
                  , typename result_of::end<Sequence>::type
                > gen;

                typedef typename gen::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return gen::call(begin(seq), end(seq));
                }
            };
        };
    }
}}

#endif

/* convert_impl.hpp
rmY7ZpkxqYqXBKoimbFSFpRU+ZCtWKQ0Yk7vWbBhtZin8SzZHIufiwQ/y5AfhEX38FaVR3DSfYnkxEwnjlrZgQsiDzoMFh48IsHbE89y7Wdl7cfBthWEcqeB/td/Vl/RU6auuANED/JWcOekhsLp4PiEnMiCPMUhzOfI/C5OMxZ3Azj/gkGwTWKzbPNMaZvxeCos1HxgGm3cAz8aYj4w82VIofghxDyTjhLM1UaICVq6nv5n3VxDOH3Ti387oxrpfWfISMtRKCZwFEpLEeKmFw+1YRikXjzAZmYvgEni7umn/RzQjwPrTB5FaEC+xRpxTaxcTLKRbMleMvdThOzQV9/jeWMDHWrlh/dY73OHxlKH5kdCb+7FMSJ00Xuhahtv5LtzAu7CvAxCHF3gUKe0gKI9gnUYFhtsKajyaZwcCOMIisvw9Rh+zH11P1UejFRbG54uN6PQrPRICXCrrWcIi/E7mqXEatZApqQU8Dtqk2OtXBHqAOx3bOFHMzXFzMgxca41JsKstB5fBQ7Jm8+j3FVnYzSJcC7R6XGEu0duyg69Q5rg2+8gE3x0CJrg2iEUU37oTnJq2M8Wejs93kCX1XRZxoPj1/Rz3hB65yN+ZwbdnjYEx8Qp9OuFIUH4k8p0V4tGS//S56alPxwFPbcLfAbQY4csfo5MIwNX9Pfj+Gu/47ZrANT0DzEPHigo3ZlEoeCJNoRAjY9EiCj7
*/