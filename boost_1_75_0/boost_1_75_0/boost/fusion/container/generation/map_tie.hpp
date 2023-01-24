/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MAP_TIE_07222005_1247)
#define FUSION_MAP_TIE_07222005_1247

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/map.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_MAP)
# include <boost/fusion/container/generation/detail/pp_map_tie.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/support/pair.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename ...Key>
        struct map_tie
        {
            template <typename ...T>
            struct apply
            {
                typedef map<fusion::pair<Key, T&>...> type;
            };
        };
    }

    template <typename ...Key, typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair<Key, T&>...>
    map_tie(T&... arg)
    {
        typedef map<fusion::pair<Key, T&>...> result_type;
        return result_type(arg...);
    }
 }}

#endif
#endif

/* map_tie.hpp
yNz0Q8nz6+bvxvQqjwpLF/TJX9wN1f4wExh+zO06Z7x3kyczVNGoVXfvcOFiR3mPAv5TNV2jOQRcoJ7gXPDwaKfJnKcoQWMmLlpjQ8txJM4LRYOq/LDOoXStXNXWN3kl+rwi+Zeen9WjiP5UK4R9jfH35p1snd9xjZ9B3rnDdjGVde11EJi/70fPUO7NEJUR4GPRjoI00LgeZjwCnUq9ZbOtPkWgODR8+4mSU01nSbCiTGepvxI/z8rkqWMuV8rGzBwz9o8OxWUyOqxcjjAw9uT9c0QV10L8lk8jDV+2TE1oTolieurzgPcoGOPcWUCTnA7F3stoxLMcrkGBV1YGrUyMRxzZcd2zk/efQ7dzNWZvvGce/Ac5mExu57hluLaaInZn1d6jzZc+LtzxHly4JzLIQcYhevC2BPlNf5ko35MAcrhpXtPa00JERJy+mbFXML4Rl+XDoOJRketoqF4Sil+GbBZXSUV+mEbPPcGzcEhX2jz1/YrD8PCIvTLvwUqqSNf06hxTi0qfKrthoyN6oCWvnOvGDQIyps9u0AiuQ/IW0wbKEwYY6IseibfEfO5yZKCXM6k7PqDre8DdWZjvMjH3Kc4UdW/lYuwPNPcfndwbCPby6eUq0nBMkpHgs+C+xWFCJVa+lMBYH1CWlC6Rp4GeCqHFagWaVwQEmpc6BzL56Nw+u3GoIH3t0pBq9N18uonWZw3ocxl15Q3G
*/