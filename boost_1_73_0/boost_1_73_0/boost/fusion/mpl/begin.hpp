/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_10022005_1620)
#define FUSION_BEGIN_10022005_1620

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/adapted/mpl/detail/begin_impl.hpp>
#include <boost/fusion/iterator/mpl/fusion_iterator.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct begin_impl;

    template <>
    struct begin_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply
        {
            typedef fusion_iterator<typename fusion::result_of::begin<Sequence>::type> type;
        };
    };
}}

#endif

/* begin.hpp
/h3Mjz8d8w70bagj7P8Z6v39wIRmxqu2c8LuJthO24ObtI1E3qpj1XrcVYw/8/6mZLYltJ/RJ5/Ccwv3fb5vdyoQC+jqUNpNlrbtl7Sqsxy28+l01o6g05Owyb8A5MW4nQJYYMPwR1h747/b5VtPNZdl2k+1kdglecfuZen9ND24S9O/q4P/J2pt9b26p/qozcLbC145qnLtjgV/KMTDtoYIlF6pMPMJp8GdnHUZg+tr6Ia3ZXISGoq9WQ+H7v2mZ+Njl0b4FqNtM5kLhansbw7h1ryBhD+u6eSWeS8dd9Iegbu4+A4B34QRrLSbADV8LMW80HbgtgHcLXracAh0s3DXA9Ot19DU6EJkO/NKms6GzQJU/MqQhZ6qzpZUPdfvRBa3ufAtQ1DgObW7i4BObu3jrj46zt54jvuMPH4M4fEzR+DxbAtTuyRtyo9DL+jbG++U79b/pC49MPfCMvuSbd5rotB4WTZudFruzxc71s5Oe9FwH/ozRCUv3X3G3mNYiQBif6wltYS2S+6KXQk8mjCzDs1NVe0qvLwp+kMWNpL8Kg6l50ORdhSx8K3bFPrXA7ChdteYx9bQr07oN48o3gfSeu03lwg210ROg72REFrhSh3oYDvrxRp3COuXTYVro70b1ojvpG2PfjP4
*/