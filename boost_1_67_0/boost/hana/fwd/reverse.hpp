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
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
*/