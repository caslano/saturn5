/*!
@file
Forward declares `boost::hana::lift`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_LIFT_HPP
#define BOOST_HANA_FWD_LIFT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Lift a value into an `Applicative` structure.
    //! @ingroup group-Applicative
    //!
    //! `lift<A>` takes a normal value and embeds it into a structure whose
    //! shape is represented by the `A` `Applicative`. Note that the value
    //! may be a function, in which case the created structure may be
    //! `ap`plied to another `Applicative` structure containing values.
    //!
    //!
    //! Signature
    //! ---------
    //! Given an Applicative `A`, the signature is
    //! @f$ \mathtt{lift}_A : T \to A(T) @f$.
    //!
    //! @tparam A
    //! A tag representing the `Applicative` into which the value is lifted.
    //!
    //! @param x
    //! The value to lift into the applicative.
    //!
    //!
    //! Example
    //! -------
    //! @include example/lift.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename A>
    constexpr auto lift = [](auto&& x) {
        return tag-dispatched;
    };
#else
    template <typename A, typename = void>
    struct lift_impl : lift_impl<A, when<true>> { };

    template <typename A>
    struct lift_t {
        template <typename X>
        constexpr auto operator()(X&& x) const;
    };

    template <typename A>
    constexpr lift_t<A> lift{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_LIFT_HPP

/* lift.hpp
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
*/