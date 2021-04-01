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
8O6NAv1tYBGwjVS50BVogfac30rmQW6NpxpeNdaTj432W24D0nl5Irf4Vw2ZMzPUWx/gk9fU+eDc2xydhcUIWcsE2AsqzWACT3ceCtjuhu/PhlvLC5dGIWCOwx4O27L56u57SJO1VbOJJXgPYqx1sBJCP7o7rrH9FccO1XscUsDazgYBMl6Anr9RPRr9InfDRKweKjolUPsx1VTfxzwjeVWDOskzUcJAIPMFVXMVkuMhf0DBoe0ZMPLLhbYiNuzRf7ClFWdY29xebLfeicwHk6cKBV5hZSfjrXBsLySbbbzVogW55FU2tRvhNvY76DLrZbCE2b4C6MWOymPbJitujUZgn0a1OI4n2NPG6M1dENIlzUhrDv3yFMfVzOpLPxVF7mxm9HqsiUFkWHL+Nmwaxb9kLi0Lwi4x5pCfEH3WsmMUQEA/yi6P4/2ufw+yTTzVoWhQ/0YO+qO7EysAM+lGi4AUeLuF5+lZ16Q2ehNlFKvIBeNHoOPw9+T8BW1VqRRcMCJRXJtLooDcHBTreYCxOcKZaKhbZiGh7oFOtugzh5NXiJqvXcksPcb1Ww==
*/