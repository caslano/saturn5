/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_DETAIL_AT_IMPL_02042013_0821)
#define BOOST_FUSION_MAP_DETAIL_AT_IMPL_02042013_0821

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/utility/declval.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename Tag>
        struct at_impl;

        template <>
        struct at_impl<map_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef mpl::int_<N::value> index;
                typedef
                    decltype(boost::declval<Sequence>().get(index()))
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& m)
                {
                    return m.get(index());
                }
            };

            template <typename Sequence, typename N>
            struct apply<Sequence const, N>
            {
                typedef mpl::int_<N::value> index;
                typedef
                    decltype(boost::declval<Sequence const>().get(index()))
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence const& m)
                {
                    return m.get(index());
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
lm+Aw7AhRqMBV2Fj/Cc2xffxDvwUm8v3vQX+gC1xFxnMaUk7DMIRwlWC8U7aORBWEPIJVwhKW5N42pjkEDYSbN9Bb6A9STBB2p7YtTvJIVwK1LY/8W5V3AbFgAHYndCevyNU761PJGQRVhB2WNuoEFqVtFO5wGfvnixLGElIl3YrK1HdbiWPzwHSfiVT2rAUEnL42y2Y6WjAPXiY0D+Y6XiF4NNG28YljzCSvw9iLKYTzgaTLkHd7uWwtH25qmr/0pngZ2RdoYkQaKR82B0jCImELEIe444QlDYyRZiPPr0oJ+GEMi9eREubmVxpN3Oe4BVCmkyLZVrVtqTNZ6UtTUBb8k2IJcwgLJa2NUq7moPYP4S48Twhgr+zCEpbG48g0iasDClpd7MjhPITwoMoP+F8iLYNTjbjwvjbti1OrrIs4SDhCp+9+7AM4QSfe0sbHbd25A13EAoIPnz2J1ja7nj1LWm/M0OZV6cdTwGfCwmXCF7t2daMyyMcIVxQtfPpjqGERIIfn5er2v2MJMyQ9j97Cer2PwV8voJX0Kc/ZelAHSIYCcGKjItCEyGcvzMJywlZfN6BRwjL+du3Hu3LCCMJmYSVhD2EU4QrBL/6tA8iRBBm1He1sXENrsE1uAbX4Bpcg2twDX/+4EG494+8/x+TFJceH5mYMMHcBOCG2wBUbkQclvd5yzWWe+S+wmjCCwFunGNZ7yuEDAjr32d4pDkPseXpB9vSX/cmPgx1l65pVfdwxjQ3369Ksb2Xtkvy0lry0oKwW7kv29ZhXrhpU/a9R7lHJmlKXiTdXpIupy3W12JWJFQnvEikWY7TnRSXbukTvOx37ynpe8m6sE2/h6S/w0H6Lyn3jUpJn5tzN5R2X0vZb7FPe4+y/fXTjk2JlLjK8e7O0vIwUPKw10EeXiYPhfp5UEJ0WnJb3q2YGp1Ujncglmc7dPawz8crSuUK0s2Hcov/htKWdUBfRI7XgUE/7bSbuQ4s38Ecuac+mVCPMJHwqvIddJwPbmSWvT+op+6jXNKNNDd5YJrmXvGExJSYyZHFLU3Ir/WesfRjLP3+S7/BpX6nDXJfviGhCqEBYR/lKHBcjrTr+U5r0pfx3rjPfE9VorP9rjvI12tKHWvnOF/Oftdt81RT8vRPuc9LVJrvf6infX5eJz9Gnfxc7/dfb129Ys6XNUrNNiyUvNUnVJb6+E/yFqWft4mJ0ZPSbiRfsr64/6CMN0en+Z4u9rJfX2+Qp+U6ebqRfZVt3ppI3vLN60wbbRxdZxO1Jq+Ble3X36EAltfPq9LoiAqXaf4O3sh6lO0r311rjJrvwt7K9uvyLfJXpJM/Z/e3etv2JWlDQ1Sa70J4Fcfry9BePz9TlH3SpPT4m7euiqO0/X3wuNVxvQvTyduN/D6UXu/SdOvdJemzx3GbBL177nptMG5e3+jOtjlx3HZFr42E832+O9sn+8wYcz63Ndjc51rzQ0n/fjlw8fg2txa3VejvJsfqcgwfxh+VsDvBTe6N1ZR7Y+3lnlh3bILD5N7YaPS33ruT421sLfGp7901l/gCsAUSrMtlyXK3OVhuFpMr4mysjnPU9wpLWW6FLPeoLPeYarn8UpabIcs9IMvNVC1XWMpyS2S5pbLcMutyDEH6y2XIclNkuanqe+qlLDdflsuR5Rao7vEGy3KTZTn1Pd4acg+0JnaUe6M95N7oAKwt98bryD3RujgR66nu2RdI/A0lfus9Xmk7UUXaTvjiKGyAo63LM7TTX36yLJ8oyyfJ8smq5Y2lLB8qyw+W5YfI8kNVy0fJ8vVledt71JXlHvXt2F7WVwfV8stLST9G0o+V9OMk/Ymq5fNLSb+zpN9F0u8=
*/