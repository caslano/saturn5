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
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
*/