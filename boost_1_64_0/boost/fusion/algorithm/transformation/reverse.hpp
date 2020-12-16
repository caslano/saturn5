/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REVERSE_07212005_1230)
#define FUSION_REVERSE_07212005_1230

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/reverse_view/reverse_view.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct reverse
        {
            typedef reverse_view<Sequence> type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        enable_if<
            traits::is_sequence<Sequence>
          , reverse_view<Sequence const>
        >::type
    reverse(Sequence const& view)
    {
        return reverse_view<Sequence const>(view);
    }
}}

#endif


/* reverse.hpp
Zv+oTeiMWGGhUxyEgvFn8e5pcXGK0mv0lSK1MJ+vFP9HGO5e/vYd7Gz2tdlMmk5/+0L2lxL7jOWi7kXcSeY6e5nWj1jo1SpsMD4Mci8ok+Dr7MtiRwrSD0lAtmp1IoAd8ghvAVt8/Vaq8SxAg41VsvZ+ovS5icgVWvsuCGwjj+Zm2aiey0HaeEJsHCZty4ZcqdWjADZ6tqNp2j3V99XZsia/s0TqhLxDXa8x6/Xvdyoab2N+7VjWun8i+fsrchU21TakpyL4PUSM/WwMPCXS98wS/xR5b3BavJsG3kMoTu1F4yTj/u1wXxfrPrG+0JCvEHyujH2i8Z7ZulrVFWg36tT7TJaGtNY+UH25sau5v9vOtZlG3QYfqlDOb0a3ZZ8XEW7O9w6udfrrDslvs7H8bhOd3SW/kUi91j4MOiua0D4kv1K3PHH0flIbusl5TXLm8Vx4NXYe0el2leV6bWi0rWh7sf17JXFlLzY539jPZ63I37dP7b/zgLudlBSqd0Jd/XRJWJouLrttGc48Llbv/td4yrrY+B7WXkprkrynJyG7tPvr8VspTijkG1plFw/sZr6jr/bY6tT7gT3cBD+w7e79CMLrumxZOfSdqZ88mvhgz5I5RYH9wKz9t0L3D7P2PwvdD8zaz+yH8w8L1Q/M2p/sv8c/7GK3f9jtZ7addOrO5alL7si5YMhzo/Y1zT+M9iXjOOLjY/Ar+VD8J/4CE+BHcCL8GJ4G/6o/K1HSWW6RzjeyzvXfMF3WOS/WAJfAttCTjoyBwByLdD6Rsyg/hRnwc7gEfgGXwi/1Z9o1kE6nNp50OsMMeLLYcQpcCrtAj7+UfPfLM9tp8Jf6jZTPs3AM/K3oL0J2SLzdiNNwhucjss71URgND8NY+BhMg0fgAvgEXAx/Cavgk3A7fApeA59W687le1m+o536deeG/QJscAmMgUthCsyGa+ByWAHPEn1nwxthLrwF5sOn4Qr4LLTDN+FK+C1cBdugfw2MgCUwEZbBZFgOl8NKWAjXwSJ4LvSUt3xHw1iL8n5f/JM+EPv/pPyAEIm3DHEa/IA2yX4Nl8Ih8DKYCLdIPd4Kp8HL4Tx4BVwEt8EseKW+XomeeIt6dYb4L6XBvnAOHAjnSv2Yp/yg5JsUTkecBj+ovtS/brAf7AX7wxg4AMbBgXAaHKSrp05Jr5tFuWWIX98CGA4zocTjGzBweddLeb8j5f2uLl6dxEuxiPeK7HPwKkyAv1fx5DsKTrSI96a0i2MwEb4FVf4k3jCLeHVS7kehDb6oi1cj8TpbxNvBdRp3wk7waolXg9RKvE8kXiS8VuLtFX03Sj5rYCy8Rey+FS6HP4WVcB/cAG+DF8D9cCc8AG+FB+E+eAjuh7fDh+Ed8DC8E/4O3gX/Cmv1/W5h4PqYKnZOk/o4XerjDKmPM/X3xR64fIe08aQzFNpgtL5/tAeudz24rgPsCcNhlL6+NqCvm+iLEH2RUN1PidfdIt4uqefXwUh4veTvOHJE4i2Q/lErj2MSr5fUuwFwOBwIx8JBcBG0waVwKMyHw6ATDofXwhFy/2LgITgSPglHw7fhGFgPx8K/wXHwCxgHv4LxchZsAjwVjoc9YRIcAJNhEkyBKXAinApPg2lwMpwLp6h9GuQ9GE5CnIZ9GkZIvxIDh8KRMAmOgp25sOgTzn77pF1Qfo9V5wfh+7jf5/8YfV+rD2QoPpAz7/tx+kEW3tc0X8gq4m3S4tz3/+kTmX6wZfwib6R9HkGOIxGftgubgOQh25CHkWNI+884QxTJRKqQ3cgR5DgS8Tlr/5FCZAvyAHIMCfuCcz6R9C9a/SV/yPn/hKrmz/9rc/k23X79B2Uu/wDsB28=
*/