/*!
@file
Forward declares `boost::hana::adjust`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ADJUST_HPP
#define BOOST_HANA_FWD_ADJUST_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Apply a function on all the elements of a structure that compare
    //! equal to some value.
    //! @ingroup group-Functor
    //!
    //!
    //! Signature
    //! ---------
    //! Given `F` a Functor and `U` a type that can be compared with `T`'s,
    //! the signature is
    //! \f$
    //!     \mathtt{adjust} : F(T) \times U \times (T \to T) \to F(T)
    //! \f$
    //!
    //! @param xs
    //! The structure to adjust with `f`.
    //!
    //! @param value
    //! An object that is compared with each element `x` of the structure.
    //! Elements of the structure that compare equal to `value` are adjusted
    //! with the `f` function.
    //!
    //! @param f
    //! A function called as `f(x)` on the element(s) of the structure that
    //! compare equal to `value`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/adjust.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto adjust = [](auto&& xs, auto&& value, auto&& f) {
        return tag-dispatched;
    };
#else
    template <typename Xs, typename = void>
    struct adjust_impl : adjust_impl<Xs, when<true>> { };

    struct adjust_t {
        template <typename Xs, typename Value, typename F>
        constexpr auto operator()(Xs&& xs, Value&& value, F&& f) const;
    };

    constexpr adjust_t adjust{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ADJUST_HPP

/* adjust.hpp
E2m0DF/jbpv4NEDdpbRYaOxSdAbJJsPBgtFWDA7v4fMtg3HYw5s7mNaKyCaiG0nO0VVMwuPXwxLzYNdEcXROBuy63nUxSzN5wckrHJtRB9UoMuqEFP+1qEGOm6dbswATPPK6XVdNDyC42LZa37oH9bCpMcJS3/wkvpkIlzNJFK49QKFmXMitF9MCbUi0Z+Hf3FF28/qKkeKoBqFbNt4kMtuJY/1x6zzklYk79qwx0mIvWFl2dGCJwB3AFFQqY6xTQ7zkw81wfjMarZq1AoAdqFSbu3rHqN/CQG0dQvI3Tqjc5qMw74arzA1BgmUIZwy+HUscDpn45XlsqBzDXkbxXuEzXg+QGVRbtMbLOUyH9/GOASpdvDeztGB9zLRxW4qIIbiTKziI5hwdWOJO3KHcObtjYaC5UOuQGvIIjS5W9rizoB4Hqw34CTInxRjUyF9zGU/o+irIdbJhBl8CP/ad9qHnYnmGLgiybjWT08//0SfvT/cyuZ9yjsExobgMZa3qAOjMI53fNMBZTVwLjP6D4YL+gBHMcU9ppXAFKoU429sCtxqDPjN1l5/+sQ==
*/