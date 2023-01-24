/*!
@file
Forward declares `boost::hana::replace`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_REPLACE_HPP
#define BOOST_HANA_FWD_REPLACE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Replace all the elements of a structure that compare equal
    //! to some `value` with some new fixed value.
    //! @ingroup group-Functor
    //!
    //!
    //! Signature
    //! ---------
    //! Given `F` a Functor and `U` a type that can be compared with `T`,
    //! the signature is
    //! \f$
    //!     \mathtt{replace} : F(T) \times U \times T \to F(T)
    //! \f$
    //!
    //! @param xs
    //! The structure to replace elements of.
    //!
    //! @param oldval
    //! An object compared with each element of the structure. Elements
    //! of the structure that compare equal to `oldval` are replaced
    //! by `newval` in the new structure.
    //!
    //! @param newval
    //! A value by which every element `x` of the structure that compares
    //! equal to `oldval` is replaced.
    //!
    //!
    //! Example
    //! -------
    //! @include example/replace.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto replace = [](auto&& xs, auto&& oldval, auto&& newval) {
        return tag-dispatched;
    };
#else
    template <typename Xs, typename = void>
    struct replace_impl : replace_impl<Xs, when<true>> { };

    struct replace_t {
        template <typename Xs, typename OldVal, typename NewVal>
        constexpr auto operator()(Xs&& xs, OldVal&& oldval, NewVal&& newval) const;
    };

    constexpr replace_t replace{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_REPLACE_HPP

/* replace.hpp
TO5FYfIT+1GvMLkPdZVJ+V9ncj/rDSb3tN5icl/rZ0zu/TS+0dD4zvvfZfnlh11dvA8y7nu8xvdZ+DW+LzWu20k1row6SbwTKSFtLm6m+RaGIl9AldHotJZQZX2+3+Wy+TfjSdXWFPGVP1tL1uN7ZoN61DJt84KjBE1rzpTfot3rXP9ESo1peXq84H1q3sc/Ne/jn5r38U/N+/I/Nb8o+3r16tvPn33tTxi3a4xy/+54T828zN+FHqbcPz68zPfKxkzFnDVMJSb6YaY0ZUazHSWVfj2la05cNfBKZ3qfAzRDT+Z9b2nN07+nva2T788Jh/GVHyicN/LJVxB3zWIcFvO6luEUR2vp+PXWqKW8pZzC863sJCvm3BDz0euZvZcJq7akYt6mJZyaovMbqFPM8V/uzHyEo19wejN/CRTzluMUnvsvx5dwApnU5RSOPO+4PCmomDe+TC15PsCG2C8zDrz2AplzlwslBGCFdaBNoM7MjswXMruAQt63MtuWcL5VcP448raiGpsQdzIGiyFj0peH1dS7e51CfvF1WtLGcnWWTLFrTAMFL03e/wcNwRvBbwTKb20t/39kKP//h2fDH4Smw13Hy5fNE///hs9dfB1YrfznibJv18ciXwzdDv/hmv59ceWX3f8J4LXKIvk9Vmh3sCtohcqT34T+87WRr2urlX+O5L8D+fL/oOdw4PYa/kHi/9/wNXldGfKf
*/