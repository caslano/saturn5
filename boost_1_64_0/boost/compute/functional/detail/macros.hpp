//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_MACROS_HPP
#define BOOST_COMPUTE_FUNCTIONAL_MACROS_HPP

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#include <boost/compute/function.hpp>

#define BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(name, signature, template_args) \
    template<template_args> \
    class name : public function<signature> \
    { \
    public: \
        (name)() : function<signature>(BOOST_PP_STRINGIZE(name)) { } \
    };

#define BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(name, signature, template_args) \
    template<template_args> \
    class BOOST_PP_CAT(name, _) : public function<signature> \
    { \
    public: \
        BOOST_PP_CAT(name, _)() : function<signature>(BOOST_PP_STRINGIZE(name)) { } \
    };

#endif // BOOST_COMPUTE_FUNCTIONAL_MACROS_HPP

/* macros.hpp
7mr6nkNf7+k19VWvY9GkrgDdu5pNl/pB5+3SSSegjedsmtQDoB99H3xZKwyss1Dv0vgQ3Jvm/cDJR9uu5yB7T7XzUnbrdXCfPOjWWbrj15nfsatFw8bwmb3exAga2hfx+JbPdwqf2u0gJzhnh/tQpqDxeBX099XRrry3pLGh983vgzI3KV7ViNjv0W+4m07PQ/d18djixbtNc3vgxYp72Z8iretr1vk7mOFoGmzSzS8mDwdFTKW/SZ4n83z9/YAx42u0D2vrWkW6eIdxSoX1oWeebOFsPTPRuAsor9TXrdc8aBs3pkfzdv6H1zYxCIpgDA42dF6HTjtM1yYsP7qZ3thzsvm39J/5nuQFJ689CuewztVCjqwYI9Dza9j00fpkbOq4Y+Tvxh8ZZyCqGoNVhNyhIMdlz7SRD0/A0uENbZ+fjKOY7zN67puNFadKjPns+L9gecbGHHyxFA8tRazoOJ4xZMTaSRvjfWipJ0A33ofLQXPjIzRmDEwhLqIHGQSmNB5iAzIIXDEOArobGDv+Ab7S42s79D5Fzm9wed+b9B7dJ1sJ9rWNhQqRRs+jsf41xqNzPlC/pWfnpYsz3jEc/8jAiF2i7f7QuLfaoe+Ozp4Dyrhb7xj8WLFmU8jeG0roYv+uT+pvQpAziJm/v4m1VQ30FmSo/Jwq+Me4tHDC+jD3c1BmMbYNMUl7wFhxbdB9Fn0Hut26h8vFaN2u47nepDE7bAYlk+0xxvsGx5gnrTO1iA+aR12Kcx2f0Q07/vwJWHnQQvfLIrCGvPEct9EGpRiRE2zWcgyObeBuL/SxHS90rHU+CdFgg2t0I3b81FNsurRXt7BP4aF8tluNLWKlBDGfX7KIExiqL9Y2DkZnsw3bBfXgy9ku7MnrIi2bTgYb0nSGzfgSpBO7PcJc0/vTz3XoYkHXfbQwGjb6Rj+vlmM5TGo0YC+4WIF6NCJsDOzRbKz8oNeBF0/APm6vt83fcTNspQsvBd4I1LHj/OaeV4IRecrlrY4j82djjeWzN1xQ43AGHjdNIpFxRrQ0jWBFtjPWZKvXV/2PNdOuop0HrRjHeuEUaOZRIeR7cDOHTkSsxW4P/oQOhqmt11j+U4ER5qDY7dP3ekCH8ZFl6jmMi2MXAz2ny5k7g3JMz8Iuyjmj83DmOJQz/vG1gcH8xOZKw5batzHuHLYHm9ouD3MY5NGgu/MSdOTjTUz5POLbGMwj11HloI9EnC/k5Q74jhhf2APoc2OO29jjyh683aKIUZIHnQfdbPFun5Msx6hzeXvQDQWco+iNPjpv9NHeeExXCPSNExP6jdW5NyNPzIxo1yKNstBxqN4EdBEDzeOdNf0Aci+WEVLssT719i06cajPfB6hT3HHAWjeHVU6xFb3MVe95Zo2TQQMTKGLn15Gt28Zhl7APUm9qXFqpo957w5ldB1fjL2YO5bhYEMDt3qnIg4nZsx4BgNnnVih9T18nHc2MI9Wd1jpMnHe8i42Tma0Bjly6FYVzTMjZTgUZ8RVzZfg1HldzK0Kc+Zu+rkM4y2ej13Lou9yEAKudLt/vAw3JmEanDV5uliKo3eDybTX9zi7mPUe3f7PrhPWmE84GFHBzQHRUFYZxilr/5MORtVtYtwr/6kCZiJZovWWofM/6+JIdZCWtOIxPudg8CY51+oe5vvZuN2+eCKdKWB9l8ANrm3gJ4MN9brqaFfWWO87XLxhEYs+Ne/0vpGLQz8MsPa4sYtB+w0w1lyM3X66PBdX0n4HN3Ex5e13VMCVtx/05/P0ONA7fJruPV/TsbI33xIu0rG6R/1KMO6dEOMXuBj3qRXDH/1CjXXfz8N+KL+r/2GFO/wP8Z3u8De+X/wF/54=
*/