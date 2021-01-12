/*!
@file
Forward declares `boost::hana::reverse`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_REVERSE_HPP
#define BOOST_HANA_FWD_REVERSE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Reverse a sequence.
    //! @ingroup group-Sequence
    //!
    //! Specifically, `reverse(xs)` is a new sequence containing the same
    //! elements as `xs`, except in reverse order.
    //!
    //!
    //! @param xs
    //! The sequence to reverse.
    //!
    //!
    //! Example
    //! -------
    //! @include example/reverse.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto reverse = [](auto&& xs) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct reverse_impl : reverse_impl<S, when<true>> { };

    struct reverse_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;
    };

    constexpr reverse_t reverse{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_REVERSE_HPP

/* reverse.hpp
/imrB10Chpgehx6Bhg9mnaVg/e95Vlm/sJdJ+NxtdHoqEF5z5+r10Q2+7X3nBcKPnR8InzsxEL51UiD8kcmB8D78nYC/N+P/8bO//6nfmeWFh/oLOVVwbDRlxDMhWr4/QD3xQWc9ljRp30dHZF0e1EvMkT9wYFIF94VCmi91tkj8d/YZWwjgEWdwR7D/d8+dwR2BWiQNR9K/5HAPqlTtt/+otEz8I1i+7D9YMkwfajDrg0D+
*/