/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_VALUE_OF_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_VALUE_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_impl;

    template <>
    struct value_of_impl<set_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                result_of::value_at<
                    typename It::seq_type::storage_type
                  , typename It::index
                >::type
            type;
        };
    };
}}}

#endif

/* value_of_impl.hpp
BcyAAU4p0s1DM4IHsq4q9dY8arAV4mNIXo5AluU86XEBy5AplmHcTji9BUpOkg4keWD6m4Xn+Tj11YmapwZMDL7XVSQP+UxomBH9kK/tTYhQCjig2eMuv1Ni7mt30ve/eCdi8LN3ame/jWa5cktUmqVZIHAzxr+6nGiWDItmycgaI+biaZLuUZDWQPDCCpSCzTEMI3w+rtlB8+GtxSge0qkG5iQb52SS+nz35TpcRObVsk1KGEF6Z6+OKJ/nxslpeVL9mj6O/bTvwQk6/p4OaLqzP4pKh6v5ufKyKPMDsEJkachb/bg1JSMqtGm54DM5LffbpmVbSKAATEu5mpa2S//5tIw+sqNpmXaHnIzqO2gy0sfjZPQez/t9ON5kbrYBi6ATB4XQZFaFSxtxKVnzZlrWvJn+rIlF3poZEl5mMiedRuTX9pLdobz6EU347aPBhG91XvCyYmL8xCyUYYjOtcSVks9LxQ3qrNs60hYN5VBkHM7GiJ7RMef+UjkXFaU0F73uorOvQp8LtmHX5EJ4CDu7b7LkQih234NeRgEyXqW4MGyXUUfBvkK+nRdJ4wA4hr7L1+RGD9Ax5LgKj6GYJjyGLmiUcqN/jVByo2kXKbnRzaeRQYAuhoUpevsSkqsTQy8NAuAqJ+u2Em/NTcm8qd0sfjzozLyqq1ELwcIht9FClM/CiUROMb6Xr+zKg0i/zDCUhQ8lhsq7RCaG
*/