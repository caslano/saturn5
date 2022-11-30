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
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
*/