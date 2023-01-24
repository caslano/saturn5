/*!
@file
Forward declares `boost::hana::for_each`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FOR_EACH_HPP
#define BOOST_HANA_FWD_FOR_EACH_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Perform an action on each element of a foldable, discarding
    //! the result each time.
    //! @ingroup group-Foldable
    //!
    //! Iteration is done from left to right, i.e. in the same order as when
    //! using `fold_left`. If the structure is not finite, this method will
    //! not terminate.
    //!
    //!
    //! @param xs
    //! The structure to iterate over.
    //!
    //! @param f
    //! A function called as `f(x)` for each element `x` of the structure.
    //! The result of `f(x)`, whatever it is, is ignored.
    //!
    //!
    //! Example
    //! -------
    //! @include example/for_each.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto for_each = [](auto&& xs, auto&& f) -> void {
        tag-dispatched;
    };
#else
    template <typename T, typename = void>
    struct for_each_impl : for_each_impl<T, when<true>> { };

    struct for_each_t {
        template <typename Xs, typename F>
        constexpr void operator()(Xs&& xs, F&& f) const;
    };

    constexpr for_each_t for_each{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FOR_EACH_HPP

/* for_each.hpp
SF/Rbei7U+Dt+gvcXw0ReHyoQ0r02QRZi/FJ/watuL3cB9zdJHfj3Xyc+LtvLvfjwPNuwe3x5gfgXSPi3XALvKTXyxbeHm9VAN4aEW/9LfC6rvp80helLZ49Ku9pmocF93A80fe0Pg/SIF7eKUjW7NljjyA+D5EB5ZTeF9R0L+/IPbf20Rki7kdEHAuD+BwvFXGvCOJz/CzSwHsD+19vqVuyAU08JQzg+MIG3Fq32kl5u85SPm4PKR+3r5SPO1DaUrdoTddvlLa4h1k4oInvA+L4a28z/rvi+B+K4+8Qxy9pZVyKhWZvkLa499QwoOneU+xAji904K3H3S3K+ytR3v8Oajkeybnzm9w3BPKZObCJz63ieItuMt4UaVM5lTlFPueKfLoD6ql9qkTWuD6eGnj79ZH84Ji3OI2B65hiEOfnL2lLHP51TDtIXBcG3dx+aK4znm0p85xBTTIvEvHkt4InUOZfSHi7vRIug28ksmb2niNr4r160K3tZmBA29DBt277RkBb423aHpfx+t9kTX4m9TZ9+gbz+qhgzp8hWNb4XHrdbfo+EtxE25HbtH0/oK0Q9Z/Fcyv33N6nRkU18WqN4jwkRLWcS/prbX+2okKqWF9x633LtAPN4/APD9yervIAuo6IdJ26ga7ggPywhG9TKG0YImP9u4gQj+s1gCpAe6dEeNsqEd6xS4RKgCRTIiRrJEL7FRLh6ccA
*/