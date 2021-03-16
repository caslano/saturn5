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
aSHMfs10FqZ+A2ZShWmumfbCdNBMT2FO1EyyMGZ7T4YwozXTSpjZmqkvzCLNHCvM85ppIMxuzfhf8DOH+cFh4k1DSpj0AFNSMrmnX/oameMcrWyH6ecwF2tmDTG0zlNb3iYy07TMy8LM0sxqYeZq5kVh7tbMemGe1sxTwrysmU+F2a2ZN4X5XDO7hflVM88Jk6SnYkYL00EzY4Q5VTMlwozWTJUwxZp5V5gbNTNemCc1UybMDs3MEGafZmYJUz8=
*/