/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_AT_IMPL_20061029_1946)
#define BOOST_FUSION_AT_IMPL_20061029_1946

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/utility/result_of.hpp>

namespace boost { namespace fusion {
    struct transform_view_tag;
    struct transform_view2_tag;

    namespace extension
    {
        template<typename Tag>
        struct at_impl;

        template<>
        struct at_impl<transform_view_tag>
        {
            template<typename Seq, typename N>
            struct apply
            {
                typedef typename Seq::transform_type F;
                typedef typename result_of::at<typename Seq::sequence_type, N>::type value_type;
                typedef typename boost::result_of<F(value_type)>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Seq& seq)
                {
                    return seq.f(boost::fusion::at<N>(seq.seq));
                }
            };
        };

        template<>
        struct at_impl<transform_view2_tag>
        {
            template<typename Seq, typename N>
            struct apply
            {
                typedef typename Seq::transform_type F;
                typedef typename result_of::at<typename Seq::sequence1_type, N>::type value1_type;
                typedef typename result_of::at<typename Seq::sequence2_type, N>::type value2_type;
                typedef typename boost::result_of<F(value1_type, value2_type)>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Seq& seq)
                {
                    return seq.f(boost::fusion::at<N>(seq.seq1), boost::fusion::at<N>(seq.seq2));
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
wxtD0dLAijJbnlalLFoGGO/tD4+Wh6BlghXnazn7luJypLg+o9sl03loWfBsdgqfM4vqAhbA7FTgjEO0J8B4Do0s72nMeCnOuvtGRToPYLzWk0JaHUazgfGaNXufuQVtmWQ9h+/IobqA8dzdylbLpesEmI7ZZ7ZtR9CyJUud/FdL2i/wv4KYNY3ZO4Dq0qrgXhr7Ii2B6gLGcz/22YeOaIlg/syOfxZM+8wKxns05KvpK9DsYHwtH8+U6ES5S2MG3fp7JeUuxU16v7s67QmwYGabZ0SupT3RuqAduDXzX7QwsLLMDlZ8OgzNDFaU2RPXd0vRLGC8LiXnRUZQ38H4On9rsysJLQ1Mxyytx4oZaHvAeN/vPfhnElomWAyz8e6D+qDp2hRcy+Rza3zRosC8mNm7tX6BZgLzZLZh0rrZlLsU576pcHfKHYz39nDUxFzKHcyP2Zsdwdm058F8mTWLXNKK+g6mZ3Z7l18jtCwp7ua90XvRcsFCmF2xlb5G+9pccC+1r+2fSnUxgzMb8v3iMModrAwzj1aHKqOlgnkza7EstDPaLDCeQx0/vwaUnzSm15JxCyk/s/Q+4O+SjSk/MF7P9NXnP9C+bluw7wn9h8+ifQ3mxWs9t2kL/Ew8Bgy//lAWXk9+438FzQSmcwMT5k9We2W9YmiPOxSM2z279Qm012D4GTWYmJK90hOtUEchCrG4yM/ON0TzAONxjbq+uIHmD8bnM1ZIPYamByvK4n5e8L42WpQ0X4WRlcMod7AizK4+afsH5S6tZfOi9t+jtZTGrNO3eks0M5iOxe2P+2YjWrI0ZpeQtzfRRkpjrrkzPgUtFcybxb2cXKoM2iwpB882md5odjAvFhd68SjVM01ap25adFe0nVKtwwwLg9AOSOt8WX1UDTSHNF9O5L4paJlSj2z//XsIWrY05rALd5+h5UhjXpzbtxDtM7BizCr6jzTSXupUsNZZlzIS0YLAeO4PfOsmoEWB8fl0SQm5aHXB+Dr7ul9cg2aS4jrN7GVCM4PxdcY8XN4czSJZreSndI6sYEV4rT/70o32hJTf3V0xm2lPSGMmxjcrjbYMzJPZon0Jf6Ktk/IbPjWB9lK6ZLXG1BuGtkWy9nNujkTLkOZLGdo5hvaSFGftcI/655DiYtbE3kfLlHIvufyb6mjZkr0uvaIKWq5kLea0/RJNdC5oc37N9kHzBuPnwb9qeD00fzDeo4Dlr7qj6cEi2JiPviz7AK2DNObwRnvS0ZLA3Jm5Xr0/GK0PGK/ZDzmL6NwmSzl8X9KdajZSGjNdP3slmk2KW3Jurz/aPGm+Z00z7tCzG8uvHLx+nfXeG78fJRPMI/9r5eWFEEcHxi5F8+6ijQkmYiYmUpwODK8TYOKnXQu17xkC82H22ZdPeqBFgZVgVuOO+yO0eDBPZqW3NFmA1gGsMFtL1wvzj6JZwLxY3O1JGzqhWaV1nqvafz2aTYr7arOhI5pdMq+Dg81oaZLFXdnWFi0DzJdZ+0j9N2inwIoxGzC9SShalmQzRlj90XKk+X6a7NIc7TlYEVaXVgO809DeS/an6+IWaB5dC/aoY3Dz+WhBYN7Mcgrv3IwWJln82387oMWC8XUOb7/5DvUWrCSzFuUv+qElg/kxe1fH/V/qEZg7z69TpQpos8ACWNy04KYV0dIlm3y4bQz1AawMs0d7Tp9Dy5Xya3u+9LdoolvBmm1fPeMhmg6Mn5UJxROfUT3B+Jjfjdj4I9UTjO/rMYdmbkGLAnNl9rRrFT1aDJgbs94XIt9RH6R1jij9pB71AUzH7Ob8b/9ES5LGvHp3hxXNIq0l2FDSl/oHxvv+pSg5Ai0VDK89enjd+Os7qnU=
*/