/*=============================================================================
    Copyright (c) 2013 Mateusz Loskot
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_SIZE_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_SIZE_IMPL_01062013_1700

#include <boost/fusion/adapted/std_array/detail/array_size.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion {

    struct std_array_tag;

    namespace extension
    {
        template<typename T>
        struct size_impl;

        template<>
        struct size_impl<std_array_tag>
        {
            template<typename Sequence>
            struct apply
                : mpl::int_
                    <
                        std_array_size
                        <
                            typename remove_const<Sequence>::type
                        >::value
                    >
            {};
        };
    }
}}

#endif

/* size_impl.hpp
mjecUToZhhm+zQHIV5jJ8GUWYv/KcqlUGdoOfxm6IsO4iOU7qfUUqiMj5sv47WwPSJiTtNeLvfBYImbcJcBEYkMgEfS9XzHL7441WDpXM2yWYtXPZ+Ay/MbLZ3OCJsxUzY1goQ4hGgEemZ17Ezgms3J/7YhdIQEq8ZrS82kmOTUtZNQCXyru0Docsvbnc8c/9Y4lpKuynd/1nHMNSQV2sOelpX7NSH+bPE9gIUkm3nZyjMlH5cqC2vRcI5mgr4nMwwtv6qo6J9xUlg64JcXUJs34ABoVg7ihod98t7gRuJDnJ9GL6UE8LBhWcVSzt8Ot4Ab1haGftEm4lwualRnP+yaQO+zlQ3AlKf/kJuFO70l79hkNV1dF2/WMk2RZ00xwHEa3pBl10mR5vEfBBJKZxLOvX9QRv27QgPC+y3wB9xfujQcr+Re64Z4CtbdHdiZ8K/e/1Gnox2bF+87Ni1/pDz8PLtnuFAZB3C+iG2NDfFooSZd5MPY9RoRp938RCdzm8YvwQ8fEZad998ZAp8h27BxGMkVygI9yKPFiKM+94BcRmV0uV7Od9+wiFA==
*/