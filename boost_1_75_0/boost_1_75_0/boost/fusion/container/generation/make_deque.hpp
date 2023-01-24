/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MAKE_DEQUE_01272013_1401)
#define FUSION_MAKE_DEQUE_01272013_1401

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/deque.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
# include <boost/fusion/container/generation/detail/pp_make_deque.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic interface
///////////////////////////////////////////////////////////////////////////////

#include <boost/fusion/support/detail/as_fusion_element.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename ...T>
        struct make_deque
        {
            typedef deque<typename detail::as_fusion_element<T>::type...> type;
        };
    }

    template <typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<typename detail::as_fusion_element<T>::type...>
    make_deque(T const&... arg)
    {
        return deque<typename detail::as_fusion_element<T>::type...>(arg...);
    }
 }}

#endif
#endif


/* make_deque.hpp
tnF8afq7hRn/3OTH4sphuLHUMLM94N9x+EPVaZtGJJ/aPfWoMuqjiJv39C0J3qm5s6ZnbW96Ly0evHH/DGIeW//d0HuehoMWbGY4flQz3ii9ZGmRqpYe0d6QvTkGTe2VpE2ZHDfHMIDY/xE9aIrvtaITdejvc5Ky+J6V5uhUE3gbVCch7CjWavzKUPF2/voBf3LPKA/VWlLXTvlAUH3qsRH2iHTLsDrglszsqtFanlb5A2w5zRov4oofk1tzTL3RzhlrmnKMhZxcuWAIr7r44o+5sOVka87Nx3bDHonv6dRiQulSJpeV60+QKAba9oOqQDHQ1UHl58w0XbS5cnXmfU+FlLILswVXSMortdIThZQVladolZ/7WxtmXcI31UeGQYILZWHJg3w1E6fXUw7zTuIAvY3nMJGn38p6QRHKsJ39M4kU3zzXn0dWi0zc2DrBi1ybO0MkZQKkv5j19ypKmh9Hc9MbzKTijf4qEkJfw5REelzVAhZCF2QmBfzcz/CSI+jOusCjrEC8aUKEOUamnHCjF5L1kfd70jz76qWqgX3uvqn7Pomkqqbt9fH9LXf2b4JjbHQLRy4XPUc+3O0fzdbKVmYVw6yXX9rGfiuWePv1S7F3/Ku2Pr5RCgttReYrBxlOeteFUxvKhuJFccMG39oRDbqYV1uO3D9LT1NZWZ7rz1z/sx6gRUmpTCP4ZvLTY4drHxXmfEfx7BX8
*/