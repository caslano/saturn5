/*!
@file
Forward declares `boost::hana::div`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_DIV_HPP
#define BOOST_HANA_FWD_DIV_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Generalized integer division.
    //! @ingroup group-EuclideanRing
    //!
    //!
    //! Cross-type version of the method
    //! --------------------------------
    //! The `div` method is "overloaded" to handle distinct data types
    //! with certain properties. Specifically, `div` is defined for
    //! _distinct_ data types `A` and `B` such that
    //! 1. `A` and `B` share a common data type `C`, as determined by the
    //!    `common` metafunction
    //! 2. `A`, `B` and `C` are all `EuclideanRing`s when taken individually
    //! 3. `to<C> : A -> B` and `to<C> : B -> C` are `Ring`-embeddings, as
    //!    determined by the `is_embedding` metafunction.
    //!
    //! In that case, the `div` method is defined as
    //! @code
    //!     div(x, y) = div(to<C>(x), to<C>(y))
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/div.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto div = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct div_impl : div_impl<T, U, when<true>> { };

    struct div_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    constexpr div_t div{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_DIV_HPP

/* div.hpp
ZWLOJn1UMikDwVYaCChJPio4Ec2lLfjks1uJXWd8Aeyalbgg6Zd9bWmJ871QqxmWxJcd8qELxhIztM4A9HDSw7HTl7T5dSiSr4vcoVE2uaHjnMXlx7h9fs3hc9BUOVqXl6zKOlvFypzMZd/nrnV2ISC+7F+o7ABfaCshtNcAfdeB6dGQX6tXGJg1CPHQeZlrKapB5TM1elu1AkGcKc3C4YXke1gMply6GkPndqf/iatNw5US4NbrgeRJ5SQ+HQ09KFuDW+/DE2XaaFTsX8DSpQ0jaf/7659D8QuyURu6zcXxdP+APKoVb6CPehhzjlpJzwA919FzAz3L6FlOzwp6LqbnPfR00XMBPefT00fP2fScTs/b6XkvPVfQ836REko/kMAHRgH7Edz2mD9dX2fdnpNp3b7EGIpm6augRQbDJMpWWhzdq9LZfLP+oOPcqow5oehYx0erOJmoLaw+kPoP+afbVzHeYPNpqrVXYKJbnHHiozaVj7jS5Hj32sY30B4OXje6B+p1I4a5RMwiYgQ8xrmNzR5ZxYd1NoSatIod+54m7IEBqhMG8NNSDeAryZFnL82QpEeeuTJvqQbtywaHsZzp+qpNU11OjSZ4zXu9tBg8PytoqkSlH3H+0wN/D7t9ZGavaHAsWzDSBu8W+5HO06wR3szw28aqO++H8DpWg7/6w7F58H4vhNwz0oJpDrccPn741OHGXvXB9s4z
*/