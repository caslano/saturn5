/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_END_IMPL_09122006_2034)
#define BOOST_FUSION_DEQUE_END_IMPL_09122006_2034

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/deque_iterator.hpp>

namespace boost { namespace fusion
{
    struct deque_tag;

    namespace extension
    {
        template<typename T>
        struct end_impl;

        template<>
        struct end_impl<deque_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef
                    deque_iterator<Sequence, Sequence::next_up::value>
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return type(seq);
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
2qdntS9T94+9pKke42S9P5QxKuKS48/f5Pjb/91YPrskv3Ol320S4XXleDR3zK9ePg3OVSn9IvS8Sj9UGS9h4bac9M9yMfZkouQttIXzsXuDvJXpeZuZNDZp1kytNzSHMLx2FFjjjqN/pJZP47yK21o4fDYk7QqXaWuF3JjzP+k6n/99nPf5COtVuUxX7cFyTmnW7utWSTNM+iL3JrzJejVmaRqqrjtzpfra1cV0p2dqGutiuPS9nyN1cQbhGPkIaSH5YHLfJDUT6qyx7HbDc5j62tWzdL3fyQC1LmaXGJ9pKf12CjPR7vtR8jVAyqcP4R3yVe6UL3k6o5K1RpSNMW/RzvnQy6dPK2ljkH6NowlPsW21cz7IgNp/vdF5sPv908q5Lr6rnDt9HNNTz5/pmXQzSs9c4XZdXGVyvg652LysE83TZD8vXDnXfh4OSh7kGUPqnKrvKcfbVR7UBxRPnRx33se8QO+THVuXv3SrzVJodchjjowfGC6flUjCB/yvpt48Tht32XnkUesLzo/7BvLI+VvGF5iWI5/z+vKYyfNrczPT8849n1qelHjcK8t1ks+eBP/aNmDyWeY6n5l0VLQ15vxn9vmKlj7+YyXNGMJfSLfSdbpZQ3Ibn6ZJHWOZlEvzurKScyPLpM+8428FX+fzwUfKb4VWrvJrPadzQe1xCWnrnN4Jpf6Yp2foNOz+d7DZcdlsku5fSTfRNF1tWEhjfqcGmHzv+8iWUVIHwwmfsJ7FPM3CoqxsdnSRPJO4/jRDJE3H8i3zc97Pk6xXZZqmDDWhm3Nj9tWsfM/4mZdvjWm60tO0EWnKvtrV3ax2pmnSgGWaJjckss8rvSMm6X3KeiEu0rOmu79/ZmUaL+MNQqX+dCV8Rnqx5unRSdaaW1jg/rnErM6eljRvkWudTYRTSp11TtNq+H3g9rXOKofrXLnulWj061yWy3VOXRJ29XznJc75/EI5j7Q2y6fxPOL+ddkqu+sy83EMcl3G3yS/dkk5zHPf3jnPpyMJZnmWc5A78+s75Ff66Ns/ayLA8f6BRG/MX3V7iVR+p40i/IP8VbZxzt+5nK/0Y283jkuPxu74ll7qXFZfKd9LvqZ50c9j51JeUhednvEhdZHlUmaSjOO9odAA8+NabZpXOfedRz614yrRmN4bkr85fNdXuchneVvTfNpy3RgnUn/dW0QcZnVPXWx/T6eDc96+Jm+JfuZ5s6Y3vvzsx64Qhf34E8kbyx2O78kOztfS3yp1sZ1z3s7lPGw8vtH6+DY9Grsx5aWBzmOdU5Vyamc3xnhCchJP9548bSpV1tLw80jsxxt/3MF53PMq+3HPnjEInjEI/zVjEG5WxyAcfX/Xq/cVxSWUXRW67tm+Heac2xiEcC9pn8K20nenKYYa+oo3w7+hL36Btdsl1rPdUdnuTdnuLcN2FtnO12S7p2S7p7ENVhnm/S+X7XbKdsZ5/9+RPpbvYgi+h+H4Pg7DD3AM1uBU/BBn419wJX6Eq/CvuBE/wdvxJO7ATw35SGvqOh/PST4OSj7+JPl4QfLxouTjJcnHy5KPP0s+Dkk+XpN8VEs+Xpd8HEYZOyJtNZSLydiRByUfD2EvfBgH4CMYg/swDh/FHHwM83A/rsDH8Tp8Ajfgk4bjd9rb9fHrIccvVI5fz7rtaD9xXV8Gy3ZDpL5EoF4/69luqGw3TLaLNpRPYjPX5eMv5XOplE+AlE8HKZ9AKZ+OUj5BmIfBUj6dpXy6SvmE6M9hkHYJnCvpGp/D0FeeA9EP+2F/jMYwnIgDMAkHGva/rLnr/V/SRNv/PPTFfJTtaAdwfZzSZLt0bIMZhu2q6klvoWy3SNLLMWxXI9uFmWw=
*/