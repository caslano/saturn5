/*!
@file
Forward declares `boost::hana::first`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FIRST_HPP
#define BOOST_HANA_FWD_FIRST_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns the first element of a pair.
    //! @ingroup group-Product
    //!
    //! Note that if the `Product` actually stores the elements it contains,
    //! `hana::first` is required to return a lvalue reference, a lvalue
    //! reference to const or a rvalue reference to the first element, where
    //! the type of reference must match that of the pair passed to `first`.
    //! If the `Product` does not store the elements it contains (i.e. it
    //! generates them on demand), this requirement is dropped.
    //!
    //!
    //! Example
    //! -------
    //! @include example/first.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto first = [](auto&& product) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename P, typename = void>
    struct first_impl : first_impl<P, when<true>> { };

    struct first_t {
        template <typename Pair>
        constexpr decltype(auto) operator()(Pair&& pair) const;
    };

    constexpr first_t first{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FIRST_HPP

/* first.hpp
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
*/