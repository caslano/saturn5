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
7qdR4g8DL1UAxnwN2e3Nj4EUqFFi7JefDvVhVWhBOTO4S16KzVh+8Iec5R2uoPhNA992XK0NMUStpWp7pa5mEOBfrVxqTC5hfksFk9unTlOY74JwjF2smhmhnu03Pvv76kAhH1y7bqm7Xzg0o9NqoU95P88kHHWvPQwvBJkM5hVXz62iQPddpPyyhnXkOGyr4dkos0587E/wcwZ7NyRQEYrB0knnP6ONzvw3zF1GD4YRvRWu8x05h+Wj2qfe9LN4mE8uKDJS8bcjrdHjkm15bfxUY0KDciLhJOmmp5Z9Pil8me/SLKotgV0rZeuA7Ik/L5N5ZkYSSf1qbXWtZMryN7JjauOBYqrxhtEhPBE0WgbAwJqscobvvufcqtoFky2nfAn74MNIX2+ADyBMzAc32HJ08KWfAf1m/3zgdLHr+9QAq/3Q82zqnLbsz3lbif8ToyJJOL06SBFGYeHQME+2eg5IYkR/5bXVnWtaOUAlKLq0vlVpV5UM2MaarTi7f999eRPlTCmxkHtehOK6vTTF2yysOhLlxTWHJEWNKw6KsSDpz9VgOZ1Gi6tYpg==
*/