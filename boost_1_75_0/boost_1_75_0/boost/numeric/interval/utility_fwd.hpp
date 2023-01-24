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
JiSXqGlXgvreZDnZ6RmMkyb9DIYu6ZYc+R/6JZNS8YDLl2UVC6/FdG0tc+9zti64myRXSk/1xiMYm5K6YLzMRoKKm3KVmgd32PBUDZqrtjpb52/HV3k2nD/+jNuZmA1ppFWchT5Et6ZaTfyMNACCNrUhtulQ6YalJlOFunbuyWjsmZDj8zJI7wWT9fhSJKyRVnUIabxUhu3bpWZT3NHTeB3g7nR+vgRbQUUA8xfqrRyjpBBw529wp2RRtglNnR3VBdkgCVboL/HMEQYqF+uo4NFica/7n8WJajzu3S7uJHr2uqtqaTbxkeHGiasoRkueocuyYpBl00GWYbKgV6brsizDy1p9wLR97Hss1OX4iRIGYd45Cla9jc5OVoIOuYdhXp5voCGrTJb+Zp5FcYA72CJtotPSlhpkgoN0Jli9gfgiFjF6hxySpxafinJCW+jMnPDicwUnBEEauTyWE/5u1jnhtie5VPX6ML5/ry5Qr3eXX4kn1fLwn1zK+42i1Aui1M+2CDG6egkXoz/4Mn8EsUd5MyLd9Ss/+4+/7IdgNxKrTRJlagD55dU+HZ6XOCB4zG/5Betwr8CtsM/Ubb0p05E3VAv2fEVMMioMHKrFXZ2w36qXbfDaXOhEH7qCNi/VJ3uLLULg3m/pu5gv0yboT4GefuI7qMW+cAJh8FhhiqjakcyKaAmWnUA+PiIdR39qg/SRlfabt3hRD7Zv
*/