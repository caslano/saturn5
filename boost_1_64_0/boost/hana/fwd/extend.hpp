/*!
@file
Forward declares `boost::hana::extend`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_EXTEND_HPP
#define BOOST_HANA_FWD_EXTEND_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Comonadic application of a function to a comonadic value.
    //! @ingroup group-Comonad
    //!
    //! Given a comonadic value and a function accepting a comonadic input,
    //! `extend` returns the result of applying the function to that input
    //! inside the comonadic context.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Comonad `W` and a function of type \f$ W(T) \to U \f$, the
    //! signature is
    //! \f$
    //!     \mathtt{extend} : W(T) \times (W(T) \to U) \to W(U)
    //! \f$
    //!
    //! @param w
    //! A comonadic value to call the function with.
    //!
    //! @param f
    //! A function of signature \f$ W(T) \to U \f$ to be applied to its
    //! comonadic argument inside the comonadic context.
    //!
    //!
    //! Example
    //! -------
    //! @include example/extend.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto extend = [](auto&& w, auto&& f) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename W, typename = void>
    struct extend_impl : extend_impl<W, when<true>> { };

    struct extend_t {
        template <typename W_, typename F>
        constexpr decltype(auto) operator()(W_&& w, F&& f) const;
    };

    constexpr extend_t extend{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_EXTEND_HPP

/* extend.hpp
ksS/uKj5CRc2qzxwzJ+DdPEL4Xei/6IZFC5UqWd9sFQVnmneF1nIbmK9OdEgrPkeMisWQxjILC0TlmBIxI6Byo1fZ5HLHqMKMcyQWaTXJwIG0Nt40+FO8whyKonxl+6nLpGZvElZbQ0nHJscwrTyadKmKKE1Na2331up8PRXGeXNzp8hMoJ4DroCEUCuGpCNPk190y5PjGdtd2l/0mBiBghpQcbtMsdlEQxxJ1bsHuj2rpwzRCNYA163GsrXOF38/Q1V1cSwNkFbrhAeT90Q9YkLrZC/LK2H7TDkxtNLAkF6p5jF9wueucsBwt79f+g7Db0UZNZF2uUF/HjrEc1RYj4UucTyZykqvIykjfRao12UPwc7yUEogmwKohC+5fiUv4YEwl5o1FyIliGdz4zF2a7M0bbzC9agLyGLE1MEd6/BrjRh+RfvBV1XH+uIM4K8U9Vc2YavJj6FmmdV6sP0S0eWH68lxBfNRF6hHTFkfIe6jOZfdlqylWzqWFnGnM2kP6m+u9gdaexhlX2R5PUJvyw3h2tvPTIzXgjS581vffHqaJyin/C4S9p+3A==
*/