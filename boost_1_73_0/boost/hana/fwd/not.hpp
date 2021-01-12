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
6ZOdQUEzXiyVlei69Lr5iqZceHIxs4CLGZRihs1CDhu98BxywJUqFkb2buSYxsN7wPUytIpTukfURos1X+YImWztI9m48WaPgzvnsu7GPHNkeDkIZeiR4VV5gJgGcPWrrBz257wfQmHp+3/taUFHYpZd67bgF3JPLxY39/gxyQw40T25tp8fQqML/AOEt3swEA0V38MkGg0HSTQSUs1IULsxfZFuUkZU/NmuOsYGqC9IqDon
*/