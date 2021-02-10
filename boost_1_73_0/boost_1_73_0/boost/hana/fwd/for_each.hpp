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
+D07ISQErpp0QeDE/t73Pn/PNumyhMc0gZvxYDSek+FyPiF3g/l0Mg4CctPp4hjj9Nyw1/9xVwf68O5F7Jfgha2NuM3FvzRSp9GEvEHxwagHbN9L4sEh5I304P2QN3BsCCmzXJl7Qt5L9GC0mR/PRD4Qc4s9GGYih2LzmrPHVIEz7MGnL19+gZ/g8ufLTy6MQs5oBoGifEXzRxeuYtvzexputxeSfnWBKgizi5JqkTIJUiTqJcwp4H3GIsoljSGUEFMZ5WyFD4yDSikkLKMwnN3e+9M/XXhJWZQaklehQaZCZzGk4TOFnEaUPRccmzBXIBIMR/KYSYWEWjHBLzA3BUXztTQcJn2YSQHhc8iycIWJQgWpUhv5q+dFOs9QvReLSHrRfvoXqVpXM7lHEevwFcRGgRKgJXXBIF1Yi5glpkVDsHOjVxmTqXtQg6l47IkcJM0yw4VxjMpCNoWgtMc1MNigYqZMIwWXJtVLKtYNIPpoWBKdc0yEPiAoFmizCxq3U27Bdub7FKWn1uCzpTnojUFwFAMfBgH4wQdYhZJJF+78xc1suQDcgvPBdHEPs2sYTO8N2Td/OsLSM0yWA91ucioxeQ5svckYjcucP+7yOp0uS8zRsQzG5M6fBrPhN+ziUaZjClemoEVV06/g
*/