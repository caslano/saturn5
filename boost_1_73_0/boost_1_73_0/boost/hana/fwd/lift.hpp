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
3Tf3T0JptaJUjfryVp2e0ajCr7nMkJQljK1mGop7mi0P0lopqaBp679iz7mw2pIzhriUXtuIh4bywX32HkxzpWXhEAvrKLov7UxJd9bs0F3WMd6Ng0prvflG7rlKnkkO8woctSXL7nXJzP+S1aPr059FD1cUyWPeUMISA4/iKhhTaQrLYUxmXDvYwMp/nds/kXX52tqqqhZ78kceakLLIEEYzKbkYUD0/rL+IL/NGD9sX6wTi+VIXXceIrHcP6YGiAf0y+6HscCmRWekyRGeUKA9u/CrKluv1ayGMneBTCjamxEaTdLwqsZY2VGrVeN4zjww6+xuchNV8wdFettU/YaomhtyXG1oR6aqaAJhsSJUDXuu7PyjR07iPsBXCoBHS0ND3aCxrOfCVV26FjtsaJGRSBpH4cgz9qBnHi6x1QaWtyirThljrna71NInM0D8kAr7jcGYEVJQKHZUnpAz0P/+QKHVWooWLUYA04WvrJjI98oGk2hTepm0ahhQjhRVPvvi7dlgKC68IFwN7+wVdgxRRr7LsF9mZPJHbtk7mIjBhdXHiu1wS8uR2hxxrcZ4BUjuYYQm1Nsn01iEcfxRyCNRQg88WtoYPqc9r/EFLr+Np9OYXrUtA0YmmL1XHQ9Dle/lRUC03h4TleQ9
*/