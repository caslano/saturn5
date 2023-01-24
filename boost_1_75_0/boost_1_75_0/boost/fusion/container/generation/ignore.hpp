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
nrDxTeF5EUyW487kBm8JksjmrV2DVW7zlq0Ee1/QTIJ/49rRYKJBN2mHS8sFMuoMpnC3f2AWBpoNWA6aKE3Q9a9kzUQpaUwDON88k9s3kxpYu7VN4EA9oYrOvYv8ujxDt+cpflDWGs9AzWbphRsbs1na8YMGsmJwwJyowQNm7ucweQ1OGE1u7OC/myI3dmexjw1TbrcsDbUoniOR0/1FLQGKlClnvLIzVSoCu1/thTDVqX4WSf2xObwyi82stXSSQBsPMrF/fRUZ0GcTiAqH3GiURNd83mgylZ3/TTKVabpMZRro2s+SnZUFckonR3vh6nGGHVw9whteNe0BWa7iu8ihYqayHR6ZeXi46Z5KP39fHGI+oua6YCgK+9pm0LwUghRlsdGL7KN7cGGn7ok0+Dr8pN/flEEPMcqg+/q8SRMG7/6zRpO5/f5dg873ArIO9vs0lK/r1xHl6+SOQi95zCpN51tZo+l8FzwPsV8xCJLVJexudt6fjRSArk/DmVc0KKgiXZ/9pEU3HPxz9kA1Oq45Z2W1u4Zk42b/brVZCiIn7iNLG9mjcf8n6wKJRw6X3cNk9XaGkhjFS+vWNgXAix3BxGFX7ooM7KPlvusbl/9f25j8/yBlcDYJ/49pUv8OFQUT/o/a1UAGdtd1jcmW/ramsY7d5uyOj9vP1zSlW7aiAPKkxV9GBvPHc5NPz/703cyj1wjhbgaA4KVY
*/