/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_IMPL_09232005_1341)
#define FUSION_CONVERT_IMPL_09232005_1341

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/set/detail/as_set.hpp>
#include <boost/fusion/container/set/set.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion
{
    struct set_tag;

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<set_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef detail::as_set<result_of::size<Sequence>::value> gen;
                typedef typename gen::
                    template apply<typename result_of::begin<Sequence>::type>::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return gen::call(fusion::begin(seq));
                }
            };
        };
    }
}}

#endif

/* convert_impl.hpp
Dpe00IqSzQoNMtTPaXN/3a5dJ4esZqfllnMH9gq1r+nr99+LH81tEzi+e4hdfhdIwrwYbTyDN7EBexHSTZihJdku7iSrhoeLv+Fz0lhowTrqN4wobvl6ZDuygr1G8CIAwArW7k7u6spQODZULQ10T6gPASOVxnWRz0Gjt5UT+WvqOSZAQ3DRTItBTuOp3/nreo77YYGM/ckP02Vn4wuz6wDJ0kIbNwAhUGtCjPJEtBxbiyu9uaGuZslrvu5dkW9hbq0Qf8udlaIzh06F8gV8e4UT9XyJU1NvXIA0j6WUJhhDzCAtybl2UeYcLu7LkMEgikP9VJoL5ln9DJiHpaJh8GXinTUw0qLxChWRgAzoq7cBDbhVXqAwQAXplwE9q2nRv0MbyevU6k6soKFtZiZD2uXxjC+vquxLWID5YwWmnuS2Cj4KX4+kRN8kl3WDsPw+OfIZsyNNcTdAyrUoIwM42mJT7JuqM3KDyI9To0XDIAzN6Q8ojIRsVbpZfcmrhczzlbBBg0ioELQTtbaJE4TFmhcK+PolSYDdH5pVaicO8DkiFFExnqmFYUzBwg==
*/