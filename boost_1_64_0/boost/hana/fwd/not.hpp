/*!
@file
Forward declares `boost::hana::not_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_NOT_HPP
#define BOOST_HANA_FWD_NOT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Negates a `Logical`.
    //! @ingroup group-Logical
    //!
    //! This method returns a `Logical` with the same tag, but whose
    //! truth-value is negated. Specifically, `not_(x)` returns a false-valued
    //! `Logical` if `x` is a true-valued `Logical`, and a true-valued one
    //! otherwise.
    //!
    //!
    //! Example
    //! -------
    //! @include example/not.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto not_ = [](auto&& x) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename L, typename = void>
    struct not_impl : not_impl<L, when<true>> { };

    struct not_t {
        template <typename X>
        constexpr decltype(auto) operator()(X&& x) const;
    };

    constexpr not_t not_{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_NOT_HPP

/* not.hpp
ImQU42jGtUJE0+wcx8BvFXniK9/YLsS7lHOMC+0SmcGisfkin/+EaUBuy9T62Dt4NPP1oxKexZQHmgz1nlQUi6nJRTKebWnWiCmh/ttm337OFyELUPqFJFE2bRcaVaGBR0Aj70DT293wjjRerSjDEqD9fiLAOEbBxL7+jhKZsycmeA9FfPQRN6KikpsmaVTXQ4uAERwJz2U4KkIrraD44ihmeyX3JeUmQl/GFhy394El/A5V42UTRb352BWQGJYRxyc6UZgGsgkqC1zdtyKWUAWPidW0CDPe/+Ksvyc0+1bRn5SN4FjKFOl55Qtcc97stlxMsFQblR0UGPjcQ3vA2LPhwsfdzFsVbx9oNJ5mWKlS6g5+b1hbZYXHGMsA2bW3NXJ0RV7uVO55Bxf8zSwMEwX3pTmQ0K0pA6J8/qBJ5r9V/RMTiGrlKKijDp2LKfiBSJffxREBg3olig+0yEEVQ7LLG1a8YW8+0J4asYbD3//mE89whJZJzAk7YigKZ82brxwJBY01VUaAxvUx5H0CRJAKVDetxLpW0Ul2ZHcj8X7h2cUp26D4YQ4USg==
*/