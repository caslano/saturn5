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
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
*/