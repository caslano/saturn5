/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_CATEGORY_OF_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_CATEGORY_OF_IMPL_01062013_1700

#include <boost/config/no_tr1/utility.hpp>

namespace boost { namespace fusion { 

    struct std_array_tag;
    struct random_access_traversal_tag;

    namespace extension
    {
        template<typename T>
        struct category_of_impl;

        template<>
        struct category_of_impl<std_array_tag>
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
x9ODZlxfOYNj+LhWHxzvBD4cezqBDNa3dprreE5zsOl4Tg3GJoGPpfFsvSWpz5AbW3OZWrHUcrdyLIGPo/H+4jZutV2ltMYx9VsVK27ZgnqZYLrxoF5E2bNQHnudfDpnJ5KFzLqZwgb2YC6dT2eTaVEn6y3ZgYRq+fQiZUdh0E4m+vpWSyTXAkVmICeka2RWX8NCe6L57ECuP9En7YrW9A2sx3ZE85nsuom+TOpXNcmBdbIFMeatZtg9KOyOkpPVkZSw+TqwmWxac2A1e2C1NdPJgp1NF+xcopCGrLKF3ECfnc4mVutLQ55k269q+xPr26slsqn1MqkC+WvcX9Wn8slBu5BYnWye4Fe16By7ty+xeh78vCHYPy7bn5vS+rWYFId88Zsy4ZeDovySGYh0C/rk13T5Avgj0TeQTdvrDvSt05/m+vXH6Wzq52TrOGxrgWzVMX+PqagKWyrSXngcaWtyoD/Tn1g9TaydgSL3bUD2BbklelbLFHLptdfJ5NLcXscNx7f7MqvlEjlKY8Ign4eSZFfPJvrT+czqWUiG2teUQV02Ab01baeh5BsMDmSyBc5vFytc5kIOmngqvdo6q6cShYTFug7lh97fm86BAcrGnL1uOpfPDGShHa8pjnogr2gO44znxzNZxidEPJXuSxfSKVuYaPels6sX1gAbNb9uQTSg1RODPgXVBRtd2GAwjX0quZrsfz9j3Exff7qwxkDKzovqzcPQQ31PmJ3PbJiWYy8ZDTGgdGvYFCe3bkKOUwE+vYbmJgxwq0G6ydX6BpJrybS1DeRP5SuNL72kwsc18d7cQL+9TrY/kYUsUuSzzrydSxcSmaydGBxMDfTDX9IXU5pxkuiDgXwBHJ/LrCvb5ZyGHelEYU27sMY62bVsdBKO9+Oif/sS+TzWg0hb44PQniA2MZ/moB/OxP1wXeiHOachplNest5co9zMtqtO0y2lnBG35njUB39NQf1PnE/ntvxzx/XV3HGc6Rp8rQqn4E/NY/j303V5/jIVzVU9e6RYdSvbWgLbEPe/2zagjWK525Lz5gkJg5PnqLoe2Qi0Uyptj7WaNR6OrUPGXGcXy6uXtiiWy02YAdebxVHH3qZB0+IwDqatFjVf+4NpLKzOyf3JBFRsJpvsWydF9fZnr/+ntiaYfmxx7QvHc/C8KmeNN73gU8sP1RtOzYMrupJDf3qVxYbbbqW8WPeY7jFdI4tt5fV0dS+juG2WXnIxb7Ni0ykvVnaG26PMi/miTrPsbDXE8dZNDhXq9Yo31J+HP7uXHNPdNaZnKcEMu7WhNepea/2llxzaBn6lypj0+tDmejidMWOG4D/Ol0szVGpu22jVh+DyXvzs0nBpjLj2Gf677RmqAwl1U2y5pTGN8rAYI8aiPBbL/G25zPk3piVd49ZKlXbZ+VuT5jThHgT7oFPqnO5v0L+3qKTWstTAYDqbz/eJSa0YG/sy2bUATeUH7PUy2SV6DEVhjVw6kcobSHbATm0Ao1omacN5J5NNG9xgJglHBOdTmdxKQ3NDicwiqTKVXa+FBbM+4zan3fibfhyquMNDQ05tVIyGi3Xb3UNz61L8znz/SHZAihzWW2LOxbYuL9m1XNeci63uif/1wm/bORer1Sv10brhiPwGeeVK/BdO0gk4D2VTdj/8oWwGWswHU5lEFv60k7mCOC+vk0ujm9Mw0UgmCsLD62QzyYGU+MtWf/anynMuNgC/FE5cBMd/bOjOuVgJmsPvHUIShb7+3qRsIH8goo4xd3L5ocFmfbRZrM7Z61Ycb84Ft1l26YWG1nNr5frWHvT7r6TNa7ktbwjm0L3r51NrDS05Zukx3TKhoXZ17t9OjFLo7lI=
*/