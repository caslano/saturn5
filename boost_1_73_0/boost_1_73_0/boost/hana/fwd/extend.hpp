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
9UX/GBTBu4uzcQ8C1Q/iUD+CKIGeXoy61oak5opMlIgLUZWcDKBr/V55mvgT9pyvIkkJbDedceYIV/u8DEslZ8WVKj7IGET7vkDkyPuOZS2b55kOjtbeY5xeCPJTa6+F5CrsC2eXuwjeH/4hFrv50zLmXZrX+YOcygstb62OOJZtmtSNo/pVaMkJL1O2XfTordmDP3BrtliUawbX//SNWuh33H19cdoejSD2qVn8gpJUyVx18wqfjapW6FoiP6B6GOZs7joaUQlNuIrsigJuw7Uu4Xxiv7TrXQp9jZioosak/oBSGcYZYD6tbVAyU8BVlc1s4Ojhj1Fckzp0CgMrG1IkydOXRULUyzNJYgvvKeKKcl3jwXsILufcFyG65Z+srEg69wmKoj33AjZGv4x+6joqfqxTCmmAUZil7bYjeHcyKad6YeIbkptyUqsA7y0IKEoDpWoWOB1lBM971Y8tLcpOF8RJiCcLQKwVgJIclOls24czN63B2dQ+TMJAHhl6U49saM1YHU8xN9KrdOVa+luKcX1TDqJYDYDbtb6xwq/Ee7F/Ui28jdXx+Bdr5yr9jkf3yN/ED/8SRf2gLTa6ClUuOG6p4a9XaRDZ66sDQr8I9Sd4V1RYpbJXHCwpDVq6K4rfJbNoqBFSQwB9
*/