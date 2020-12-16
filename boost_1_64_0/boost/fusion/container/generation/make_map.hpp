/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MAKE_MAP_07222005_1247)
#define FUSION_MAKE_MAP_07222005_1247

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/map.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_MAP)
# include <boost/fusion/container/generation/detail/pp_make_map.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/fusion/support/pair.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename ...Key>
        struct make_map
        {
            template <typename ...T>
            struct apply
            {
                typedef map<
                    fusion::pair<
                        Key
                      , typename detail::as_fusion_element<T>::type
                    >...>
                type;
            };
        };
    }

    template <typename ...Key, typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<
        fusion::pair<
            Key
          , typename detail::as_fusion_element<T>::type
        >...>
    make_map(T const&... arg)
    {
        typedef map<
            fusion::pair<
                Key
              , typename detail::as_fusion_element<T>::type
            >...>
        result_type;

        return result_type(arg...);
    }
 }}

#endif
#endif

/* make_map.hpp
nkQTx6VcS9WwPvpiO6yJfdEPB2BtHI91MA/r423YAJegP67FKx11ivIdQL4blOvqFHG2Ynv0xQ6aNtcSWe82ffwhaYOqjS2xLbbCSAzEW7A1zsA2qOZDPrfRapCPYNl/Z8zD7pKPwmryWSyf0eVoa3OV74zhbL819sVueB1GYyTejAPQggPxXozGpTgI1+NgfA1jcC9ej1/hULyIw7AR+4rFIByBfTAOs3AUbsLR+COOQaorTfE4DsfiUhyHn2MyhnLgZvw73opzMBsXYQ5uQgvuxSl4FnNRadO3YkvMx044FfviNJyKBbgJp2M5zsD2lNs92BfvxeF4H47G+3ESzsGZ+AAuxLn4FM7DrTgfT9vuK/I5KJ+P5diK5CPnY5G8Lx7CDrgUr8FlGIfL0YwrcAY+ig9iEa7CJ/B1fBI/xZX4M65CZd9rsDUWYyiuxQG4Dkfh05iC63EyPoOzcAM+hM/iGizBrbgJj+FmbCptfMPwBZyFW3AevohP4kv4T9yKu/BlVNuQ5HMIx8n9QtuG1F7uRx2wNXbC3hiMw7AzJmMXzMeuOAdD8BUMxXLsgW3Zfk+8EcNwiQmlbn6HLqZXOfWq+rheF5h3EP3DfV3qu7vwuiDKhzprTVwvbUwvXTyvaJZPI80mFZFKSQdJ5SR/LrYuff+/6nT/0P7/lsmpeX3U/9MX9rKf/6/0ce/YXf0yVcMUNyxqTB9tgD/b34925D4zTft3CRAo8f8e9yD+X8k21/h/6pYkAKAHv9Xt36PC/wvj/xk//8ld36qqf6+rarzAA8OV+TVeW/pSev13iprXGn9k7ZQrj9njBcq5kHMUWM3183qGtGH/HYPxdgzHWTgY78RheBdaWXdBDG01pEKDZ4JongcibYCu7X9+zmd9SBuftO/pnuMRL217MZHqvUn/XI7tpBJNu10CaTFJ30aXSNI+R0NiFMrzMFyfg5HgbHPTt7dpn28hz7bQPcPC8Hn5zna0WAxA+7MoVlziGRQh8nwJ+3Ml9sT8f90rvZN38k7eyTt5J+/knbyTd/pfn/7Y9n/5/c+P5ywGY6mt/5ff/v+Qpv0/oLr8hq+htnUOw8hQXj+l/G6USoA0s5Ihj9q1lPG8U9e6jrG2qI07SvtlH237WwkrMI8GFWc710u2eanmXKtzLOxSW7sLbewp6rwFjvFwEzNTJuUZjqVrwLwwzXjdJrwOd2yLsAEMLNa2kVk04xCVMbBbsBllU48DWbmG45G22BjtNlhc08Yo8ycoIQPs46cd5Rwk7dYzq6nlPA0HUs6z12nK2ZztUs4JlZTzZ09rylnag392lF+etIeSL2ljNskxWHC1ulyGJd2cqz0n+nKNdJyTgl4hfWW8sKZcG2rLhPM7ISNH2vs051w3rvaMlMVR6Zf+CSmaskherymLiUqHk8rHUSrl0P0Z13KIM7jeEgyuo2QPriM5Fu3xufSx8Jef6NHSLnwdDlbO6zOaY5lktobQw2JStjk3z4P3kNv3jMH5na07Bjk/+utezqGaB/t1EOnYnuRN29bJvlk/JU+WjcNfZdnsiTl52nJ9VObrz7OPdDxZIdf8IxijnOcSTdkouzZ5dp6/2eg4z5In7XE57xkJrvcWD94bzmvCcunydHdtO+pE/aSfQBe5n3bEoRyz5TndMSvRK5LkfHh4/Hc/f+nrvIkcu1GZJOvLRI5/s219JVKB8fHL8WrPseN98qM6Lys1xeJy3iNknHZoLbUMOmGsUgYvaMpgqjk3Y+L0SvvOKMcd8YrrcZcYvDe2GJzfUuada6W2z+fkmqUvjfN+aDvrsv4ex/ycfKvMO+haFo73kk+gfT9K1ym55gw+f0J08SKiNfEi5Pw=
*/