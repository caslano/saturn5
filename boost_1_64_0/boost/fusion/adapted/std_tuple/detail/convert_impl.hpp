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
uiEnfanW0WzyBRWMXPRroVTbs8v6YVowS3sG4P95ImZYV3J00DwNNGRLIl064s4lw+INZhZpO1qqbdpokJK2cPXHTS7lRHBK37Eb+TvZe6i4fcd7wk+iSEtkgnkYfLTU/PiE8KxmzoXW9PWqJxbBMULvmnnHg+z0mZEskxZV6G84K9by/Ih0aR4P81DrfWEF7aAq3i8bxrATsCfCM7FSufk1FtjsnYxE6B+AkDvd1hTjYyEfD+5OCHmOf1MfLi8T3qUqlbhNVbOlNKzB6vqKMPiOWmOl7byMfKwL02iFwIgD6CXo/ncUrbcdMqFlgOkpTIMcNWaRyquwLYF60GlVb/p5aFxYoe0c/byZfHB899vlkQc3tBLRqPY7JKavWvZUkhgcqmutVUf2v90ITVEitGiw/RGU+SVxUBYTtl4mh8QsdWdkQsRo5/D1xP5AZN0UXzW1drILpWlyree8LmIkZRRKszxyWVp+klb9QqtT3QM7qtZxM24idcyfeNYQZvM9q+VbKr2oc7EKwnzQotSB2AV6+HCKOhAffU6Yr8GRibXUoqHCJqPOBy0ERA==
*/