/*!
@file
Defines `boost::hana::detail::any_of`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_ANY_OF_HPP
#define BOOST_HANA_DETAIL_ANY_OF_HPP

#include <boost/hana/config.hpp>

#include <type_traits>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    std::false_type expand(...);

    template <template <typename ...> class Predicate, typename ...T>
    decltype(expand(
        typename std::enable_if<!Predicate<T>::value, void*>::type{}...
    )) any_of_impl(int);

    template <template <typename ...> class Predicate, typename ...T>
    std::true_type any_of_impl(...);

    //! @ingroup group-details
    //! Returns whether the `Predicate` is satisfied by any of the `T...`.
    //!
    //! This metafunction will short-circuit the evaluation at the first
    //! type satisfying the predicate, if such a type exists.
    //!
    //!
    //! @note
    //! The implementation technique used here was originally shown to
    //! me by Eric Fiselier. All credits where due.
    template <template <typename ...> class Predicate, typename ...T>
    struct any_of
        : decltype(any_of_impl<Predicate, T...>(int{}))
    { };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_ANY_OF_HPP

/* any_of.hpp
pfi8BLnX/v3bkjvJU1mKs7LLUhzZeGjfC9JDnhYgGwjOXKUnFbIac7vzBlidsW5nP8e6OXKgbve/SQ8NrvUFvDObHdlodZKu1PvaIPJhJZOGvIF6PfQn2jAKyb0GgivMyrQkrmCVYE9U0tGOWzqg6bxuDY78PFZUvXug3n6BFQiTJhfRyRtNuGdQIP3ojxQ74KMxFDlO2+DlYsbFyChYDlliQrQAFenDc7hh30kOoDuvTfiveDn+twohk3ec5OqKKdniKVSyQ9QbPTQ8sBMMfjv0KJmWRYlrIFzKwCYV7E0AmRz+Dlk2YO0I24YHJnLvQ+hUbITwxIsD3wOwiduVN/AsaS0hmzNJCw30jvN1PDH6cZOvrXJE/4dCh67/I+Fwnrg5E7lvXU2y0lPCo4TyzH66mZPrmLXZiN0imNrImwB8iq35CufNfOoq1Enfh5YPm/EtD82TI38mQUkThM05Oq+ZMma2N01eOZ+snN+sz5YdOTDhXcsWGYfKZwmtmUFDpEsZp2J0K/iYTlaXILUfPAvURt0iC/9dTdUMiyCZ+EPEkfGsmCSWmMJj4FVMCo8shyfu+CU0ODLqk7Cpka+aSEGmqiwkb9mPerhYkOnReczSjEEYDVF7asmfZWazFZyMSGkIHzaWbJ5FSgdguMADDAnvg3LzxNB+I/6N8iR0mgnQRUAAzf+tC+3SV81HVpaeegNHAiXkJSVEWvFH
*/