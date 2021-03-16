/*=============================================================================
    Copyright (c) 2001 Doug Gregor
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_IGNORE_07192005_0329)
#define FUSION_IGNORE_07192005_0329

#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion
{
    //  Swallows any assignment (by Doug Gregor)
    namespace detail
    {
        struct swallow_assign
        {
            template<typename T>
            BOOST_FUSION_CONSTEXPR_THIS BOOST_FUSION_GPU_ENABLED
            swallow_assign const&
            operator=(const T&) const
            {
                return *this;
            }
        };
    }

    //  "ignore" allows tuple positions to be ignored when using "tie".
    BOOST_CONSTEXPR_OR_CONST detail::swallow_assign ignore = detail::swallow_assign();
}}

#endif

/* ignore.hpp
ClV8X4+3mBmtUx1BmOEQUYH0le6tqSteYujvwboydaUrewHHCp1bVs4Cj25RobUN4iYBWHvzLnUCDNHtIgzhA1YfB95AlNdRskjFSSTqOqLh9vrGRD3ETitaGMQNdI+RYoQk3cMb7oYzelVIpwac7TNa7mAyPeT1r567DYxoyyID+1BquL8XmgNOlhZTw71g7IlEQ0cj1LsvNVyPwwkI3hxK4ys5OLipN8XK1uMILausZGUjA1uh3WV04bCMttM=
*/