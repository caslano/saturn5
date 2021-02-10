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
6sfU1LNiXBlIFy3TErIVlo2y8apDbrJGaR2jp7TEzTbam9yKi2YcLj2zHbxSjUirFmYJaMa+d82UB5+RHT32+EbWge1qGPiPChswCzcMwFVgBmGju6Gsby/2EgzxYOmIvQ24ox3QMI3Bq2I78WLmagqTCQA7ROFBB/uOd1jc4YrkoY2DrXpsq/3IXoDvKlxWqa92wMYhVCMt2LsJwkgwsp0E7bfgFjp0WtsuX/tuvDsco/Dt4tKl8CgtYjAFr4LwVc9gHIrdPI9Bl2xY9Zk8wKgIIX5s+KAJHYphA9c7IyqGDU8OGRqGC6L1RX8+hZW1ycZiJyQxkPxtIAjO5jMIPwZ7xCN80AyrhTrzXUizIKQuACkFH/oOzVFHOeLQ0nc0EhvDjH1CjMrwYie0eI7NiImpHumbyKcFCKYEpgOOEDXmUHR+w+6CT1XVWQN+fBn/z+iHoQM+23j/pEWAkE/rtxYZ/RNgQg4+R4r56K/nY/RiE6Y8v7874Wbr+eLECkeSH/MNZl/OxpPRPBO0wukzjZn9XjZR9h2lvu1671eYZFsOA5eOcRjmDUe5aS0e5PajBFbkggf6pfBejXK1Ia52IGjZMrZWI5wxTxBkRNDFbRDeB2RwOul/XDDLHZyd8f8Q0YpCHkIIFHmuSyFE
*/