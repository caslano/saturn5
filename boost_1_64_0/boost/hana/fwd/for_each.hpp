/*!
@file
Forward declares `boost::hana::for_each`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FOR_EACH_HPP
#define BOOST_HANA_FWD_FOR_EACH_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Perform an action on each element of a foldable, discarding
    //! the result each time.
    //! @ingroup group-Foldable
    //!
    //! Iteration is done from left to right, i.e. in the same order as when
    //! using `fold_left`. If the structure is not finite, this method will
    //! not terminate.
    //!
    //!
    //! @param xs
    //! The structure to iterate over.
    //!
    //! @param f
    //! A function called as `f(x)` for each element `x` of the structure.
    //! The result of `f(x)`, whatever it is, is ignored.
    //!
    //!
    //! Example
    //! -------
    //! @include example/for_each.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto for_each = [](auto&& xs, auto&& f) -> void {
        tag-dispatched;
    };
#else
    template <typename T, typename = void>
    struct for_each_impl : for_each_impl<T, when<true>> { };

    struct for_each_t {
        template <typename Xs, typename F>
        constexpr void operator()(Xs&& xs, F&& f) const;
    };

    constexpr for_each_t for_each{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FOR_EACH_HPP

/* for_each.hpp
EBzQsGVzc0QUKmtRoVbJrjRRbL7PGqPp2nerCgktHnWK7FA7BsYPrhWc/HJOc72BWZtt1jnIKsbGsqFtt35xpypvtWOyWgaZeCvocWqVR7Fc/d+TbcKJD6+tLF+5LPYLIz517BThnTHCgcYmJWB5emQY7ADH/ewYLAKUrRUTB1qEb5LsnMQ3yEWiR5bAgbzS805uYDJN/4dMIrIH476JjY3Lo+id1RKXRfDLTywIwH9l6MzMM9+j6ywPiVtH0c2yTv2tu4+44g+BP0dX1SGkdF7PZvb6292t/tc8AoOKQqXsBSxXdxNkFK8+DzBlggfAgS0hsELszu83PFdr34YQ/XwfvwlFHvk9oJ2jI3LyUq1jxB8uVB4+cOlIti/gV8JbcrAnYUWT+fP9tKoiriyaxJRO2RA2Bo2B1ykMA9jDoWh+4BQ/Z2kryu+ZpihAbhSpfgs2ZB03SccEBotTShJDbBr+tz0gGIMQKh1aHGz+NKkNGruC2UGZtGT6wpXaU2DS1wmFpfmTmgBaIRKke/H+VflFbPKM1epEP39IiOsk7NFdVl0wqi7dqqPQdw==
*/