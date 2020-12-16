/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FRONT_10022005_1618)
#define FUSION_FRONT_10022005_1618

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/front.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/iterator/value_of.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct front_impl;

    template <>
    struct front_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply : 
            fusion::result_of::value_of<typename fusion::result_of::begin<Sequence>::type> {};
    };
}}

#endif

/* front.hpp
OsJQ8mqwx4hOSeM9UaO7vXzRP+8yenVd6D2ruyTym3FG99+K6lCnO03dqXgLsXm5OHt6YXW9JuaBm5cxHGVZnBe+vNEpy+Ie+b2uHej4htk61v1tGG2ku67TXbiCZWW64TffWnKzxw/OzUz64lrHuBNlXPaYGUQZyiIxuzKb2r+bmDvddfxQMg7/6ED2N5yu53H2NlLTbzxva43qhPq7RLztc1ulU0LE/jVrfNKdfov83k7q8hux4kwlM345kr+HmrsDNLfIyeuf+u90i4D79uYhaP4mA4c3gKbvnHYn3N+nJibHXT+LbSd+Q6bDuhuYQFA+0Cc/EAz1tyA66JPPY91r/K7KBrRGGD7qVzBNdwCxzWcHe4+GJrbhhvsv62AeJxmKQTBZ+eTffwFi6CnyvWPDfib7eyH7OyWN/o76zV/G2Rq9/l2tUt23D51srFRqQZvfOF+M0W1+PhaOb/MIJ6eYwwtrK6vndFzkn8QYHVc/Go6Oq3Q5xRxrzSzUl33G0LbPF2F8xpCeeDgUGTPFKyqGY5I+iY4LMaFsImH4MYr35v86ZOgtCvc+hP52vuzHCr+Kc3Jc3B4Rlo9zDfb2Yddujh4jyJXLVNZ/bf7NtcW7TtCAv5KxW1/2f/PdAHzeb2Z/D/Y58Pc5uuHfdh9mgZb/ltfQBSRJFnf/BlccavuoCrM4un9P+X1B3LnEs0HcXfzdxj2AZuPu3TDVDo3xnLd5o+xv6P8Q/+aNoan+r3gT/B2RYP9k/3VIG45T9I7V7NzMOFXMLL55uQYf9cBornxomtcobhvjtC1s3DrGaFtoxsOhFiPq9MilHEP64fLdp6b3ktM3jf6TtewwEvsxZaGtrzVp07VBf67jt6G+1OS6nGfNmx2vAWgte6OtjrnmAuvL6VMLi7SRp8IoLWqGNoZd7w09qSgdswn41lXW3bs48g31bqD5fLMd1AKd8g3bZE19jy23dX7398m52UPjpcn0IZnZybsdp5uU3p1h36i0E0u1j33PnTgXubzD8fELSHa2dBcardN4JzHWRhjZHxY+YXUfzyT6sKlrBcxUmYZeN3g6F/4M5gB3iXI0gKYcxjAT51TWnhqwuaM2LKpz/xon+/2bNizKnjgjYHX9rtCFre6d4FNYD7+rTUtbpAVhHbOcP/NyCuNlyTJ+I/0U1pq+cG3HHJubouqfhK2tYG1goHXnZ2AeFfyW8sprf4evRBodc0x9c9p0ZtvL3UlqOBbFbwso3d9epDSh7qeszrcbef7bvbPiqEqTVeTrLlLTZ3uLR5VG2SK9St4sWT3qeloweN2Z78QOTnidsk7T+cX7Uv+SkI7xZUPqVHMrVZ4X3DPTFtt0qbdysiz6PqPR47gUbtZ/9B/k9XRKWUF+74O/t2rp0HQWdlnWmk9u2+UXa1kPzhiaiso7/Q/L/k4nNn1GqDpoMkHnMrGPH2EWz3mM66u4mHFuCpr26igvaP7xikSsxbNWdx/bkVq3kmmuGkkU2hY0+vvYal3+rlSTGhWI0HpLUmur3+VPZhr9ZkzHV1iRGt1yob/x/rPXfPF4OywjPU3oWR5rKLf7ZRqF6UShbSqN4iUNZ9Je6bTh84wHx2enDs1M0v+i5riH2hSd3hurijGl+Ko461CSx+DPxjh/4p9Q3mN7rOV8pstYx4iFRU0jTV91bEWOea+Os1n6sjC7O3DZAW6Uz/9gqVT5u22v2Zmt0KmzlcrCqvwuy8bo32SXdjrwKSLlJcfWzZjux3D0HQMwbqzP3uk7A/2xoe4qhPWc0SkBidAfF+qUANLRr2p9dm587rh3WTsY1x4TY1w8zGxEw6G4RF57gpk56rMi7GI70CkK9v0erzVfjjU=
*/