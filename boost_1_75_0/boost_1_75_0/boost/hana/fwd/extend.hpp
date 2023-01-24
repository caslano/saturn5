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
hKJPIu25jhSKPwlmkXPpDEeRU0uZ84CfqRfMCAnmN7kcgIZdYT8nAHAfZf7Z7nJnHePt8QrwDSqTsObnHYxAwT7RvRZQON+hpKAea8QF+rABRLeafoF76djSUjIcdDivhR4f3nFeyiKSo4QiLE1+Bbj+RFhyBul54J4Hzf6u1LMf7g7dll7hOvMmUDF7sflYjLiKYmg/dRDPjguNWJM6cmLzDmo59i53JjJRNmFnmHZIfFLMLK0UMtCryJ0KI+5AWO8M9B3euxvoAUqXRcytpNL/j18hYyb26z0VzF8yryx/gvYc8qd+kHD+n/o3RdZT/S4CM11cVDeM6Sv2WTe4KMxHORD+BMxHCHM1MLjGNjmupGCRqwAH9j/gu5bYZYJ3Mv2gp5LWEd8SoHe/Tk/5l/5E5kajqUpOduxXspNYYQ8fYWF5dRHkw7gPhZxl5+RT9+/sRV57FvhiHWjOl9EXJo6eKWsS3sR9oPk4BE6Pc/ctPUmkLr3MJ+8zJg04X8gea0rBZYGvyU0T7Hb+p5NLqnPDxDIMrn4Brqo/G6ZecLU9EUy6UHYiOJ6SVprIC/8m8bPSsk7K62AppzAt5TvPgDDvFAnTxSSmGhBc3iGawENczh1K2eSz3vnXmSZ1NPJZCs5hFjxp387eJNDuHA3TMOKaKUG94I7wq8RP5BnrHPJC2lGx/Bdu6dGaG4V+TBR6SYA4x4OPUinHzrhZ
*/