/*!
@file
Forward declares `boost::hana::insert_range`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_INSERT_RANGE_HPP
#define BOOST_HANA_FWD_INSERT_RANGE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Insert several values at a given index in a sequence.
    //! @ingroup group-Sequence
    //!
    //! Given a sequence, an index and any `Foldable` containing elements to
    //! insert, `insert_range` inserts the elements in the `Foldable` at the
    //! given index of the sequence.
    //!
    //! @param xs
    //! The sequence in which values should be inserted.
    //!
    //! @param n
    //! The index at which elements should be inserted. This must be a
    //! non-negative `Constant` of an integral type, and it must also be
    //! true that `n < length(xs)` if `xs` is a finite sequence.
    //!
    //! @param elements
    //! A `Foldable` containing elements to insert in the sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/insert_range.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto insert_range = [](auto&& xs, auto&& n, auto&& elements) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct insert_range_impl : insert_range_impl<S, when<true>> { };

    struct insert_range_t {
        template <typename Xs, typename N, typename Elements>
        constexpr auto operator()(Xs&& xs, N&& n, Elements&& elements) const;
    };

    constexpr insert_range_t insert_range{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_INSERT_RANGE_HPP

/* insert_range.hpp
EKDI0NJ4mgkBPLnbTU1tN8lLQpX0geMM/PgT7ZapoxRm02xWMwREdaGh3vzJLZBGsDpUA/iyN4A/XS48KaqmME3VFFNKIgx50NP+wSQxS+ImH6haJqvxJr9JlKnqiar3pfU6VEZKK6oZWrHElMnbfZla0Z+7FROVUkgVzmwxiM0olXn78WQwjhem4bh/EI5PMUm7rZBwfFo6jpf/t3F89Lg8R7Bdtmqu+YaK0ZM1TwuH+66mWYQ202FOId7LUw1tpjHPwA23TOG2UnhkiuQZRkfSTOx+mmFMxAzjappgdGlVb0idW/xzRHMLY/x3G89HDS7CwhU833eslsjvhhmi71rXNnGxoM/VAfrxm8g/5uojEwW+CKN+0Dcxji5zsezixPPB7X3X9h116aKnYAeHrKptK5zTpesUPfgF11+pCIwitUq3q5cjNc7BUNl3dXC765RWhV2Zu8t6KQm6KXXJw2XsBp/Y3neIy6I+qtXjcRMen4K1E1WLV7k8sZBLc+0r25dcWiGX5nEdYD8vahzUgIEOKo2qb6anbIcsjTInFjDg7TsqP4R17S3YhTyZDpkn+nulGnvYQWS5HhP4Uo2JBRNoVOKioHs66E8inmuHndfMAJFBU4ObPaKj72/J8wLk9F+eGUj7xMn3S3nw8Sz6sslDYSZ5KLIjD0UjkAdZmpQFysKQh5vd1ApcsO5azhKB8qcjy2SZ4FwhE/2ukwXdbdWmPAA1trqeTyIDlFqkqMxEv+ihCAnQgQo4XnbcpIQsbZXEONPSS1z7LK59EAhmHG0AiUCxF8ouMM9HqbCL9A6KKbsoC2LqhE50PVbQTWlN2nqRnBpC0mTK6JDNETWaw+c6S7mwmFoV9CxKoxY+m1o57r6jIGCoyjEJ8CXR+jxoRVJKdhLJuCIooaxKTu6nKgGJRDE1J6ge1Jr+RGsS8XBl0Esg9hx6Yn1myUmjyi+p6gdVxEMOBtwWA6lJT2aQR6pf6Haq8+wcFCbLo5pBHn2D5dGTUx4t5oZHcSHXBcgWPS49QbFJresA0S4rm8felBe/5U4RXqI4RXytyj+aJpOgz2NTfFH56lDiSyS5/qpVBox+BRG+2Zcqvv4M4qsOEl+uRxoWDq6gmRgFeqhjm+0JMhB+BkISzYpK4IYtRmrZrgQqXGO25JKLS1SPb6g+QFRyYSUmwvmhjqE5qSmQX6rogCBwfBtyNBDOl4pwhQbClUqEKzIQjobz3Mh+C+F8ScRbCFdoIpyPBs03F1LdJ4+YkZM1Zr5UNuLR4/Id7H5YE1/xIXLaskOir4vHuJWGPyUvdlLpO6Y5tfmKqKarSrc23yOq3XSpavNhD/LEtqr0y6/NL4x1FMkMmv+6Jh59+XqR13Yn3mq72a1V9mvzB2Innc29DYttCwWPUoLtGI6PuaUT0uyRy2iAbNP67139NYrJGy/eyHGEuybh30nbNK/Auex4VKF+B2+iaFRSns9TUhO4RaM7NYE7NYFHNHpSE3iSE9BwfouKmoh1qQZha27HvxjUByedmXTRe9VKB9HpeXkaoZ5XpGSzRaHB/qFhL9SR5WB3e+ztjmh1bIXiiFbEVvjizVcg2oCI6Z1ALpewPnue6VudRjdoZZf4nZ74daGQvvJ17KnrOzSxPXbM2dAZ0fBepJ1ceR+EM8+lV841XHn2wgqkz+sv5HEjqpYwVe9Jp4p9yxvnmlS9ixx3OF8ZvxPO8z+/m+8TSdf2U1J6atK797VMDj/sWpyB3i+8kxMstkkwW8094dq/FJFj+pnmK8kduWiRvuID7CaGz3qMOLfmvHf1lU7mqNmr7wgOxLW8Ne3e1S/gHWKwWdV/SzerFbqry90c/JAMX/xOt/4=
*/