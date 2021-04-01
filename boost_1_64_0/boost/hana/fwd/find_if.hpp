/*!
@file
Forward declares `boost::hana::find_if`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FIND_IF_HPP
#define BOOST_HANA_FWD_FIND_IF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Finds the value associated to the first key satisfying a predicate.
    //! @ingroup group-Searchable
    //!
    //! Given a `Searchable` structure `xs` and a predicate `pred`,
    //! `find_if(xs, pred)` returns `just` the first element whose key
    //! satisfies the predicate, or `nothing` if there is no such element.
    //!
    //!
    //! @param xs
    //! The structure to be searched.
    //!
    //! @param predicate
    //! A function called as `predicate(k)`, where `k` is a key of the
    //! structure, and returning whether `k` is the key of the element
    //! being searched for. In the current version of the library, the
    //! predicate has to return an `IntegralConstant` holding a value
    //! that can be converted to `bool`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/find_if.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto find_if = [](auto&& xs, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct find_if_impl : find_if_impl<S, when<true>> { };

    struct find_if_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr find_if_t find_if{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FIND_IF_HPP

/* find_if.hpp
fI/x3IGw31YtHFY0g89WcFiUHzhmbqIuRt9VCgRkwomxgftRyWlPiNL3fzNYZge+3iz7vC71psFKz3+G0NfOvIvxoO+Rz5oiUu2yeiuoRiKTTtHbug56c9LIHGKo5h1iYP987f59ed2fRG9m3nIRAkwJYr4e0K90/Lf6Sfl+DDgOHOHQozcJWn9veYXWaMleqXburcMLGk92IdlwDOmgFhBxMzk+NxqfBkFQurQje50NvmSAqWlc/XAuMwovfPie5ddw/nhKMHNa53/g5mOBkPoJkkbL+NAyEJTRx7EShtca/0My4wS5MFOb64OyDkiFNM4sYPVbOP3equ3hxH1r+ugKVcIe9lgHyQxjRGLpc0yFs1CNzooWaCHWokhcqoRPGy1vjIeA2n4fstQKRlprXJj2pkZABEFOjeoXcKYpftiZ0J4d1ksDcmYP81Wxn/IVjPNvuyB4yCTvQdFtLS469ON4JKE0MsuFyNNPwlFErd2OGjS5am9XNWgOC4/WeBQ+yapr3e/3cmGL91ZbRlW4ZeF2QTwxIfJwRHnK9gc2f/Cv/hMJLkj62TB7NQ==
*/