/*!
@file
Forward declares `boost::hana::repeat`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_REPEAT_HPP
#define BOOST_HANA_FWD_REPEAT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Invokes a nullary function `n` times.
    //! @ingroup group-IntegralConstant
    //!
    //! Given an `IntegralConstant` `n` and a nullary function `f`,
    //! `repeat(n, f)` will call `f` `n` times. In particular, any
    //! decent compiler should expand `repeat(n, f)` to
    //! @code
    //!     f(); f(); ... f(); // n times total
    //! @endcode
    //!
    //!
    //! @param n
    //! An `IntegralConstant` holding a non-negative value representing
    //! the number of times `f` should be repeatedly invoked.
    //!
    //! @param f
    //! A function to repeatedly invoke `n` times. `f` is allowed to have
    //! side effects.
    //!
    //!
    //! Example
    //! -------
    //! @include example/repeat.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto repeat = [](auto const& n, auto&& f) -> void {
        f(); f(); ... f(); // n times total
    };
#else
    template <typename N, typename = void>
    struct repeat_impl : repeat_impl<N, when<true>> { };

    struct repeat_t {
        template <typename N, typename F>
        constexpr void operator()(N const& n, F&& f) const;
    };

    constexpr repeat_t repeat{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_REPEAT_HPP

/* repeat.hpp
PdvA9rM9lKNa5lEr2yF0PERdaPkw4lFqtgc6/Zh+Qv9I/0Q/RQT9AlrfoUVo8gPU8dFHiLdOilyPfMn3Ml2nK5HrLdciV3wvL14bZWNsBFQDyyMMJWCV42ifz71jdHrZnp2nT9ME7aDItcj1jutNaEtS5asd12ih41rHAud3XF+87uWL3/F9JXI9Vy+z0HEF9a4pqAH+m8euHFuQJXlUrkiud8exBd6mcoXfK1uKQFKFiDPPxl7+q/QKev1r9AX6dbpCv0Ffwjh8FX35TfoybNeImeer9DV4rZ8q2QHWzY6wYdaRWUrJyx49kiU8b2SKUcE88gnqARWXtoHeoe/Qd+mP6XvwyhE6ikjz5OdoGOTd0ZMlXn5I0FNAkIVYPzsuyg8KOgoEXOLlBwQRPcD6QGEQL3PfcqoUPuaRz8+66W8Q8QweP01/Ds3eE7r9kN6nvyWHbtCP6Cb9Hf09/QPdyouy24jjbuifowMudbvUDHoM1A7i5S6Ql+9iLStiJ3sUtFOguMw9v3jN95UWHDnRQuWrkQVCZBCihuflxU++/sX9OLCkRznyvEXsvpcYe1rMqeNi1pRz5ffFfPgh9bBetpk1sfvgwe1MgSV62Fa2CbQVVM3uLFJ2LchPfNV97+WFD/791HTj779aTU/s/ua7/Jm80if3jfiq8QrJPaUvk9xDeoPkXtQ7JPejfkJyT6qJyb2oTib3o0JM7kM5
*/