/*!
@file
Forward declares `boost::hana::front`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FRONT_HPP
#define BOOST_HANA_FWD_FRONT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns the first element of a non-empty iterable.
    //! @ingroup group-Iterable
    //!
    //! Given a non-empty Iterable `xs` with a linearization of `[x1, ..., xN]`,
    //! `front(xs)` is equal to `x1`. If `xs` is empty, it is an error to
    //! use this function. Equivalently, `front(xs)` must be equivalent to
    //! `at_c<0>(xs)`, and that regardless of the value category of `xs`
    //! (`front` must respect the reference semantics of `at`).
    //!
    //!
    //! Example
    //! -------
    //! @include example/front.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto front = [](auto&& xs) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename It, typename = void>
    struct front_impl : front_impl<It, when<true>> { };

    struct front_t {
        template <typename Xs>
        constexpr decltype(auto) operator()(Xs&& xs) const;
    };

    constexpr front_t front{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FRONT_HPP

/* front.hpp
uCR+vmdzpfK4IDHjdGMYsRlnpfnR74zbAvJvOI0nGyNt8RNOn+GoGOl/YSQ550MMtIe5KlehDlFhz5vfgplRrR1lPn8hH6ZxlBkrjjKjo1lXIolb+UReHJPFq1yVQs6BGT9ifpACu5PL9XChT+iFZgxYaPuFCeyUP1i0QgcQXU+eH6yuYY6R8XPVOqrPkP+uqA5HSO6AWy4YqC7FFyZ0gJfr8iE4X6yPqporBXMGFVS1kr7l1zOHuRY0bnTVVVpPkc6IgN5HdVDu2DVW1OtgcNi6qen+8a4SIIk3P9lNtTwaV8vbL4jrsTrlp2au5fyFO1OhkNbg/zt7VwMfxVHF77glXM3JLc2pp0SbtqdGiRo8aMGkNqEhpIhwCFyiTQMqpWdEjfbSphopeKCsQxQVtWr91p/+tGpVVFTUhFQC4RtaCqGlaGtdSFu+CgmY9vy/N7t7H7nLbVLQ30+zbdi93dmZ92bevP/Me29n/FgO3Vif9rPjZvH6QxfYUbY4Z31m4MddU8uTlBtWs5fpXgdPU1qv4WnKQpwwsVWE3DySTvEmmmDX8CKUGNV10jehvU+xoED4DbeNnNBUsxMGvguaN3iw7hZFL7IHw0er2iU8GPfQdKZTDp559UPRolqXtGlEDf8M8vMHr3apT+BvCmi7EX9z8RfC33Hc8+K8DWe657jCeQUOchuMVa64bEfeuMz33fSPc+flPeR6ZUagBFtYk5YtW5lYtiy7vi9ife9h1+xetGqqwl+ZQ+HzeKl94Ia1FGjog9yoAZYbN078Iro4+X4GroW/B/ccTj4czst3OFIv0n/Js2PnyI708ZzssbzS22F4jQfrr8ijND77xo1Zx2fzXzLk+Ixe7xwcjxO9gYZO6EBT+2RDh+NNRTQQgtKZH1WxexU3pUq2dOQM5bgh+Tcoz67vjRha8vSRuiMLM8Ul9UlxqMWwOh7lBSujZMJBOb158Zc9ivzZ+A2btU8m5VEEkHkjJbmCLx9EKqnYyuTMYEkXwFpqvcZ8GEp/hfF65Bvmk8YxkU/Jta6+zuP4YhnRACVgAzoyHnJLltNtYeeyZDwhPTPpDFfsFFRqqVGpqFO79WmTGPIisaqEKu+rlIV8lLevDkcnYPtHlCI9OhOQJYrRNxg3oidXIm73RFu187Pjq9lEdcoOaHE8ARcoowlqEVZiKHqftEfpb+QOuxkno9mkLXV+1Itd+gw1f4hWioG1dEPSTyM1p7tPKg4zXbts5sHp7k9N91ByukVh/cMKi1wRYCKAjcTEm2gNPVpGS9VWFGG3GjKBu8v6aUE1ulRwCaExLpvHR7gj6DEZr2GUe2s0QJODgHr+0KvaA1cq7/P+tj3EwngvEwM/NZWODd+OSWrOI7UafVnEUYHJDHQi7lqpuIT0m2H9ty62zzHqdYBwEEy7yb+St1xWaPv5cZEfQ557yyL302kKpcorz4OrTIk8QHdeg03po/RrI/1S8Yp39Q40E+5swh1pjP0eDMptrVSMZx5T2XxlYvviZd/dzK8m32nv4q2MiQyB90Jw7E8zP3cJRwLOtA7oRAec/Ep0wA2yyOJQ5F5c1Ubuo744Vn96LJ69znwLjo0oeqaDP4epCB5JqiEsgEbNpV9Ar03Und968zZ+U0YO+Mw3adhAumYF2aQ0vET3GlTroV8GQSRLFPTPA4b+OSUbj/bwqohUpHN2JTirRXGRB6l4p34NcTIjjZPrmJ5SClmgiIX1P3u9Sz2CP1cxxhnoHjX4W4S/3+BvUjH+cH4S51/jjLUYX4LDpbxkbN5LLucBO1WGuw76Z8zO0SN1PESn4Y6HbuDxUKmoJvP2GwxRY6j7jiFqmyFqqSEFK+nkyT07hv8=
*/