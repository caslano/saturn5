/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ERASE_10022005_1835)
#define FUSION_ERASE_10022005_1835

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/erase.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct erase_impl;

    template <>
    struct erase_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename First, typename Last>
        struct apply
        {
            typedef typename
                fusion::result_of::erase<Sequence, First, Last>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* erase.hpp
navEvFZYI2rUTUi9mfmYpDrkDk7Qr9clcN2ffamkVel+BrznYIeJtxYwyfi18I1DWaE/5NUqYdlVqPYDrTl0ra1S3jd+bq7MBTDB1Z/QDIgln+DiuaEYP6I1hQE0kppvFSV7naiZaUmVtBZk9Y26Pn/HvLPUtmE89sMOslRQU2oUxNcmJJvawuMmN0RwIUqeMRxiE58TfveHDEb/lAWkhYigHjgijeQbAW+YJeDMvTSAB/huVCBIVmeCFEl2IzLlOiZYL8Zy6pYyQd3CWkFV7mk7O2kBB3mVBzOZfJA3v8GfO7b1EjcNUlSVrvHc3sHq/0rb07j0yWN2+pDcetHjgNwsO/05nEpsNbtq8bTD894sbl7d8wD/GzS/GBZIhBa6KqERyGuZ0PdyAK1tb0yZ30HAbr4g/gJVqa6sXxrzInQL6LMGLF+81zsS0gItE/PkcY3IDYLSNB689ke0jP2CcgO4m0LMvpdosPl9KYtcPj7HWasywAQCCAqa1PsbF9M3yQnJmGDyOzzYjUk2T6Ou8u5puXXia/Fp98fReSMJH9scTztzKBJ6aY7dWQ==
*/