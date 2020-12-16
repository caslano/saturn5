/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CATEGORY_OF_IMPL_04202013_0940)
#define BOOST_FUSION_CATEGORY_OF_IMPL_04202013_0940

namespace boost { namespace fusion
{
    struct std_tuple_tag;
    struct random_access_traversal_tag;

    namespace extension
    {
        template<typename T>
        struct category_of_impl;

        template<>
        struct category_of_impl<std_tuple_tag>
        {
            template<typename T>
            struct apply
            {
                typedef random_access_traversal_tag type;
            };
        };
    }
}}

#endif

/* category_of_impl.hpp
VBeujG2iunBV0kbqwtUxj+rCl2KbqC58OWkjdeGamEd14drYJqoL18U2PevC9bGtrgs8L+7ZNPLczETqYQXd2ats9Dl4Xwv0innr6HMFvq65uIv3k6cYlQvzG4Rj5zhb5Xj+xphj8Mf8pohj4AfffFPznM5EkUwjjm8pG39IiHlwj/vv1u9ETN6t3/VY/G69OeLybr0lYul36/cCO32v7a0pht/sdG604vrMrtsDncsLZ0Yrpr9p/kDpFA/0H1pddpqT/iOlo6ryudGxzrEjT3eEXJoD+e3O3hzhYG857MpZdUp/+/mp0oeU/c+sbtyh7X8OXc2E8Lw06/jlOOntJ/2FYjU1N3e36BiWsH6P1bO8QrcAjdeobv8y1mlEWNxIMRv1/9712Jhzwin8X4U2tWk+G9rX6XoJty88ZuZ/zO6LmSHYGx6yTpv0+wM9q42T/rtAn6xNk/5AoLdg//tQnxjnveCiyyWKqFMPRQwXKSLNDwd8bQdzulo/vK/wLel/DHX485FA1/78U8TEn3+OmPjz0ZDBn3/xdefPx3zd+fNxX3f+fCLU4c8nA1378ymfRf58WnFTB119fibS4/r8bGQT1+e/hjbw/98CXfv/7xET//8jYuL/f4YM/v+Xrzv//9vXnf//4+vO/8+FOvy/wSa+rv2/oc8i/z8v4KY+8/nR0McnCrey7UZO41tG3PnRopussbaxaCaZ/PwmVpsyRwn0jc+d3cf6pp6em2Rw2jeDXsPdL67DQ942T3AqLPAtenDzP+Iv7MHn4fktE5wKFXyrBCcPgL8owckb4C+OODoO8K2TXPK3TZJL/l6S5JK/bZNc8rddguv8vTTBdf62DzkaqeU7JLnk72VJLvnbMcklfzslueTv5Qmu87dzglP+0HZ2cTzvzKWMsb6r1rmpkL6b1jki0nfXOkXA+h5WX1U1//XNsul6RaBXZlpT62bPmTUX7XFP8HqWu/fQXqJZF5O+t+icUuj7iM4uRdj7il7kgLRXaq2e0fP7+Zq7/2j/QKcEgh0QMEoo2IEB48QyOyjB5uG5gwNGiQabFTByPdjsgKFTpbz1+azIAj0zJ9C1Pw/xmXsHzPV1kwT26aGiG41tDxNtLfxG+jzW6fCqZnfKzfEeDl0WJI+vo4164EcIxxgTHD44UvGZU80vqta0u0/pVWCNelbVaXm10tkBrL9G6ZR52L9W6/D/VkY/Cvp0/RD6u9/9PZeemy9/2yEB+W3A6eQK0gadVuuz8ZagtWt9lUNmyTtugdIPPYR0CmOh6K5NLRINWWXbIdFdGzlatCKblKdjnHYI2SyWv02auAyWiMZjG5NhWz7DlmXVuikgbHLgsl2aZJXpRpPzOWJ5Yyabrhe3CrF+LOt0HKQu11Glow8mvax0Xa5jStftapnVdZ2C35aD6fI8TjRzxRFrK1jDMI+1laLNmQe714nmxhrHQzt1VaM9NdNq2TntEwp9xVhpeLA0SCehLSv3LyzJfeMnprmbb3h9mpsvJJyWiuELhkbKxY8/+3v4JK0VHoGPqkZfWBoujfYvpgtIymrubzxi8o25FjG5h7UeMJqDAssCpufrJwKm5+snA4aziTumoxm2Z5auStqsqU51+T3RCDnWvZ0c6Hrue3XA+FsPp2kqZLlLU9OmaTq2QZqYNxUvL5s/Nlry749pJbhdGzgTMUo6tfdTDFu0pH/AnS+Nv91KO+i50vXcVEfpfJJknfSu0vXenjXQZVUc5gu1blR9Pspay+jzBWvrrEYfQTjs00TDikS2fYPVeTUiaadD03sRzjDa0GCpv5K4x++NYP5dhszOBNOXJNr8ngUWhnc29NTdhm8CcxcAoj2/Gbr+TK0=
*/