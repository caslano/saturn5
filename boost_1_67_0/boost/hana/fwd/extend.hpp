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
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
*/