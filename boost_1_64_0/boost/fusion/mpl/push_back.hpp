/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PUSH_BACK_10022005_1647)
#define FUSION_PUSH_BACK_10022005_1647

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/push_back.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct push_back_impl;

    template <>
    struct push_back_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename T>
        struct apply
        {
            typedef typename
                fusion::result_of::push_back<Sequence, T>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* push_back.hpp
85L3SlBn71I8r7MugsDrgb2kX87VDzfKc7UF6gLxkMKcyWdbjh9w2ff3Ectx3SQ6ZyPvXsjirQ1Oqjk3lCcNGWp/+fstR3Rd1sdQngMrW++jQR5kw9rlA55H71UgP3lneJKOes6M8cmPAVdPmWF/xbMZT9/b2pPf0kfJxIc5UXzrMfbXyW9P+iEhelVInCn6uOZ42fm8JnD75Bn8sODYp87QVz+R4tg3ANmXarl4+w/90HL8EU7xvkOAI+eC3Cc17tq90VlLfG2rqKMUzz920IM/LIX7oY8GIXFmUnGUO2KIteBzmON1vw8d+zBjQgfX4YOS6Q9UW/NZVcXJLu/2pyTPlrf3aYmHyzv5Gc1BeaU8N78WOH5Drz/1Rk9gkTzYr/c1pFWvOSw+pL3cWSWPUer8w16Y61zF4OS/HuKstVSsJMjBnLYOH9U3Ury4E3b5LHMap8ZPnpSgdFAXQd5w4M93IL+Jb6V4PrYIuQ2u7AV+D/w7hgeb4dZJWoazr92QQ3t9N/WdtQm6sAmCXLgnyaHGdblnuZh/HRG+u+9Znp6DOf+x4dp5GOX6fopr52Jwe0GudyD6czG4q2z8X7gNZ8XyuLWT5sP/6WohdwLj2w+Yl6wt8RoF8fjcjeD5t4wxNwGzb1Htkc3N2Ml0+U5AZy+Y5g27p9tsm00aHHoPGfekHF7neY+WxKwtX1PpD4yc6BMXUjwlB+yZy0iOj++gTpk3eVnLYzc357l3Bcvz1cNr2+f68vlXXd0W5LiZmNM0HOw130C82JcPHBxWVGMp3x2TycebUuvQySxu7EEbwB8SkBNvyeJ+AcvhZhVjXShPNK8Y7y8c83BchI20ZbSr4QhDTZ4j8/KDl3r7e9ekA6NtiP7wvFQaMd6H7lwkncZJOYaznRTi+XJh34XlaCNOrKfGlquNOeJizLqo4VqjTr7pm8nX7zxtG5427tBXLxbmuSUv5gHDMUbeMuoyyNXvq/UsR64juS8YnjYKob+Wh/lMresubnh+vBd3Soc5g2Vxt3fBcLQhCl+C0U8d72x+PoWH/CcmL2WH8Fx9CcPLbKM9yzVttH1Jwwm20cSlDC/YRruWF2yjrUsbnmmj2oThmDaauIzhqDaCXFOeB4u5zhac4OVuoXjaIpZ75C0Pr9Cgz93ScMyZ016A00mdtd2zHHVHRO9WFqeyJfslwRuFeSgb6irMg4ah7m8d5g1om05bpDf5wVj//eV8lcNV4UGUZ6c9zw1LoTXbZpzfPRcbM4cS84x21Lj91h3YX7dlTnI2DevOOzDmAyXm+9wdmZO8xwLsLgJzgTAZK5xlLA5U8b7GwofOT9gSeUtu4e48wu81/E6HSDqcz97Za0W/4yCBqKPJR3psabFciaNxPekn7j0qgPsIvNS7QsXzSLnjd75AOgn/nuQ4UwcU5hTmFKe3QbXa7bqOwJyx5SAv+G3mBceFYmLtXYcsAod5GCeCfGpVzyHzn7CNFadF3bXeUOSzfXfP8frjd231ENddiHF/oL4BG2TR/95qU9Ldc8mH0E3gG710fYKzxJx0fYJzlDnp+gTnmOGYvLbuxZx0fSFefu+Y4/tJH/V4n/h3vxs/cuEnH8MuVZzuxlBIAR+M4pDRT67rnMhn674WT+czVhzaxwaG6BP3kxxWHpQHuN0KCJ8lOHIbIPtndiXu6pyHTe63gpPWj4kGY76o7rFDt2EPnGaI01lXnG3mJDVh9grteI6XwVGdF4LqhTl7lkMF2hjIM/v5puV0aUgiCu9rthzf6bgXdvsiHhDg9+PnSlZQRsuJh1TBGac4A5SROfllwzFlbBqOLePIcPYv49jwbRnzxw0HZcQ9DQnHTfbyjLX43X8=
*/