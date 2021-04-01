/*!
@file
Forward declares `boost::hana::one`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ONE_HPP
#define BOOST_HANA_FWD_ONE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Identity of the `Ring` multiplication.
    //! @ingroup group-Ring
    //!
    //! @tparam R
    //! The tag (must be a model of `Ring`) of the returned identity.
    //!
    //!
    //! Example
    //! -------
    //! @include example/one.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename R>
    constexpr auto one = []() -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename R, typename = void>
    struct one_impl : one_impl<R, when<true>> { };

    template <typename R>
    struct one_t {
        constexpr decltype(auto) operator()() const;
    };

    template <typename R>
    constexpr one_t<R> one{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ONE_HPP

/* one.hpp
Ls63c3C3Ins+n4XghDCSPoVWc2d+ljqhZK5bk3IGXh5apTqJjrB4ySV8QX0Hv1kO85A6J+uPTOFFZ0fowLE8qbEBX0lycjFxB+SzlIPBy8chUSZPzp1ZFDq5i376lrJg/1ru+cBRyD/IPMwr4/8a1AZ5Tefb9eo9USWozFoWOfEZIljaB3mSOoTAtPUlvrEUc/koiI5rL+6s+IgNPGDH5TKZgnpIp8rBB0XuXp9H+APLc6/FcoytDefead8r8X5bUp3vQ4m7aSx6XbJEs8B+NtKPlPoOqqaaShxpovneyB0Jos1dT2jxs7ji0g30vH2crOAdHcyl2SWOeBNfWvDsYRi5RC2PBTVgtcrKps4fBGF2LqNg9QsMurrchSSjfIDeQLfh65RegZT3fbPvwF3RawAy1kIJAOuw5upeiiKtwLulLJF4hvukI0EpxnmwFasaJ4JpvNSJrbmDqWkcJ4lWwVNDabqTE7xDB1v7Hu6ZIbUPyH4BBLaLNki48dPGVpIAO2a3SRsky5u2inm5nLfAk1JiAb0toDS5NSTSBWyujilolyn6l9x1Cl0GiQ==
*/