/*!
@file
Forward declares `boost::hana::index_if`.

@copyright Louis Dionne 2013-2017
@copyright Jason Rice 2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_INDEX_IF_HPP
#define BOOST_HANA_FWD_INDEX_IF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Finds the value associated to the first key satisfying a predicate.
    //! @ingroup group-Iterable
    //!
    //! Given an `Iterable` structure `xs` and a predicate `pred`,
    //! `index_if(xs, pred)` returns a `hana::optional` containing an `IntegralConstant`
    //! of the index of the first element that satisfies the predicate or nothing
    //! if no element satisfies the predicate.
    //!
    //!
    //! @param xs
    //! The structure to be searched.
    //!
    //! @param predicate
    //! A function called as `predicate(x)`, where `x` is an element of the
    //! `Iterable` structure and returning whether `x` is the element being
    //! searched for. In the current version of the library, the predicate
    //! has to return an `IntegralConstant` holding a value that can be
    //! converted to `bool`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/index_if.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto index_if = [](auto&& xs, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct index_if_impl : index_if_impl<S, when<true>> { };

    struct index_if_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr index_if_t index_if{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_INDEX_IF_HPP


/* index_if.hpp
Tw9JuSl4RdxlVOoyuzkAocgMj3wYja/KdjrOCal5VOo4uzkZB0Vxl/GxHO9KyPFBlmJBdV7MyyP3GVKckGCqFUuKXRxhIiXYrNAKQWpqh5Q+ltAqK1cQcxa5cfzP7ozyKQ5TKg6KOMrbFe1ihoNnjOA0rkVEQoBvjqgtYXb9CXZLmF2/ZBcZ8A4epJNKiGU0N6sTMJ1VKnF7OWqCcswojEwcno9Df0eGUh5JPqXwpMskdsPlCrSUcHcOaWxysW7AVWm6KMpKLEWeXMsp8og0pZZMct5TmNcdGh649gVfYHmMmvLI2zwxOwepOZJ6N0QU4ocnHFPkT+a7XhxlRVjMkrgLudWAUBZGFkTWsSyMJLaWJKIBhxLGkC1hXJhBGMEvOM8hjMuzCKPVY1gmh5ZHKXwpIsmyZrHtZ7ZLqGuNQCIjOSVy6ZASKcnLJpSRSyCUy+0KZatRlyySe7iBStOFsi5VKJEIIpXMbRPX6MEgqUtLLrMJ5RxxFAoSOZA4JinJbHK5cCgNKY4bqcptCKUUnxS5ZBW5x5aSbMkul+gTNoQSUmFLIqMjkMj6nBK5JIeOjGQTx+glEMcWe+Io+4UNNVmeXU2yJJq9MJOa5G2gdySzHkqWyJywjcq2hdkLbUgk+t9IMXvOUOLYZIkj1yFuZtKRK+3qyCUjkMjlOSWyLodElmeTyCY7EikH7VWoIwhcukRK3u0JJeTDhkRG7QH3HHvAvSQ7cFviiPayJHJ5ikSSLAbPUfJUiVxqSyLrRgbcsu8OJZQttnRkfQaJpCpkni2JXJgikSSLzHDJUBLZmlMiIzkksimbRLbYkcgcOrLVrjjWp4ijIemcuJSl3U/1kwuy64YD2UuHCdkhW5AdtSGOUqoySiQIJIGU0ihn5mhV3ElI5MocErnclkRGbOnI8hHoyCU5JXJODomsyyaRc160RKLqh6EjF9rQkU32dGTrkDqSknGNLTdE8qhN1I7YQu0WG0IJ0R0patcPJY5LM4gjiyJVpCWOS2yIoxT9EUhkeU6JDOWY2awcYmZTb0coLYEkccSUZDdLqaUmF9qVyIgNiZxjTyKX20Pt6DDV5BJbEtlkSyLLR4ba0CBDTbdX25tuo8/aEEoIeHaJJHnk1apCyRIJhts8b00VNVXWNlqNbiFricCZhHJwSsglSSUyteyS5XaEcghNWU4taVcol2YQSjPfCo1+vmBUO9UxGXlJJiWEU1WC/ZSeZhfBW4cpmi22ELzelmjOSRVNutnF4rmlY5vbtQ3OtDmcsoOqjBX1VteOjm3jXBfwKJRNWS5k63FFFoXZYSH8VjLXQi5PI0eWuKPkXtiBrBdactnE3JZIbk9zp0C7Ukq3Rm/3inPBM0ad7R5ntQZ/6GsIpBQlakyPIRNRyiNNIFNTSumRzincA3rQ53vU8MEaBc/wrZcCHxjeLQ7uCxYTj/LTM+NjMw9ntEfjF1TKTKuBX4x2/g3R2CgkpMcruA/usSBNfXFPC1EJC9EdZNug3fGrhnRfOXslcCndZi5k43/DffwlrCZvedfsfTIe52U5rC+2pq6hL7a2OUa/2Bo9Ro/RY/QYPf6/Do7vaoxSMNoz24xgNBmFpsjwM7eMO/PIgDNVRpr5ZIiZX8aWFcqgslz5tyF/+tZ95GUI51R6T8sTlcpUelWrVkSleyq9rlW7RaVnKmWhVXtEpTqVstGqVVHpm0pZadU+UemfStlp1X5RWTiVstSqCxuGg/0y/owjuDrN38LROSg+7MC2zszxYghBE90UBaWKTu/9HW6qIE+H7hada+c6RTduqWtf3qGr+N2geO/f4u/oda9tGLt27pi1YVdDh+4fOl4pHg0o+isqKSJL0VA=
*/