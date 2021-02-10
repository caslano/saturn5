/*!
@file
Forward declares `boost::hana::drop_while`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_DROP_WHILE_HPP
#define BOOST_HANA_FWD_DROP_WHILE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Drop elements from an iterable up to, but excluding, the first
    //! element for which the `predicate` is not satisfied.
    //! @ingroup group-Iterable
    //!
    //! Specifically, `drop_while` returns an iterable containing all the
    //! elements of the original iterable except for those in the range
    //! delimited by [`head`, `e`), where `head` is the first element and
    //! `e` is the first element for which the `predicate` is not satisfied.
    //! If the iterable is not finite, the `predicate` has to return a false-
    //! valued `Logical` at a finite index for this method to return.
    //!
    //!
    //! @param iterable
    //! The iterable from which elements are dropped.
    //!
    //! @param predicate
    //! A function called as `predicate(x)`, where `x` is an element of the
    //! structure, and returning a `Logical` representing whether `x` should
    //! be dropped from the structure. In the current version of the library,
    //! `predicate` should return a compile-time `Logical`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/drop_while.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto drop_while = [](auto&& iterable, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename It, typename = void>
    struct drop_while_impl : drop_while_impl<It, when<true>> { };

    struct drop_while_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr drop_while_t drop_while{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWDDROP_WHILE_HPP

/* drop_while.hpp
fwHxpZSR0Y5IhFldDjUxnwyrhynieOVhjmW6wpQs9+WaIZ2vS7OSBbagioaMK4y0HsMRKfEOt3Iz3hJMClxowdNiVsq1qyDgL5s1OxRbQRjIDaASXe+HSs2EBpuyexnDt3Hb33ndPkZG1Q2/qt/oMdpr81+rmJJSQMqVpNIKsPo3bhQgaWHNghBTRT5mrjI6m/gSyX2mN7rSavt5Yi2fJXSbL1+juHwKVezpBnc37t3hJ0PpfTUE3ZorzLQL0O+oJA3RxNDUQNFC0GJN1LhrWSwbv0TBGOyGesWYTgXriF8q3+SWPz+O5uV7x2FmKhunhM102uiM1FyaXTVJomprI/8a6YN7MKb+G3XHqgazBk0W4OA0GQRCoERBrhUAyDQkFirqlDbYIivDneuH8OhFnd3eTEmBasXYyUCZoDxCs94/oc3gpJPQLkup+VvR1phODhUJL2ognUhvEKebKATGxgDIlpktsZxF4Ez/Un+oa/DEQvQe4gMWKe1LSH/OzPEWWhUpX8YAfwwZUZYNPn0oRTKHCSXiqeUM0F4M74dD5OvOQTOBFx7hfigMrJQGFbtJrLUlR5yLQbHhzUxStS3441xwhyNu0zSwu65H9Ke6ui1TudgmblA9+DTrn6p0BsSqsil6gblfS0EWflZb
*/