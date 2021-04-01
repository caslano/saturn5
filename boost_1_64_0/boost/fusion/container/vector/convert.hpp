/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_09222005_1104)
#define FUSION_CONVERT_09222005_1104

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/as_vector.hpp>
#include <boost/fusion/container/vector/detail/convert_impl.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct as_vector
        {
            typedef typename detail::as_vector<result_of::size<Sequence>::value> gen;
            typedef typename gen::
                template apply<typename result_of::begin<Sequence>::type>::type
            type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_vector<Sequence>::type
    as_vector(Sequence& seq)
    {
        typedef typename result_of::as_vector<Sequence>::gen gen;
        return gen::call(fusion::begin(seq));
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_vector<Sequence const>::type
    as_vector(Sequence const& seq)
    {
        typedef typename result_of::as_vector<Sequence const>::gen gen;
        return gen::call(fusion::begin(seq));
    }
}}

#endif

/* convert.hpp
d2gZG0pBEZyN81ETUbPkgFDNP9l22pZmo+H+Da3Jw7KjrYPGMdh7+5+k8h86C3njcqOCjEfQz5Xn43ee9XiUwLyTw9ADa66DEHbSw0x/jeYh5aSCZ4Fjn3WLYtAqBPar/fYSNY0oT/gVCkLHzM2BPGx1fykQONyRtTfjbOMTa9042wz0QpxGDysM8sAkuVDBm1K0boTJTQyb/ee0R0d49gICpAUXJKTcgR4r90dRu6fnxZdtk24YeSEF2YtPLZ7ac0lEEE3HOOdWq9HXgrrLdr1eX2fsvfjaA/sK6LE8/2Nb6M5jkS7ePQtuCL19r0P8ozPtZYDlSLU3DCiC3G3iu5aaQw+Ol4xBaiVeruGQSba+JkpaqfxEPnLMtuCNRGcg94OgnNyHFb+Lw//F8kU/XktHeGGztnNjDIH3/67qshKWKHzIxx9kaG57WuvraPjx59hbaJiGrLROilPkzFfu2oV4z6k+F8rx+csQnC8b02oUMINXgU0DwpVIHHXwXTbR4d50qbNueu3QD9SaFm6R7Vm/0oD8VZJMg/HDb/0QlfnGGN8ouG5PQc1F2A==
*/