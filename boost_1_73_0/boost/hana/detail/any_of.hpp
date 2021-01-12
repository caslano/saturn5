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
fTf7Lkgi3GVC+9n50bFifS7nP0+shEysbk6sHk6sXplYo1ebidUBfiLd6CqWn1Q2BbF6intsICQnqA8Dq45BWEWAFR8aBNpnGhdn48LCHsxcN0Oc54ytWt0h8zZzTa6fdxawQo0HSGc6+rGhoF0HqjRJu+uRKs5N7a6T5LFsryaEq9zHsr26t55wC2OS24Yl9VdWDk/qI6RRLdKohSekN+qcqvcjNWapTJfu+tkhmaQlYWHX
*/