
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/and.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C_, typename T1, typename T2, typename T3, typename T4 >
struct and_impl
    : false_
{
};

template< typename T1, typename T2, typename T3, typename T4 >
struct and_impl< true,T1,T2,T3,T4 >
    : and_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4
        , true_
        >
{
};

template<>
struct and_impl<
          true
        , true_, true_, true_, true_
        >
    : true_
{
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = true_, typename T4 = true_, typename T5 = true_
    >
struct and_

    : aux::and_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4, T5
        >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , and_
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , and_
    )

}}

/* and.hpp
CZwsdqfAaDhVHcMk74ewu6SjHcPUTupnFGwCo2E4bA/bwRjYFXaA6phJSa+ZSbnNEL9mil8J2vJ+0Xt5V4ne+zACfqDRs4letIneW6L3a9gO/kajV+pD713Re0/0fqfRqxS9cBO9StF7A4bBNzV61aLX1ESvRPTugY3hdtErtcg7Ajgtei3hDtHbK+d1HwyHpbAzfAj2gg/DCfARuAAegIvgozAdPgaXw8fhJngQ3gmfgFvhIbgXHoYPwCPwEHwSvgbLNPXR8pL3+hgv+Rsj532s+D0ORsPx2rG6L3kv305SHzvDMNgFqvXnJe/1Llz0WsMmMEKjl+LD3jWiFyr2Wmr0ikWvuVbPZKxuM836yOeREtG7RtrHdo56po/j3x62hjEwCnaAcTAWXgs7w+thVzgRdoOpsLsmjn8+7Ak3wt7wAOwDH4P94DHYH74I4+BLcACshAPhr+Eg+Da8Fv4eDoGfwevgJTgMfgWvh03IywjYDI5U4zfIcy4kD+RXH7+hu5RvD9gc9oTtYS9Y7edYRUtwsCUaqdpa87jFSeXusYu7X6kfv+jP+MXyV75/YxjffiXwcYwX0IlmX8jJ/7/xjG8/X/cxjYO5xpKQYuQgUolcQro0CrYkIHZkH1KBnEdCr2IsI5KEFCMHkbPIZST26mDLNMSO7EZOIueurh/r+N/y+7a+/w8sqvv3f+VbfpwmXv9u+ZZvhc1hFpyn9Cce0/d3Sb+TH32wrLP3rGefk/TNeMTsTk9dUaB+L/Hsh5K+2lj2FeVadP1O0o+q9k3NZx99U2q/U047dLL1MXNDGhpj9C4kn5bndHFixyQmzpo8dk7ihEDj9M53xIr9fswX/E/3NdXPC3T2NbVqr+wPvf0vWfs/ik2Kmpp1w9bz9slXbl7glepr4tmT/XJNy7VehXRQ2i7oWtO+OYyA4bANjIJtYScYBeNgNJwA28NpsCOcBTvDDNgFroRdYTHsBnfA7nAP7AMPwr7wOOwHT8D+8C0YB9+BA+Hf4SD4DzgYhuDrENgCDoXt4TB4HRwOh8ERcDYcCefAUfBmOAZmwrEwC47Txqh7zh3LLlS7tr30xdj9fPYO5Hm7/lm75mft79tzdqDP2P+Pc4WuxLN1UmNiYzWuf/6t/9X/6n/1v/rf9/v3Lb3/8+5/Zd7/B2rG8pfKe/GFRjzzw9/DZKWj/Un3+/+MMdMnJOflZlizc9XxPPvMi2It78T4MtzxXh5haejoD0h4xtkfwGI/ju2hzxj7Bx72WPfERqEuKsyU8SjusdthjP1Nwb/zzRuRelZGkeiskvEnvLY7tre6tqV/IUu2rSzOBRz7jrDvzQjHum/JLlt2j3Esm1x6sr1DtpfIto1txcEC2S6S8dG3yvY6tr8ib5ScY3s320reXONmil3pD3RuW13bA5zbJWwnt6YsxOd9bKeS/8UFyel52XbHvnT2acfAK2t29fuh850mPUbfDxIeZOwH6cdHxuqjmn4QOeUTZiTOmhfgmlR9Io3rFe0OMq6RM5DjQo95sRngulTYNFun53vRF1Mfu+m77aOZ6OijaXlTafaObhsr2/Rv0XXX7JgPr9x6JuZ9OjX0xQRJ+yrt7iX+kWxxx/JsJ7FZOsIY2BN2gb3gQNgbXgf7wGmwL7wR9oNpsD+0wjiYDwfAFXAQXA0Hw/XwWng3HAIfgkPhc3AYPAGHw5/BkfBNOAr+Fo6WPph42A2OgdfBsTAJjoNWOB4WwhvgnXAS3AMnw8fhFPgMnApPw2mwEs6Af4ALZP3whfAGeAtMg8mwAKbAtXARPAjT4J9hBoykLDNhD5gFe8FsmA2Xwq3QCvfAHHg/zIUHoA3+FN4KfwmXwzfgCvg=
*/