/*=============================================================================
    Copyright (c) 2005-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_BEGIN_IMPL_02042013_0857)
#define BOOST_FUSION_MAP_BEGIN_IMPL_02042013_0857

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/map_iterator.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template<typename T>
        struct begin_impl;

        template<>
        struct begin_impl<map_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef map_iterator<Sequence, 0> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return type(seq);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
biXpSJ/kkSYqlHW9N7XUJ8mnB+4wlykhLTIuOTYhOtncf/kM1vlIJp5g+lUlfVlP3hIH85s/m+sggXVi/uxl7cvdpJTNHDpK+XzkufyJ8rxPNOGoUmeLv48pkyNjuEY3IZqtqTzkXeYz+dWl3sh2K7XP9ndIh2ehTao+PFD6YS/ZvhJXclxmunbbFFIms7dQPvEN4vSuIXlX9TUfX2qeq4LSsIHlVJ8jlM9SPy/VKq6foUOCjG4ybo91XNvOlnFbSsZ1soybVDKuo2Xc/prWcUGWcWNKxpEG+WBcA+u4TubPj9SwfO5oXtcmm3Wd6WBdZ1nXa3JGkozLsdZFqqK1fqq+SzrbpLpsE3mm2LotdzYzx2UiUes2H9tcuz/pXMq2DJdn8qdJekw2708Kasu2NHfLUnafENr6Fy1lUJdLm+4JSXebpLtF0i26XdJVuqJw4t0nsi0S+LPMtI/Ij+CBCrTTwX34GmkvryZp80MYHVv2/tPRvjKcz6ZK2vc8RFm3G+MSHbxzRaceaLd5Mp8pl6oOONq2Sp//wbcVf3+erKct9y55Pn+nlHsb7qXcxiqWck9NTUiPu+5y+3vLuyxsy824RBkXWM5yG2zK7V8SV5l1ulCe+18gxwP3yfGAoaG5nGkJkzgakLq1p4zjgVzV8cADBvvfynzNerCtd1I+TZmlPyWd38oAJ44TotTHCbJ8f+v+heWV17DIeyC6GBzXicPSD8FTcjyxRo4nwhpb1xWVtnhdhZdxLPFRE/v1E1Wyfpw+bjCU87hB1qe23Kp7VqYKevcunL9X8L9278vZe1zO3sty9p6V43tfevfWnL9n5ey9JmfvcTl7D6pfHXM8U06O+/jyqTdeO9R66937v+MienFfAXJ+Jedd4Tb9pk8nOUvfBp7St0FxHxBy7iTnVPE2fUCckj4bTmNdPIOt8SPsg2elLerHEp+Xu5wLyTkS+TA/I35V4guqwLVt7ICB2AV7YFdU4umGE7AHTsOemI3BuAHvwmexFx7FEDyFvfEn7Iu3ubOusC4OwN44CAdgKEbiYIzFIbgEw3AjDsPdOBwP4Ag8jiPxUxyF/8LR+DWG4yUci5Uo6z3ohREobX3lfIm4lflt2vrWYr6aWA8bY31sg36yXhrIemmEEWjADGyMS7EJbsGmuB/98Utshl9hc6xBugFYC1tgALbE9ngndsNWOBBbYyi2kfxHucl5kJwfhdu8z2STO+9XwKexEW7HQHwOO+JOjMTncTu+gL/iLlQifRElHTkfUc5T7NN5mPnq4yPYFB/DIFyJXXEV9sDV2BfX4jh8CqNxvaRT6C7nDnIuoaTTRTlGlOsK/5D3H9yFAdgHO2Ffibc/zsGBuAwH4RoMxadxML6IQ/AADsV3MQzP4DD8HIejl1K/sBqOQl8cjU0wHHvjGByAEZiF43A+jsenMRKfxQn4MsbgIYzFd3EinsZJeBHj8QdMwF/xXvwNE/EaJuOtrJMU9EcTGjENh2M63o1TcCJOxRzMxIdxGj6O03EDzsA8nIm78UF8D7PwOM7Cz3A2nsds/B7n4jWch8o92flYB3OwES7AxrgIQ3Ap9sNlsp05F5TzCvIk9Un6pDAPj8p+baXcY1+FDXE1tsK12A3X4d34JMZgLqbgekzHDZb30bjJ+QRuk/Sq4wxJL0vSmyP7z2zsiHOxq/Tl0hdzcLj05RKFCzERF+EcXIzzpY+ZR6SPmfX4EG7BhyU/K93lHEPOPcIJRmV5qeeb5f0bW9Afn8FA3Ibt8Fnshc/hMNwp5X4ep+AunIUv/Ze9e4GLotoDOL4gKpoZvlFRUUlJUdc3PlLMFyUqKSkaBshikIgroFJSYZmRWlFp19Q=
*/