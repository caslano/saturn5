/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ADAPT_VALUE_TRAITS_05062005_0859)
#define FUSION_ADAPT_VALUE_TRAITS_05062005_0859

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of.hpp>

namespace boost { namespace fusion { namespace detail
{
    struct adapt_value_traits
    {
        template <typename Iterator>
        struct apply
        {
            typedef typename
                result_of::value_of<typename Iterator::first_type>::type
            type;
        };
    };
}}}

#endif



/* adapt_value_traits.hpp
UzX94s8XlQf08wXUd/8IkRNMx8yGs0KxjvJ8jpCdwyWqWzkOgq1H8ja5lcOe6t3w7SAQAx27lORSK07nFP2MWBRJGqjsceXudWx3SdP2uB0fSNOOedAdtl5mXdfwr3Aa7xIo7olnUwwjoXO1B/eAD1B/jFu7B6FOUZ+k1Lkdcrtbmu7EV39uIa2f/moogCdtT26jWh+NP2b/v9YbSawXsxkvSajwMp9XpZtXOaDZTvZk+x+iqNeqj2o6xqiuzmHfzy5jZaBtUo2F8nWzl4sXE6SD1H3Wq6iurdy/D8ooIA09XU8jdk1qWah9mFR9jHIa11ukGitdqGpESI1LbuVSGebwg2tXB1NcoR2W6DCMfAl281q/cyur26P94Gfe8sHyZpSQzDlmkyw9X7c0Xa8LxAsKYhlOE7R/OgWsR3tJNY2arSWDXKjiy35ZFnKMdCvfBSfgRfhxXTAD3oQ/3Mqy9ihXc6AHSY+imj91UY2BWjOeMo/DM+lQaksau6vBeak+BQTCJFN0NHVYnVzm2L68+2Y0/0Lzl2TBm8sDGfB3UTDzLYQrjia/hapYfkePTQvhe493HY3SOpQrpSoEHQm1FElVL9CXTKlqj/7lSf4SWLK25YCGZdfihQtwB3GUobLQhXuldR1UzQkq65GqDtMXi15NL5CM0eGiJV2qSqEvZqkKw5xcb6VRbWapOtOMK2fcBNe2KRjDTh52Vlh/
*/