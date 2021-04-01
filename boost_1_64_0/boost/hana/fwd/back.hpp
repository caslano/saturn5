/*!
@file
Forward declares `boost::hana::back`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_BACK_HPP
#define BOOST_HANA_FWD_BACK_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns the last element of a non-empty and finite iterable.
    //! @ingroup group-Iterable
    //!
    //! Given a non-empty and finite iterable `xs` with a linearization of
    //! `[x1, ..., xN]`, `back(xs)` is equal to `xN`. Equivalently, `back(xs)`
    //! must be equivalent to `at_c<N-1>(xs)`, and that regardless of the
    //! value category of `xs` (`back` must respect the reference semantics
    //! of `at`).
    //!
    //!
    //! Example
    //! -------
    //! @include example/back.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto back = [](auto&& xs) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename It, typename = void>
    struct back_impl : back_impl<It, when<true>> { };

    struct back_t {
        template <typename Xs>
        constexpr decltype(auto) operator()(Xs&& xs) const;
    };

    constexpr back_t back{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_BACK_HPP

/* back.hpp
JChPK1tZfywJHhBfwDR9jm67FAYtcpmhTeRr12Cv/EH5eRVvmqvjTGygfsPi+GnVWUrxZHu8lWBg/ET4glQXZ3A1qD158a3HpdU4YeW3QfC1X9TjvTuhvW+N3ZNTiXb4OVTV61y6XWWmDESXz0ldAqe1hTN5FLH0PsRXZpFKbUpzwBzdWN++KCui6klQic6HJqzt6EcUut+oFIufXeLMdJyaRZYiOUsxY/wMifzrVm7z8iCpuwiCKSgRI3usGUQwnvlXrgGgrwqHOZyR3uvwmSng1QO92+dpbBShACnM8UY9dPxg8HYHF7Ck3OLZzQJEkE2PMDYHW6ygIuCqBRYbAlsuyH/Mo5pvQfHjMKOI3rQzrefSosL/Qdt4as1NOqXeQkThBwwk7U6yP7VG4UG9+RQx2sMIetUaNNsScdfS52yBzx+JUGSpYTX+Cj0hGYxzD1oLLRznWF5uYsdIFrLuscTJb5KL4CCh4YyhhpLMKNt0qNxj7RHrlxP0+Ktu8lCHaXt+FDu4RV7QQhC6UWB0hUnSnD8ga3PvTXBBOzd+rh5BjrttxNofRkEpBw==
*/