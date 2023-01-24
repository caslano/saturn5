/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_05042005_1136)
#define FUSION_BEGIN_IMPL_05042005_1136

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/vector_iterator.hpp>

namespace boost { namespace fusion
{
    struct vector_tag;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<vector_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef vector_iterator<Sequence, 0> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
K+M3y4m2AmnP1mkr+7LmPtTDsmrkkgb2Cgp/9zhGZFUGP8CoGr36aSXB70T9sRZW2hW5LIkMEzUK+ek0CIZo09koBWvsjJWMWRFKjp97SxsxpyGBLWyRS0bkyJ9iStzPwM1prIkyChB1ieNzLigJm7jit/gWUGAL/D0bIzWXGKLl4Q74Yj+RjQO19Py4NkrkrQMHs1Q2wd8lhVijXJPrgVag480Wv3DikfMbKJtUorLhMZqnS2U2T/zdZjZ3kBCzZATDbq4YJXFbY6LiRLy0gSVJy0JoQwJA0H3YMlFwMjRH9aKxpFKyP6CBtcKOJu4WoHMcKt7HJbkHW0cbuubwsNafBjPxpyTnJaJq+zFDlwim214Uk9VzB+i2O5hue8ATYAL83FgOlJEQbFmdickRYHiSbCotudjkXl8692KTh0n5rkRIVdmz5lxa8txpUuUo+p9FShticxejQEOuXxuTTeCbOAdDneHNAilRmfAAuANNS2Lo3Vvy3c2GcHdCoXdae0YDWef/sC9C56lq7iu0V3l5Rb0KPfM7kwyxwu7kFo0JO5XtD9erjecpESfpYokRseDAbHloAt6d36tsfqhezYZrpAPBXQRXxuUtTOI8zOXPTVSeZuu/KdlEAUeHDj+mli5iU7JZ8t3KOnspeyRI3kKbiXLGMppD5Ab6wmU6cS4zv7vuP4Wx/DCCViIGXBRB/Zaz7bsNg/rN0AKs
*/