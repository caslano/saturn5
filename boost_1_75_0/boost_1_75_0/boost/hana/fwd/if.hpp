/*!
@file
Forward declares `boost::hana::if_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_IF_HPP
#define BOOST_HANA_FWD_IF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Conditionally return one of two values based on a condition.
    //! @ingroup group-Logical
    //!
    //! Specifically, `then` is returned iff `cond` is true-valued, and
    //! `else_` is returned otherwise. Note that some `Logical` models may
    //! allow `then` and `else_` to have different types, while others may
    //! require both values to have the same type.
    //!
    //!
    //! @param cond
    //! The condition determining which of the two values is returned.
    //!
    //! @param then
    //! The value returned when `cond` is true-valued.
    //!
    //! @param else_
    //! The value returned when `cond` is false-valued.
    //!
    //!
    //! Example
    //! -------
    //! @include example/if.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto if_ = [](auto&& cond, auto&& then, auto&& else_) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename L, typename = void>
    struct if_impl : if_impl<L, when<true>> { };

    struct if_t {
        template <typename Cond, typename Then, typename Else>
        constexpr decltype(auto) operator()(Cond&& cond, Then&& then, Else&& else_) const;
    };

    constexpr if_t if_{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_IF_HPP

/* if.hpp
PF5KpugvXvNfQ9tcmDWsCP4S5uJb3YL8B39B7J0/ih3p5o1RjBWb/iTsN1uJrZTTPbT0VsrbyVoUNpavQW6TCzF/QM2GHJkQErCFCpFp8f8EYZwwDf/HCWORGyGMFkbhegT+H448/X0m+/M6f0rfWZg1OGOxP3WIeGRCy3cA0qXUY5zgEnLZE4xZwJYhZApO9qQjTaAv3cWyNkpBCzCxdAZ7GpIgdEf5MLSZK+QIKWi/ENTwZyv01/IpTARrnYvW2ewpjAststlzk+cEHXD5x44F5LG+GWjb1Kp1nAMgkYFIJ6AuT3CzZzMRjCe3kMr6Rgjj0SeTjZ6FvQRWFNZzJlrQ0xziIAL9ZjYb62nBEEDTBNYrL6BehXp6LnSvoBHUuFKCh3uR+v9FQE5u1tvF8gsFM9KRQgybtQGQ33jhQcznRMA4IUkYwp5QTUR6Y81ANp5V6AR6aF5cjJYsxmmTxIcFcBMTwAu9h5MPyiTA68QMp4iSyAFFJOFZ0Fp6hvUuo+4/nbN7URPDnoJFBGDJY1c0e0QhSTqVPVs0C+0w/mixZYZIu1+2WY08xFIkDrz3IpeAf/SXhFhcgnKiKhU8Eme31rMPbqkNH6DPcNjGjThvnOHbzS/9DWCWPJpxMQ6QifHHMilnsLkgjALji9pNYE8oW1qYIEQy60xiEqYZy2xmHXQE15ZGj9Cj8Vmmf26cyHGbmcPmPwfXY8FV
*/