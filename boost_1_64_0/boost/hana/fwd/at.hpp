/*!
@file
Forward declares `boost::hana::at` and `boost::hana::at_c`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_AT_HPP
#define BOOST_HANA_FWD_AT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns the `n`th element of an iterable.
    //! @ingroup group-Iterable
    //!
    //! Given an `Iterable` and an `IntegralConstant` index, `at` returns the
    //! element located at the index in the linearization of the iterable.
    //! Specifically, given an iterable `xs` with a linearization of
    //! `[x1, ..., xN]`, `at(xs, k)` is equivalent to `xk`.
    //!
    //! If the `Iterable` actually stores the elements it contains, `at` is
    //! required to return a lvalue reference, a lvalue reference to const
    //! or a rvalue reference to the matching element, where the type of
    //! reference must match that of the iterable passed to `at`. If the
    //! `Iterable` does not store the elements it contains (i.e. it generates
    //! them on demand), this requirement is dropped.
    //!
    //!
    //! @param xs
    //! The iterable in which an element is retrieved. The iterable must
    //! contain at least `n + 1` elements.
    //!
    //! @param n
    //! A non-negative `IntegralConstant` representing the 0-based index of
    //! the element to return. It is an error to call `at` with an index that
    //! out of bounds of the iterable.
    //!
    //!
    //! Example
    //! -------
    //! @include example/at.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto at = [](auto&& xs, auto const& n) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename It, typename = void>
    struct at_impl : at_impl<It, when<true>> { };

    struct at_t {
        template <typename Xs, typename N>
        constexpr decltype(auto) operator()(Xs&& xs, N const& n) const;
    };

    constexpr at_t at{};
#endif

    //! Equivalent to `at`; provided for convenience.
    //! @ingroup group-Iterable
    //!
    //!
    //! @note
    //! `hana::at_c<n>` is an overloaded function, not a function object.
    //! Hence, it can't be passed to higher-order algorithms. This is done
    //! for compile-time performance reasons.
    //!
    //!
    //! Example
    //! -------
    //! @include example/at_c.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <std::size_t n>
    constexpr auto at_c = [](auto&& xs) {
        return hana::at(forwarded(xs), hana::size_c<n>);
    };
#else
    template <std::size_t n, typename Xs>
    constexpr decltype(auto) at_c(Xs&& xs);
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_AT_HPP

/* at.hpp
4A4pv7Xmr/mtGwZVEcjDZnrt3tk4Up6IO3SWRsmEGpuN8/JH1nS0GukJMMOjbDbvhjypUK6xQClF1GhoJD5lV7qbezwVr8YlhvqduFRGgVRlVHZcCDa7Bobzon8dm72LPslnx+t3Bu4AXehHGlFdKVgN0cygO1mMPMeDCnmOPFgZLzrZo+wnSh7VT4ndKcIib/a+qe/+EX23ed8e31qx1VDW0I0BCa0+K4sCaA1DPaohly8Sa7k9/f7LgQgUDYZOPp/DmtknGDqZdD5/Fg3JWTMqYpc2SUJDOU21IcZmLhvDMZRDP8tVf9jRhXjP9rN1Ca9yfaXhcEc+6DJSc+J5NtP7Te4GHK63lefCd1hUsBorchYY4zKOY1bsp4R3Dsu13VSVuJ10GhGinU7168BTaIWFNdH7QByaL837kk68JqqE8E2CTmgi3/Ed1OW5tOGLKAcWWh6pqT6qH6q4WmHYP5jDNx3DB3ti6NKR3z6IR/0Ci9TEiEm5sAMaQ57Bn837XqT1b3GkJDwirf74INc+Hf8zkqp8qbtKgXqbXoU7B81OzCxU758LfVkc0urOgc64M44JD25zRH7tVG7lnExMBii2AXvYTQzYroDI2ZCfuNUk1B53uVo9JJ41zft8HBxvIU0cmYihDqUrC3kdCXf/nYd593+hNXqd9/d9SIv5dwiFtmICgWZGF3l3JSrN610pD5Wo7LOi3fvVBFFf4BPrMv4XdcjobyEih+Xc/wWpdo3A8F+N55Eh3GrTiPjE2mluA1ucKDP/FyT9PLRpMv23HvVGSdNo4YDRBTZPXmDBD69Xnu47M0ZOHsdJogOwTPAeiyDTgZB+gip0Us0Vh6oi0AY8sCq4QbohIIxZy3Ds5/mnCv4bpZgHpUHBWYP8E13qBXqJeu/bXVqIJXL9dABsM5C3cXJ6Gidc3EZTDwxnPUsojTUWo8bsZVa5PopKC4OaqaYB+BTwsASRpP3etzjBojPUV7CqeKR3i7dHzsZZvjRRXMITj7odVfiZG9xqEyYebA7j0QW7GoW/VND5rxpcAE0Dsc8Aer00M8FLrMfrdGQTlDTOoromvjTAkl+ixC3WE678VEwRShTz7+Hax8r0VRMb4fmfYCM7CUUPH0oqZggAF8A+/eMX0VN9C0VV4e2KT8ZK+rM4EfT+VnnUDWdggNeIehQqcGcCKCwUzBDSSzWzF9ACo62uXMFzEsxiLBa+sOgPGEzqWxlbZ7FuEi6ot8bq6+xuX1mMK3rXeAo1ACIXtSgEDlyFCdz1v5B4hIppu1bv/llGmzpkWCz0oW+5fTbK3xiaXI7NnHZgxK3Rzw/7MWUZdxClBH6OCeuXydtDM64eaUOUuX+x12A3GOp2Gmzd3vAyLS/+qF1vobSku5SvLvWzc2K77I2jeKBTuEyN+C0hk7HqJ3J1DtUZTjeK+CcirZsg7ng2dCXr+vroa2BmJ9yPgTfLg7aAdNTBjRdrlOo9UIIKwDM+fzxqGbrhth+YKPif236vLgVBB6PLExnKrrj/yLmnQlwnmIKPn4RLteDR8fJtv6KKdwcpXXsUOz41Pu7436CaAL1v2wvbqVLJhS87D+PTkxsD8oPHao9LgVGNFihnNzSWGPHH11hiCjabo5ba46ZAeqOlAHnuRkvt0U3rL0Y8RYH8YOYS+1UjbQjO3QLnzmSIu5nhJVr+IX8esi6Df2LykTbxd2jGsYeG0l4sf+/ZtSPl7U+ZD+W/X6NUr4gp2xE88Uul+PUpv1TaNIP89/PTks8XeTBgzqKvF5NVIsKnliovUk6v5Of+zU9SOV7qmEGpxzgMaFB2FuQ/J9ffDPR4Pgi+kk5DF4M7UJSX/2JAPoyP0hmpepE=
*/