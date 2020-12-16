/*!
@file
Forward declares `boost::hana::and_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_AND_HPP
#define BOOST_HANA_FWD_AND_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Return whether all the arguments are true-valued.
    //! @ingroup group-Logical
    //!
    //! `and_` can be called with one argument or more. When called with
    //! two arguments, `and_` uses tag-dispatching to find the right
    //! implementation. Otherwise,
    //! @code
    //!     and_(x) == x
    //!     and_(x, y, ...z) == and_(and_(x, y), z...)
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/and.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto and_ = [](auto&& x, auto&& ...y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename L, typename = void>
    struct and_impl : and_impl<L, when<true>> { };

    struct and_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;

        template <typename X, typename ...Y>
        constexpr decltype(auto) operator()(X&& x, Y&& ...y) const;
    };

    constexpr and_t and_{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_AND_HPP

/* and.hpp
pPd/MftXD+C3S713A1kYYMDQ2b5sr/1yLN1037XguCdWxNatAF/uIY4+g8/nVkdcCWUbDNKGH4G+26mp1xt5miF2UM6A+UWSC3UyeYoh5rnAfDIx7yxXb5pBBHKvIHyL0la94oQH0O94Nq3qj57ZoCcXYDI9J1ITIU15RMGPTlN1npeY2EjUl50nQ1SP+r1VpOLyGlCxk1TUQMXyGBW9z+hLt2Z5XABG3PSDkIge9enLcaqAS9LDX+ohj6Z5lA519OWsa8e6q47s+tjUZBfjvxryyu1xHsbwrRw+1STMSN1UYLU3xA1tX2AiBI5Aa57vGuCkXipwCrbjpLqCAXRq8xRNq1AO5rwd/NCyviLnSLDVEpZm5rfJt/7aCIqWq0NnsAnUc7n+Ps71AsltbiMB56jjz4w5dm4awm3iWhRDuFvNbWzON6VTbEfXSEpbTqv5bXJGHk4BdvHAX7n6L9V6jcCLemB9801j1V9epsH+KBsM539DmHK/CGDqKKBKAUULf84T5o7DqG0MoQP/yOAxDSFmqDQ/hMIDuaAxxSC3XAieKbOhSgZOx+mPpXLDUBTX0fi/Sf6CFY28r6KTA6PxRDzz2+Uv3EEOeuFRQwE257+YX647LirftpcKrzSRw3saj1Air+L5Nv/PyrvywvfD0gWCA9UXz06Q7Gvc3l/GXnEqw6bcSoEUJ97+STHibVxl7szpCPyl7kN0MvfzJvNbmLcHiD6Jx8EqNO5I0/Nb196AfWcPh3zgXFT2bRRz6yW20au9Qf5Z6rspNuHRcu+3kKO/3RIt8rbxrbvBDO9jzIhVPsP7K2aOQr+zlNbK6qrQGMEg3ucTrTgVgou+6xGzJTSu+/P4LIGj0IYtToB//9tSbP+/AivB7TMIRRXqiu9URfUuxcArVM/VFJcYMsTlBN9pyCXNaMnjQv+yOy4xKy+NUB5hgiyuBBgCZNRqHn8qIABvZnXu+qf4pghQbvXlC5ln1UH4cmO57Xqurm9WfvL9GOOj/KfkAWbAUILIQB4lJufw5nViuVjRF3TgswTGifhbV5l6803EIwsYj/adL3AjHHVKHGmgXNCdPSIJ6xPDWcfv51jzVF9J5EGgxKURj8/gFiQcF2we4t2MDlzqrispc4VKFBjnG89cCrc1mIeMioTGiXlglCJ0OBcg4Df3JLxmujA47Eg+h2hI0XvlIrayU/SfGLZxfLVqYALR2yY5SEpQx3RphAOwhhfjvFHmUk8LoAbVQtI1MB6007HlwiPjLF8aZxw0dBFjRs4ARfUHmCvffFGdfAQ0Hylh3Wyl9QSwbJpM/Kqrk+0xDqq2eR6IlsHqaj9pGDUpx0HEkThm8KjswDnVdwU7mRypcHObJEaFLrUdGgM1fQsUpstQkZbxxRiPBGOM7CqrUK8+ja2seJ2nrOcBa1Bwbubn13h3UHIUXoERZ6qjruAKQi1M7vnex2MlpAVkKmlRWi5oQfw86vElfJGqKpNwewYkIW4UY2wMyqy3qN9fqKvR6y1awKAU2bSAVKAF8GJ1wUM4aHU6eNx7o8DBrXqms7IDh7DGtOL65sDRnENtC6UsyvrFMOS2hWaiR57Xr9D7+lhCf8KEKZUwyW08AvTWNrrj179TqW93jA90WZxveZRZYq+3kduCmlW+fTWWWGPNeZqzudFqqj06W76TwQ61R/Pk28vwUBDstNb8Vd5uCltr5e3zjWGpRH8yJZ7MeBr0i7M0DRySi3dJzx7EbEY98XhSEuzMkG+jBxAlaXqF9KQK2Xi36NmDk7Kz8D5Ez85Iys4MasNqrmicb52TV7NizuxNnsblQ2uP59VcXHt89qYL5e3NokmkuwWWjybX5NXePGxa4DM=
*/