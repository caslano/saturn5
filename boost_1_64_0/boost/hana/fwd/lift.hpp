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
fi1ZmGYkHeCQQO3ZPnfhTq6zrDz0dFmQhQ/aKGlQB3LM9GtiCxKl8L6MjwAMFSAo9xzDIi+uk3xfxLGE+RPDAS8QjIcrYgEi6e+UL1jJmHYF5hjhrovCUhCFd/lbz3FiNjOD35Sf+ktHCVyv8K4TV68UBv45hSow8M1lN1OzA1GNFlqfANK9iWcI2TQEk0I+aWjQBy4Q0HQOYouViaciBlg+GTaFsXnEZhVx7rStXLVNXZNP/2IuLeDZ0sFdT/FnNNYLFJXX3OjRjLd6XNWEyolj5pRvsanWyKP4R0/BxC5Owp9N57KVgqXLbDI5s2KMIEX4tPDuxTXrptafAu95QqirW8ZWIjmVWNK/s8lFt/eKaHAkr3nNnhIt3I+9gqtkJtz1wSflf6SDFv9TO6ibzqpoTga427FuotXG+gvGBXGLFpCuDYs/7s1cBpwhYezP4UfG88TSFjygBL3LgXNmNQOkOyUkf+xVWweduDx5mKSXCONHyvo8BEUsihb9ldjX/eOGiioHId2/ZyZcOAVEm2yzZiItFHI/vhS9NfYPfKSCBF4zKEgbHBNpkQ==
*/