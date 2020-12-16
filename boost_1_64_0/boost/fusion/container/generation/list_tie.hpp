/*=============================================================================
    Copyright (c) 2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_LIST_TIE_06182015_0825
#define FUSION_LIST_TIE_06182015_0825

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/list.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_LIST)
# include <boost/fusion/container/generation/detail/pp_list_tie.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic interface
///////////////////////////////////////////////////////////////////////////////

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename ...T>
        struct list_tie
        {
            typedef list<T&...> type;
        };
    }

    template <typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<T&...>
    list_tie(T&... arg)
    {
        return list<T&...>(arg...);
    }
}}

#endif

#endif


/* list_tie.hpp
FezNbN4DOGNoRmHGVIPmXYBNyFyby3jb9sgyqZsoZkPa4nhcpMRcmm0ryM/NNci2HcQrxVtVSLxl9w6AGRITmbdxytDC/OKcLMrK3C5+2Nsc/1hjrttN7ZhTiygXU4yzwLRNtNVIDPSEDN8tw8dk+B4Zdj1nO32bc7bTjz1nO/2tMlwhwwtleEBL2zI7KGXmTa5Hbkz2osxCNPU5RRMLs7Pzrv55amO1xVK/YJTl5styh6rLLczOyOLLRqEZrv6MiG377AxLrD8nVG2vbcE9I8p6grhYrGGYwvsV0guyCyfRjCNlIdfVS81lfV5TFpr4ro6bcj3y1OhZqadr3rt2zvomx95ed/8uPb7T4zvb+M5jiDI+9e60hR3ObKk/rtnPFxOXhq26cnwXSZZjJMdO9brdDfmISWq/GS0xFX1xNN6EY1CZfxl5qMxfLNf9DZXfmcwfqLSZYw+Mw0gchz3xLozCh7AP7sBYPIhxqLQb98NGmIjNcDC2wySMxJuxLw7F0Tgcx+MI2b4QJcvvylv2rwb6y/axLWX1cDw2xnSZbwJ5qMxnlPlqY4rMlyXzzcJmOFvKpRRDcY60ac/DEXi77PcdmI/zsdT1t1/f76Jh+gi5muzoWn9Kb/V6vxJ3k0+RlWt/jxjr9X9JjOMYYDXjq8jmWKBhH8fxwO4+V44JJsQyPZbhsWB34gO2O9Z5jOATp8YIHsVqjLAkzvk7IsP7qjFCGp7GMqzqe33iBSPZI55tIJcrw1hB3k4+SNbGENXKdAlqLJGL2njiLPscrZhweVxh6Ep/MhjSn8+AnEW+PM4gM53HgMvjjUjGrSBr444QprV/B2U847SxR0miNf5I4/9KyBXkTV31+ENPetKTnvR0Q+P/4qlF1yf+3x+g1i8fJDuOJZxd+157LOE4ZnAWm12/GIxrYIfXflzvaa/1uM6T6zvN9Zz9tVyKXMNVo/ZabRe5Uq7LuCbjOuzya680slxzcR1lc/0k1072103Wa6Vcsvm6aBPaXwdx3cM1j+NrnGqycg2jJz3pSU960pOe9KQnPelJT3q6fukGxf/T83JKlAqA3x3/75P4P9bVWduds/j82tvo/s3encBFUfYBHF8VFM9ITX0TFW/ECxQVjQwFlRQVlZKSBIRVSI4VFkXzTbvJ1NR8y6ui1EQzw7Reyw5Ke9PSsvIqLUmtrLR4TdPK7P3Nzn93Z4dZWbLjfd/PzqenrzvM8cwzs7O7z/Ef47Y4d/UIv9/vf+O2UHdtm+7aBt21Fbtre3TX9uuunqXqbcJVrWepahuscZuz+/og+o5W2g5XGPy/1w7naRvc/0P7m5u2N4/a3Txtc9O1t7lpa/PWV3kn7+SdvJN38k7eyTt5p//+6U/6/Z+ZMeHy2/+V5//tbkTb/ydKf86J+dmp1qRc80RTS+YrMZzKbPNt+yNmXEa2mVHjqZNNtr/vpN7ghO3vaeaJKfmZ1iRbd/IsszXdsX65c31lvqytrt8Qzzv/rvwpKSM7w2piCpY+3xfU7eckuS6SlENRkVFrEssodRhvkJdu9rHZ8rPhRlKAjB+bEkr5fO3s856SllZpv3R73/6a/q79/WOc46nzs7CJxDUYYJvH2IjcHMt0WTYQKSfmK4cvffu/UfvD5upi1O2RfI8iNSHFkh5k3chvnPm2jaT3oE+95J0YfpfKu/s83il5zJM89pM8WqXf/1fS7/84ycoyJZo8TuK0OM54TlqlseFkvIXkwZplsa2oxmfYS5lY2OcE/n7VSWUfzlgAXLdKeSv5c8ljoI9xOZad1IwTyTPnp+WoxenJGIXLLc82p6Q8ded8u+Q1RvIaRcpnmbhTmvEZZnNaVfJY0/+35XE=
*/