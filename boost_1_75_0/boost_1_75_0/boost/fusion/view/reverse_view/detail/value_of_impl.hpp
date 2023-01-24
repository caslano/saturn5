/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_IMPL_07202005_0900)
#define FUSION_VALUE_OF_IMPL_07202005_0900

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/prior.hpp>

namespace boost { namespace fusion
{
    struct reverse_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<reverse_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::value_of<
                        typename result_of::prior<
                            typename Iterator::first_type
                        >::type
                    >::type
                type;
            };
        };
    }
}}

#endif



/* value_of_impl.hpp
qtl6Z1fGPjn45Dao/Q5BgQyfdjCQoOgWc/VIU893dWlP/hZicWeH1aduXXROF90rxmI06LW033WbXrbrgkJRI4EApmV2FE8MTtAHP+CCw5xWoCnP6erNzY5Xgi1BkHPChk+IE5eExp34BCu0DE0kSdvrXgudkP+L6yguC8GGU3wjvRJ1H6jyK72bgZUqNlaQUZrXQI0T17lsSL4iBJUdHPgdat3guTxCoY0NVsvQLuLGRElWE5I0ddaG1EjwqotU+aVP4q+/kRdpQ29rCGZVL+ieqO5NKzfDywhXIt4sFQkDbwREQp8yYmp4GbbTOTUjOVM4g9+JI7NHw6qCbRr2+xhqPuLNuRm6mRqC41cHMjAddBcoCEh/d/YqWMYVmgyqKU73o0EzgpPW7dvPDiBToDcN823ZkvsdC+0nz5r85MoPGnxXjo8JefZuZ9B4mUDoQKtRpx28THu+HAP0Dinu2EwaDzZsLHTbN/Xn3MpczhhOrXnG8KnAgaBNEzoMvkaDa2lNX2hg33cFyWjXe3OUlT+/eR/Fb3tA5bWYWnaJ+FuV9aAzVfh+iHtv6OsDlCw3yabhcllfeBjcHBsqCS6zpvtlwdHYiUKxjBVevTxgiXCTTamB1iNV34neVzEvFem5FqZuctoB6rASZtMzpwgUh20aOeHZEFF9sWftBPeTV/doEZt8Nss8IsHzkLzuYB2uhjx5TRcAcy5Ob990
*/