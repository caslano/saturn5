
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION!

#include <boost/mpl/aux_/preprocessor/params.hpp>

// local macros, #undef-ined at the end of the header
#define AUX778076_DTW_PARAMS(param) \
    BOOST_MPL_PP_PARAMS(AUX778076_MSVC_DTW_ARITY, param) \
/**/

#define AUX778076_DTW_ORIGINAL_NAME \
    AUX778076_MSVC_DTW_ORIGINAL_NAME \
/**/

// warning: not a well-formed C++
// workaround for MSVC 6.5's "dependent template typedef bug"

template< typename F>
struct AUX778076_MSVC_DTW_NAME
{
    template< bool > struct f_ : F {};
    template<> struct f_<true>
    {
#if AUX778076_MSVC_DTW_ARITY > 0
        template< AUX778076_DTW_PARAMS(typename P) > struct AUX778076_DTW_ORIGINAL_NAME
        {
            typedef int type;
        };
    };

    template< AUX778076_DTW_PARAMS(typename T) > struct result_
        : f_< aux::msvc_never_true<F>::value >
            ::template AUX778076_DTW_ORIGINAL_NAME< AUX778076_DTW_PARAMS(T) >
    {
    };
#else
        template< typename P = int > struct AUX778076_DTW_ORIGINAL_NAME
        {
            typedef int type;
        };
    };

    template< typename T = int > struct result_
        : f_< aux::msvc_never_true<F>::value >
            ::template AUX778076_DTW_ORIGINAL_NAME<>
    {
    };
#endif
};

#undef AUX778076_DTW_ORIGINAL_NAME
#undef AUX778076_DTW_PARAMS

#undef AUX778076_MSVC_DTW_NAME
#undef AUX778076_MSVC_DTW_ORIGINAL_NAME
#undef AUX778076_MSVC_DTW_ARITY

/* msvc_dtw.hpp
Xi/eJN4ifle8TbxDvFu8T3xQfEh8XFxUgiahKKEjwZRgSbAlrCT4EgIJXwk/iUCJYIkQiUiJWIk0iXyJQokSiQqJBolGiSaJVoluiR6JPol3EsMSYxITEqIUcYomhUnRpxhTOBQuRUjxpHhTfCj+lEBKCCWKEktJoKRTdlGyKPmUYkoZpYJyk/KE0k8ZpAxTxijjlCkKXZIhqSNpIWkv6STpKRkgGSoZJhkhGSMZL5kkmSKZKpkuuUcyRzJP8ohkoWSZZLlkjWSD5DXJNsknkq8lBySHJEckRyVFpOSkFKXUpZhSbClTKb6Uh5SvVIBUsFS4VIxUktQuqUypHKkjUvlStVJ1Uk1SrVJtUj1SfVLvpMakJqXEpaWk5aT1pTnSFtIC6SDpEOlQ6WjpOOkE6TTpXdLZ0rnSBdLV0jXSddL10jel+6VfSw9Kj0iPS09Kz6CKUGlUOpVB1aEaU02pTlQ+1YfqT42kJlJTqenUDOoeaia1mFpOraU2UG9SW6h3qR3UTmo39TV1gDpKnaJOUykyyjKaMjoyLBmODFeGJ+MlEyATKBMsEyUTKxMvkyyTIZMlkyuTL1MlUytTJ9Mk0y7TKdMtMyQzLDMhI06TolFpyjR9GptmQRPSPGjeNB+aHy2QFkSLoEXRUmi5tCJaMa2UVkGrptXQ6mnttA7aE9o72jBtkjZFE5GlyTJkdWT1ZY1l7WWdZPmyvrKRsnGyibJJsumyGbLZsjmyBbLFsiWylbJVsvWy12RbZAdkR2RHZadkReWk5BTlWHKmcvZy7nIecoFyIXJhcpFyMXKpcmlymXL5ckVyJXKlcuVyTXLNcu1yXXIDcsNyY3KTclR5TXmGPFOeLW8sbyFvKy+Q95D3kw+Rj5WPk0+UT5bPks+Tr5Svlq+Rr5NvlL8mf1e+Xb5XfkpenE6lq9JZdFO6LV1Id6d70n3oAfRgegQ9kh5NT6Kn0jPoe+jZ9Bx6Ab2QXkmvpzfRO+lP6L30QfoQfZQ+QZ+mqyvoKHAUrBR4Cu4K3gqBClEKMQqxCvEKmQpHFAoVihSqFGoVGhRaFToV+hUGFEQVpRTlFJUVGYr6imxFY0VbRSdFgaJQ0VMxRDFcMUIxSjFZMUUxTTFLMVsxTzFfsUaxXvGaYrPiXcUuxXFFcSWKEk2JrqSopKqkrqSvZKVkr+Sk5K7ko+SvFKkUrRSjFK+Uo5SnVKhUplSpVKPUoNSk1KbUofREqVupT+m10qDSkNK40oQSRZmmzFRmKVspC5SDlcOUE5STlDOVc5XzlQuVS5SrleuUG5VblFuVO5X7lN8pjyqPKU8ri6vQVTRVuCq2KjwVoYqnireKv0qESqxKgkqySopKukqWSr5KgUqpSoVKtUqdyjWVmyrtKl0qT1R6VV6rDKqMqUypKKqqq1qoWqm6q3qq+qoGqSaqpqrmqOapHlEtVi1TLVetUq1RvanaptqtOqQ6pSqiJqomp6aspqPGVDNV46hx1fhq3mq+apFqUWpJaslqGWq71HLUStXK1SrUqtTq1FrU2tQ61brU+tVG1SbVptVE1Znq+uocdQt1W3WeukDdQ91H3V89UD1cPUo9Tj1FPU09W71AvVS9Ub1ZvV29S/2J+rD6uDpFg66hqsHSMNYw1bDScNJw1/DS8NHw14jTSNXYo5GpcUSjWKNEo0ajVqNFo09jVGNCg6KprqmjydTkatpr8jUFml6afprBmmGakZqxmvGaSZrJmhmauzRzNY9oFmqWaJZqVmvWajZrdml2a/ZpjmlOaM7QEteS0qJrKWvpaxlrcbSctDy1vLV8tKK1YrV2aWVp5WoVaVVo1Wtd02rWuqnVqtWj1a81rDWuNaU1g0E=
*/