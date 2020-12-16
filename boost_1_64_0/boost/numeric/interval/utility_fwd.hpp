/* Boost interval/utility.hpp template interface file
 *
 * Copyright 2013 Cromwell D. Enage
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_UTILITY_FWD_HPP
#define BOOST_NUMERIC_INTERVAL_UTILITY_FWD_HPP

#include <boost/config.hpp>
#include <boost/numeric/interval/detail/interval_prototype.hpp>
#include <utility>

/*
 * Interface of simple functions
 */

namespace boost { namespace numeric {

    /*
     * Utility Functions
     */

    template<class T, class Policies>
    const T& lower(const interval<T,Policies>& x);

    template<class T, class Policies>
    const T& upper(const interval<T,Policies>& x);

    template<class T, class Policies>
    T checked_lower(const interval<T,Policies>& x);

    template<class T, class Policies>
    T width(const interval<T,Policies>& x);

    template<class T, class Policies>
    T median(const interval<T,Policies>& x);

    template<class T, class Policies>
    interval<T,Policies> widen(const interval<T,Policies>& x, const T& v);

    /*
     * Set-like operations
     */

    template <class T, class Policies>
    bool empty(const interval<T,Policies>& x);

    template <class T, class Policies>
    bool zero_in(const interval<T,Policies>& x);

    template <class T, class Policies>
    bool in_zero(const interval<T,Policies>& x);  // DEPRECATED

    template <class T, class Policies>
    bool in(const T& x, const interval<T,Policies>& y);

    template <class T, class Policies>
    bool
        subset(
            const interval<T,Policies>& x
          , const interval<T,Policies>& y
        );

    template <class T, class Policies1, class Policies2>
    bool
        proper_subset(
            const interval<T,Policies1>& x
          , const interval<T,Policies2>& y
        );

    template <class T, class Policies1, class Policies2>
    bool
        overlap(
            const interval<T,Policies1>& x
          , const interval<T,Policies2>& y
        );

    template <class T, class Policies>
    bool singleton(const interval<T, Policies>& x);

    template <class T, class Policies1, class Policies2>
    bool
        equal(
            const interval<T,Policies1>& x
          , const interval<T,Policies2>& y
        );

    template <class T, class Policies>
    interval<T, Policies>
        intersect(
            const interval<T,Policies>& x
          , const interval<T,Policies>& y
        );

    template <class T, class Policies>
    interval<T, Policies>
        hull(const interval<T,Policies>& x, const interval<T,Policies>& y);

    template <class T, class Policies>
    interval<T, Policies>
        hull(const interval<T,Policies>& x, const T& y);

    template <class T, class Policies>
    interval<T, Policies>
        hull(const T& x, const interval<T,Policies>& y);

    template <class T>
    interval<T> hull(const T& x, const T& y);

    template <class T, class Policies>
    std::pair<interval<T,Policies>,interval<T,Policies> >
        bisect(const interval<T,Policies>& x);

    /*
     * Elementary functions
     */

    template <class T, class Policies>
    T norm(const interval<T,Policies>& x);

    template <class T, class Policies>
    interval<T,Policies> abs(const interval<T,Policies>& x);

    template <class T, class Policies>
    interval<T,Policies>
        max BOOST_PREVENT_MACRO_SUBSTITUTION (
            const interval<T,Policies>& x
          , const interval<T,Policies>& y
        );

    template <class T, class Policies>
    interval<T,Policies>
        max BOOST_PREVENT_MACRO_SUBSTITUTION (
            const interval<T,Policies>& x
          , const T& y
        );

    template <class T, class Policies>
    interval<T,Policies>
        max BOOST_PREVENT_MACRO_SUBSTITUTION (
            const T& x
          , const interval<T,Policies>& y
        );

    template <class T, class Policies>
    interval<T,Policies>
        min BOOST_PREVENT_MACRO_SUBSTITUTION (
            const interval<T,Policies>& x
          , const interval<T,Policies>& y
        );

    template <class T, class Policies>
    interval<T,Policies>
        min BOOST_PREVENT_MACRO_SUBSTITUTION (
            const interval<T,Policies>& x
          , const T& y
        );

    template <class T, class Policies>
    interval<T,Policies>
        min BOOST_PREVENT_MACRO_SUBSTITUTION (
            const T& x
          , const interval<T,Policies>& y
        );
}} // namespace boost::numeric

#endif  // include guard


/* utility_fwd.hpp
000oH8j1DpNx0DRtcZpnTMUerln8nXMNk2OYEdj5Fc8oMBm/S7OnP+d6VyyyaPJY1laYsbCylT5t5lzDnITd7JjXkWcbxXYaNV7AcwHMUVhWiQH/YS1QbPOQ4yWZn5u1fzM67H4k161iRQ0HLWYdhMnfPDVv0yHuOYqtv2PEdTQDZies4sRtPLtthLkI6/rTxJzncpinsJXNT31gjYQ5C/sxPSqdNWsLvl0Iu327xk2uMZibsAm/y7DOt1csM6Uo19FYmIOwXTPf/WL8YHJ8OfvdP3OtKO0yctfN4t6ovK/F2K6jGT9YMWELlxS9xbNbkvb45pVf0p3faRVr1u1gCGMEk7H9dnnaDuYnTPazc45d4Xc3mImw6wEJRTg+mJmwpRm7dzF+MEth9dKGXWHuwiyE+VTsepKxVSw5Pnsk9/6t2mvzk31yLdYCmLEwz1wbxt0bJvMsfWeRM5wzmKmwodv0lnI/gskYjVzrxjwbCXOW+TKiUSxzQumnb5hhUd4RYBphDU9bOfMeAJMxOldx5CXWT+U3A3y6FfC8BJM52Hr7tAP8NrNN2+b/Sp7P9Q6TY6i/MLg91ztMxuF1ylfmWQ+Yq7DUkLfZXO8wOddHLU4HMZeU3xzTadd5niOV32zabesLjh1mL+z42YY23IuV9z14WoR11zVZuy5FnBpMq6bY8vURfRl3mIMwkwG1O/OsAbMVFl4nugzHDvOWtdwgoTfXCkyOofsL956sBTA5L/eLNWENyUtW9n5N8iPWCaWf+waYcY+zTNFef3l9ag3ieoDJsd/6WIl1KVhpt7+7+zTOC0zm0uEyNdw4LzDZlwFF5g9gfYHJOUupdI21fKNi0z+0TmROKH250ahIPudMaRe5Nplr5QXMXtZ53VfMXb3t2utowzh3c+aLYh09307g3qFYUlCHIzwzwJyFTcyb0JZ1Fybn7GPx/ReYLzA5hh+XHxzm3/uVdo2SDCtyXpR2c7/E6vJ7OUwjzM7GfS1zCeYmrMyniSX4N41U7dpTPn3pCN5vYa7CqjU338Cxw+RcB1z6+ZT3I5jMiWZBBpd5/oTJMfiUClrB+yZMjn1UiSjeDfcpffH5eoz7yj1lDPN/FbxgnYC5CHN+s+Yd456mbabR/lE8KypWbt6Qcjx7wxxknnXdyto6Elbqr43/879pEcszWIqwcXiWTlicxVoH8/9rY/F0r/OUa8V2R6GNwdOlbAq/3YfAjP/aaDxbJa1+xnUL8xemsfZzZw4KG4Vn92unqjLPYD5/bSSe0fVWnuUag/kL+/xt7xzOZ3rh+P5NokfrCuy4r8D6/f3eMxzPmUYtHzF30/lN54/ZVrtznvm5E3cEYXnBm8rwfTBDYS5TvBkHb5i+sNCgHYN5R1DstM7dAq53xaKC321kTsAshd3Nr1aT41MsrcXh4dw3YdbCHr3dzN8cC9MI816+aivrp2KVkgb05VqBWQjbOGrwN541dhbGYRiez5pGv2QtgBn9/c/2xurwH38sn+3+Z7avY2M5n7sK4z4UzyULDrHuthc2BM+R11+ncwy7Cn/z3wAMzVnBfh4V7QbhOevXcubEVxgm9E++DMC/flvL35Lnl9OF3yOj8a+HRBZ4s/ac0dOJ0/2f9cK/LhpnHkM7Xxjbnni+fqbx4D6mWES/w7+4phWbuzXAgN8ZFFu4+tcdrjHF8h9X5fsSFHMKm/qR50jF1iSn5XN/gJUSNrWRUyeuI2E98Kzq5cq5NsoutO54hpabFc28FtYFzwXPItpzXmCLiv5vPjvjXz+ZsT6DdeIy7wh/rGY9v0X8JgAzFTavzE/eN3NgFsIce3zk+F7BNMLK6QZsZy1X3rf6rPj/M72ip2M=
*/