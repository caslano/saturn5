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
BIYwzQDT3nitR9jsjrXjnH2c0bADeQt3s5YsY39u16xoy5Tc9Sob47xVCKOpMey7/8Nm976sfU6L9Uiy9je/u8GKOITVgX57ugt0MyWNjLTlNxsvOUw8Y94QXRVcBC24AwXsicPqZV++a39z8aeKm/HCrF+9hE8rzppVoL8+3NsEQBViVULePbL35USpKC2ffK+TEMRjXofMLush6ILXV8ulhVQ5yEskg98q1rVNaZ5L37uqi8LSg1jD229RW5xmMfNbEhMV2/VyiOctDE/nPOepZoSgVd8lS7w3Uv52R2h+N9wSCUQBkB2b6AspB7Lk8nqvP7eido8T2qm0JMLZFICLIfHWU5JtQChsgjIjLq/Q6kRm7LhHSjYynNTxX165gZYYWf473lKRALNJ29aM6MB7c0HCern+PeVA5H9s9W+aM+wocHmzeT8BeN/xgx+qXd/tWh+QZ5tbQ1i/cf4e10OJC4OzhL7LpSBGQa96GhHmokdl2AhKv0rNz243g6dJZ9Gh26/xqyVKj/SHt81pxYyKdlewFaY5NIq90nFAyZ73nvDvx/b9cIw7VA==
*/