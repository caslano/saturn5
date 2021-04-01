/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ADAPT_DEREF_TRAITS_05062005_0900)
#define FUSION_ADAPT_DEREF_TRAITS_05062005_0900

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref.hpp>

namespace boost { namespace fusion { namespace detail
{
    struct adapt_deref_traits
    {
        template <typename Iterator>
        struct apply
        {
            typedef typename
                result_of::deref<typename Iterator::first_type>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& i)
            {
                return *i.first;
            }
        };
    };
}}}

#endif



/* adapt_deref_traits.hpp
R3QajXZgv3QRcSFLYm4v/VPlaYavEJpfX/Z8chMEO8do0fKvgC3yn1rSlcIRdW9+SQvmPFe6xPO2fT1T9JVUAIeOWbxuboxfrrUaUmuSDyOJdXZDfuzWdd3PgSiyXyKPIosHw0iiZC75hi3nEcnCNWatamJpN52+7+RIXqTiEwTzwqqRECF8XhbKV53caeN7yqS4qCEEbiqZ9T5kc+xNiSnjJQa2sQ7M5v3cqcg2qe6F1n88Cg2R2xiP53N0hXmG+0f4nsJ8dS/Y9gYGmDfNRJyuv/KKfbwRo9GAFITEcZOfD6y3zxGa8Gww3bABqK3NYGsGaZ8oU5WfzAdeOwbolMoL70DWUv/hWPUd7nhdf0+vtl5lZKULU29T63MAdguusCZ1RleZSPUCYnKTfQSQBrTL5SLqUnC8H9IFvKB0BgMTBK9z6gqy4vSqJI0F8Hk+QNC7ZGuPZz2vUWLCGxUSwdTRbxYYIUPc1jVHxn2St9Y5BQO7SP0w5GuWGPRrgumlitT5PKrPW9s+ePCw8o3RBCAl+D2/b7ea248Q5IfWi9XK1+HAlnUZ2jRrnA==
*/