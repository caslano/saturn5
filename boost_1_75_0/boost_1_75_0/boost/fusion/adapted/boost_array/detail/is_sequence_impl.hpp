/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_SEQUENCE_IMPL_27122005_1648)
#define BOOST_FUSION_IS_SEQUENCE_IMPL_27122005_1648

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion {

    struct boost_array_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<boost_array_tag>
        {
            template<typename Sequence>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif

/* is_sequence_impl.hpp
nsvP8bKU+xFOCsFSbn1JYNzCUfOkZgSt62Yk1k+Yj/QPOnoNYyMcvXf/2P6EmbXEpAxjbWg1y5ZZT/l5uPAHeynrb8YgSlb+kJUJufzaZHp/2D3cwFpkQg4R7L0hRxA8wdwcFPGwODQFFCLjwt0UoSfn0bzWJ/r5bT47sOpesI9qnWuSWe3O4HQnpXOe1DeTxLOGBbvhsuuhfnwDjKrtu4GTU/E6ZUqUyZotgy4LfYDxa5sDlGalrYdi3NOM7dZ8tqn8WGwqnxvBd12MnerJwOgJyYL7vi0j2u/jeqOzEyWMbjrhbgzAmQ+yhSta0GWoS0YCDhqjA6wf8xC2JgdtH0FFZl9aT34wMNWJto/xZLoHto87HNrEVNB3FAeemu3BvgkWAKBexPVgWI0e7puAq2Qq7IxQhZUMFoUdzOxEYWfywvoahZ3dF9H99vfg3jVYweQMXs37G24pfetp0S7JysQYl7LF8TGddLB9YkbqfWe4U1zKKMYiDVnDGpxsi8L++ic6h+1yx2RHfOqEZnOW7pzLOGeStbkOHQT1aK5xpM49w+3IVibaXcPq2UdjaC9b747Jgo+q3M2lO4vPcqVvKeqPO0fwtLgDUVLrqbJzT8ZbmuMFqUnq9yfJKCAp7b62+2+hdtt3ZYh2+3VgT34J9f7oEO1m5+32cyK128Fwvd0OJoLTte60aGKS0yFVjCmG7bPcYaFLB4hCr+xM
*/