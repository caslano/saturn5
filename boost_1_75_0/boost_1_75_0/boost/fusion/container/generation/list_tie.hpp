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
uaB1rK7Ilu+6Gv2/rGmKePOKR4PN15Gd0LssZUemsoVtCMv0OKn26q9Oe33n8BxoWMec6NMWlPtQKSsl/Ff2y9HGpuyT3THl7Ft9de9pdqPEbGPfkCddWMpNV7ZmKnGycjDdsh5uQGE1VrOTCz/m8h+JQPkqRtEbm3dkrmE2WTMjWNW1yTtPe0lXyK4cZudsBMMBQ+d6hoB1xYhyGJQnlXWjP8vLel26E/pYzQq3hj6e3YN9TIA+uqLZVxveWxPOmYmV4O6KffUaJ/9klipt8NCWULnxMIvrweIYOLlsppPemD8/hk1ulzmNYD7sbOc9IKs/NB6VjKJIyejASrOUVlcJSpG5nJzY6xFYnK2kF0lKkTS+uTNBBCx8I6jYYqOOdqwJEzTB8NUQzs40m2dUE80ax+lIkSC9iqA06b0ECIr0JiC9iXSQLr2E3osKShEIRcCCIKIgLyUUAaX3Kl0h9ACBhJBkb957z/0wO8/O/s//+Z1nds/Mfhj34cg8/dNpezIE9oO9K/qP80ey3/lC5+nJrVMkh92YJ5YWt6A/n8G4X/CeKx1loNApLGIsW+aockGmB/+4Xkir0Zlma1wdDrWJox8qrMRGp0etE7wOPIIMfwzLkQ4qXxsdfGl/mUyFv+feep4yA5PnLPOt/vIGZsKIfsyA3muf30P7CC2WGfWOvlPxaXTQzxOt5nZPjVatGjJLZRGxgX177HxL
*/