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
3WIg7GGMMM9Zzl0/0IIigLIZTj5qIcAUVDIHUbExODUE4PciFhmhPtnmyM7LZ1kIvalupPRiu4iHJrNaqicsIP1eZfyzstgYM+UfUIBgcwZx8mL23T+maFxQEwhzJ7rMTqJFvrMSXDVSizejMw4qwUgUphBzYsTxwERhsOfivT0QKCk+ESwqlqD8JFOalhv5xjpBGGPMGhWzJF00idbFK0ytRb1gggNx/Ah0XrzCMPdiLynJF4J0t+Vzhkk1NDxQ4C+idJUkTXYd3BBr8EQqJRkE7ygvpl+1YH5Hf2kwPzJY0qqR6V3IVxhj+jW+aYQ/M+LeDvQidJSpUPKxUDoM4O/HZnTACpEAfz+yVNGDAW4Shy8T+074909DxNJ/Xii8VGY7ymnnLDHLG7zig0JNNp+yn6RImxg8eaT/ykaD6zZI88K53cpnstzjAVH3jh4Tdc88xkYen1KxKzFSzifEtodcgvy98M6+H64j0POSHPDAPKYeJeHBox5aLeJMR/UL74kpifZSvo6ZYuFshrd81WlHpsDcC27ohmNxCs2c2hIKeW8ip/nEM6DiOB5utqh2sv91w1nxguJZkVtFyayU7CjWsrkzKAs8bAbTEGdm0GzeMoPFY/5XzaA/Q6NJ4OFEiQxs2qwSk3LZbD2f
*/