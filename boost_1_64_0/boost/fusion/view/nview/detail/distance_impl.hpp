/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_DISTANCE_IMPL_SEP_23_2009_0328PM)
#define BOOST_FUSION_NVIEW_DISTANCE_IMPL_SEP_23_2009_0328PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/distance.hpp>

namespace boost { namespace fusion 
{
    struct nview_iterator_tag;

    namespace extension
    {
        template<typename Tag>
        struct distance_impl;

        template<>
        struct distance_impl<nview_iterator_tag>
        {
            template<typename First, typename Last>
            struct apply
              : result_of::distance<typename First::first_type, typename Last::first_type>
            {
                typedef typename result_of::distance<
                    typename First::first_type, typename Last::first_type
                >::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(First const& /*first*/, Last const& /*last*/)
                {
                    return type();
                }
            };
        };
    }

}}

#endif

/* distance_impl.hpp
ZzWXb4u+HtCDPIb1ACiksxYQAmw/j2wldoMM5lk5+q0GH6dH3xKb4V0o5KjjYZNYQ3VbFSHAuYejWolLQQbzFaDfnrNr4NsXk+1+QCkMtSz+Ie5IoJsqgvN/W3pQoEjFXrQpLYocteVqQVQUUG4LVESJljRJ29g2CUlaQEFRUfDEAxVvVFRUVFQUD1RUVFRUVFS8EG/ECy9AxWN+//z9mVQL+rqrz/LLDvlzZHZ2dnZ2xiIxWCfpqI0h4DGnc217cBcOLLt3/0oT+iRU0P5hWJIC35lIlFjntwUGIYPFmbCdZLBCM3qgLKde5E/AZp1yUVTOBXlVXRgGVtflSnsu3M3mwuMQH0c5qSplMGtg8WC5MhAYRH7eElsG9zAZrIH0/0UGrsZZkmWAGHgexjWZIj/vXnx+PdP9rsnlY7CNziYWHqBKBk111Q2Sogn2+7lvsD4TBpMOrMSBV2+/nM7nHoUR7UgHVNR5DNa5MTHCiSkilS6PpGqvLXHYvvLGTBFzvo/FnB+BCtpDL1FR79SmUV7QmePgOXpvZoo6R/fjwMZerrcpWxkqSB+GqaiBHU1jRNaJdQsk/O7O5kxRA/QBVgN0NXxq1b5TUfvLJlNiHVCOpEXc9b1M+IxksQoHDve7qTvGQxBJtXK5VctChSgi3G/4MlOc0z2IzxWJS543OX0Q8/oV1oiPotHjdcufH4SE7a13ZEJnksVD+Lwp4yDKYVwF4zSKOyqeH/KSelog4ffgv8+ELiSL1ZpRM+/PESb0AfiUYvJBxeuovJ0Fw8FzGX/PhHyqjfYwDtxXnUj5XfdDGu2vdijZY0bR6AtLyntpgYTH35KzRG2ER3Cgq/vS1Sb0Ptht9ZRRUT85isyGxoisOCRHEnuWfUAWvEuyeBQH/mx0P0cSgG3J+KB78V0UysIfdMnXC0LCaoZ1zxI1ZR/DgZ9n30B9ie81cn/M/xTbzWCZfJ8bcXCfG+UwhGzmGnyuPq6JbMU9sI78q93K5SApR5Dj4PvwHlnQRPrwuCGPr2fSnZC74bpk2oMqthPhKpeku6ItkPAYZZ8syCSdeAKfTf26fWlCV4AjiXRCsSxUmEzEwc/4S7PE2c2T7OzmLnBaNdU0BfmjFo11Jf3kHd8wHDw+U5YF/UkOa3Fg/s3D3jI5vRPKrBpLKvIlDRpLnVW+AMZTS+WJgaMAe9+BcrDyf57CgXYVN35mQu+ACx20kqYqmhelTiTQCB1I6knDcTB9gKOzYA7J4WkcuGHyrl8pYo37LtqHxiuaF800Sg5P2Di4HMZmwSLKfXkGB55Z+xLVl7kd0vNIH7opileZNHoCMrdeNg6+H1+YBYWkD+twoFenk6g+/22wqgutnZ2VykHe6SZHwXOhlmXBcSSHZ3Fg++Vxm0zorTDPqq+iJJYviGyQdt+C4+D3Lm7DdZP2n8/hwDXP15AclsGeTnTO20mpPoRVCIKQ8PjlM7YP8TzzIW4RubOXaArqsRGZxp9SfQiOw/Yp12XBJpLDeg2fk3bSPuNmSEsiG6Hi7n0wUD+7pH/xQOsXSf0tW6CJ9SXeyoJbSR4v4EDv8/abbEJvEjm0S9sruIsWcvk9WCipEp+Sdp/RGPax1+1SWB/9VyUyMP6o9NbIFIKNgsctt9s24iVmI26EqSprmAoi5WWJMRSxOZMohykkhw04cPOuU1eY0BuwfintO1XEbwWR8vyIlihgH+bF9bCKfhul4k62TWSj3ycpK4Dj2Ef7cJ2Qw1b8SVYnh6YGSdFKhiI2Vvl9FvSiefEqDpw03n+XCb0WLokjOcQp6G9gEznTJ+lYnKGIPf/8MQt+ov3WRhwouGTQFSb0GliZQHJIUCmHal+9JK8=
*/