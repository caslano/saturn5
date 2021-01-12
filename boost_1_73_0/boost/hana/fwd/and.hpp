/*!
@file
Forward declares `boost::hana::and_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_AND_HPP
#define BOOST_HANA_FWD_AND_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Return whether all the arguments are true-valued.
    //! @ingroup group-Logical
    //!
    //! `and_` can be called with one argument or more. When called with
    //! two arguments, `and_` uses tag-dispatching to find the right
    //! implementation. Otherwise,
    //! @code
    //!     and_(x) == x
    //!     and_(x, y, ...z) == and_(and_(x, y), z...)
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/and.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto and_ = [](auto&& x, auto&& ...y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename L, typename = void>
    struct and_impl : and_impl<L, when<true>> { };

    struct and_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;

        template <typename X, typename ...Y>
        constexpr decltype(auto) operator()(X&& x, Y&& ...y) const;
    };

    constexpr and_t and_{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_AND_HPP

/* and.hpp
ioYQdvUxbP/GS0foHV8Zmf7kGvFbBNLGixxDgptpvwTu573ORI1buI/ssqSeZe4gjqeMeA/zeY+GKp1blE44lM4t5sRzESbKCbuUi4ieOOk7iY+zpy5As9q+050zZeccBewhwzecsEh5iMInHQf3ihsv9N34zmU3LV+y+H+agWjXB2EIshx0ZV3uRJHJcuD2x9LH6+PojxiKPCcVR1w5qeJ9Add67iVZHGiOZAzUR8AoesQM
*/