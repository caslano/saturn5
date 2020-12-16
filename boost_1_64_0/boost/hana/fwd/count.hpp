/*!
@file
Forward declares `boost::hana::count`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_COUNT_HPP
#define BOOST_HANA_FWD_COUNT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Return the number of elements in the structure that compare equal to
    //! a given value.
    //! @ingroup group-Foldable
    //!
    //! Given a Foldable structure `xs` and a value `value`, `count` returns
    //! an unsigned integral, or a Constant thereof, representing the number
    //! of elements of `xs` that compare equal to `value`. For this method to
    //! be well-defined, all the elements of the structure must be Comparable
    //! with the given value.
    //!
    //!
    //! @param xs
    //! The structure whose elements are counted.
    //!
    //! @param value
    //! A value compared with each element in the structure. Elements
    //! that compare equal to this value are counted, others are not.
    //!
    //!
    //! Example
    //! -------
    //! @include example/count.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto count = [](auto&& xs, auto&& value) {
        return tag-dispatched;
    };
#else
    template <typename T, typename = void>
    struct count_impl : count_impl<T, when<true>> { };

    struct count_t {
        template <typename Xs, typename Value>
        constexpr auto operator()(Xs&& xs, Value&& value) const;
    };

    constexpr count_t count{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_COUNT_HPP

/* count.hpp
QWASpwhwigqkEJqE4V9GmVg7SBB8CR2W48NNC29UR03MUw0+FMcNiMwvzA5cTpz5+mR6nV04NDBDxmvEUzgqMHW9heSXPsgvUe9ZHs5ClbdTtcq+JLXycmXCIT7mFld8pF/hKYG71idRqamFpzCVsY9rrx9rHIuuqf0b2WhFIfp+mXovGbIepzyKunZ14Sn2mgd43jfSespzPhWOeGmV/ourzaNcTtVy44q/iOoL1BzR3mt/pR/nphOKcTQ0YFDmXp9ARAMWpQwh8vhORPSDRzoR0XIlRxgUsAiH62kWaSCNugpG86626ny6h651VpSaZQkUcJMGiyYVnuK/vKvWfECtuc2itqZcMfEBQwfJmwp2+08iGTjjJPCx8U4NH1ct+Ep46gcWZ1n07edt9+mYHAdP5I55q+++z+h4Gd/8+42OUnxr8D3z/v8OXxXf5NOQYSH5593x9IH6Ra5h8sDSK4eqCZQV0m6SLs0bohk8yajZbrqi9eMN4zFI7efswWGrPsacVkiU+ir7MO4h9i9BUyoT8yymo2T+t/8dOjtlv/5Tg5iHThLLQB06W9ySWWgM2Dua61Asldn6CM1rk72GzhnWgK+7jY9IQuWYiX2as37c2dHCVAhQ2BjHUpgWSJpc27ZMqa509jH4Swg4A5a63oL9vna1xpf9QrFfTvuSuxo69Jvd5hNnzkcbvMrZtwst/Qm8C4vTVJ6BbICfiCg5+9MsHfuL4HpA3KnJp94ea/KqNMwArzLsNqa5LOR0xrD04D2EpTRAzQLcV1Zp4L7YwO3bvu1f/Wk9NZB4niz6UOL7q/cnvm9+IPHdvirx/Yf3Jb4f8Ce+j+5U3pJO5a2/PvE9tVN5d3Yq7x+d4rM7lTe/U3nP3pv4/lmn/DcnxpNIwloLYsl3Xm2P7abKPDlbw1dFzR8XHFw4RB5IlE6cLwK9O4np3SuC3mXALnhywcFFf+V7s0Cfojg28CkCYTjQcswbrvh+1RXADbGGW1ovjx5xXyLJTUgBH3ZHZbuZDi3k88W/DI+JZo9wAEsIbTvYTLp/WH2eXEmzKfn8CyDBf2N6yM6mEuLn6EAJfsbbib4PjqfvaRp951uQKuhcGoz+XY35xgqY5Bxrey7lPWF0SEX0Zxqkz8rAJ+JvdtT49fm36/KiDF8ubfZuOMkhBkFVeAfYn5b8USQP4ISvNAIgq8a2xo+O3b5mvHG89hr42NXIsxoKj2fibBP8L5B8r5bX5RQ9bx/7YLxPME6IZYcr++hkPUG/eashlqtLCAzsD88y5rzrq5CcaF94rNGtvH+nvtO013gxvmWwEAhFHGzMD5vrlk3j8owGRV4hjqNJFs3X1PfAgncuUNgzRGGb6eGVf+pPQFVZXtO/Mna23UFOc3xZ3CTpYeI8HhUykp/8Mt5pTlm5Fzur0AyUc809umTvTJLsnSEmEEnaM7B4+XLlJVZ5msWLxNlieKkuqgcmv/K7kZEYVnSkxnIRv/mpxja9pvpfBf4jACwXBYnxISYf4JN6ffjTcQMs/DnRIF/LpdinaKXYeYSphPgR1uvA+FZpQUcbX8sdWk3EZ11c5nXDv7KDpO1O+UUCJmf7pnFnY4QfqBUjPM1CMigZMWO5t7Ce65K/PWAdca6Gx5871Xea6PaH4rr9w1VqtyPlrH+rxrj1xrsS6evI3ye8S3ufwVQ/QH/upPl+xiOd5nsW2//dLOY7OWvQnB66omSjG8XH1UbydH7arylglTE/Ug3aCINq99AZikAG5VfWIIbCkZsG/k62KJ70W1V+SdhMeBCiKvZ7sIfKUnb8XkdWNngZSOfrhb1uuUeR1OlrXfs4WiAHLN2/HbhC3MUZDVijr4TQLmE=
*/