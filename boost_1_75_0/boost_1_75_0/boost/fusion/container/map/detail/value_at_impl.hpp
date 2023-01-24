/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_DETAIL_VALUE_AT_IMPL_02042013_0821)
#define BOOST_FUSION_MAP_DETAIL_VALUE_AT_IMPL_02042013_0821

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/at.hpp>
#include <boost/utility/declval.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<map_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef mpl::int_<N::value> index;
                typedef
                    decltype(boost::declval<Sequence>().get_val(index()))
                type;
            };
        };
    }
}}

#endif


/* value_at_impl.hpp
qGwXe3nF/mhqYCGvxzzuHvEgXFu2yQWxPJrvJdJE+VZee/+JprVn4pGtDuWRGbYZQzhiq0M5YrjCV3iaMrwCnnCUgZXn/0fTTIJJwbHi210bR2B3OyTAdmXmIOFVDlrRAd+1slrN1XsIeSV4Kj89zV+eHSgUBIgtf3h7UX2uID4OZqQ9fl7R1R5lCG7iHYEn386r7NFcj2GNk8QEjklsFH8PeZTOkNn/majgIlFBRtqU84q6QQEB16gkIJ47oEftDCwJ/gZuam+ZFA3Otfsd9MdkKxNTpBV6zOcjmCtGoUgCL5A2ZE0DfFdI4SoPSC540ImxFYgEqEA9Ge1AEZjicwlDSW4v4Fp1Z5yYRXLUY3a8AC5Y/rZSC/oq3FJ0Tu/dmqvLYLkG0SCN4R1Cp7kDrpc+hMVvLMAF5gW4IGwBLjAvwAX6ApzMtdeGLUBykO7yfCIX4C1WfQHWhizAwdZQbqfTqC50AQafPwUC5nYYulzJp0dxV7G/LWCxD6sIgxNOgSON0wDkAd1PZOtBhv+MtoPMR4FstM5oFH2/SIJPOpCUth4Nu8F3xdPTWRI9ncEpF/Z0ptxF52Iph935gO7M4f130ZsyJzvupdACoXoin77+ysdMP/NR/N98dFj0NaSqezjPdsqzgfO04wqXFETSkwUd7I/XhutgIze0Qepf/5jZ9F0a6Ud8qNJ5VkRPorQEWMj6YxGzuVJw+Q7u
*/